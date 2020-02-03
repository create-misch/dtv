#include "database.h"
#include "database_connector.h"
#include "database_query.h"

#include <log4app/log4app.h>

#include <QSqlDatabase>

namespace database
{

constexpr const char* DatabaseType = "QPSQL";

Database::Database()
{

}

bool Database::InitDatabaeConnection(const QString &databaseNameConnection)
{
    auto result = QSqlDatabase::isDriverAvailable(DatabaseType);
    if (!result)
    {
        log4app::Log()->error(QString("Driver %1 not suported!").arg(DatabaseType));
    }

    auto database = QSqlDatabase::addDatabase(DatabaseType, databaseNameConnection);
    if (!database.isValid())
    {
        log4app::Log()->error("Database connection isn't valid!");
        return false;
    }

    m_databaseQuery = std::make_shared<DatabaseQuery>(databaseNameConnection);
    m_databaseConnector = std::make_shared<DatabaseConnector>(databaseNameConnection);
    return true;
}

bool Database::CloseDatabaseConnection(const QString &databaseNameConnection)
{
    QSqlDatabase::removeDatabase(databaseNameConnection);
    return true;
}

DatabaseConnectorPtr Database::GetDatabaseConnector() const
{
    return m_databaseConnector;
}

DatabaseQueryPtr Database::GetDatabaseQuery() const
{
    return m_databaseQuery;
}

DatabasePtr CreateDatabase()
{
    return std::make_shared<Database>();
}

} // namespace database
