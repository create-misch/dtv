#pragma once

#include <QtCore/QAbstractItemModel>
#include <QtCore/QDebug>
#include <QtCore/QObject>

#include "log4app.h"
#include <log4qt/appenderskeleton.h>
#include <log4qt/loggingevent.h>

namespace log4app {
class LoggerModel;
/// Класс для вывода в modelview
class LIBLOG4APP_API WidgetAppender : public Log4Qt::AppenderSkeleton {
    Q_OBJECT

    // LogObject interface
protected:
#ifndef QT_NO_DEBUG_STREAM
    QDebug debug(QDebug& rDebug) const Q_DECL_OVERRIDE
    {
        return rDebug;
    }
#endif // QT_NO_DEBUG_STREAM

    // Appender interface
public:
    WidgetAppender(QObject* parent = nullptr);

    virtual ~WidgetAppender();

    bool requiresLayout() const Q_DECL_OVERRIDE;

    QAbstractItemModel* model();

protected:
    void append(const Log4Qt::LoggingEvent& rEvent) Q_DECL_OVERRIDE;

private:
    LoggerModel* model_;
};
}  // namespace log4app
