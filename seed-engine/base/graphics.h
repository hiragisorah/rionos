#pragma once

#include <unordered_map>

#include "window.h"

#include "..\utility\connected_pointer.h"

#include "graphics\bill_board.h"
#include "graphics\font2d.h"
#include "graphics\font3d.h"
#include "graphics\geometry2d.h"
#include "graphics\geometry3d.h"
#include "graphics\model.h"
#include "graphics\sprite2d.h"
#include "graphics\sprite3d.h"

class Graphics
{
public:
	Graphics(void)
		: window_(nullptr)
	{}

public:
	virtual bool Initialize(void) = 0;
	virtual void Finalize(void) = 0;
	virtual bool Begin(void) = 0;
	virtual bool End(void) = 0;

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
	virtual void Rendering(ConnectedPointer<BillBoard> & bill_board) = 0;
	virtual void Rendering(ConnectedPointer<Font2D> & font2d) = 0;
	virtual void Rendering(ConnectedPointer<Font3D> & font3d) = 0;
	virtual void Rendering(ConnectedPointer<Geometry2D> & geometry2d) = 0;
	virtual void Rendering(ConnectedPointer<Geometry3D> & geometry3d) = 0;
	virtual void Rendering(ConnectedPointer<Model> & model) = 0;
	virtual void Rendering(ConnectedPointer<Sprite2D> & sprite2d) = 0;
	virtual void Rendering(ConnectedPointer<Sprite3D> & sprite3d) = 0;

	// get / set {
public:
	Window * get_window(void) const { return this->window_; }
	void set_window(Window * const window) { this->window_ = window; }

	// } get / set

private:
	Window * window_;
};