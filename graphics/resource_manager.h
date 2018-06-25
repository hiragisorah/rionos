#pragma once

#include <d3d11.h>
#include <wrl/client.h>

#include <unordered_map>

#include "bill_board.h"
#include "font2d.h"
#include "font3d.h"
#include "geometry2d.h"
#include "geometry3d.h"
#include "model.h"
#include "sprite2d.h"
#include "sprite3d.h"

using namespace Microsoft::WRL;

class GRAPHICSDLL_API ResourceManager
{
public:
	struct MeshData
	{
		ComPtr<ID3D11Buffer> vertex_buffer_;
		ComPtr<ID3D11Buffer> index_buffer_;
	};

private:
	std::unordered_map<Geometry2D::TYPE, MeshData>
};