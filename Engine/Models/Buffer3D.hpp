#pragma once
#include "Buffer2D.hpp"

template<class T, const size_t depth, const size_t width, const size_t height>
class Buffer3D
{
public:
	Buffer3D() = default;
	Buffer3D(const Buffer2D<T, width, height>* data, size_t dataSize);

	Buffer3D(std::initializer_list<Buffer2D<T, width, height>> initlist);

	Buffer2D<T, width, height>& operator[](size_t index);
	const Buffer2D<T, width, height>& operator[](size_t index) const;

	const Buffer2D<T, width, height>* data() const;

protected:
	Buffer2D<T, width, height> m_Parallelepiped[depth]{};
};

template<class T, size_t depth, size_t width, size_t height>
inline Buffer3D<T, depth, width, height>::Buffer3D(const Buffer2D<T, width, height>* data, size_t dataSize)
{
	for (size_t iter = NULL; iter < dataSize; iter++)
	{
		m_Parallelepiped[iter] = data[iter];
	}
}

template<class T, const size_t depth, const size_t width, const size_t height>
inline Buffer3D<T, depth, width, height>::Buffer3D(std::initializer_list<Buffer2D<T, width, height>> initlist)
{
	size_t i = 0;
	for (const auto& element : initlist)
	{
		if (i >= height)
		{
			break;
		}

		m_Parallelepiped[i++] = element;
	}
}

template<class T, const size_t depth, const size_t width, const size_t height>
inline Buffer2D<T, width, height>& Buffer3D<T, depth, width, height>::operator[](size_t index)
{
	return m_Parallelepiped[index];
}

template<class T, const size_t depth, const size_t width, const size_t height>
inline const Buffer2D<T, width, height>& Buffer3D<T, depth, width, height>::operator[](size_t index) const
{
	return m_Parallelepiped[index];
}

template<class T, const size_t depth, const size_t width, const size_t height>
inline const Buffer2D<T, width, height>* Buffer3D<T, depth, width, height>::data() const
{
	return m_Parallelepiped;
}