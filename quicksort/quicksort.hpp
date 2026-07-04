#pragma once

#include <array>

template <
	int Pivot,
	int First,
	int... Rest
>
struct filter_gt_pivot {
	
};

template <int... Vs>
class QuickSort{
	static constexpr std::array data = { Vs... };
	static constexpr std::size_t size = sizeof...(Vs);
public:
	constexpr QuickSort() {
		calculate(std::make_index_sequence<size>{});
	}

	template <std::size_t... Is>
	constexpr void calculate(std::index_sequence<Is...>) {
		constexpr int pivot 
			= calculate_pivot<data[Is]...>();
		
		//calculate(std::index_sequence<(data[Is] < pivot ? Is)>);
	}

private:
	template <int... Vs>
	constexpr int calculate_pivot() {
		int first = data[0];
		int mid = data[size / 2];
		int last = data[size-1];

		if ((first < mid) != (first < last))
			return first;
		if ((mid < first) != (mid < last))
			return mid;

		return last;
	}
};

