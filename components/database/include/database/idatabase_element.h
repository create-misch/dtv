#pragma once

#include <QString>
#include <QVariant>

#include <QList>

namespace database
{

using ColumnType = QString;
using ColumnName = QString;
using ColumnDeclaration = std::pair<ColumnType, ColumnName>;
using ColumnsDeclarations = QList<ColumnDeclaration>;

class IDatabaseElement
{
public:
    virtual ~IDatabaseElement() = default;

    virtual ColumnsDeclarations GetColumnsDeclarations() const = 0;

    virtual QVariant GetValue(int index) const = 0;
    virtual bool SetValue(int index, QVariant&& value) = 0;
    virtual int GetMaxIndex() const = 0;
};

} // namespace database
