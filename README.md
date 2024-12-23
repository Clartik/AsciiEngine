# AsciiEngine
An easy to use rendering engine for the Windows Console.
Originally made for a solo project in 2022 but now is repurposed as an easy tool for anyone to quickly make graphics in the console window.

## Installing (Git Clone)
1. Git Clone Repository
2. Run Scripts/Setup-Windows.bat to Generate Files
3. Open Solution and Done!

**Ensure to separate the Engine from the Sandbox for more modular design and less spagetti code.**

## Installing (Static Library)
1. Head to Releases Section on this Repository
2. Download Latest Release
3. Follow the Setup Instructions on There

## Quick Example
```cpp
#include "AsciiEngine.h"

// Make a subclass to add custom behavior
class CustomApp : public AsciiEngine::Application 
{
public:
    CustomApp(const AsciiEngine::WindowProps& props)
        : AsciiEngine::Application(props)  {}

    // Called once a frame
    // Override function to add any custom behavior that needs to be drawn
    virtual void OnUpdate() override 
    {
        // Draw Box
        AsciiEngine::Renderer::DrawLine({ 0, 0 }, { 20, 0 }, '#');
        AsciiEngine::Renderer::DrawLine({ 20, 0 }, { 20, 10 }, '#');
        AsciiEngine::Renderer::DrawLine({ 20, 10 }, { 0, 10 }, '#');
        AsciiEngine::Renderer::DrawLine({ 0, 10 }, { 0, 0 }, '#');

        AsciiEngine::Renderer::Draw(playerPos, 'X');

        // Move Left to Right
        if (playerPos.y == 2 && playerPos.x < 18)
            playerPos.x++;
        // Move Up to Down
        else if (playerPos.x == 18 && playerPos.y < 8)
            playerPos.y++;
        // Move Right to Left
        else if (playerPos.y == 8 && playerPos.x > 2)
            playerPos.x--;
        // Move Down to Up
        else if (playerPos.x == 2 && playerPos.y > 2)
            playerPos.y--;
    }
private:
    // Start inside the box
    AsciiEngine::Vector2 playerPos = { 2, 2 };
}

int main() 
{
    AsciiEngine::Application* app = new CustomApp({22, 12});
    app->Run();
    delete app;
}
```

## Documentation

#### Application

##### Constructors
The width and height of the canvas will be set to the size of the Console.

```cpp
Application(unsigned int fps = 30) 
{
}
```

Used to control the width and height of the canvas.
```cpp
Application(const WindowsProps& props) 
{
}
```

You can use the WindowsProps to control the width, height, and framerate of the application.
```cpp
struct WindowsProps 
{
    unsigned int Width, Height, FPS;
}
```

##### Get Instances
Use Get from Application class to get the static instance of Application.
```cpp
static Application& Get() 
{
}
```

Use GetWindow from Application class to get the running instance of the Window.
```cpp
Window& GetWindow() 
{
}
```

Gives a boolean that tells you if the Engine is still running or not.
```cpp
bool IsRunning() const
{
}
```

##### Control Behavior
The OnUpdate function is called once per frame. Override this function if anything should be renderered every frame.
```cpp
virtual void OnUpdate() override
{
}
```

The Stop function stops the entire engine from running.
```cpp
void Stop()
{
}
```

#### Main
If you are to create a subclass of Application to add additional behavior, you can still cast it to the regular AsciiEngine's Application as seen below.
```cpp
int main()
{
	AsciiEngine::Application* app = new CustomEngine({ 22, 16 });
	app->Run();
	delete app;
}
```

#### Window
Window class stores the ScreenBuffer used to render anything onto the console screen.

```cpp
struct ScreenElement
{
	char Character;
	Color Color;
};
```

##### Get Functions

Get the width of the ScreenBuffer
```cpp
unsigned int GetWidth() const
{
}
```

Get the height of the ScreenBuffer
```cpp
unsigned int GetHeight() const
{
}
```

Get the width and length of the ScreenBuffer in Vector2 form.

```cpp
Vector2 GetConsoleSize() const
{
}
```

Control the visibility of the text cursor
```cpp
void SetCursorVisiblity(const bool showFlag) const
{
}
```

#### Renderer
All functions in the Renderer are static. Ensure to call the Renderer after the Engine's constructor was called.

Draws a single character on screen.
```cpp
static void Draw(const AsciiEngine::Vector2& position, char printChar, const Color& color = Color::WHITE)
{
}
```

Draws a string of text on screen.
```cpp
static void DrawString(const AsciiEngine::Vector2& position, const std::string& printString, const Color& color = Color::WHITE);
{
}
```

Draws a line on screen by controlling the start and end position of the line.
```cpp
static void DrawLine(const AsciiEngine::Vector2& startPos, const AsciiEngine::Vector2& endPos, char printChar, const Color& color = Color::WHITE);
{
}
```

##### Color
```cpp
enum class Color
{
	BLACK,
	DARK_BLUE, DARK_GREEN, DARK_CYAN, DARK_RED, DARK_MAGENTA, DARK_YELLOW, DARK_GRAY,
	GRAY, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE
};
```

#### Input
All functions in the Input are static. Ensure to call the Input system after the Engine's constructor was called.

Checks if a key is pressed. All keys including mouse buttons work on this function.
```cpp
static bool Input::IsKeyPressed(Key key)
{
}
```

Get the position of the mouse cursor.
```cpp
static Vector2 Input::GetMousePosition()
{
}
```

##### Key and Mouse Codes
```cpp
enum Key
{
	KEY_BACKSPACE, KEY_TAB, KEY_ENTER, KEY_SHIFT, KEY_CONTROL, KEY_ALT, KEY_CAPS_LOCK, KEY_ESCAPE, KEY_SPACE, 
        KEY_PREV, KEY_NEXT, KEY_PRINT,
        KEY_INSERT, KEY_DELETE, 
        KEY_LWIN, KEY_RWIN,
        KEY_HOME, KEY_END, KEY_LEFT_ARROW, KEY_UP_ARROW, KEY_RIGHT_ARROW, KEY_DOWN_ARROW,

	NUMPAD_0, NUMPAD_1, NUMPAD_2, NUMPAD_3, NUMPAD_4, NUMPAD_5, NUMPAD_6, NUMPAD_7, NUMPAD_8, NUMPAD_9,
	NUMPAD_MULTIPLY, NUMPAD_ADD, NUMPAD_SEPARATOR, NUMPAD_SUBTRACT, NUMPAD_DECIMAL, NUMPAD_DIVIDE,

	// Dont Work for Some Reason
	/*F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24*/

	KEY_NUM_LOCK, KEY_SCROLL_LOCK,

	KEY_LSHIFT, KEY_RSHIFT, KEY_LCONTROL, KEY_RCONTROL, KEY_LMENU, KEY_RMENU,

	VOLUME_MUTE, VOLUME_DOWN, VOLUME_UP, MEDIA_NEXT, MEDIA_PREV, MEDIA_STOP, MEDIA_PLAY_PAUSE,

	KEY_SEMICOLON, KEY_PLUS, KEY_COMMA, KEY_MINUS, KEY_PERIOD, KEY_LSLASH, KEY_TILDA, KEY_LSQUARE, 
        KEY_RSLASH, KEY_RSQUARE, KEY_SINGLE_QUOTE,

	KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I, KEY_J, KEY_K, KEY_L, KEY_M, KEY_N,
        KEY_O, KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z,

	KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,

	MOUSE_LEFT, MOUSE_RIGHT, MOUSE_MIDDLE3
};
```

**Contact: clartikdev@gmail.com**