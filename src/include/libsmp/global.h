#pragma once

#include <memory>

namespace libsmp {

template <class Ptr>
using sp = std::shared_ptr<Ptr>;

}
