#pragma once

#include <glm/glm.hpp>
#include <string>

#include "Color.h"
#include "Window.h"

namespace AsciiEngine
{
	struct ScreenElement
	{
		char Character;
		Color Color;
	};

	class Renderer
	{
	public:
		static void Init(char emptyChar = ' ');

		static inline char GetEmptyChar() { return EMPTY_CHAR; }

		/// <summary>
		/// Adds Char to Draw Call
		/// </summary>
		/// <param name="position">The Position Where It Should Draw</param>
		/// <param name="printChar">The Character That Will Be Drawn</param>
		/// <param name="color">The Color of the Character</param>
		static void Draw(const glm::ivec2& position, char printChar, const Color& color = Color::WHITE);

		/// <summary>
		/// Adds the String to the Draw Call
		/// </summary>
		/// <param name="position">The Position Where It Should Draw</param>
		/// <param name="printString">The C++ String That Should Be Drawn</param>
		/// <param name="color">The Color of the Text</param>
		static void DrawString(const glm::ivec2& position, const std::string& printString, const Color& color = Color::WHITE);

		/// <summary>
		/// Adds a Line to the Draw Call
		/// </summary>
		/// <param name="startPos">The Start Position of the Line</param>
		/// <param name="endPos">The End Position of the Line</param>
		/// <param name="printChar">The Character That Will Be Drawn</param>
		/// <param name="color">The Color of the Character</param>
		static void DrawLine(const glm::ivec2& startPos, const glm::ivec2& endPos, char printChar, const Color& color = Color::WHITE);
	private:
		/// <summary>
		/// Checks If You Are Drawing Out of Bounds
		/// </summary>
		/// <param name="position">The Position</param>
		/// <returns>Whether You Are Drawing Out of Frame Or Not</returns>
		static bool IsDrawingOutOfBounds(const glm::ivec2& position);
	private:
		/// <summary>
		/// The Character of that is used to Render Whitespace
		/// </summary>
		static char EMPTY_CHAR;
	};
}