#include "directx11.h"

DirectX11::DirectX11(void)
	: clear_color_(DirectX::XMVectorSet(.2f, .4f, .8f, 1.f))
{
	
}

bool DirectX11::Initialize(void)
{
	if (!this->InitializeSwapChain())
	{
		return false;
	}
	if(!this->InitializeBackBuffer())
	{
		return false;
	}
	if (!this->InitializeDepthStencilView())
	{
		return false;
	}
	if (!this->InitializeViewPort())
	{
		return false;
	}

	return true;
}

void DirectX11::Finalize(void)
{
}

bool DirectX11::Begin(void)
{
	this->context_->ClearRenderTargetView(this->back_buffer_rtv_.Get(), (float*)&this->clear_color_);
	this->context_->ClearDepthStencilView(this->dsv_.Get(), D3D11_CLEAR_DEPTH, 1.f, 0);

	return true;
}
bool DirectX11::End(void)
{
	this->swap_chain_->Present(1, 0);

	return true;
}
void DirectX11::Rendering(ConnectedPointer<BillBoard> & bill_board)
{
}
void DirectX11::Rendering(ConnectedPointer<Font2D> & font2d)
{
}
void DirectX11::Rendering(ConnectedPointer<Font3D> & font3d)
{
}
void DirectX11::Rendering(ConnectedPointer<Geometry2D> & geometry2d)
{
}
void DirectX11::Rendering(ConnectedPointer<Geometry3D> & geometry3d)
{
}
void DirectX11::Rendering(ConnectedPointer<Model> & model)
{
}
void DirectX11::Rendering(ConnectedPointer<Sprite2D> & sprite2d)
{
}
void DirectX11::Rendering(ConnectedPointer<Sprite3D> & sprite3d)
{
}

bool DirectX11::InitializeSwapChain(void)
{
	// デバイスとスワップチェーンの作成 
	DXGI_SWAP_CHAIN_DESC sd;
	memset(&sd, 0, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = this->get_window()->get_width();
	sd.BufferDesc.Height = this->get_window()->get_height();
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = this->get_window()->get_hwnd();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;

	D3D_FEATURE_LEVEL feature_levels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL * feature_level = nullptr;

	auto hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
		0, &feature_levels, 1, D3D11_SDK_VERSION, &sd, &this->swap_chain_, &this->device_,
		feature_level, &this->context_);

	return SUCCEEDED(hr);
}

bool DirectX11::InitializeBackBuffer(void)
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex_2d;

	// バックバッファーテクスチャーを取得
	this->swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&tex_2d);

	// そのテクスチャーに対しレンダーターゲットビュー(RTV)を作成
	auto hr = this->device_->CreateRenderTargetView(tex_2d.Get(), nullptr, this->back_buffer_rtv_.GetAddressOf());

	return SUCCEEDED(hr);
}

bool DirectX11::InitializeDepthStencilView(void)
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex_2d;

	//深度マップテクスチャをレンダーターゲットにする際のデプスステンシルビュー用のテクスチャーを作成
	D3D11_TEXTURE2D_DESC tex_desc = {};
	tex_desc.Width = this->get_window()->get_width();
	tex_desc.Height = this->get_window()->get_height();
	tex_desc.MipLevels = 1;
	tex_desc.ArraySize = 1;
	tex_desc.Format = DXGI_FORMAT_D32_FLOAT;
	tex_desc.SampleDesc.Count = 1;
	tex_desc.SampleDesc.Quality = 0;
	tex_desc.Usage = D3D11_USAGE_DEFAULT;
	tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tex_desc.CPUAccessFlags = 0;
	tex_desc.MiscFlags = 0;

	this->device_->CreateTexture2D(&tex_desc, nullptr, tex_2d.GetAddressOf());
	auto hr = this->device_->CreateDepthStencilView(tex_2d.Get(), nullptr, this->dsv_.GetAddressOf());

	return SUCCEEDED(hr);
}

bool DirectX11::InitializeViewPort(void)
{
	auto & vp = this->viewport_;

	vp.Width = this->get_window()->get_width<float>();
	vp.Height = this->get_window()->get_height<float>();
	vp.MinDepth = 0.f;
	vp.MaxDepth = 1.f;
	vp.TopLeftX = 0.f;
	vp.TopLeftY = 0.f;

	return true;
}
