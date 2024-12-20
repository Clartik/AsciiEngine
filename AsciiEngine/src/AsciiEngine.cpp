#include "AsciiEngine.h"

#include <iostream>
#include <chrono>
#include <thread>

AsciiEngine::AsciiEngine(const AsciiEngineProps& props)
	: m_Width(props.Width), m_Height(props.Height), m_FPS(props.FPS)
{
	Init();
}

AsciiEngine::AsciiEngine(int fps)
	: m_FPS(fps)
{
	// Set Initial Width and Height to be One Less than Total Width to account for the 0th column/row
	glm::vec2 size = GetConsoleSize();
	m_Width = size.x - 1;
	m_Height = size.y - 1;

	Init();
}

AsciiEngine::~AsciiEngine()
{
	delete[] m_ScreenBuffer;
}

void AsciiEngine::Init()
{
	ShowConsoleCursor(false);

	float secondsPerFrame = 1.0f / m_FPS;
	m_MillisecondsPerFrame = secondsPerFrame * 1000;

	// 2D Array in 1D
	m_ScreenBuffer = new ScreenElement[m_Width * m_Height];

	for (int row = 0; row < m_Height; row++)
	{
		for (int column = 0; column < m_Width; column++)
			m_ScreenBuffer[row * m_Width + column] = { m_EmptyChar, Color::WHITE };
	}
}

glm::ivec2 AsciiEngine::GetConsoleSize() const
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	glm::ivec2 vec;
	vec.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	vec.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	return vec;
}

BOOL AsciiEngine::SetCursorPosition(const glm::ivec2& cursorPos)
{
	COORD cPos;
	cPos.X = cursorPos.x;
	cPos.Y = cursorPos.y;

	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cPos);
}

bool AsciiEngine::IsKeyPressed(const unsigned short& key) const
{
	// toUpper Used Because KeyState Had a Hard Time Converting Chars to the Virtual Key Values
	return GetAsyncKeyState(toupper(key)) & 0x8000;
}

void AsciiEngine::Draw(const glm::ivec2& position, char printChar, const Color& color)
{
	if (IsDrawingOutOfBounds(position)) return;

	if (color != Color::WHITE)
		m_ScreenBuffer[position.y * m_Width + position.x].Color = color;

	m_ScreenBuffer[position.y * m_Width + position.x].Character = printChar;
}

void AsciiEngine::DrawString(const glm::ivec2& position, const std::string& printString, const Color& color)
{
	if (IsDrawingOutOfBounds(position)) return;

	int tempX = position.x;

	for (unsigned short i = 0; i < printString.size(); i++)
	{
		if (color != Color::WHITE)
			m_ScreenBuffer[position.y * m_Width + tempX].Color = color;

		m_ScreenBuffer[position.y * m_Width + tempX].Character = printString[i];

		tempX++;
	}
}

void AsciiEngine::DrawLine(const glm::ivec2& startPos, const glm::ivec2& endPos, char printChar, const Color& color)
{
	if (IsDrawingOutOfBounds(startPos)) return;
	if (IsDrawingOutOfBounds(endPos)) return;

	bool endPosXLarger = endPos.x > startPos.x;
	int x1 = endPosXLarger ? startPos.x : endPos.x;
	int x2 = endPosXLarger ? endPos.x : startPos.x;

	bool endPosYLarger = endPos.y > startPos.y;
	int y1 = endPosYLarger ? startPos.y : endPos.y;
	int y2 = endPosYLarger ? endPos.y : startPos.y;

	int dx = x2 - x1;
	int dy = y2 - y1;

	if (dx > 0)
	{
		for (int x = x1; x <= x2; x++)
		{
			int y = y1 + dy * (x - x1) / dx;
			m_ScreenBuffer[y * m_Width + x] = { printChar, color };
		}
	}
	else if (dy > 0)
	{
		for (int y = y1; y <= y2; y++)
		{
			int x = x1 + dx * (y - y1) / dy;
			m_ScreenBuffer[y * m_Width + x] = { printChar, color };
		}
	}
}

void AsciiEngine::Render()
{
	// Drawing From the Start
	SetCursorPosition(glm::vec2(0, 0));

	// Render on Screen
	for (unsigned short row = 0; row < m_Height; row++)
	{
		for (unsigned short column = 0; column < m_Width; column++)
		{
			SetColor((int)m_ScreenBuffer[row * m_Width + column].Color);
			std::cout << m_ScreenBuffer[row * m_Width + column].Character;
		}
		std::cout << std::endl;
	}

	// Clear Buffers
	CleanScreenBuffer();
	CleanColorBuffer();
}

void AsciiEngine::ShowConsoleCursor(const bool showFlag) const
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;
	
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

bool AsciiEngine::IsDrawingOutOfBounds(const glm::ivec2& position)
{
	if (position.x < 0 || position.y < 0 || position.x > m_Width - 1 || position.y > m_Height - 1)
	{
		DrawString({ 0, 0 }, "[ERROR]: You Are Accessing Out of Bounds!", Color::RED);
		return true;
	}

	return false;
}

void AsciiEngine::CleanScreenBuffer()
{
	// Refreshing Screen Buffer
	for (unsigned short row = 0; row < m_Height; row++)
	{
		for (unsigned short column = 0; column < m_Width; column++)
		{
			m_ScreenBuffer[row * m_Width + column].Character = m_EmptyChar;
		}
	}
}

void AsciiEngine::CleanColorBuffer()
{
	// Refreshing Color Buffer
	for (unsigned short row = 0; row < m_Height; row++)
	{
		for (unsigned short column = 0; column < m_Width; column++)
		{
			m_ScreenBuffer[row * m_Width + column].Color = Color::WHITE;
		}
	}
}

void AsciiEngine::SetColor(int8_t color)
{
	WORD wColor;
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (!GetConsoleScreenBufferInfo(hConsoleOut, &csbi))
	{
		DrawString({ 0, 0 }, "[ERROR]: You Are Accessing Out of Bounds!", Color::RED);
		return;
	}

	wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
	SetConsoleTextAttribute(hConsoleOut, wColor);
}

void AsciiEngine::Run()
{
	while (m_Running)
	{
		OnUpdate();

		Render();
		std::this_thread::sleep_for(std::chrono::milliseconds(m_MillisecondsPerFrame));
	}
}