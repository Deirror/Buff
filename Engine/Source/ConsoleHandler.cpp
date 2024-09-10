#include "ConsoleHandler.h"
//------------------------
#include "specdefchars.h"
//------------------------
#include <stdexcept>
#include <iostream>
#include <conio.h>

static inline HWND console = GetConsoleWindow();
static inline HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
static inline CONSOLE_SCREEN_BUFFER_INFO csbi;

//Don't know why but when called twice removes scrollbars???
static void setConsoleSizeWithoutScrollBars(short width, short height)
{
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    SMALL_RECT r;
    r.Left = 0;
    r.Top = 0;
    r.Right = width - 1;
    r.Bottom = height - 1;
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &r);

    COORD bufferSize;
    bufferSize.X = width;
    bufferSize.Y = height;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), bufferSize);
}

void Console::setConsoleFont(const wchar_t* fontName, short fontSize)
{
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    fontInfo.nFont = 0;
    fontInfo.dwFontSize.X = 0;
    fontInfo.dwFontSize.Y = fontSize;
    fontInfo.FontFamily = FF_DONTCARE;
    fontInfo.FontWeight = FW_NORMAL;
    wcscpy_s(fontInfo.FaceName, fontName);

    SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
}

void Console::setConsoleSize(short width, short height)
{
    setConsoleSizeWithoutScrollBars(width, height);
    setConsoleSizeWithoutScrollBars(width, height);
}

void Console::disableQuickEditMode()
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

    DWORD prev_mode;
    GetConsoleMode(hInput, &prev_mode);

    SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}

void Console::SetConsoleFontSize(short width, short height)
{
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);

    cfi.dwFontSize.X = width;
    cfi.dwFontSize.Y = height;

    SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

void Console::setScrollbars(short width, short height)
{
    COORD bufferSize;
    bufferSize.X = width;
    bufferSize.Y = height;

    SetConsoleScreenBufferSize(hConsole, bufferSize);

    SMALL_RECT windowSize;
    windowSize.Left = 0;
    windowSize.Top = 0;
    windowSize.Right = width - 1;
    windowSize.Bottom = height / 2;

    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

void Console::changeVisibilityScrollbars(bool state)
{
    ShowScrollBar(console, SB_VERT, state);
    ShowScrollBar(console, SB_HORZ, state);
}

void Console::clearConsole()
{
    system("cls");
}

void Console::clearConsole(short startRow, short endRow)
{
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    short consoleWidth = getConsoleWidth();

    for (short row = startRow; row <= endRow; ++row)
    {
        COORD coord = { 0, static_cast<SHORT>(row) };

        SetConsoleCursorPosition(hConsole, coord);

        for (int col = 0; col < consoleWidth; ++col) 
        {
            std::cout << Symbols::ce_WhiteSpace;
        }
    }

    COORD resetPos = { 0, static_cast<SHORT>(startRow) };
    SetConsoleCursorPosition(hConsole, resetPos);
}

void Console::makeNotResizable()
{
    LONG style = GetWindowLong(console, GWL_STYLE);
    style &= ~WS_SIZEBOX;

    SetWindowLong(console, GWL_STYLE, style);
}

void Console::removeMinimizedBox()
{
    LONG style = GetWindowLong(console, GWL_STYLE);
    style &= ~WS_MINIMIZEBOX;
    SetWindowLong(console, GWL_STYLE, style);
}

void Console::removeMaximizedBox()
{
    LONG style = GetWindowLong(console, GWL_STYLE);
    style &= ~WS_MAXIMIZEBOX;
    SetWindowLong(console, GWL_STYLE, style);
}

short Console::getConsoleWidth()
{
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    short columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    return columns;
}

void Console::changeVisibilityCursor(bool state)
{
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = state;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

COORD Console::getCursorPosition()
{
    if (GetConsoleScreenBufferInfo(hConsole, &csbi))
    {
        return csbi.dwCursorPosition;
    }
    else
    {
        return INVALID_COORD;
    }
}

void Console::moveCursor(short x, short y)
{
    COORD pos;
    pos.X = x;
    pos.Y = y;

    SetConsoleCursorPosition(hConsole, pos);
}

unsigned char Console::getPressedKey()
{
    while (TRUE)
    {
        if (_kbhit())
        {
            return _getch();
        }

        Sleep(DEF_SLEEP_TIME);
    }
}

unsigned char Console::getAtomicPressedKey(std::atomic<bool>& flag)
{
    while (!flag)
    {
        if (_kbhit())
        {
            return _getch();
        }

        Sleep(DEF_SLEEP_TIME);
    }

    return 0;
}

void Console::printSymbol(char symbol, short times)
{
    for (short iter = 0; iter < times; iter++)
    {
        std::cout << symbol;
    }
}

void Console::printSymbolAt(short x, short y, char symbol)
{
    Console::moveCursor(x, y);
    std::cout << symbol;
    Console::moveCursor(x - 1, y);
}

void Console::printEmptyLine()
{
    printSymbol(Symbols::ce_WhiteSpace, getConsoleWidth());
}

void Console::printEmptyLine(WORD color)
{
    setConsoleColor(color);
    printEmptyLine();
    resetConsoleColor();
}

void Console::printString(const char* string, bool addNewLine)
{
    std::cout << string;

    if (addNewLine)
    {
        std::cout << Symbols::ce_NewLine;
    }    
}

void Console::printColoredLine(const char* line, WORD color)
{
    if (!line)
    {
        throw std::invalid_argument("Nullptr");
    }

    setConsoleColor(color);
    std::cout << line;
    resetConsoleColor();
}

void Console::setConsoleColor(WORD color)
{
    SetConsoleTextAttribute(hConsole, color);
}

void Console::resetConsoleColor()
{
    setConsoleColor(DEF_FOREGOUND_COLOR);
}

void Console::printLine(const char* line, Alignment alignment, bool addNewLine)
{
    if (!line)
    {
        throw std::invalid_argument("Nullptr");
    }

    switch (alignment)
    {
    case Console::Alignment::Left:
    {
        printString(line, addNewLine);
        break;
    }
    case Console::Alignment::Center:
    {
        size_t padding = (getConsoleWidth() - strlen(line)) / 2;

        if (padding > 0)
        {
            printSymbol(Symbols::ce_WhiteSpace, padding);          
        }

        printString(line, addNewLine);
        break;
    }
    case Console::Alignment::Right:
    {
        short consoleWidth = getConsoleWidth();

        short textLength = strlen(line);
        short times = consoleWidth - textLength;

        printSymbol(Symbols::ce_WhiteSpace, times);

        printString(line, addNewLine);
        break;
    }
    }
}

void Console::printInThreeAlignments(const char* left, const char* center, const char* right, bool addNewLine, WORD color)
{
    Console::setConsoleColor(color);
    Console::printLine(right, Console::Alignment::Right, addNewLine);
    Console::moveCursor(0, Console::getCursorPosition().Y);
    Console::printLine(center, Console::Alignment::Center, addNewLine);
    Console::moveCursor(0, Console::getCursorPosition().Y);
    Console::printLine(left, Console::Alignment::Left, addNewLine);
    Console::resetConsoleColor();
}