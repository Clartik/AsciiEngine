#include <AsciiEngine.h>

using namespace AsciiEngine;

class CustomEngine : public Application
{
public:
	CustomEngine(const WindowProps& props)
		: Application(props)
	{
	}

	Vector2 playerPos = { 2, 2 };

	virtual void OnUpdate() override
	{
		Renderer::DrawLine({ 0, 0 }, { 20, 0 }, '#');
		Renderer::DrawLine({ 20, 0 }, { 20, 10 }, '#');
		Renderer::DrawLine({ 20, 10 }, { 0, 10 }, '#');
		Renderer::DrawLine({ 0, 10 }, { 0, 0 }, '#');

		Renderer::Draw(playerPos, 'X');

		if (playerPos.y == 2 && playerPos.x < 18)
			playerPos.x++;
		else if (playerPos.x == 18 && playerPos.y < 8)
			playerPos.y++;
		else if (playerPos.y == 8 && playerPos.x > 2)
			playerPos.x--;
		else if (playerPos.x == 2 && playerPos.y > 2)
			playerPos.y--;
	}
};

int main()
{
	Application* app = new CustomEngine({ 22, 16 });
	app->Run();
	delete app;
}