#include <cmath>
#include <iostream>
#include <utility>

#include <transfer_function/TrivialTransferFunction.h>
#include <wpi/array.h>

wpi::array<double, 3> GetDriveTrainInputs() {
  return {0.1, 0.21, 0.3};
}

int main(int argc, char** argv) {
  const wpi::array<double, 3> foo = {-1.0, 0.0, 0.0};
  
  TrivialTF<3> deadband{[](TrivialTF<3>::input v) -> TrivialTF<3>::output {
    for (auto& itr : v) {
      if (std::abs(itr) < 0.2) {
        itr = 0.0;
      } else {
        itr = (itr - std::copysign(0.2, itr)) * 1.25;
      }
    }
    return std::move(v);
  }};

  TrivialTF<3> identity{[](TrivialTF<3>::input v) -> TrivialTF<3>::output {
    return std::move(v);
  }};

  TrivialTF<3> square{[](TrivialTF<3>::input v) -> TrivialTF<3>::output {
    for (auto& itr : v) {
      itr *= itr;
    }
    return std::move(v);
  }};

  {
    auto ret = GetDriveTrainInputs() * deadband * square;
    std::cout << ret << std::endl;
  }

  {
    auto ret = square(deadband(GetDriveTrainInputs()));
    std::cout << ret << std::endl;
  }

  {
    auto ret = wpi::array<double, 3>{foo} * deadband * identity * square;
    std::cout << ret << std::endl;
  }

  return 0;
}