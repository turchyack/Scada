// src/plc/PlcEngine.cpp

#include "PlcEngine.h"
#include "TagManager.h"
#include "Tag.h"
#include <lua.hpp>
#include <QFile>
#include <QTextStream>
#include <QDebug>

PlcEngine::PlcEngine(TagManager* tagManager, QObject* parent)
    : QObject(parent), m_lua(luaL_newstate()), m_tagManager(tagManager)
{
    luaL_openlibs(m_lua);
    connect(&m_timer, &QTimer::timeout, this, &PlcEngine::executeLogic);
    exposeAPI();
}

PlcEngine::~PlcEngine() {
    lua_close(m_lua);
}

void PlcEngine::start(int intervalMs) {
    m_timer.start(intervalMs);
}

void PlcEngine::stop() {
    m_timer.stop();
}

bool PlcEngine::loadScript(const QString& filename) {
    if (luaL_dofile(m_lua, filename.toUtf8().data()) != LUA_OK) {
        qWarning() << "Lua error:" << lua_tostring(m_lua, -1);
        return false;
    }
    return true;
}

void PlcEngine::executeLogic() {
    lua_getglobal(m_lua, "main");
    if (lua_pcall(m_lua, 0, 0, 0) != LUA_OK) {
        qWarning() << "Error running 'main':" << lua_tostring(m_lua, -1);
    }
}

// ===== Связываем с TagManager =====

static TagManager* g_tagManager = nullptr;

int lua_get_value(lua_State* L) {
    int addr = luaL_checkinteger(L, 1);
    Tag* tag = g_tagManager ? g_tagManager->getTagByAddress(addr) : nullptr;
    if (tag)
        lua_pushnumber(L, tag->value());
    else
        lua_pushnil(L);
    return 1;
}

int lua_set_value(lua_State* L) {
    int addr = luaL_checkinteger(L, 1);
    double val = luaL_checknumber(L, 2);
    Tag* tag = g_tagManager ? g_tagManager->getTagByAddress(addr) : nullptr;
    if (tag)
        tag->setValue(val);
    return 0;
}

void PlcEngine::exposeAPI() {
    g_tagManager = m_tagManager;
    lua_register(m_lua, "get_value", lua_get_value);
    lua_register(m_lua, "set_value", lua_set_value);
}
