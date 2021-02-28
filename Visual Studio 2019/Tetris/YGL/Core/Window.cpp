#include "Window.hpp"


// ウィンドウプロシージャ
LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);

}

UINT Window::WindowWidth = 640, Window::WindowHeight = 480;	// ウィンドウの幅と高さ(ウィンドウモードの場合のみに影響する)
LPCWSTR Window::WindowTitle = NULL;	// ウィンドウのタイトル(ウィンドウモードの場合のみに影響する)
HWND Window::hWnd = NULL;	// ウィンドウハンドル
MSG Window::msg = { 0 };	// ウィンドウメッセージ

// ゲームウィンドウを作成する
HRESULT Window::CreateGameWindow() {

	// ウィンドウクラスを設定する
	WNDCLASS WndClass = { 0 };
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = WndClass.cbWndExtra = 0;
	WndClass.hInstance = GetModuleHandle(NULL);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = NULL;
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = TEXT("WINDOW");

	// ウィンドウクラスを登録する
	if (0 == RegisterClass(&WndClass))
		return E_FAIL;

	// サイズを指定せず不可視のウィンドウを生成する
	hWnd = CreateWindow(WndClass.lpszClassName, WindowTitle, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, GetModuleHandle(NULL), NULL);
	if (hWnd == NULL)
		return E_FAIL;


	// 以降はウィンドウのクライアント領域を設定する

	// ウィンドウそのもののサイズとクライアント領域のサイズを得る
	RECT rectW, rectC;
	GetWindowRect(hWnd, &rectW);
	GetClientRect(hWnd, &rectC);

	// 得られたサイズから適切なウィンドウサイズを求める
	int new_width = (rectW.right - rectW.left) - (rectC.right - rectC.left) + WindowWidth;
	int new_height = (rectW.bottom - rectW.top) - (rectC.bottom - rectC.top) + WindowHeight;

	// ウィンドウのサイズを適切なものに変更する
	SetWindowPos(hWnd, NULL, 0, 0, new_width, new_height, SWP_NOZORDER);

	return S_OK;

}