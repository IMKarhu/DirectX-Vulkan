#include "directX.h"
#include "../ext/imgui/imgui_impl_dx11.h"
#include "../ext/imgui/imgui_impl_win32.h"

Directx::Directx(HWND hwnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hwnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
				D3D11_SDK_VERSION, &sd, &m_Swap, &m_Device, nullptr, &m_Context);

	ComPtr<ID3D11Resource> backBuffer = nullptr;
	m_Swap->GetBuffer(0, __uuidof(ID3D11Resource), &backBuffer);
	m_Device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_Target);
	backBuffer->Release();

	/* Deptstencilview is NULL for now since we dont have depth stencil. */
	m_Context->OMSetRenderTargets(1u, m_Target.GetAddressOf(), NULL);

	D3D11_VIEWPORT vp;
	vp.Width = 1280;
	vp.Height = 720;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_Context->RSSetViewports(1u, &vp);

	/* Init ImGui D3D. */
	ImGui_ImplDX11_Init(m_Device.Get(), m_Context.Get());
}

void Directx::Begin(float red, float green, float blue)
{
	if (GuiEnabled)
	{
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
	}
	
	const float color[] = { red, green, blue, 1.0f };
	m_Context->ClearRenderTargetView(m_Target.Get(), color);
}

void Directx::End()
{
	if (GuiEnabled)
	{
		ImGui::Render();
		ImGui:ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}
	m_Swap->Present(1u, 0u);
}
