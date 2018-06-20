#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl\client.h>

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxguid.lib")

#include "..\seed-engine\base\graphics.h"
#include "..\seed-engine\base\window.h"

using namespace Microsoft::WRL;

class DirectX11 : public Graphics
{
public:
	DirectX11(void);

	// get / set {
public:
	Window * const get_window(void);
	void set_window(Window * const window);
	// } get / set

private:
	Window * window_;

	// override {
public:
	bool Initialize(void) override;
	void Finalize(void) override;
	bool Begin(void) override;
	bool End(void) override;

protected:
	void Rendering(ConnectedPointer<BillBoard> & bill_board) override;
	void Rendering(ConnectedPointer<Font2D> & font2d) override;
	void Rendering(ConnectedPointer<Font3D> & font3d) override;
	void Rendering(ConnectedPointer<Geometry2D> & geometry2d) override;
	void Rendering(ConnectedPointer<Geometry3D> & geometry3d) override;
	void Rendering(ConnectedPointer<Model> & model) override;
	void Rendering(ConnectedPointer<Sprite2D> & sprite2d) override;
	void Rendering(ConnectedPointer<Sprite3D> & sprite3d) override;
	// } override

private:
	ComPtr<IDXGISwapChain> swap_chain_;
	ComPtr<ID3D11Device> device_;
	ComPtr<ID3D11DeviceContext> context_;

private:
	ComPtr<ID3D11RenderTargetView> back_buffer_rtv_;
	ComPtr<ID3D11DepthStencilView> dsv_;
	D3D11_VIEWPORT viewport_;

private:
	bool InitializeSwapChain(void);
	bool InitializeBackBuffer(void);
	bool InitializeDepthStencilView(void);
	bool InitializeViewPort(void);
};