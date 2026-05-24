#pragma once

#include <cstdint>
#include <array>

template <int>
class digits;

template <int N> requires(N >= 10)
class digits<N>
{
public:
	static constexpr std::size_t size() 
		noexcept
	{
		return
			1 + digits<N / 10>::size();
	}

	template <std::size_t Index>
		requires(Index < size())
	static constexpr char get()
		noexcept
	{
		if constexpr (Index == size() - 1)
			return '0' + (N % 10);
		else
			return digits<N / 10>::template get<Index>();
	}
};

template <int N> 
	requires((N >= 0) && (N < 10))
class digits<N> 
{
public:
	static constexpr std::size_t size()
		noexcept
	{
		return 1;
	}

	template <std::size_t Index>
		requires(Index == 0)
	static constexpr char get()
		noexcept
	{
		return '0' + N;
	}

};

template <int N>
constexpr auto to_string() noexcept {
	constexpr std::size_t size 
		= digits<N>::size();

	return []<std::size_t... Is>(
		std::index_sequence<Is...>
	) {
		std::array<char, size + 1> str;
		((str[Is]
		  = digits<N>::template get<Is>()),
		 ...);

		str[size] = '\0';
		return str;
	}(std::make_index_sequence<size>{});
}

template <std::size_t Capacity>
	requires(Capacity > 0)
constexpr auto reverse_string(
	const std::array<char, Capacity>& str
) {
	std::array<char, Capacity> rev_str;

	for (std::size_t i{0}; i < Capacity - 1; ++i)
		rev_str[i] = str[Capacity - 2 - i];

	rev_str[Capacity - 1] = '\0';

	return rev_str;
}

template<int N>
constexpr bool is_palindrome_v 
	= (to_string<N>() 
	== reverse_string(to_string<N>()));

