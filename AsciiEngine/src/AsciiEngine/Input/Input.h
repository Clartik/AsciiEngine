#pragma once

#include "Keycodes.h"

#include "AsciiEngine/Math/Vector2.h"

namespace AsciiEngine
{
	class Input
	{
	public:
		/// <summary>
		/// Checks if the Key Entered Has Been Pressed
		/// </summary>
		/// <param name="key">Enter a Character/Number for Corresponding Keys or use VK_KEY for Virtual Keys</param>
		/// <returns></returns>
		static bool IsKeyPressed(Key key);

		static Vector2 GetMousePosition();
	};
}