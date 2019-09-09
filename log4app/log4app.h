/// @file log4app.h
/// @brief Интерфейс библиотеки логгирования
/// @author Алексей Максимов
/// @date 2015-08-14

#pragma once

#include <QtCore/QScopedPointer>
#include <QtCore/QSharedPointer>
#include <QtCore/QTextStream>
#include <QtCore/qglobal.h>

#include <log4qt/level.h>
#include <log4qt/logger.h>

#include "export.h"

namespace log4app {

///
/// \brief Интерфейс библиотеки логгирования
///
class LIBLOG4APP_API Log4app {
public:
    ///
    /// \brief Конструктор по умолчанию
    /// [in] append Не перезаписывать лог-файл. По умолчанию лог-файл
    /// перезаписывается. Если данный параметр опущен, то
    /// используется значение из глобальной конфигурации log4app/append_file
    ///
    Log4app(const bool *append = nullptr);

    ///
    /// \brief Деструктор
    ///
    ~Log4app();

    ///
    /// \brief Включить вывод сообщений в консоль
    /// \param[in] use \a true включает вывод.
    ///
    void useConsole(bool use);

    ///
    /// \brief Получить объект корневого логгера
    /// \return ОБъект корневого логгера. Всегда существует
    ///
    Log4Qt::Logger* logger();

    ///
    /// \brief Получить объект логгера по имени. Если логгера ещё не существует
    /// то он будет создан
    /// \param[in] name Имя логгера
    /// \return Объект логгера
    ///
    Log4Qt::Logger* logger(const QString& name);

    ///
    /// \brief Уставить для сообщений логгера \a name индивидуальный лог-файл
    /// \param[in] name Имя логгера
    /// \param[in] append Не перезаписывать лог-файл
    /// \sa Log4app
    ///
    void setIndividualFileForLogger(const QString& name, const bool *append = nullptr);

    ///
    /// \brief Установить уровень сообщений
    /// \param[in] level Уровень сообщений
    ///
    void setLogLevel(Log4Qt::Level level);

    ///
    /// \brief Получить указатель на экземпляр логгера
    /// \return Указатель на экземпляр
    ///
    static Log4app* instance();
    static Log4app* instance(bool append);
private:
    struct Private;
    QScopedPointer<Private> d_;

    static Log4app* instance_;

    bool appendMode(const bool *append) const;

private:
    Q_DISABLE_COPY(Log4app)
};

LIBLOG4APP_API Log4Qt::Logger* Log();
LIBLOG4APP_API Log4Qt::Logger* Log(bool append);
LIBLOG4APP_API Log4Qt::Logger* Log(const QString& name);
class WidgetAppender;
LIBLOG4APP_API WidgetAppender* CreateWidgetAppender();
template<Log4Qt::Level::Value level>
class LogStream {
public:

    template<typename T>
    LogStream& operator<<(const T &t) {
        out_ << t;
        return *this;
    }
    LogStream& operator<<(const std::string &t) {
        out_ << t.c_str();
        return *this;
    }

    LogStream(const QString &str) : out_(&out_string_, QIODevice::WriteOnly) {
        out_ << str;
    }
    LogStream() : LogStream(QString()) {

    }

    ~LogStream() {
        Log()->log(Log4Qt::Level(level), out_string_);
    }

private:
    QString out_string_;
    QTextStream out_;

private:
    Q_DISABLE_COPY(LogStream)
};

using LogTrace = LogStream<Log4Qt::Level::TRACE_INT>;
using LogDebug = LogStream<Log4Qt::Level::DEBUG_INT>;
using LogInfo = LogStream<Log4Qt::Level::INFO_INT>;
using LogWarn = LogStream<Log4Qt::Level::WARN_INT>;
using LogError = LogStream<Log4Qt::Level::ERROR_INT>;
using LogFatal = LogStream<Log4Qt::Level::FATAL_INT>;

} // namespace log4app



