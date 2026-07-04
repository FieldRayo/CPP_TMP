#pragma once

#include <array>

constexpr std::ptrdiff_t MAX = 1000;

class DSU {
    std::array<std::ptrdiff_t, MAX> data;
public:
    constexpr DSU()
    noexcept
    {
        [&]<std::size_t... Is>(
            std::index_sequence<Is...>
        ){
            (
             (data[Is] = -1),
             ...
            );
        }(
            std::make_index_sequence<MAX>{}
         );
    }

    constexpr std::size_t find(std::size_t x) 
        const noexcept
    {
        if (data[x] < 0)
            return x;

        return find(static_cast<std::size_t>(data[x]));
    }
    
    template <std::ptrdiff_t U,
              std::ptrdiff_t V>
    constexpr DSU merge() 
        const 
    {
        auto copy = *this;

        auto u = copy.find(U);
        auto v = copy.find(V);

        if (u == v)
            return copy;

        if (copy.data[u] > copy.data[v])
            std::swap(u, v);

        copy.data[u] += copy.data[v];
        copy.data[v] = static_cast<std::ptrdiff_t>(u);

        return copy;
    }


};

