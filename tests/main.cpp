#include <iostream>

void print(int x) {
    std::cout << x << std::endl;
}

template <char... Vs>
constexpr void foo() {
    (Vs == '(') ? stack.push(Vs) : stack.pop()
}

int main() {
    foo<'(',')'>();

    return 0;
}
