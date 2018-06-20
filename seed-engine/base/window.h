#pragma once

#include <string>

class Window
{
public:
	Window(const std::string & caption = "no-name", const unsigned int & width = 1280, const unsigned int & height = 720)
		: caption_(caption)
		, width_(width)
		, height_(height)
	{}

	// get / set {
public:
	const std::string & get_caption(void) const { return this->caption_; }
	const unsigned int & get_width(void) const { return this->width_; }
	const unsigned int & get_height(void) const { return this->height_; }
	const HWND & get_hwnd(void) const { return this->hwnd_; }

	void set_caption(const std::string & caption) { this->caption_ = caption; }
	void set_width(const unsigned int & width) { this->width_ = width; }
	void set_height(const unsigned int & height) { this->height_ = height; }
	void set_hwnd(const HWND & hwnd) { this->hwnd_ = hwnd; }

	// template cast
	template<class _Type> const _Type get_width(void) { return static_cast<_Type>(this->get_width()); }
	template<class _Type> const _Type get_height(void) { return static_cast<_Type>(this->get_height()); }

	// } get / set

	// virtual {
public:
	virtual void Initalize(void) = 0;
	virtual bool Run(void) = 0;
	virtual void Finalize(void) = 0;
	// } virtual

private:
	std::string caption_;
	unsigned int width_;
	unsigned int height_;
	HWND hwnd_;
};