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

#include "bill_board.h"
#include "effect2d.h"
#include "effect3d.h"
#include "font2d.h"
#include "font3d.h"
#include "geometry2d.h"
#include "geometry3d.h"
#include "model.h"
#include "sprite2d.h"
#include "sprite3d.h"

using namespace Microsoft::WRL;

class GRAPHICSDLL_API Graphics
{
public:
	Graphics(void);

public:
	bool Initialize(void);
	void Finalize(void);
	bool Begin(void);
	bool Render(void);
	bool End(void);

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

private:
	template<class _Type> void RenderingList(std::vector<_Type> list)
	{
		for (unsigned int n = 0; n < list.size();)
		{
			auto & pointer = list[n];
			if (pointer.isExpired())
			{
				list.erase(list.begin() + n);
			}
			else
			{
				this->Rendering(pointer);
				++n;
			}
		}
	}

private:
	struct MeshBuffer
	{
		ComPtr<ID3D11Buffer> vertex_buffer_;
		ComPtr<ID3D11Buffer> index_buffer_;
		unsigned int indices_cnt_;
		unsigned int vertex_size_;
		D3D11_PRIMITIVE_TOPOLOGY topology_;
	};

private:
	std::unordered_map<Geometry2D::TYPE, MeshBuffer> geometry_2d_type_list_;

private:
	bool InitGeometry2DTypeTriangle(void);
	
private:
	void DrawIndexed(const MeshBuffer & mesh);

private:
	template<class _Vertex> const bool CreateVertexBuffer(ComPtr<ID3D11Buffer> & buffer, unsigned int & size, std::vector<_Vertex> & vertices)
	{
		size = sizeof(_Vertex);

		D3D11_BUFFER_DESC bd = {};
		bd.ByteWidth = vertices.size() * size;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vertices.data();

		auto hr = this->device_->CreateBuffer(&bd, &sd, buffer.GetAddressOf());

		return SUCCEEDED(hr);
	}
	template<class _Index> const bool CreateIndexBuffer(ComPtr<ID3D11Buffer> & buffer, unsigned int & cnt, std::vector<_Index> & indices)
	{
		cnt = indices.size();

		D3D11_BUFFER_DESC bd = {};
		bd.ByteWidth = cnt * sizeof(_Index);
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = indices.data();

		auto hr = this->device_->CreateBuffer(&bd, &sd, buffer.GetAddressOf());

		return SUCCEEDED(hr);
	}
};