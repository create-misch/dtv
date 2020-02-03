#pragma once

#include <database/idatabase_element.h>

#include <QStringList>

namespace database
{

inline QString GetColumnsName(const ColumnsDeclarations& columnDeclarations)
{
    QStringList columnsList;
    for (const auto& declaration : columnDeclarations)
    {
        columnsList.push_back(declaration.second);
    }
    return columnsList.join(",");
}

}
