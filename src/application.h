#pragma once

#include "window.h"
#include "guiManager.h"
#include "timer.h"

class Application
{
public:
	Application();

	~Application();

	int Run();

	void Update();

private:

	Window* m_Window = nullptr;
	GuiManager m_Gui;
	Timer m_Timer;
};