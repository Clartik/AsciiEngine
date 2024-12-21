#include "Window.h"

#include <Windows.h>

#include <iostream>
#include <chrono>
#include <thread>

#include "Renderer.h"

namespace AsciiEngine
{
	Window::Window(int fps)
		: m_FPS(fps)
	{
		// Set Initial Width and Height to be One Less than Total Width to account for the 0th column/row
		glm::vec2 size = GetConsoleSize();
		m_Width = size.x - 1;
		m_Height = size.y - 1;

		Init();
	}

	Window::Window(const WindowProps& props)
		: m_Width(props.Width), m_Height(props.Height), m_FPS(props.FPS)
	{
		Init();
	}

	Window::~Window()
	{
		delete[] m_ScreenBuffer;
	}

	void Window::Init()
	{
		SetCursorVisiblity(false);

		float secondsPerFrame = 1.0f / m_FPS;
		m_MillisecondsPerFrame = secondsPerFrame * 1000;

		// 2D Array in 1D
		m_ScreenBuffer = new ScreenElement[m_Width * m_Height];
	}

	void Window::Render()
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

		CleanScreenBuffer();

		std::this_thread::sleep_for(std::chrono::milliseconds(m_MillisecondsPerFrame));
	}

	void Window::SetCursorVisiblity(const bool showFlag) const
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO cursorInfo;

		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = showFlag;
		SetConsoleCursorInfo(out, &cursorInfo);
	}

	glm::ivec2 Window::GetConsoleSize() const
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

		glm::ivec2 vec;
		vec.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		vec.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

		return vec;
	}

	bool Window::IsDrawingOutOfBounds(const glm::ivec2& position)
	{
		if (position.x < 0 || position.y < 0 || position.x > m_Width - 1 || position.y > m_Height - 1)
		{
			Renderer::DrawString({ 0, 0 }, "[ERROR]: You Are Accessing Out of Bounds!", AsciiEngineColor::RED);
			return true;
		}

		return false;
	}

	void Window::SetCursorPosition(const glm::ivec2& cursorPos)
	{
		COORD cPos;
		cPos.X = cursorPos.x;
		cPos.Y = cursorPos.y;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cPos);
	}

	void Window::CleanScreenBuffer()
	{
		// Refreshing Screen Buffer
		for (unsigned short row = 0; row < m_Height; row++)
		{
			for (unsigned short column = 0; column < m_Width; column++)
			{
				ScreenElement& element = m_ScreenBuffer[row * m_Width + column];
				element.Character = Renderer::GetEmptyChar();
				element.Color = AsciiEngineColor::WHITE;
			}
		}
	}

	void Window::SetColor(int8_t color)
	{
		WORD wColor;
		HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;

		if (!GetConsoleScreenBufferInfo(hConsoleOut, &csbi))
		{
			Renderer::DrawString({ 0, 0 }, "[ERROR]: You Are Accessing Out of Bounds!", AsciiEngineColor::RED);
			return;
		}

		wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
		SetConsoleTextAttribute(hConsoleOut, wColor);
	}
}