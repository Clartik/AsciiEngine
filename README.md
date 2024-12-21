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

## Dependencies
GLM is a dependency for this library. Please install and setup the GLM library to allow AsciiEngine to work accordingly.

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
    glm::ivec2 playerPos = { 2, 2 };
}

int main() 
{
    AsciiEngine::Application* app = new CustomApp({22, 12});
    app->Run();
    delete app;
}
```

## Documentation
You can use the WindowsProps to control the width, height, and framerate of the application.
```cpp
struct WindowsProps 
{
    unsigned int Width, Height, FPS;
}
```

#### Constructors
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

#### OnUpdate
The OnUpdate function is called once per frame. Override this function if anything should be renderered every frame.
```cpp
virtual void OnUpdate() override
{
}
```

#### Main
If you are to create a subclass to add additional behavior, you can still cast it to the regular AsciiEngine's Application as seen below.
```cpp
int main()
{
	AsciiEngine::Application* app = new CustomEngine({ 22, 16 });
	app->Run();
	delete app;
}
```

#### Renderer
All functions in the Renderer are static. Ensure to call the Renderer after the Engine's constructor was called.

Draws a single character on screen.
```cpp
static void Draw(const glm::ivec2& position, char printChar, const Color& color = Color::WHITE)
{
}
```

Draws a string of text on screen.
```cpp
static void DrawString(const glm::ivec2& position, const std::string& printString, const Color& color = Color::WHITE);
{
}
```

Draws a line on screen by controlling the start and end position of the line.
```cpp
static void DrawLine(const glm::ivec2& startPos, const glm::ivec2& endPos, char printChar, const Color& color = Color::WHITE);
{
}
```

#### Input
All functions in the Input are static. Ensure to call the Input system after the Engine's constructor was called.

Checks if a key is pressed. All keys including mouse buttons work on this function.
```cpp
bool Input::IsKeyPressed(Key key)
{
}
```

**Contact: clartikdev@gmail.com**