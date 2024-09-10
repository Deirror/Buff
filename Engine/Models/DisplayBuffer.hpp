#pragma once
#include "../Source/ConsoleHandler.h"
#include "../Source/winsize.h"
#include "Buffer2D.hpp"

template <const size_t width, const size_t height>
class DisplayBuffer : public Buffer2D<char, width, height>
{
public:
	DisplayBuffer() = default;
	DisplayBuffer(const Buffer<char, width>* data, size_t dataSize);

	DisplayBuffer(std::initializer_list<Buffer<char, width>> initlist);

	void displayContent(Console::Alignment alignment) const;

	const size_t getWidth() const;
	const size_t getHeight() const;

private:
	static_assert(width <= SCREEN_WIDTH, "Width must be less than  max screen width.");
	static_assert(height <= SCREEN_HEIGHT, "Height must be less than max screen height.");

	using Buffer2D<char, width, height>::m_Matrix;
};

template<const size_t width, const size_t height>
inline DisplayBuffer<width, height>::DisplayBuffer(const Buffer<char, width>* data, size_t dataSize)
	: Buffer2D<char, width, height>(data, dataSize) 
{

}

template<const size_t width, const size_t height>
inline DisplayBuffer<width, height>::DisplayBuffer(std::initializer_list<Buffer<char, width>> initlist)
	: Buffer2D<char, width, height>(initlist)
{

}

template<const size_t width, const size_t height>
inline void DisplayBuffer<width, height>::displayContent(Console::Alignment alignment) const
{
	for (size_t iter = 0; iter < height; iter++)
	{
		const Buffer<char, width>& content = m_Matrix[iter];

		if (!content.isEmpty())
		{
			Console::printLine(content.data(), alignment);
		}
	}
}

template<size_t width, size_t height>
inline const size_t DisplayBuffer<width, height>::getWidth() const
{
	return width;
}

template<size_t width, size_t height>
inline const size_t DisplayBuffer<width, height>::getHeight() const
{
	return height;
}
