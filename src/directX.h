#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>

using namespace Microsoft::WRL;

class Directx
{
public:
	Directx(HWND hwnd);

	Directx(const Directx&) = delete;
	Directx& operator=(const Directx&) = delete;

	~Directx() = default;

	void Begin(float red, float green, float blue);
	void End();
private:

	ComPtr<ID3D11Device> m_Device = nullptr;
	ComPtr<IDXGISwapChain> m_Swap = nullptr;
	ComPtr<ID3D11DeviceContext> m_Context = nullptr;
	ComPtr<ID3D11RenderTargetView> m_Target = nullptr;

	bool GuiEnabled = true;
};