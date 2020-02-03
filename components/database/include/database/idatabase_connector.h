#pragma once

#include <QString>

#include <memory>

namespace database
{

class IDatabaseConnector
{
public:
    struct ConnectionCredential
    {
        QString databaseName;
        QString userName;
        QString hostName;
        QString password;
        int port;
    };
    virtual ~IDatabaseConnector() = default;

    virtual bool ConnectToDatabase(const ConnectionCredential& credential) = 0;
};

using DatabaseConnectorPtr = std::shared_ptr<IDatabaseConnector>;

} // namespace database
