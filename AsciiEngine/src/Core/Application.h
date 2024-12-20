#pragma once

#include <string>

#include "Window.h"

class Application
{
public:
	/// <summary>
	/// Default Constructor
	/// </summary>
	/// <param name="emptyChar">The Character of the Empty Area</param>
	Application(int fps = 30);

	/// <summary>
	/// Default Constructor
	/// </summary>
	/// <param name="props">The Properties of the Engine</param>
	Application(const WindowProps& props);

	~Application();

	/// <summary>
	/// Says if the Engine is Running. Should Be Used in the While Loop
	/// </summary>
	/// <returns>Whether the Engine is Running or Not</returns>
	inline bool IsRunning() const { return m_Running; }

	inline Window& GetWindow() { return *m_Window; }
	inline static Application& Get() { return *s_Instance; }

	/// <summary>
	/// Virtual Function that Can Be Overridden to Modify Any Behavior
	/// </summary>
	virtual void OnUpdate() { }

	void Run();

	/// <summary>
	/// Stops the Engine From Running
	/// </summary>
	inline void Stop() { m_Running = false; }
private:
	/// <summary>
	/// Whether the Engine is Running or Not
	/// </summary>
	bool m_Running = true;

	Window* m_Window;
private:
	static Application* s_Instance;
};