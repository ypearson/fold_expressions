#include <iostream>
#include <string>
#include <vector>
#include <array>

using namespace std;

template <typename... Type>
constexpr auto sum(Type const &...value)
{
    // return (value + ... + 0);
    return (0 + ... + value);
}

template <typename T, typename... Args>
void FoldPushBack(vector<T> &v, Args &&...args)
{
    (v.push_back(args), ...);
}
template <typename T = double>
constexpr T mathFunction(T x)
{
    return x * 10.0;
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

// template <typename T,std::size_t N>
// struct Data
// {
//     std::array<T, N> array{};
//     template <typename Fct, typename... Args>
//     constexpr Data( Fct&& f, Args &&...pack)
//         : array{ f(std::forward<Args>( pack )) ... }
//     {
//         static_assert(sizeof...(pack) <= N, "Too many args");
//     }
// };

int main()
{
    constexpr Data<double, 5, mathFunction> data{1.0, 2.0, 3.0, 4.0, 5.0};

    for (size_t i{}; i < data.values.size(); i++)
        cout << data.values[i] << "\n";

    return 0;
}

// int main()
// {

//     constexpr Data<int, 5, mathFunction> data{1, 2, 3, 4, 5};

//     for (size_t i{}; i < data.arr.size(); i++)
//         cout << data.arr[i] << "\n";

//     vector<int> v;
//     FoldPushBack(v, 1, 2, 3, 4);

//     for (auto &i : v)
//         cout << i << "\n";

//     constexpr auto x = sum(1, 2, 3, 4, 5);

//     return sum(1, 2, 3, 4, 5);
// }

/*
The problem is that the arr member is not initialized. You can fix this by giving it an in class initializer:

std::array<T, N> arr{};

But the best choice would be to change your constructor:

template <typename... Args>
constexpr Data( Args &&...pack)
    : arr{ F(std::forward<Args>( pack )) ... }
{
    static_assert(sizeof...(pack) <= N, "Too many args");
}

It may be best to move the function into the constructor though, if you dont need it outside of it:

template <typename T,std::size_t N>
struct Data
{
    std::array<T, N> arr{};

    template <typename Fct, typename... Args>
    constexpr Data( Fct&& f, Args &&...pack)
        : arr{ f(std::forward<Args>( pack )) ... }
    {
        static_assert(sizeof...(pack) <= N, "Too many args");
    }
};
*/