#pragma once

#include <memory>

#include <QString>

using Key = int;
using CellName = QString;

const CellName DefaultCellName = "";
constexpr Key DefaultKey = -1;
constexpr Key RootKey = 0;

namespace libsmp
{

using Key = int;

template<class Ptr>
using sp = std::shared_ptr<Ptr>;
} // namespace libsmp
