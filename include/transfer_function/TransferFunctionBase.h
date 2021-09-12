#ifndef __TRANSFER_FUNCTION_TRANSFERFUNCTIONBASE_H
#define __TRANSFER_FUNCTION_TRANSFERFUNCTIONBASE_H

#include <cstddef>
#include <utility>

#include <wpi/array.h>

namespace transfer_function {

// An abstract class which could process rvalue wpi::array without calling any
// constructors.
template <std::size_t N>
class TransferFunctionBase {
 public:
  virtual wpi::array<double, N>&& operator()(wpi::array<double, N>&& x) = 0;
};

} // namespace transfer_function

// Syntactic sugar, which allows users to write codes like:
// auto result = data * tf1 * tf2;
// which is equivalent to:
// auto result = tf2(tf1(data));
template <std::size_t N>
wpi::array<double, N>&& operator*(wpi::array<double, N>&& lhs,
    transfer_function::TransferFunctionBase<N>& rhs) {
  return rhs(std::move(lhs));
}

#endif // __TRANSFER_FUNCTION_TRANSFERFUNCTIONBASE_H