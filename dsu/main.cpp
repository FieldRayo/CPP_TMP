#include <iostream>

#include "dsu.hpp"

int main () {
    constexpr auto dsu =
        DSU{}
            .merge<1, 2>()
            .merge<2, 3>()
            .merge<4, 5>()
            .merge<7, 8>()
            .merge<8, 9>()
            ;

    static_assert
        (
            (
             dsu.find(2) == 1 &&
             dsu.find(3) == 1 &&
             dsu.find(5) == 4 &&
             dsu.find(6) == 6
            ),
            "x"
        );

    return 0;
}

