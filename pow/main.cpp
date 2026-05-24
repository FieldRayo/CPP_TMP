#include "pow.hpp"

constexpr double alpha = 1e-14;

template <double N>
constexpr double static_abs() {
    return (N >= 0) ? N : -N;
}

template <double A, double B, double Alpha>
constexpr bool equal_aprox() {
    return 
        static_abs<A - B>() < (Alpha);
}

int main() {
    static_assert((
                (equal_aprox<
                 pow_v<3.0, 3>,
                 27.0,
                 alpha
                 >()) &&

                (equal_aprox<
                 pow_v<11.0, 2>,
                 121.0,
                 alpha
                 >()) &&

                (equal_aprox<
                 pow_v<2.1, 3>,
                 9.261,
                 alpha
                 >()) &&

                (equal_aprox<
                 pow_v<2.0, -2>,
                 0.25,
                 alpha
                 >()) &&

                (equal_aprox<
                 pow_v<7.0, -3>,
                 0.0029154518950437317,
                 alpha
                 >())
                ), "x");

    return 0;
}
