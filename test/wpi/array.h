#ifndef __TEST_WPI_ARRAY_H
#define __TEST_WPI_ARRAY_H

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <ostream>

namespace wpi {

// A simplifed array.
template <typename T, std::size_t N>
class array {
 public:
  array() = delete;
  array(std::initializer_list<T> other) {
    idx = cnt++;
    std::cout <<
        "The constructor of wpi::array has been called." << std::endl <<
        "The index of the object is " << idx << "." << std::endl << std::endl;
    std::size_t i = 0; 
    for (auto& itr : other) {
      data_[i] = itr;
      ++i;
      if (i == N) { break; }
    }
  }
  array(const array<T, N>& other) {
    idx = cnt++;
    std::cout <<
        "The copy constructor of wpi::array has been called." << std::endl <<
        "The index of the object is " << idx << "." << std::endl << std::endl;
    for (std::size_t i = 0; i < N; ++i) {
      data_[i] = other.data_[i];
    }
  }
  array(array<T, N>&& other) {
    idx = cnt++;
    std::cout <<
        "The move constructor of wpi::array has been called." << std::endl <<
        "The index of the object is " << idx << "." << std::endl << std::endl;
    for (std::size_t i = 0; i < N; ++i) {
      data_[i] = other.data_[i];
    }
  }
  ~array() {
    std::cout <<
        "The destructor of wpi::array has been called." << std::endl <<
        "The index of the object is " << idx << "." << std::endl << std::endl;
  }

  T& operator[](std::size_t idx) {
    return data_[idx];
  }

  T* begin() { return data_; }
  T* end() { return data_ + N; }
  const T* begin() const { return data_; }
  const T* end() const { return data_ + N; }
  const T* cbegin() const { return data_; }
  const T* cend() const { return data_ + N; }

 private:
  static std::size_t cnt;

  T data_[N];
  std::size_t idx;
};

template <typename T, std::size_t N>
std::size_t array<T, N>::cnt = 0;

} // namespace wpi

template <std::size_t N>
std::ostream& operator<<(std::ostream& os, const wpi::array<double, N>& v) {
  os << "[";
  for (const auto& itr : v) {
    os << itr << ",";
  }
  os << "]";
  return os;
}

#endif // __TEST_WPI_ARRAY_H