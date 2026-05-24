#include <iostream>

#include "palindrome.hpp"

int main () {
    constexpr bool p1 = is_palindrome_v<999>,
                   p2 = is_palindrome_v<959>;

    static_assert(p1 && !p2, "x");
    
    return 0;
}
