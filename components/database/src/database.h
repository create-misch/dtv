#pragma once

#include <database/idatabase.h>

namespace database
{

class Database : public IDatabase
{
public:
    Database();

    bool InitDatabaeConnection(const QString& databaseNameConnection) override;
    bool CloseDatabaseConnection(const QString& databaseNameConnection) override;
    DatabaseConnectorPtr GetDatabaseConnector() const override;
    DatabaseQueryPtr GetDatabaseQuery() const override;

private:
    DatabaseConnectorPtr m_databaseConnector;
    DatabaseQueryPtr m_databaseQuery;
};

}
