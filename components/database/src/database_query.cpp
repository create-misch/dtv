#include "database_query.h"

#include <database/database_element_help.h>

#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>

namespace
{
QString VariantToDbString(const QVariant& value)
{
    auto stringValue = value.toString();
    return value.type() == QVariant::Int ? stringValue : QString{"'%1'"}.arg(stringValue);
}

void PrintSqlError(const QSqlError& error)
{
    qDebug() << error.text();
}

} // namespace

namespace database
{

DatabaseQuery::DatabaseQuery(const QString& databaseName)
    : m_databaseName(databaseName)
{
}

bool DatabaseQuery::CreateTableForElement(const QString& tableName, const IDatabaseElement& element)
{
    if (element.GetColumnsDeclarations().empty())
    {
        return false;
    }
    QString createQuery = QString("CREATE TABLE %1 (").arg(tableName);

    QStringList declarationsList;
    for (const auto& declaration : element.GetColumnsDeclarations())
    {
        declarationsList.push_back(QString("%1 %2").arg(declaration.second).arg(declaration.first));
    }
    createQuery.push_back(declarationsList.join(", "));
    createQuery.push_back(");");

    auto database = GetDatabase();
    QSqlQuery sqlQuery{database};

    auto result = sqlQuery.exec(createQuery);
    if (!result)
    {
        PrintSqlError(database.lastError());
    }
    return result;
}

bool DatabaseQuery::DeleteTable(const QString& tableName)
{
    QString createQuery = QString("DROP TABLE %1;").arg(tableName);

    auto database = GetDatabase();
    QSqlQuery sqlQuery{database};

    auto result = sqlQuery.exec(createQuery);
    if (!result)
    {
        PrintSqlError(database.lastError());
    }
    return result;
}

bool DatabaseQuery::IsExistTable(const QString& tableName) const
{
    auto tables = GetDatabase().tables();
    return tables.contains(tableName);
}

bool DatabaseQuery::WriteElement(const QString& tableName, const IDatabaseElement& element)
{
    if (element.GetColumnsDeclarations().empty())
    {
        return false;
    }
    auto database = GetDatabase();

    QString queryText =
        QString{"INSERT INTO %1 (%2) VALUES ("}
            .arg(tableName)
            .arg(GetColumnsName(element.GetColumnsDeclarations()));

    QStringList list;
    for (int i = 0; i < element.GetMaxIndex(); ++i)
    {
        auto value = element.GetValue(i);
        list.push_back(VariantToDbString(value));
    }
    queryText.push_back(list.join(", "));
    queryText.push_back(");");

    QSqlQuery query{database};

    auto result = query.exec(queryText);
    if (!result)
    {
        PrintSqlError(database.lastError());
    }
    return result;
}

bool DatabaseQuery::LoadElement(const QString& tableName, IDatabaseElement& element)
{
    assert(element.GetMaxIndex() > 0);

    auto database = GetDatabase();
    auto columnsDeclarations = element.GetColumnsDeclarations();
    auto queryText = QString{"SELECT %1 FROM %2"}
            .arg(GetColumnsName(element.GetColumnsDeclarations()))
            .arg(tableName);

    if (columnsDeclarations.size() > 1)
    {
        auto findColumnName = columnsDeclarations.first().second;
        auto findValue = VariantToDbString(element.GetValue(0));
        queryText.push_back(QString{"WHERE %1 = %2"}.arg(findColumnName).arg(findValue));
    }
    queryText.push_back(";");

    QSqlQuery query{database};

    auto result = query.exec(queryText);

    while (query.next())
    {
        int index{0};
        for (int i = 0; i < element.GetMaxIndex(); ++i)
        {
            element.SetValue(i, query.value(i));
        }
        ++index;
    }

    return result;
}

bool DatabaseQuery::IsExistElement(const QString& tableName, const IDatabaseElement& element) const
{
    Q_UNUSED(tableName);
    Q_UNUSED(element);
    return true;
}

QSqlDatabase DatabaseQuery::GetDatabase() const
{
    return QSqlDatabase::database(m_databaseName);
}

} // namespace database
