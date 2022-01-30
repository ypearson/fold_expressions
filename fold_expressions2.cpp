#include <iostream>
#include <string>
#include <vector>
#include <array>

using namespace std;

template <typename T>
constexpr T mathFunction(T x)
{
    return x * 10.0 + 25.0;
}

template <typename T, std::size_t N, T (*F)(T)>
struct Data
{
    std::array<T, N> values{};
    std::size_t i = 0;

    template <typename... Args>
    constexpr Data(Args &&...pack)
        : values{F(std::forward<Args>(pack))...}
    {
        static_assert(sizeof...(pack) <= N, "Too many args");
    }
};

template <int... Is>
constexpr std::array<int, sizeof...(Is)>
make_inc_array_impl(std::integer_sequence<int, Is...>) {
    return {{(Is + 1)...}}; // +1 to start at one instead of [0, 1, ...]
}

template <std::size_t N>
constexpr std::array<int, N> make_inc_array() {
    return make_inc_array_impl(std::make_integer_sequence<int, N>{});
}

int main()
{

    constexpr auto a = make_inc_array<10>(); // [1, 2, ..., 10]

    constexpr std::size_t data_len{10};

    constexpr Data<double, data_len, mathFunction> data{30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0, 120.0};

    for (size_t i{}; i < data.values.size(); i++)
        cout << data.values[i] << "\n";

    return 0;
}