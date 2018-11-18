#include <log4app/widgetappender.h>
#include <log4qt/layout.h>

#include "listmodel.h"

namespace log4app {
class LoggerModel : public ListModel<QString> {
    Q_OBJECT
public:
    static const int kMaxMessages = 1000;

    LoggerModel(QObject* parent)
        : ListModel<QString>(parent)
    {
    }

    ~LoggerModel() {}

    void onNewMessage(QString m)
    {
        addElement(m);

        if (count() > kMaxMessages) {
            removeElementByIndex(0);
        }
    }

    void clear()
    {
        removeAll();
    }

    QVariant data(const QModelIndex& index, int role) const override
    {
        if (index.isValid() && index.row() < count() && index.row() >= 0) {
            if (role == Qt::DisplayRole) {

                return constElement(index.row());
            }
        }

        return QVariant();
    }
};

WidgetAppender::WidgetAppender(QObject* parent)
    : Log4Qt::AppenderSkeleton(parent)
    , model_(new LoggerModel(this))
{
}

WidgetAppender::~WidgetAppender()
{
    close();
}

bool WidgetAppender::requiresLayout() const
{
    return false;
}

QAbstractItemModel* WidgetAppender::model() { return model_; }

void WidgetAppender::append(const Log4Qt::LoggingEvent& rEvent)
{
    QString msg(layout()->format(rEvent));
    msg.chop(1);
    model_->onNewMessage(msg);
}
} // namespace
#include "widgetappender.moc"
