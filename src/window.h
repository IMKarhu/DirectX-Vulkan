#pragma once

#include <windows.h>
#include <optional>
#include <memory>

#include "directX.h"

class Window
{
public:
	Window(int width, int height, const char* name);

	~Window();

	void Renderer();//TODO
	static std::optional<int> ProcessMessages();
	Directx& GetGfx();

private:

	/* Window procedure. */
	static LRESULT _stdcall WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HWND m_Hwnd;
	HINSTANCE m_Hinstance;

	/* Window properties. */
	int m_Width;
	int m_Height;
	const char* m_WindowName = "DirectX and Vulkan training.";

	std::unique_ptr<Directx> m_Gfx;
};