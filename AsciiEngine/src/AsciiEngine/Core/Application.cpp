#include "AsciiEngine.h"

#include "Renderer.h"

namespace AsciiEngine
{
	Application* Application::s_Instance = nullptr;

	Application::Application(int fps)
	{
		s_Instance = this;
		m_Window = new Window(fps);

		Renderer::Init();
	}

	Application::Application(const WindowProps& props)
	{
		s_Instance = this;
		m_Window = new Window(props);

		Renderer::Init();
	}

	Application::~Application()
	{
		delete m_Window;
	}

	void Application::Run()
	{
		while (m_Running)
		{
			OnUpdate();

			m_Window->Render();
		}
	}
}