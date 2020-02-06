#pragma once

#include <database/idatabase_element.h>

#include <QString>

#include <memory>

namespace database
{

class IDatabaseQuery
{
public:
    virtual ~IDatabaseQuery() = default;

    virtual bool CreateTableForElement(const QString& tableName, const IDatabaseElement& element) = 0;
    virtual bool DeleteTable(const QString& tableName) = 0;
    virtual bool IsExistTable(const QString& tableName) const = 0;

    virtual bool WriteElement(const QString& tableName, const IDatabaseElement& element) = 0;
    virtual bool LoadElement(const QString& tableName, IDatabaseElement& element) = 0;
    virtual bool RemoveElement(const QString& tableName, IDatabaseElement& element) = 0;
    virtual bool IsExistElement(const QString& tableName, const IDatabaseElement& element) const = 0;
};

using DatabaseQueryPtr = std::shared_ptr<IDatabaseQuery>;

} // namespace database
