cmake_minimum_required(VERSION 3.16)
project(scada-lite LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Настройка проекта Qt
find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

# Включаем поддержку MOC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# === Исходники ===
qt_add_executable(scada-lite
    # Точка входа
    src/main.cpp

    # Модель данных
    src/core/Tag.h
    src/core/Tag.cpp
    src/core/TagManager.h
    src/core/TagManager.cpp

    # Симуляция данных
    src/simulation/SensorSimulator.h
    src/simulation/SensorSimulator.cpp
    src/simulation/SimulatorManager.h
    src/simulation/SimulatorManager.cpp
    src/simulation/TemperatureSimulator.h
    src/simulation/TemperatureSimulator.cpp

    # Lua-логика (PlcEngine)
    src/plc/PlcEngine.h
    src/plc/PlcEngine.cpp

    #modbus
    src/modbus/ModbusClient.h
    src/modbus/ModbusClient.cpp


    # Описание устройств
    src/device/Device.h
    src/device/Device.cpp   # Логика одного механизма (например, конвейера)
    src/device/DeviceManager.h
    src/device/DeviceManager.cpp
)

# Ресурсы QML
qt_add_resources(scada-lite "resources"
    FILES
        qml/main.qml
)

# Включаемые директории
target_include_directories(scada-lite
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/core
        ${CMAKE_CURRENT_SOURCE_DIR}/src/simulation
        ${CMAKE_CURRENT_SOURCE_DIR}/src/plc
)

# Подключение библиотек Qt
target_link_libraries(scada-lite
    PRIVATE
        Qt6::Core
        Qt6::Gui
        Qt6::Qml
        Qt6::Quick
)

# Указываем пути к Lua из vcpkg
set(LUA_DIR "D:/vcpkg/installed/x64-windows")
set(LUA_INCLUDE_DIR "${LUA_DIR}/include")
set(LUA_LIBRARIES "${LUA_DIR}/lib/lua.lib")

# Подключаем Lua через стандартный FindLua
find_package(Lua REQUIRED)

if (LUA_FOUND)
    message(STATUS "Lua found")
    message(STATUS "Include dir: ${LUA_INCLUDE_DIR}")
    message(STATUS "Library: ${LUA_LIBRARIES}")

    target_include_directories(scada-lite PRIVATE ${LUA_INCLUDE_DIR})
    target_link_libraries(scada-lite PRIVATE ${LUA_LIBRARIES})
else()
    message(FATAL_ERROR "Lua not found")
endif()

find_library(MODBUS_LIB NAMES modbus PATHS "D:/vcpkg/installed/x64-windows/lib")
include_directories("D:/vcpkg/installed/x64-windows/include")

target_link_libraries(scada-lite PRIVATE ${MODBUS_LIB})

