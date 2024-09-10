#pragma once
#include "../Source/specdefchars.h"
//---------------------------------
#include <initializer_list>

template <class T, const size_t size>
class Buffer
{
public:
	Buffer() = default;
	Buffer(const T* data, size_t dataSize);

	Buffer(std::initializer_list<T> initlist);

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	const T* data() const;

private:
	T m_Data[size]{};
};

template<class T, const size_t size>
inline Buffer<T, size>::Buffer(const T* data, size_t dataSize)
{
	for (size_t iter = 0; iter < dataSize; iter++)
	{
		m_Data[iter] = data[iter];
	}
}

template<class T, const size_t size>
inline Buffer<T, size>::Buffer(std::initializer_list<T> initlist)
{
	size_t i = 0;
	for (const T& element : initlist)
	{
		if (i >= size)
		{
			break;
		}

		m_Data[i++] = element;
	}
}

template<class T, const size_t size>
inline T& Buffer<T, size>::operator[](size_t index)
{
	return m_Data[index];
}

template<class T, const size_t size>
inline const T& Buffer<T, size>::operator[](size_t index) const
{
	return m_Data[index];
}

template<class T, const size_t size>
inline const T* Buffer<T, size>::data() const
{
	return m_Data;
}


//template specialization for char
#include <cstring>
#pragma warning(disable : 4996)

template <const size_t size>
class Buffer<char, size>
{
public:
	Buffer() = default;
	Buffer(const char* data);

	char& operator[](size_t index);
	const char& operator[](size_t index) const;

	bool isEmpty() const;

	const char* data() const;

private:
	char m_Data[size + 1]{};
};

template<const size_t size>
Buffer<char, size>::Buffer(const char* data)
{
	std::strncpy(m_Data, data, size);
}

template<const size_t size>
inline char& Buffer<char, size>::operator[](size_t index)
{
	return m_Data[index];
}

template<const size_t size>
inline const char& Buffer<char, size>::operator[](size_t index) const
{
	return m_Data[index];
}

template<size_t size>
inline bool Buffer<char, size>::isEmpty() const
{
	return m_Data[0] == Symbols::ce_TermNull;
}

template<const size_t size>
inline const char* Buffer<char, size>::data() const
{
	return m_Data;
}