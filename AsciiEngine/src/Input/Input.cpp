#include "Input.h"

#include <Windows.h>

bool Input::IsKeyPressed(Key key)
{
	// toUpper Used Because KeyState Had a Hard Time Converting Chars to the Virtual Key Values
	int vKey = toupper(short(key));

	return GetAsyncKeyState(vKey) & 0x8000;
}
