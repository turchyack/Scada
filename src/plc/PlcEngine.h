#ifndef PLCENGINE_H
#define PLCENGINE_H

#include <QObject>
#include <QTimer>

// Вперёд объявляем Lua-структуру, чтобы не включать весь lua.h сюда
extern "C" {
struct lua_State;
}

class TagManager;

/**
 * @brief Класс PlcEngine отвечает за выполнение пользовательской логики,
 * написанной на языке Lua. Он взаимодействует с TagManager и позволяет
 * Lua-скриптам читать и записывать значения тегов.
 */
class PlcEngine : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор
     * @param tagManager — указатель на менеджер тегов
     * @param parent — родительский QObject
     */
    PlcEngine(TagManager* tagManager, QObject* parent = nullptr);

    /**
     * @brief Деструктор. Освобождает Lua-состояние.
     */
    ~PlcEngine();

    /**
     * @brief Загружает Lua-скрипт из файла.
     * Ожидается, что в скрипте определена функция `main()`.
     * @param filename — путь к Lua-файлу
     * @return true, если скрипт загружен успешно
     */
    bool loadScript(const QString& filename);

    /**
     * @brief Запускает выполнение скрипта по таймеру.
     * @param intervalMs — интервал выполнения в миллисекундах
     */
    void start(int intervalMs = 1000);

    /**
     * @brief Останавливает выполнение скрипта.
     */
    void stop();

private slots:
    /**
     * @brief Метод, вызываемый по таймеру для вызова Lua-функции `main()`.
     */
    void executeLogic();

private:
    lua_State* m_lua;          ///< Указатель на Lua-виртуальную машину
    TagManager* m_tagManager;  ///< Указатель на менеджер тегов
    QTimer m_timer;            ///< Таймер для вызова скрипта по интервалу

    /**
     * @brief Регистрирует функции Lua API, доступные из скрипта
     * (например, get_value, set_value).
     */
    void exposeAPI();
};

#endif // PLCENGINE_H
