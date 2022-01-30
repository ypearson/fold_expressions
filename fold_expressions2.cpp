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

int main()
{
    constexpr std::size_t data_len{10};

    constexpr Data<double, data_len, mathFunction> data{1, 2, 3, 4, 0};

    for (size_t i{}; i < data.values.size(); i++)
        cout << data.values[i] << "\n";

    return 0;
}