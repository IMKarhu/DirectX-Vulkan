#include "window.h"
#include "../ext/imgui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

Window::Window(int width, int height, const char* name)
	: m_Width(width), m_Height(height), m_Hinstance(GetModuleHandle(nullptr))
{

	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.hInstance = m_Hinstance;
	wc.lpszClassName = m_WindowName;

	RegisterClassEx(&wc);

	RECT winRect;
	winRect.left = 100;
	winRect.right = m_Width + winRect.left;
	winRect.top = 100;
	winRect.bottom = m_Height + winRect.top;

	AdjustWindowRect(&winRect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZE, FALSE);

	m_Hwnd = CreateWindowEx(0, m_WindowName, name, WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
							winRect.right - winRect.left, winRect.bottom - winRect.top, nullptr, nullptr, m_Hinstance, this);

	ShowWindow(m_Hwnd, SW_SHOWDEFAULT);

	/* Init ImGui win32. */
	ImGui_ImplWin32_Init(m_Hwnd);

	m_Gfx = std::make_unique<Directx>(m_Hwnd);

}

Window::~Window()
{
	ImGui_ImplWin32_Shutdown();
	UnregisterClass(m_WindowName, m_Hinstance);
}

void Window::Renderer()
{
	ImGui::Begin("Select Renderer");
	ImGui::Text("Hello World");
	ImGui::End();
}

std::optional<int> Window::ProcessMessages()
{
	MSG msg = {};
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return msg.wParam;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return {};
}

Directx& Window::GetGfx()
{
	return *m_Gfx;
}

LRESULT _stdcall Window::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
	{
		return true;
	}
	switch (msg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE)
			{
				PostQuitMessage(0);
				return 0;
			}
			return 0;
		case WM_CLOSE:
			if (MessageBox(hWnd, "Are you sure you want to quit?", "DirectX and Vulkan", MB_OKCANCEL) == IDOK)
			{
				DestroyWindow(hWnd);
			}
			return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
