#include "window.h"

bool Window::Initalize(void)
{
	{// ハンドル取得
		this->hinstance_ = GetModuleHandleA(nullptr);
	}

	{// ウィンドウクラスの登録
		WNDCLASSEX  wc;
		memset(&wc, 0, sizeof(wc));
		wc.cbSize = sizeof(wc);
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WndProc;
		wc.hInstance = this->hinstance_;
		wc.hIcon = LoadIconA(nullptr, IDI_APPLICATION);
		wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
		wc.lpszClassName = this->get_caption().c_str();
		wc.hIconSm = LoadIconA(nullptr, IDI_APPLICATION);
		RegisterClassExA(&wc);
	}

	{// ウィンドウの大きさの再調整、中央配置計算
		RECT rc;
		rc.left = 0;
		rc.top = 0;
		rc.right = this->get_width<long>();
		rc.bottom = this->get_height<long>();

		AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW, true, 0);

		int w = rc.right - rc.left;
		int h = rc.bottom - rc.top;

		RECT rc_desk;
		GetWindowRect(GetDesktopWindow(), &rc_desk);

		int x = rc_desk.right / 2 - w / 2;
		int y = rc_desk.bottom / 2 - h / 2;

		{// ウィンドウの生成、表示
			this->set_hwnd(CreateWindowExA(0, this->get_caption().c_str(), this->get_caption().c_str(), WS_OVERLAPPEDWINDOW,
				x, y, w, h, 0, 0, this->hinstance_, 0));

			ShowWindow(this->get_hwnd(), SW_SHOW);
		}
	}

	return true;
}

bool Window::Run(void)
{
	return MessageLoop();
}

void Window::Finalize(void)
{
}

const HINSTANCE & Window::get_hinstance(void)
{
	return this->hinstance_;
}

void Window::set_instance(const HINSTANCE & hinstance)
{
	this->hinstance_ = hinstance;
}

bool Window::MessageLoop(void)
{
	MSG msg = { 0 };
	memset(&msg, 0, sizeof(msg));

	while (PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
		if (msg.message == WM_QUIT) return false;
	}
	return true;
}

LRESULT Window::WndProc(HWND hwnd, UINT i_msg, WPARAM w_param, LPARAM l_param)
{
	switch (i_msg)
	{
	case WM_DESTROY: PostQuitMessage(0); break;
	case WM_ACTIVATEAPP:
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP: break;
	default:
		return DefWindowProc(hwnd, i_msg, w_param, l_param);
	}
	return 0;
}