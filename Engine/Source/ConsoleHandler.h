#pragma once
#include <Windows.h>
#include <atomic>

#define INVALID_COORD {-1, -1}

#define DEF_FOREGOUND_COLOR 0xF

#define DEF_SLEEP_TIME 50

namespace Console
{
	enum class Alignment : char
	{
		Left,
		Center,
		Right
	};

	void setConsoleFont(const wchar_t* fontName, short fontSize);

	void setConsoleSize(short width, short height);
	void setScrollbars(short width, short height);
	void changeVisibilityScrollbars(bool state);

	void disableQuickEditMode();

	void SetConsoleFontSize(short width, short height);

	void clearConsole();
	void clearConsole(short startRow, short endRow);

	void makeNotResizable();
	void removeMinimizedBox();
	void removeMaximizedBox();

	short getConsoleWidth();

	void changeVisibilityCursor(bool state);

	COORD getCursorPosition();
	void moveCursor(short x, short y);

	unsigned char getPressedKey();
	unsigned char getAtomicPressedKey(std::atomic<bool>& flag);

	void setConsoleColor(WORD color);
	void resetConsoleColor();

	void printSymbol(char symbol, short times);

	void printSymbolAt(short x, short y, char symbol);

	void printEmptyLine();
	void printEmptyLine(WORD color);

	void printString(const char* string, bool addNewLine = true);

	void printLine(const char* line, Alignment alignment = Alignment::Left, bool addNewLine = true);
	void printInThreeAlignments(const char* left, const char* center, const char* right, bool addNewLine = true, WORD color = DEF_FOREGOUND_COLOR);

	void printColoredLine(const char* line, WORD color);
}