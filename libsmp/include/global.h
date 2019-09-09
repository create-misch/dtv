#pragma once

#include <memory>

namespace libsmp {

using Key = int;

template <class Ptr>
using sp = std::shared_ptr<Ptr>;

}
