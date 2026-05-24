#include <iostream>
#include <cstdint>
#include <array>

template <int>
struct digits;

template <int Number>
	requires(Number >= 10)
struct digits<Number> {
	static constexpr std::size_t size()
		noexcept
	{
		return 
			1 + digits<Number / 10>::size();
	}

	template <std::size_t Index>
		requires (Index < size())
	static constexpr char get()
		noexcept
	{
		if constexpr (Index == size() - 1)
			return '0' + (Number % 10);
		else
			return digits<Number / 10>
				::template get<Index>();
	}
};

template <int Number>
	requires((Number >= 0) && (Number < 10))
struct digits<Number> {
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
		return '0' + Number;
	}
};

template <int Number>
constexpr auto to_string() noexcept {
	constexpr std::size_t size 
		= digits<Number>::size();

	return []<std::size_t... Is>(
		std::index_sequence<Is...>
	) {
		std::array<char, size> str;
		((str[Is] = digits<Number>::template get<Is>()), ...);

		return str;

	}(std::make_index_sequence<size>{});
}	

template <std::size_t Size>
constexpr auto reverse_string(
		const std::array<char, Size>& str
) {
	std::array<char, Size> rev_str;
	for (std::size_t i{0}; i < Size; i++)
		rev_str[i] = str[Size - 1 - i];

	return rev_str;
}

template <int Number>
constexpr bool is_palindrome_v
	= to_string<Number>()
	== reverse_string(to_string<Number>());

int main (int argc, char *argv[])
{
	constexpr auto b1 = is_palindrome_v<999>,
				   b2 = is_palindrome_v<932>;

	static_assert(b1 && !b2, "x");
	
	return 0;
}
