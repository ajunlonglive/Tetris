#include "YGL.hpp"


// 初期化処理を行う
HRESULT Game::Init() {

	HRESULT hr = S_OK;

	// COMを初期化する
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr))
		return hr;

	// ゲームウィンドウを作成する
	hr = CreateGameWindow();
	if (FAILED(hr))
		return hr;

	// Graphicクラスを初期化する
	hr = InitGraphic();
	if (FAILED(hr))
		return hr;

	// Soundクラスを初期化する
	hr = Sound::Init();
	if (FAILED(hr))
		return hr;

	// Timeクラスを初期化する
	hr = InitTime();
	if (FAILED(hr))
		return hr;

	// ウィンドウを可視化する
	ShowWindow(hWnd, SW_SHOW);

	return S_OK;

}

// ゲームループを実行するかどうかを返す
BOOL Game::GameLoop() {

	// メッセージの有無を取得する
	if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
		// メッセージがある場合

		// メッセージを取得する
		if (0 == GetMessage(&msg, NULL, 0, 0))
			return false;	// メッセージがWM_QUITである場合、falseを返す

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;

}

// ゲームループの開始処理を行う
VOID Game::LoopStart() {

	// FPSを計算する
	Time::CalculateFPS();

	// Direct2D1の描画を開始する
	pRenderTarget->BeginDraw();

	// 背景をクリアする
	pRenderTarget->Clear(ColorF(0.0f, 0.0f, 0.0f, 1.0f));

}

// ゲームループの終了処理を行う
VOID Game::LoopEnd() {

	pRenderTarget->EndDraw();

	// スリープをはさむ
	timeBeginPeriod(1);
	Sleep(Time::GetSleepTime());
	timeEndPeriod(1);

}

// 終了処理を行う
VOID Game::Quit() {

}