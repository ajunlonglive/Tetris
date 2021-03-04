#include "YGL.hpp"


// 初期化処理を行う
YGL_ERROR Game::Init() {

	HRESULT hr = S_OK;

	// COMを初期化する
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		return Convert_HRESULT_ToError(hr);
	}

	// Core_Windowクラスを初期化する
	hr = Core_Window::Init();
	if (FAILED(hr)) {
		CoUninitialize();	// COMを終了する
		return Convert_HRESULT_ToError(hr);
	}

	// Core_Graphicクラスを初期化する
	hr = Core_Graphic::Init();
	if (FAILED(hr)) {
		Core_Window::Quit();	// Core_Windowクラスを終了する
		CoUninitialize();	// COMを終了する
		return Convert_HRESULT_ToError(hr);
	}

	// Core_Soundクラスを初期化する
	hr = Core_Sound::Init();
	if (FAILED(hr)) {
		Core_Graphic::Quit();	// Core_Graphicクラスを終了する
		Core_Window::Quit();	// Core_Windowクラスを終了する
		CoUninitialize();	// COMを終了する
		return Convert_HRESULT_ToError(hr);
	}

	// Core_Timeクラスを初期化する
	hr = Core_Time::Init();
	if (FAILED(hr)) {
		Core_Sound::Quit();	// Core_Soundクラスを終了する
		Core_Graphic::Quit();	// Core_Graphicクラスを終了する
		Core_Window::Quit();	// Core_Windowクラスを終了する
		CoUninitialize();	// COMを終了する
		return Convert_HRESULT_ToError(hr);
	}

	// ウィンドウを可視化する
	ShowWindow(Core_Window::hWnd, SW_SHOW);


	return YGL_ERROR_SUCCESS;

}

// 終了処理を行う
void Game::Quit() {

	Core_Time::Quit();	// Core_Timeクラスを終了する
	Core_Sound::Quit();	// Core_Soundクラスを終了する
	Core_Graphic::Quit();	// Core_Graphicクラスを終了する
	Core_Window::Quit();	// Core_Windowクラスを終了する
	CoUninitialize();	// COMを終了する

}

// ゲームループを実行するかを返す
bool Game::GameLoop() {

	// メッセージの有無を取得する
	if (PeekMessageW(&Core_Window::msg, NULL, 0, 0, PM_NOREMOVE)) {
		// メッセージがある場合

		// メッセージを取得する
		if (0 == GetMessageW(&Core_Window::msg, NULL, 0, 0)) {
			return false;	// メッセージがWM_QUITである場合、falseを返す
		}

		TranslateMessage(&Core_Window::msg);
		DispatchMessageW(&Core_Window::msg);
	}

	return true;

}

// ゲームループの開始処理を行う
void Game::LoopStart() {

	// FPSを計算する
	Core_Time::CalculateFPS();

	// Direct2D1の描画を開始する
	Core_Graphic::pRenderTarget->BeginDraw();

	// 背景をクリアする
	Core_Graphic::pRenderTarget->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f));

}

// ゲームループの終了処理を行う
void Game::LoopEnd() {

	// Direct2D1の描画を終了する
	Core_Graphic::pRenderTarget->EndDraw();

	// スリープをはさむ
	timeBeginPeriod(1);
	Sleep(Core_Time::GetSleepTime());
	timeEndPeriod(1);

}