#include "AsciiEngine.h"

class CustomEngine : public AsciiEngine
{
public:
	CustomEngine(const AsciiEngineProps& props)
		: AsciiEngine(props)
	{
	}

	glm::ivec2 playerPos = { 2, 2 };

	virtual void OnUpdate() override
	{
		DrawLine({ 0, 0 }, { 20, 0 }, '#');
		DrawLine({ 20, 0 }, { 20, 10 }, '#');
		DrawLine({ 20, 10 }, { 0, 10 }, '#');
		DrawLine({ 0, 10 }, { 0, 0 }, '#');

		Draw(playerPos, 'X');

		if (IsKeyPressed(VK_LBUTTON))
			DrawString({ 0, 12 }, "Key was Pressed");

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
	CustomEngine engine({ 22, 16 });
	engine.Run();
}