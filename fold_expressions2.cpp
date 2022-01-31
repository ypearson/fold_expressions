#include <array>
#include <iostream>

// https://stackoverflow.com/questions/34569455/syntax-issue-when-populating-an-array-with-a-fold-expression

using namespace std;

template <typename T> constexpr T mathFunction(T x) { return x * 2 + 1; }
namespace {
constexpr auto MULTIPLIER{10.0};
constexpr auto OFFSET{10.0};
} // namespace
template <typename T, std::size_t... Is>
constexpr std::array<T, sizeof...(Is)>
make_inc_array_impl(std::index_sequence<Is...>, T m, T b) {
  return {{(Is * m + b)...}};
}

template <typename T, std::size_t N>
constexpr std::array<T, N> make_inc_array(T m, T b) {
  return make_inc_array_impl<T>(
      std::make_index_sequence<N> {}, m, b);
}

template <typename T, std::size_t N, T (*F)(T)> struct Data {
  std::array<T, N> values{};
  explicit constexpr Data(const std::array<T, N> &arr) {
    for (size_t i = 0; i < N; i++)
      values[i] = F(arr[i]);
  }

  template <typename... Args>
  explicit constexpr Data(Args &&... pack)
      : values{F(std::forward<Args>(pack))...} {
    static_assert(sizeof...(pack) <= N, "Too many args");
  }
};

template <class T, std::size_t N> struct Data1 {
  std::array<T, N> arr{};
  template <typename... Args> constexpr Data1(Args &&... pack) {
    static_assert(sizeof...(pack) <= N, "Too many args");
    std::size_t i = 0;
    (void(arr[i++] = pack), ...);
  }
};

int main() {

  constexpr std::size_t data_len{10};

  constexpr auto range{make_inc_array<double, 10>(MULTIPLIER, OFFSET)};

  constexpr Data1<int, 5> b{1, 2, 3, 4, 5};

  constexpr Data<double, data_len, mathFunction> data{
      30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0, 120.0};

  constexpr Data<double, data_len, mathFunction> data1{range};

  for (size_t i{}; i < data1.values.size(); i++)
    cout << data1.values[i] << "\n";

  for (size_t i{}; i < data.values.size(); i++)
    cout << data.values[i] << "\n";

  return 0;
}