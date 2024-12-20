#include "Input.h"

#include <Windows.h>

bool Input::IsKeyPressed(const unsigned short& key)
{
	// toUpper Used Because KeyState Had a Hard Time Converting Chars to the Virtual Key Values
	return GetAsyncKeyState(toupper(key)) & 0x8000;
}
