#pragma once

#define WIN32_LEAD_AND_MEAN
#include <Windows.h>

#include "..\seed-engine\base\window.h"

class SimpleWindow : public Window
{
public:
	SimpleWindow(void);

	// override {
private:
	void Initalize(void) override;
	bool Run(void) override;
	void Finalize(void) override;

	// } override

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