#pragma once

#include <database/idatabase_query.h>

#include <QSqlDatabase>

namespace database
{

class DatabaseQuery : public IDatabaseQuery
{
public:
    DatabaseQuery(const QString& databaseName);

    bool CreateTableForElement(const QString& tableName, const IDatabaseElement& element) override;
    bool DeleteTable(const QString& tableName) override;
    bool IsExistTable(const QString& tableName) const override;

    bool WriteElement(const QString& tableName, const IDatabaseElement& element) override;
    bool LoadElement(const QString& tableName, IDatabaseElement& element) override;
    bool IsExistElement(const QString& tableName, const IDatabaseElement& element) const override;

private:
    QSqlDatabase GetDatabase() const;

private:
    const QString m_databaseName;
};

} // namespace database
