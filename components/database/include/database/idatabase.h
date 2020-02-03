#pragma once

#include <database/idatabase_connector.h>
#include <database/idatabase_query.h>

#include <memory>

namespace database
{

class IDatabase
{
public:
    virtual ~IDatabase() = default;

    virtual bool InitDatabaeConnection(const QString& databaseNameConnection) = 0;
    virtual bool CloseDatabaseConnection(const QString& databaseNameConnection) = 0;
    virtual DatabaseConnectorPtr GetDatabaseConnector() const = 0;
    virtual DatabaseQueryPtr GetDatabaseQuery() const = 0;
};

using DatabasePtr = std::shared_ptr<IDatabase>;

DatabasePtr CreateDatabase();

} // namespace database
