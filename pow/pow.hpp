#pragma once

template <double Base, long Exp>
struct Pow {
	template <double P, double X, long N>
		requires(N < 0)
	constexpr static double calculate() noexcept {
		return 
			Pow<Base, Exp>
			::template calculate<
			(P),
			(1/X),
			(-N)
			>();
	}

	template <double P, double X, long N>
		requires(((N & 1) == 1) && (N > 0))
	constexpr static double calculate() noexcept {
		return 
			Pow<Base, Exp>
			::template calculate<
			(P*X),
			(X*X),
			(N >> 1)
			>();
	}

	template <double P, double X, long N>
		requires(((N & 1) == 0) && (N != 0) && (N > 0))
	constexpr static double calculate() noexcept {
		return 
			Pow<Base, Exp>
			::template calculate<
			(P),
			(X*X),
			(N >> 1)
			>();
	}

	template <double P, double X, long N>
		requires(N == 0)
	constexpr static double calculate() noexcept {
		return P;
	}

};

template <double X, long N>
inline constexpr double pow_v
	= Pow<X, N>
	::template calculate<
	1.0,
	X,
	N
	>();

