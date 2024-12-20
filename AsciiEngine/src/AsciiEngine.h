#pragma once

#include <Windows.h>
#include <string>

#include <glm/glm.hpp>

struct AsciiEngineProps
{
	unsigned int Width, Height;
	unsigned int FPS = 30;
};

class AsciiEngine
{
public:
	enum class Color
	{
		BLACK = 0,
		DARKBLUE = FOREGROUND_BLUE,
		DARKGREEN = FOREGROUND_GREEN,
		DARKCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
		DARKRED = FOREGROUND_RED,
		DARKMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
		DARKYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
		DARKGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		GRAY = FOREGROUND_INTENSITY,
		BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
		MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	};
public:
	/// <summary>
	/// Default Constructor
	/// </summary>
	/// <param name="props">The Properties of the Engine</param>
	AsciiEngine(const AsciiEngineProps& props);

	/// <summary>
	/// Default Constructor
	/// </summary>
	/// <param name="emptyChar">The Character of the Empty Area</param>
	AsciiEngine(int fps = 30);

	~AsciiEngine();

	inline unsigned int GetWidth() const { return m_Width; }
	inline unsigned int GetHeight() const { return m_Height; }

	glm::ivec2 GetConsoleSize() const;

	/// <summary>
	/// Says if the Engine is Running. Should Be Used in the While Loop
	/// </summary>
	/// <returns>Whether the Engine is Running or Not</returns>
	inline bool IsRunning() const { return m_Running; }

	/// <summary>
	/// Checks if the Key Entered Has Been Pressed
	/// </summary>
	/// <param name="key">Enter a Character/Number for Corresponding Keys or use VK_KEY for Virtual Keys</param>
	/// <returns></returns>
	bool IsKeyPressed(const unsigned short& key) const;

	/// <summary>
	/// Show or Hide the Console Cursor
	/// </summary>
	/// <param name="showFlag">Boolean that Controls The Console Cursor's Visibility</param>
	void ShowConsoleCursor(const bool showFlag) const;

	inline void SetEmptyChar(char emtpyChar) { m_EmptyChar = emtpyChar; }

	/// <summary>
	/// Adds Char to Draw Call
	/// </summary>
	/// <param name="position">The Position Where It Should Draw</param>
	/// <param name="printChar">The Character That Will Be Drawn</param>
	/// <param name="color">The Color of the Character</param>
	void Draw(const glm::ivec2& position, char printChar, const Color& color=Color::WHITE);

	/// <summary>
	/// Adds the String to the Draw Call
	/// </summary>
	/// <param name="position">The Position Where It Should Draw</param>
	/// <param name="printString">The C++ String That Should Be Drawn</param>
	/// <param name="color">The Color of the Text</param>
	void DrawString(const glm::ivec2& position, const std::string& printString, const Color& color=Color::WHITE);

	/// <summary>
	/// Adds a Line to the Draw Call
	/// </summary>
	/// <param name="startPos">The Start Position of the Line</param>
	/// <param name="endPos">The End Position of the Line</param>
	/// <param name="printChar">The Character That Will Be Drawn</param>
	/// <param name="color">The Color of the Character</param>
	void DrawLine(const glm::ivec2& startPos, const glm::ivec2& endPos, char printChar, const Color& color = Color::WHITE);

	/// <summary>
	/// Renders Everything that is in the Draw Buffer
	/// </summary>
	void Render();

	/// <summary>
	/// Virtual Function that Can Be Overridden to Modify Any Behavior
	/// </summary>
	virtual void OnUpdate() { }

	void Run();

	/// <summary>
	/// Stops the Engine From Running
	/// </summary>
	inline void Stop() { m_Running = false; }
private:
	void Init();

	/// <summary>
	/// Sets the Position Where the Engine Will Draw
	/// </summary>
	/// <param name="cursorPos">The Position Where the Engine Will Draw</param>
	/// <returns></returns>
	BOOL SetCursorPosition(const glm::ivec2& cursorPos);
	/// <summary>
	/// Checks If You Are Drawing Out of Bounds
	/// </summary>
	/// <param name="position">The Position</param>
	/// <returns>Whether You Are Drawing Out of Frame Or Not</returns>
	bool IsDrawingOutOfBounds(const glm::ivec2& position);
	/// <summary>
	/// Cleans the Screen Buffer
	/// </summary>
	void CleanScreenBuffer();
	/// <summary>
	/// Cleans the Color Buffer
	/// </summary>
	void CleanColorBuffer();
	/// <summary>
	/// Sets the Text Color
	/// </summary>
	/// <param name="color">The Color Specified</param>
	void SetColor(int8_t color);
private:
	/// <summary>
	/// Width and Height of Allocated Console Screen
	/// </summary>
	unsigned int m_Width, m_Height;

	/// <summary>
	/// The Amount of Frames Rendered Per Second
	/// </summary>
	int m_FPS;

	/// <summary>
	/// The Character of that is used to Render Whitespace
	/// </summary>
	char m_EmptyChar = ' ';

	/// <summary>
	/// Whether the Engine is Running or Not
	/// </summary>
	bool m_Running = true;

	/// <summary>
	/// The Amount of Milliseconds it Takes for One Frame
	/// </summary>
	int m_MillisecondsPerFrame = 0;

	struct ScreenElement
	{
		char Character;
		Color Color;
	};

	ScreenElement* m_ScreenBuffer;
};