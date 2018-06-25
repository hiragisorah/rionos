#pragma once

#pragma once

#ifdef _GRAPHICSDLL
#define GRAPHICSDLL_API __declspec(dllexport)
#else
#define GRAPHICSDLL_API __declspec(dllimport)
#endif

#pragma warning(disable: 4251)

#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl\client.h>
#include <DirectXMath.h>

#include <unordered_map>

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxguid.lib")

#include "..\window\window.h"

#include "..\seed-engine\utility\connected_pointer.h"

#include "resource_manager.h"

using namespace Microsoft::WRL;

class GRAPHICSDLL_API Graphics
{
public:
	Graphics(void);

public:
	virtual bool Initialize(void);
	virtual void Finalize(void);
	virtual bool Begin(void);
	virtual bool End(void);

protected:
	std::vector<ConnectedPointer<BillBoard>> bill_board_list_;
	std::vector<ConnectedPointer<Font2D>> font2d_list_;
	std::vector<ConnectedPointer<Font3D>> font3d_list_;
	std::vector<ConnectedPointer<Geometry2D>> geometry2d_list_;
	std::vector<ConnectedPointer<Geometry3D>> geometry3d_list_;
	std::vector<ConnectedPointer<Model>> model_list_;
	std::vector<ConnectedPointer<Sprite2D>> sprite2d_list_;
	std::vector<ConnectedPointer<Sprite3D>> sprite3d_list_;

public:
	void AddToDrawList(ConnectedPointer<BillBoard> & bill_board) { this->bill_board_list_.emplace_back(bill_board); }
	void AddToDrawList(ConnectedPointer<Font2D> & font2d) { this->font2d_list_.emplace_back(font2d); }
	void AddToDrawList(ConnectedPointer<Font3D> & font3d) { this->font3d_list_.emplace_back(font3d); }
	void AddToDrawList(ConnectedPointer<Geometry2D> & geometry2d) { this->geometry2d_list_.emplace_back(geometry2d); }
	void AddToDrawList(ConnectedPointer<Geometry3D> & geometry3d) { this->geometry3d_list_.emplace_back(geometry3d); }
	void AddToDrawList(ConnectedPointer<Model> & model) { this->model_list_.emplace_back(model); }
	void AddToDrawList(ConnectedPointer<Sprite2D> & sprite2d) { this->sprite2d_list_.emplace_back(sprite2d); }
	void AddToDrawList(ConnectedPointer<Sprite3D> & sprite3d) { this->sprite3d_list_.emplace_back(sprite3d); }

protected:
	void Rendering(ConnectedPointer<BillBoard> & bill_board);
	void Rendering(ConnectedPointer<Font2D> & font2d);
	void Rendering(ConnectedPointer<Font3D> & font3d);
	void Rendering(ConnectedPointer<Geometry2D> & geometry2d);
	void Rendering(ConnectedPointer<Geometry3D> & geometry3d);
	void Rendering(ConnectedPointer<Model> & model);
	void Rendering(ConnectedPointer<Sprite2D> & sprite2d);
	void Rendering(ConnectedPointer<Sprite3D> & sprite3d);

	// get / set {
public:
	Window * get_window(void) const { return this->window_; }
	void set_window(Window * const window) { this->window_ = window; }

	// } get / set

private:
	Window * window_;

private:
	ComPtr<IDXGISwapChain> swap_chain_;
	ComPtr<ID3D11Device> device_;
	ComPtr<ID3D11DeviceContext> context_;

private:
	ComPtr<ID3D11RenderTargetView> back_buffer_rtv_;
	ComPtr<ID3D11DepthStencilView> dsv_;
	D3D11_VIEWPORT viewport_;
	DirectX::XMVECTOR clear_color_;

private:
	bool InitializeSwapChain(void);
	bool InitializeBackBuffer(void);
	bool InitializeDepthStencilView(void);
	bool InitializeViewPort(void);
};