#include <iostream>
#include <string>
#include <vector>
#include <array>

// https://stackoverflow.com/questions/34569455/syntax-issue-when-populating-an-array-with-a-fold-expression

using namespace std;

template <typename T>
constexpr T mathFunction(T x)
{
    return x * 543.432 + 5.2410;
}

template <typename T, std::size_t N, T (*F)(T)>
struct Data
{
    std::array<T, N> values{};
    template <typename... Args>
    constexpr Data(Args &&...pack)
        : values{F(std::forward<Args>(pack))...}
    {
        static_assert(sizeof...(pack) <= N, "Too many args");
    }
};

template<class T, std::size_t N>
struct Data1
{
    T arr[N]{};

    template<typename... Args>
    constexpr Data1(Args&&... pack)
    {
        static_assert(sizeof...(pack) <= N, "Too many args");
        std::size_t i = 0;
        (void(arr[i++] = pack) , ...);
    }
};

template<typename T, std::size_t... Is>
constexpr std::array<T, sizeof...(Is)>
make_inc_array_impl(std::index_sequence<Is...>)
{
	return {{(Is + 1.5)...}}; // Adding 1.5 just so the output shows doubles instead of suppressing the decimals because the values are whole numbers
}

template <typename T, std::size_t N>
constexpr std::array<T, N> make_inc_array()
{
	return make_inc_array_impl<T>(std::make_index_sequence<N>{});
}

int main()
{

    constexpr auto a = make_inc_array<double, 10>(); // [1, 2, ..., 10]

    constexpr Data1<int, 5> b{1, 2, 3, 4, 5};
    // constexpr auto x = std::make_integer_sequence<int, 5>{};
    // constexpr Data1<int, 5> b{x};

    constexpr std::size_t data_len{10};
    constexpr Data<double, data_len, mathFunction> data{30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0, 120.0};

    for (size_t i{}; i < data.values.size(); i++)
        cout << data.values[i] << "\n";

    return 0;
}