#ifndef __TRANSFER_FUNCTION_TRIVIALTRANSFERFUNCTION_H
#define __TRANSFER_FUNCTION_TRIVIALTRANSFERFUNCTION_H

#include <cstddef>
#include <functional>
#include <utility>

#include <wpi/array.h>

#include <transfer_function/TransferFunctionBase.h>

namespace transfer_function {

// A trivial implementation of TransferFunctionBase, and users can use a lambda
// expression to initialize the object.
template <std::size_t N>
class TrivialTransferFunction : public TransferFunctionBase<N> {
 public:
  using input  = wpi::array<double, N>&&;
  using output = wpi::array<double, N>&&;

  explicit TrivialTransferFunction(std::function<output (input)> f) : f_{f} {}
  TrivialTransferFunction() = delete;
  TrivialTransferFunction(const TrivialTransferFunction&) = delete;
  TrivialTransferFunction(TrivialTransferFunction&&) = delete;

  virtual output operator()(input x) {
    return f_(std::move(x));
  }

  virtual output operator()(input x) const {
    return f_(std::move(x));
  }

 private:
  const std::function<output (input)> f_;
};

} // namespace transfer_function

// Const specialization of:
// operator*(
//     wpi::array<double, N>&&,
//     transfer_function::TransferFunctionBase<N>&).
template <std::size_t N>
wpi::array<double, N>&& operator*(wpi::array<double, N>&& lhs,
    const transfer_function::TrivialTransferFunction<N>& rhs) {
  return rhs(std::move(lhs));
}

// A way much shorter alias.
template <std::size_t N>
using TrivialTF = const transfer_function::TrivialTransferFunction<N>;

#endif // __TRANSFER_FUNCTION_TRIVIALTRANSFERFUNCTION_H