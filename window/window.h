#pragma once

#pragma once

#ifdef _WINDOWDLL
#define WINDOWDLL_API __declspec(dllexport)
#else
#define WINDOWDLL_API __declspec(dllimport)
#endif

#pragma warning(disable: 4251)

#include <Windows.h>

#include <string>

class WINDOWDLL_API Window
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
	const unsigned int & width(void) const { return this->width_; }
	const unsigned int & height(void) const { return this->height_; }
	const HWND & get_hwnd(void) const { return this->hwnd_; }

	void set_caption(const std::string & caption) { this->caption_ = caption; }
	void set_width(const unsigned int & width) { this->width_ = width; }
	void set_height(const unsigned int & height) { this->height_ = height; }
	void set_hwnd(const HWND & hwnd) { this->hwnd_ = hwnd; }

	// template cast
	template<class _Type = unsigned int> const _Type get_width(void) { return static_cast<_Type>(this->width_); }
	template<class _Type = unsigned int> const _Type get_height(void) { return static_cast<_Type>(this->height_); }

	// } get / set

public:
	bool Initalize(void);
	bool Run(void);
	void Finalize(void);

private:
	std::string caption_;
	unsigned int width_;
	unsigned int height_;
	HWND hwnd_;

	// get / set {
public:
	const HINSTANCE & get_hinstance(void);

	void set_instance(const HINSTANCE & hinstance);

	// } get / set

private:
	HINSTANCE hinstance_;

private:
	bool MessageLoop(void);
	static LRESULT __stdcall WndProc(HWND hwnd, UINT i_msg, WPARAM w_param, LPARAM l_param);
};