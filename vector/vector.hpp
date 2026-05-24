#pragma once

#include <cstdint>
#include <memory>
#include <iostream>

constexpr std::size_t bit_ceil(
		std::size_t n
) noexcept
{
	if (n <= 1)
		return 1;

	n--;

	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;

	if constexpr (sizeof(std::size_t) == 8)
		n |= n >> 32;

	return n + 1; 
}

template <typename T>
class Vector {
	T* m_Data {};
	std::size_t m_Size {};
	std::size_t m_Capacity {};
public:
	Vector() = default;
	Vector(std::size_t size) 
		: 
			m_Data(new T[size]),
			m_Size(size),
			m_Capacity(size)
	{}

	Vector(const Vector&) = delete;				
	Vector& operator=(const Vector&) = delete;	

	Vector(Vector&& other) noexcept 
		:
			m_Data(other.m_Data),
			m_Size(other.m_Size),
			m_Capacity(other.m_Capacity)
	{
		other.m_Data = nullptr;
		other.m_Size = 0;
		other.m_Capacity = 0;
	}
	Vector& operator=(Vector&& other) noexcept {
		if (this == &other)
			return *this;

		delete[] m_Data;

		m_Data = other.m_Data;
		m_Size = other.m_Size;
		m_Capacity = other.m_Capacity;

		other.m_Data = nullptr;
		other.m_Size = 0;
		other.m_Capacity = 0;

		return *this;
	}		

	void push_back(const T& value) {
		if (m_Size >= m_Capacity)
			reallocate();

		m_Data[m_Size] = value;
		m_Size++;
	}

	void push_back(T&& value) {
		if (m_Size >= m_Capacity)
			reallocate();

		m_Data[m_Size] = std::move(value);
		m_Size++;
	}

	T& operator[](std::size_t index) { return m_Data[index]; }
	const T& operator[](std::size_t index) const { return m_Data[index]; }

	const T* begin() const { return m_Data; }
	const T* end() const { return m_Data + m_Size; }
	
	T* begin() { return m_Data; }
	T* end() { return m_Data + m_Size; }

	~Vector() {
		delete[] m_Data;
	}

private:
	void reallocate() {
		std::size_t new_capacity = bit_ceil(m_Size + 1); 
		
		auto new_data = std::make_unique<T[]>(new_capacity);
		
		for (std::size_t i{0}; i < m_Size; ++i)
			new_data[i] = std::move(m_Data[i]);

		delete[] m_Data;

		m_Data = new_data.release();
		m_Capacity = new_capacity;
	}
};
