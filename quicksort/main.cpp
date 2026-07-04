#include <iostream>
#include <array>

constexpr std::array<int, 9> data = { 5, 6, 7, 5, 6, 7, 5, 6, 7 };

template <int... Vs>
constexpr int calculate_pivot() {
    ((std::cout << Vs << '\n'), ...);
    return sizeof...(Vs);
}

template <std::size_t... Is>
constexpr void calculate(
    std::index_sequence<Is...>
) {
    std::cout << calculate_pivot<data[Is]...>();
}

int main() {
    calculate(std::index_sequence<1, 4, 5>());

    return 0;
}
