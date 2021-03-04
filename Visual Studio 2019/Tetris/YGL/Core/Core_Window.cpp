#include "Core_Window.hpp"


BOOL Core_Window::Windowed = FALSE;	// ウィンドウモードであるか
LPCWSTR Core_Window::WindowTitle = NULL;	// ウィンドウのタイトル
MSG Core_Window::msg = { 0 };	// ウィンドウメッセージ
UINT Core_Window::SideSpaceSize = 0, Core_Window::VerticalSpaceSize = 0;	// フルスクリーン時にウィンドウの縦横比とスクリーンの縦横比が一致しなかったときに生じる黒いスペースのサイズ

// 初期化処理を行う
HRESULT Core_Window::Init() {

	// ウィンドウクラスを設定する
	WNDCLASSW WndClass = { 0 };
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = WndClass.cbWndExtra = 0;
	WndClass.hInstance = GetModuleHandle(NULL);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = NULL;
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = L"WINDOW";

	// ウィンドウクラスを登録する
	if (0 == RegisterClassW(&WndClass)) {
		return E_FAIL;
	}

	// サイズを指定せず不可視のウィンドウを生成する
	hWnd = CreateWindowW(WndClass.lpszClassName, WindowTitle, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, GetModuleHandle(NULL), NULL);
	if (hWnd == NULL) {
		return E_FAIL;
	}


	// 以降はウィンドウのクライアント領域を設定する

	// ウィンドウそのもののサイズとクライアント領域のサイズを得る
	RECT rectW, rectC;
	GetWindowRect(hWnd, &rectW);
	GetClientRect(hWnd, &rectC);

	// 得られたサイズから適切なウィンドウサイズを求める
	int new_width = (rectW.right - rectW.left) - (rectC.right - rectC.left) + WindowSize.Width;
	int new_height = (rectW.bottom - rectW.top) - (rectC.bottom - rectC.top) + WindowSize.Height;

	// ウィンドウのサイズと位置を適切なものに変更する
	SetWindowPos(hWnd, NULL, 0, 0, new_width, new_height, SWP_NOZORDER);

	return S_OK;

}

// 終了処理を行う
VOID Core_Window::Quit() {

}

// ウィンドウプロシージャ
LRESULT CALLBACK Core_Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);

}

SIZE_UINT Core_Window::WindowSize = { 640, 480 };	// ウィンドウのサイズ(正確にはクライアント領域のサイズ)
HWND Core_Window::hWnd = NULL;	// ウィンドウハンドル