#include "DirectX.h"
bool gameover = false;

LRESULT CALLBACK WINAPI WinProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		gameover = true;
		PostQuitMessage(0);
		break;
	default:
		break;
	}

	return DefWindowProc(window, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE HPrevInstance, LPSTR lpCmdLinde, int nCmdShow)
{
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = ((HBRUSH)GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.lpszClassName = Tittle.c_str();
	wc.lpszMenuName = NULL;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	RegisterClassEx(&wc);

	HWND window = CreateWindow(
		Tittle.c_str(), Tittle.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		SCREENW, SCREENH,
		NULL, NULL,
		hInstance, NULL);

	if (window == 0)return 0;

	ShowWindow(window, nCmdShow);
	UpdateWindow(window);

	if (!Game_Init(window))return 0;

	MSG msg;
	{
		while (!gameover)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			Game_Run(window);
		}

		return msg.lParam;
	}
}
