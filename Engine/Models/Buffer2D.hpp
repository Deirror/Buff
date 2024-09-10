#pragma once
#include "Buffer.hpp"

template<class T, const size_t width, const size_t height>
class Buffer2D
{
public:
	Buffer2D() = default;
	Buffer2D(const Buffer<T, width>* data, size_t dataSize);

	Buffer2D(std::initializer_list<Buffer<T, width>> initlist);

	Buffer<T, width>& operator[](size_t index);
	const Buffer<T, width>& operator[](size_t index) const;

	const Buffer<T, width>* data() const;

protected:
	Buffer<T, width> m_Matrix[height]{};
};

template<class T, const size_t width, const size_t height>
inline Buffer2D<T, width, height>::Buffer2D(const Buffer<T, width>* data, size_t dataSize)
{
	for (size_t iter = NULL; iter < dataSize; iter++)
	{
		m_Matrix[iter] = data[iter];
	}
}

template<class T, const size_t width, const size_t height>
inline Buffer2D<T, width, height>::Buffer2D(std::initializer_list<Buffer<T, width>> initlist)
{
	size_t i = 0;
	for (const auto& element : initlist)
	{
		if (i >= height)
		{
			break;
		}

		m_Matrix[i++] = element;
	}
}

template<class T, const size_t width, const size_t height>
inline Buffer<T, width>& Buffer2D<T, width, height>::operator[](size_t index)
{
	return m_Matrix[index];
}

template<class T, const size_t width, const size_t height>
inline const Buffer<T, width>& Buffer2D<T, width, height>::operator[](size_t index) const
{
	return m_Matrix[index];
}

template<class T, const size_t width, const size_t height>
inline const Buffer<T, width>* Buffer2D<T, width, height>::data() const
{
	return m_Matrix;
}