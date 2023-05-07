#include "application.h"
#include "../ext/imgui/imgui.h"
//#include "../ext/imgui/imgui_impl_win32.h"
#include "../ext/imgui/imgui_impl_dx11.h"

Application::Application()
{
	m_Window = new Window(1280, 720, "DirectX and Vulkan");
}

Application::~Application()
{
	delete m_Window;
}

int Application::Run()
{
	while (true)
	{
		if (const auto msgCode = Window::ProcessMessages())
		{
			return *msgCode;
		}
		Update();
	}
}

void Application::Update()
{
	const float c = sin(m_Timer.GetTimer()) / 2.0f + 0.5f;
	m_Window->GetGfx().Begin(c, c, 1.0f);
	m_Window->Renderer();
	static bool show_demo_window = true;
	if (show_demo_window)
	{
		ImGui::ShowDemoWindow(&show_demo_window);
	}
	m_Window->GetGfx().End();

}
