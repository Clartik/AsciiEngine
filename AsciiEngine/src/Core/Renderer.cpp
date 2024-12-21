#include "Renderer.h"

#include "Application.h"

char Renderer::EMPTY_CHAR = ' ';

void Renderer::Init(char emptyChar)
{
	EMPTY_CHAR = emptyChar;

	Window& window = Application::Get().GetWindow();

	for (int row = 0; row < window.m_Height; row++)
	{
		for (int column = 0; column < window.m_Width; column++)
			window.m_ScreenBuffer[row * window.m_Width + column] = { EMPTY_CHAR, AsciiEngineColor::WHITE };
	}
}

void Renderer::Draw(const glm::ivec2& position, char printChar, const AsciiEngineColor& color)
{
	Window& window = Application::Get().GetWindow();

	if (window.IsDrawingOutOfBounds(position)) return;

	if (color != AsciiEngineColor::WHITE)
		window.m_ScreenBuffer[position.y * window.m_Width + position.x].Color = color;

	window.m_ScreenBuffer[position.y * window.m_Width + position.x].Character = printChar;
}

void Renderer::DrawString(const glm::ivec2& position, const std::string& printString, const AsciiEngineColor& color)
{
	Window& window = Application::Get().GetWindow();

	if (window.IsDrawingOutOfBounds(position)) return;

	int tempX = position.x;

	for (unsigned short i = 0; i < printString.size(); i++)
	{
		if (color != AsciiEngineColor::WHITE)
			window.m_ScreenBuffer[position.y * window.m_Width + tempX].Color = color;

		window.m_ScreenBuffer[position.y * window.m_Width + tempX].Character = printString[i];

		tempX++;
	}
}

void Renderer::DrawLine(const glm::ivec2& startPos, const glm::ivec2& endPos, char printChar, const AsciiEngineColor& color)
{
	Window& window = Application::Get().GetWindow();

	if (window.IsDrawingOutOfBounds(startPos)) return;
	if (window.IsDrawingOutOfBounds(endPos)) return;

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
			window.m_ScreenBuffer[y * window.m_Width + x] = { printChar, color };
		}
	}
	else if (dy > 0)
	{
		for (int y = y1; y <= y2; y++)
		{
			int x = x1 + dx * (y - y1) / dy;
			window.m_ScreenBuffer[y * window.m_Width + x] = { printChar, color };
		}
	}
}

bool Renderer::IsDrawingOutOfBounds(const glm::ivec2& position)
{
	Window& window = Application::Get().GetWindow();

	if (position.x < 0 || position.y < 0 || position.x > window.GetWidth() - 1 || position.y > window.GetHeight()  - 1)
	{
		Renderer::DrawString({ 0, 0 }, "[ERROR]: You Are Accessing Out of Bounds!", AsciiEngineColor::RED);
		return true;
	}

	return false;
}