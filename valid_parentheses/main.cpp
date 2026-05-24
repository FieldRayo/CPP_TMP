#include <iostream>
#include "valid_parentheses.hpp"

int main() {
    static_assert(
        (
         is_valid<"()[][]">()         &&
         is_valid<"({()}[()]){}[]">() &&
        !is_valid<"()[]}">()          &&
        !is_valid<"()[{{{}}}]{[[(])]}">() 
        ),
        "x"
    );

    return 0;
}
