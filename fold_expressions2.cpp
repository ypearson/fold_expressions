#include <array>
#include <iostream>

// https://stackoverflow.com/questions/34569455/syntax-issue-when-populating-an-array-with-a-fold-expression

template <typename T, std::size_t... Is>
constexpr std::array<T, sizeof...(Is)>
make_range_impl(std::index_sequence<Is...>, T m, T b) {
  return {{(Is * m + b)...}};
}

template <typename T, std::size_t N>
constexpr std::array<T, N> make_range(T m, T b) {
  return make_range_impl<T>(std::make_index_sequence<N>{}, m, b);
}

template <typename T, std::size_t N, T (*F)(T)> struct BuildDataSet {
  std::array<T, N> values{};
  explicit constexpr BuildDataSet(const std::array<T, N> &arr) {
    for (size_t i = 0; i < N; i++)
      values[i] = F(arr[i]);
  }

  template <typename... Args>
  explicit constexpr BuildDataSet(Args &&... pack)
      : values{F(std::forward<Args>(pack))...} {
    static_assert(sizeof...(pack) <= N, "Too many args");
  }
};

template <class T, std::size_t N> struct Data1 {
  std::array<T, N> arr{};
  template <typename... Args> constexpr Data1(Args &&... pack) {
    static_assert(sizeof...(pack) <= N, "Too many args");
    std::size_t i{};
    (void(arr[i++] = pack), ...);
  }
};

template <typename T> constexpr T mathFunction(T x) { return x * 2 + 1; }

int main() {

  constexpr auto MULTIPLIER{10.0};
  constexpr auto OFFSET{10.0};

  constexpr std::size_t data_len{10};

  constexpr auto range{make_range<double, data_len>(MULTIPLIER, OFFSET)};

  constexpr BuildDataSet<double, data_len, mathFunction> data_set{range};

  constexpr Data1<int, 5> b{1, 2, 3, 4, 5};

  constexpr BuildDataSet<double, data_len, mathFunction> data{
      30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0, 120.0};

  for (size_t i{}; i < data_set.values.size(); i++)
    std::cout << data_set.values[i] << "\n";

  for (size_t i{}; i < data.values.size(); i++)
    std::cout << data.values[i] << "\n";

  return 0;
}