#pragma once

#include <glm/glm.hpp>

#include "Color.h"

struct WindowProps
{
	unsigned int Width, Height;
	unsigned int FPS = 30;
};

class Window
{
public:
	Window(int fps);
	Window(const WindowProps& props);
	~Window();

	inline unsigned int GetWidth() const { return m_Width; }
	inline unsigned int GetHeight() const { return m_Height; }

	glm::ivec2 GetConsoleSize() const;

	/// <summary>
	/// Show or Hide the Console Cursor
	/// </summary>
	/// <param name="showFlag">Boolean that Controls The Console Cursor's Visibility</param>
	void SetCursorVisiblity(const bool showFlag) const;

	/// <summary>
	/// Renders Everything that is in the Draw Buffer
	/// </summary>
	void Render();
private:
	void Init();

	/// <summary>
	/// Checks If You Are Drawing Out of Bounds
	/// </summary>
	/// <param name="position">The Position</param>
	/// <returns>Whether You Are Drawing Out of Frame Or Not</returns>
	bool IsDrawingOutOfBounds(const glm::ivec2& position);

	/// <summary>
	/// Sets the Position Where the Engine Will Draw
	/// </summary>
	/// <param name="cursorPos">The Position Where the Engine Will Draw</param>
	/// <returns></returns>
	BOOL SetCursorPosition(const glm::ivec2& cursorPos);

	/// <summary>
	/// Sets the Text Color
	/// </summary>
	/// <param name="color">The Color Specified</param>
	void SetColor(int8_t color);

	/// <summary>
	/// Cleans the Screen Buffer
	/// </summary>
	void CleanScreenBuffer();
private:
	struct ScreenElement
	{
		char Character;
		AsciiEngineColor Color;
	};
private:
	/// <summary>
	/// Width and Height of Allocated Console Screen
	/// </summary>
	unsigned int m_Width, m_Height;

	/// <summary>
	/// The Amount of Frames Rendered Per Second
	/// </summary>
	int m_FPS;

	ScreenElement* m_ScreenBuffer;

	/// <summary>
	/// The Amount of Milliseconds it Takes for One Frame
	/// </summary>
	int m_MillisecondsPerFrame = 0;

	friend class Renderer;
};