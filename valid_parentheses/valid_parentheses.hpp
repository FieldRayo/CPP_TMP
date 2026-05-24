#pragma once

#include <array>

template <std::size_t N>
struct FixedString;

template <std::size_t N>
struct FixedString {
    std::array<char, N> data;
    static constexpr std::size_t size = N - 1;

    constexpr FixedString(
        const char (&str)[N]
    ) noexcept {
        for (std::size_t i{0}; i < N; ++i)
            data[i] = str[i];
    }

    constexpr char operator[](
        std::size_t index
    ) const noexcept {
        return data[index];
    }
};

template <typename T, std::size_t N>
class Stack;

template <typename T, std::size_t N>
class Stack {
    std::array<T, N> data;
    std::size_t top=0;
public:
    constexpr Stack(
        const std::array<T, N>& arr = {}
    ) noexcept
        : data(arr) {}

    constexpr void push(T value) noexcept {
        data[top++] = value;
    }

    constexpr T pop() noexcept {
        T value = data[--top];
        data[top] = {};
        return value;
    }

    constexpr T get_top() const {
        if (top)
            return data[top-1];

        return data[top];
    }

    constexpr bool empty() const {
        return top == 0;
    }

};

template <
    FixedString S,
    std::size_t I = 0
>
constexpr bool parse(
    auto& stack
) noexcept {
    if constexpr (I == S.size)
        return stack.empty();
    else {
        constexpr char c = S[I];

        if constexpr (
            c == '(' ||
            c == '{' ||
            c == '['
        ) {
            stack.push(c);

            return 
                parse<S, I + 1>(stack);

        } else {
            if (stack.empty())
                return false;

            char top = stack.pop();

            if (
                (c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '[')
               ) {
                return false;
            }

            return 
                parse<S, I + 1>(stack);
        }
    }
}

template <FixedString S>
constexpr bool is_valid() noexcept {
    Stack<char, S.size> stack;
    return parse<S>(stack);
}

