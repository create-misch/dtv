/// @file log4app.cpp
/// @brief Реализация интерфейса библиотеки
/// @author Алексей Максимов
/// @date 2015-08-14

#include <QtCore/QCoreApplication>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include <log4qt/consoleappender.h>
#include <log4qt/fileappender.h>
#include <log4qt/logger.h>
#include <log4qt/logmanager.h>
#include <log4qt/simplelayout.h>
#include <log4qt/ttcclayout.h>

#include <configmanager.h>

#include "log4app.h"
#include "widgetappender.h"

Q_GLOBAL_STATIC(QMutex, gInstanceMutex)

namespace log4app {

Log4app* Log4app::instance_ = nullptr;

const char* const kDefaultLogFilename = "log4app";
const char* const logfileex = "log";

inline QString getLogFileName()
{
    QString logfilename = QCoreApplication::instance()
        ? QCoreApplication::instance()->applicationName()
        : kDefaultLogFilename;
    logfilename.replace(' ', '_');
    return logfilename;
}

struct Log4app::Private {
    Private()
        : layout(nullptr)
        , consoleAppender(nullptr)
        , fileAppender(nullptr)
    {
    }

    Log4Qt::TTCCLayout* layout;
    Log4Qt::ConsoleAppender* consoleAppender;
    Log4Qt::FileAppender* fileAppender;
    QVector<QPair<Log4Qt::SimpleLayout*, Log4Qt::FileAppender*> > simple;
};

Log4app::Log4app(const bool *append)
    : d_(new Private())
{
    Log4Qt::LogManager::rootLogger();

    d_->layout = new Log4Qt::TTCCLayout();

    d_->layout->setDateFormat(Log4Qt::TTCCLayout::ISO8601);
    d_->layout->setThreadPrinting(true);

    d_->layout->setName("main");
    d_->layout->activateOptions();
#if defined(Q_OS_LINUX) && !defined(_DEBUG)
    const QString logpath = QString("%1/%2.%3").arg("/var/log/smp", getLogFileName(), logfileex);
#else

    const QString logpath = QString("%1/%2.%3").arg(Cm()->logDir(), getLogFileName(), logfileex);
#endif

    d_->fileAppender = new Log4Qt::FileAppender(d_->layout, logpath, appendMode(append));
    d_->fileAppender->activateOptions();
    Log4Qt::LogManager::rootLogger()->addAppender(d_->fileAppender);

    Log4Qt::LogManager::instance()->setHandleQtMessages(true);

#if defined(_DEBUG)
    useConsole(true);
#endif
} // Ctor

Log4app::~Log4app()
{
    Log4Qt::LogManager::instance()->resetConfiguration();

    for (auto& pair : d_->simple) {
        delete pair.first;
        delete pair.second;
    }

    delete d_->layout;
    delete d_->consoleAppender;
    delete d_->fileAppender;
} // Dtor

void Log4app::useConsole(bool use)
{
    if (use) {
        d_->consoleAppender = new Log4Qt::ConsoleAppender(
            d_->layout, Log4Qt::ConsoleAppender::STDOUT_TARGET);
        d_->consoleAppender->setName("ConsoleAppender");
        d_->consoleAppender->activateOptions();
        Log4Qt::LogManager::rootLogger()->addAppender(d_->consoleAppender);
        return;
    }
    if (d_->consoleAppender) {
        Log4Qt::LogManager::rootLogger()->removeAppender(d_->consoleAppender);
        delete d_->consoleAppender;
        d_->consoleAppender = nullptr;
        return;
    }
    Log4Qt::LogManager::instance()->logLogger()->error(
        "Console appender not set");
} // useConsole

Log4Qt::Logger* Log4app::logger()
{
    return Log4Qt::LogManager::rootLogger();
} // logger

Log4Qt::Logger* Log4app::logger(const QString& name)
{
    return Log4Qt::LogManager::logger(name);
} // logger

void Log4app::setIndividualFileForLogger(const QString& name, const bool *append)
{
    using namespace Log4Qt;
    SimpleLayout* l(new Log4Qt::SimpleLayout);


#if defined(Q_OS_LINUX) && !defined(_DEBUG)
    const QString filepath = QString("%1/%2_%3.%4")
                                 .arg("/var/log/smp", getLogFileName(), name, logfileex);

#else

    const QString filepath = QString("%1/%2_%3.%4")
                                 .arg(Cm()->logDir(), getLogFileName(), name, logfileex);
#endif



    FileAppender* a(new FileAppender(l, filepath, appendMode(append)));
    a->activateOptions();
    logger(name)->addAppender(a);
    d_->simple.push_back(qMakePair(l, a));
}

void Log4app::setLogLevel(Log4Qt::Level level)
{
    Log4Qt::LogManager::rootLogger()->setLevel(level);
} // setLogLevel

Log4app* Log4app::instance()
{
  return instance(false);
}

Log4app *Log4app::instance(bool append)
{
  if (!instance_) {
      QMutexLocker lock(gInstanceMutex());
      if (!instance_) {
          instance_ = new Log4app(&append);
          return instance_;
      }
  }
  return instance_;
}  // instancd

bool Log4app::appendMode(const bool *append) const
{
    return append ? *append : false;
} // instance

Log4Qt::Logger* Log() { return Log4app::instance()->logger(); } // Log

Log4Qt::Logger* Log(const QString& name)
{
  return Log4app::instance()->logger(name);
}// Log

WidgetAppender *CreateWidgetAppender()
{

  WidgetAppender *a = new WidgetAppender();
  Log4Qt::TTCCLayout *l = new Log4Qt::TTCCLayout;


  l->setDateFormat(Log4Qt::TTCCLayout::ISO8601);
  l->setName("smp");
  a->setLayout(l);
  Log()->addAppender(a);
  return a;

}

Log4Qt::Logger *Log(bool append)
{
 return Log4app::instance(append)->logger();
}


// CreateWidgetAppender


}  // namespace log4app
