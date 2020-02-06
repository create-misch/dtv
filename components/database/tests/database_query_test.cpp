#include <gtest/gtest.h>

#include <database/database_element_help.h>
#include <database/idatabase.h>
#include <database/idatabase_connector.h>
#include <database/idatabase_element.h>
#include <database/idatabase_query.h>

#include <QSqlDatabase>
#include <QStringList>

using namespace testing;
using namespace database;

namespace database_element_test
{

constexpr const char* TestDatabaseConnectionName = "test_connection";

struct El
{
    int elementId;
    QString elementName;
};

class FakeMockDatabaseElement : public IDatabaseElement
{
public:
    ColumnsDeclarations GetColumnsDeclarations() const override { return m_columnDeclarations; }

    QVariant GetValue(int index) const override
    {
        switch (index)
        {
        case 0:
            return el.elementId;

        case 1:
            return el.elementName;
        }
        return QVariant{};
    }
    bool SetValue(int index, QVariant&& value) override
    {
        switch (index)
        {
        case 0:
            el.elementId = value.toInt();
            break;

        case 1:
            el.elementName = value.toString();
            break;
        }
        return true;
    }
    int GetMaxIndex() const override { return 2; }

    ColumnsDeclarations m_columnDeclarations;
    QString m_insertQuery;
    QString m_selectQuery;
    El el;
};

} // namespace database_element_test

class DatebaseQueryTest : public Test
{
protected:
    void SetUp() override
    {        
        m_database = CreateDatabase();
        auto result = m_database->InitDatabaeConnection(database_element_test::TestDatabaseConnectionName);
        ASSERT_TRUE(result);

        auto connector = m_database->GetDatabaseConnector();
        IDatabaseConnector::ConnectionCredential credential{};
        credential.databaseName = "test_database";
        credential.userName = "tester";
        credential.hostName = "127.0.0.1";
        credential.password = "";
        credential.port = 5432;
        result = connector->ConnectToDatabase(credential);
        ASSERT_TRUE(result);
    }

    void TearDown() override { m_database->CloseDatabaseConnection(database_element_test::TestDatabaseConnectionName); }

    QStringList Tables() { return QSqlDatabase::database(database_element_test::TestDatabaseConnectionName).tables(); }

protected:
    DatabasePtr m_database;
};

TEST_F(DatebaseQueryTest, CreateDatabase) {}

TEST_F(DatebaseQueryTest, CreateRemoveIsExistTableForElement)
{
    auto databaseQuery = m_database->GetDatabaseQuery();

    database_element_test::FakeMockDatabaseElement element;
    element.m_columnDeclarations = {std::make_pair("integer", "number")};

    const char* testTableName = "test_table";
    auto result = databaseQuery->CreateTableForElement(testTableName, element);
    ASSERT_TRUE(result);

    auto tables = Tables();
    ASSERT_TRUE(tables.contains(testTableName));

    ASSERT_TRUE(databaseQuery->IsExistTable(testTableName));

    result = databaseQuery->DeleteTable(testTableName);
    ASSERT_TRUE(result);

    tables = Tables();
    ASSERT_FALSE(tables.contains(testTableName));
}

TEST_F(DatebaseQueryTest, WriteLoadDeleteElement)
{
    auto element = database_element_test::FakeMockDatabaseElement{};

    ColumnDeclaration firstElement{"integer primary key", "ElementId"};
    ColumnDeclaration secondElement{"text", "ElementName"};
    element.m_columnDeclarations = {firstElement, secondElement};

    auto databaseQuery = m_database->GetDatabaseQuery();
    const char* testTableName = "test_table";
    databaseQuery->CreateTableForElement(testTableName, element);

    auto columns = GetColumnsName(element.GetColumnsDeclarations());

    element.el.elementId = 5;
    element.el.elementName = "lololol";

    auto result = databaseQuery->WriteElement(testTableName, element);

    auto element1 = database_element_test::FakeMockDatabaseElement{};
    element1.m_columnDeclarations = {firstElement, secondElement};
    element1.el.elementId = 5;

    result = databaseQuery->LoadElement(testTableName, element1);
    result = databaseQuery->RemoveElement(testTableName, element1);

    result = databaseQuery->DeleteTable(testTableName);
    ASSERT_TRUE(result);
}
