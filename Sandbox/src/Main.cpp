#include <AsciiEngine.h>

class CustomEngine : public AsciiEngine::Application
{
public:
	CustomEngine(const AsciiEngine::WindowProps& props)
		: AsciiEngine::Application(props)
	{
	}

	glm::ivec2 playerPos = { 2, 2 };

	virtual void OnUpdate() override
	{
		AsciiEngine::Renderer::DrawLine({ 0, 0 }, { 20, 0 }, '#');
		AsciiEngine::Renderer::DrawLine({ 20, 0 }, { 20, 10 }, '#');
		AsciiEngine::Renderer::DrawLine({ 20, 10 }, { 0, 10 }, '#');
		AsciiEngine::Renderer::DrawLine({ 0, 10 }, { 0, 0 }, '#');

		AsciiEngine::Renderer::Draw(playerPos, 'X');

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
	AsciiEngine::Application* app = new CustomEngine({ 22, 16 });
	app->Run();
	delete app;
}