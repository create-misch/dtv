#include "database_connector.h"

#include <log4app/log4app.h>

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>

namespace database
{

DatabaseConnector::DatabaseConnector(const QString& databaseName)
    : m_databaseName(databaseName)
{
}

bool DatabaseConnector::ConnectToDatabase(const IDatabaseConnector::ConnectionCredential& credential)
{
    auto database = QSqlDatabase::database(m_databaseName);

    database.setDatabaseName(credential.databaseName);
    database.setHostName(credential.hostName);
    database.setUserName(credential.userName);
    database.setPassword(credential.password);
    database.setPort(credential.port);

    auto result = database.open();
    if (!result)
    {
        auto sqlError = database.lastError();
        qDebug() << sqlError.text();
//        log4app::Log()->error(sqlError.text());
    }
    return result;
}

} // namespace database
