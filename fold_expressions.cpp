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

constexpr int mathFunction(int x)
{
    return x * 10.0;
}

template <typename T, std::size_t N, int (*F)(int)>
struct Data
{
    std::array<T, N> arr{};
    std::size_t i = 0;

    template <typename... Args>
    constexpr Data(Args &&...pack)
    {
        static_assert(sizeof...(pack) <= N, "Too many args");
        (void(arr[i++] =  F(pack)), ...);
    }
};

int main()
{

    constexpr Data<int, 5, mathFunction> data{1, 2, 3, 4, 5};

    for (size_t i{}; i < data.arr.size(); i++)
        cout << data.arr[i] << "\n";

    vector<int> v;
    FoldPushBack(v, 1, 2, 3, 4);

    for (auto &i : v)
        cout << i << "\n";

    constexpr auto x = sum(1, 2, 3, 4, 5);

    return sum(1, 2, 3, 4, 5);
}