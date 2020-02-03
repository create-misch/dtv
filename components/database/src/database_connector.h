#pragma once

#include <database/idatabase_connector.h>

namespace database
{

class DatabaseConnector : public IDatabaseConnector
{
public:
    DatabaseConnector(const QString& databaseName);

    bool ConnectToDatabase(const ConnectionCredential& credential) override;

private:
    const QString m_databaseName;
};

} // namespace database
