# etude-transfer-function

A light-weight class template which allows users to process data in series, in a conveninent way.

## Example

For a mecanum drive (or a swerve drive), we read 3 inputs (v_x, v_y, and omega) from the joystick, and then apply a deadband on them. Suppose there is a function `wpi::array<double, 3> GetDriveTrainInputs()` that returns the three values we need. With the help of the class template, we can write codes like:

```cpp
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

auto ret = GetDriveTrainInputs() * deadband;
```

Otherwise, you may write codes like:

```cpp
auto ret = deadband(GetDriveTrainInputs());
```

And the code becomes ugly when you have many processes, like:

```cpp
auto ret = process2(process1(deadband(GetDriveTrainInputs())));
```

With the help of this class template, the code becomes:

```cpp
auto ret = GetDriveTrainInputs() * deadband * process1 * process2;
```

However, for lvalues, such as variables, the code should be written as:

```cpp
const wpi::array<double, 3> inputs = {-1.0, 0.0, 0.0};

auto ret = wpi::array<double, 3>{inputs} * deadband * process1 * process2;
```

It is called transfer-function because we do the same thing with transfer functions: multiply with each other and get the cascaded one, although those objects may not represent linear systems, which means exchanging the order may give different results. However, this class template may resemble pipelines instead of transfer functions.

## Features

- Syntactic sugar mentioned above in the example.
- No constructors will be called during the process, except the assignment.

## Precautions

- For `TrivialTF<N>`, the definition should always in the format of:
  ```cpp
  TrivialTF<N> foo{[/* user defined */]
      (TrivialTF<N>::input v) -> TrivialTF<N>::output {
    // deal with the data here
    return std::move(v);
  }};
  ```
- For variables, a copy constructor is necessary, as mentioned above in the example.

## License

The code is in the public domain.