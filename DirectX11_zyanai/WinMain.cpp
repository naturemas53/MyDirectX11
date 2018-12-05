#include <Windows.h>
#include "DirectX11_Framework/Device.h"
#include "DirectX11_Framework/Device/Graphics.h"

//ウィンドウ横幅
#define WIDTH 1280
#define HEIGHT 720

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{	
		switch (msg) {
			
		case WM_CREATE:

			if (!DX11_DEVICE.Initialize(hwnd)) {

				DX11_DEVICE.Release();
				PostQuitMessage(0);
				return 0;

			}

			DX11_GRAPHIC.Initialize();

			break;

		case WM_KEYDOWN:

			if (wp == VK_ESCAPE) {

				DX11_GRAPHIC.Release();
				DX11_DEVICE.Release();
				PostQuitMessage(0);

			}

			return 0;


		case WM_DESTROY:
			
			DX11_GRAPHIC.Release();
			DX11_DEVICE.Release();
			PostQuitMessage(0);
			
			return 0;
			
		}
	
		return DefWindowProc(hwnd, msg, wp, lp);
	
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	
		MSG msg;
		WNDCLASS wc;
		wc.style = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = WinProc;
		wc.cbClsExtra = wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hCursor = wc.hIcon = NULL;
		wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wc.lpszClassName = L"DirectX";
		wc.lpszMenuName = NULL;
	
		if (!RegisterClass(&wc)) {
			
				return -1;
			
		}
		
		//インスタンスハンドル
		HINSTANCE hinst = NULL;

		RECT rect;
		rect.top = 0;
		rect.left = 0;
		rect.bottom = HEIGHT;
		rect.right = WIDTH;

		DWORD dwStyle = WS_VISIBLE | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX;

		AdjustWindowRectEx(&rect,dwStyle,FALSE,0);

		HWND hwnd;
		hwnd = CreateWindowW(L"DirectX", L"DirectX Window", dwStyle,	
			0, 0,rect.right - rect.left, rect.bottom - rect.top , NULL, NULL, hinst, NULL);

		if (hwnd == NULL) {
			
				return -1;
			
		}

		//インスタンスハンドル
		hinst = hInstance;

		//エラーチェック用変数	
		int check;


		//while (check = GetMessage(&msg, NULL, 0, 0)) {
		//	
		//		if (check == -1) {
		//			
		//				break;
		//			
		//		}
		//	
		//		DispatchMessage(&msg);
		//	
		//}

		while (true) { 

			// メッセージキューに溜まったメッセージをすべて処理する
			while (0 != PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
				if (WM_QUIT == msg.message) {
					UnregisterClass(L"DirectX", hinst);

					return 0;
				}

				DispatchMessage(&msg);
			} //while(PeekMessage)

			// メッセージがなくなったら、ゲームを処理する ※ここで、ゲームを処理する関数の呼び出しを行います

			DX11_GRAPHIC.Render();

		}


		return 0;
	
}