#pragma once

#include "Core.hpp"


class Window {

private:
	// ウィンドウプロシージャ
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

protected:
	static UINT WindowWidth, WindowHeight;	// ウィンドウの幅と高さ(ウィンドウモードの場合のみに影響する)
	static LPCWSTR WindowTitle;	// ウィンドウのタイトル(ウィンドウモードの場合のみに影響する)
	static HWND hWnd;	// ウィンドウハンドル
	static MSG msg;	// ウィンドウメッセージ

	// ゲームウィンドウを生成する
	static HRESULT CreateGameWindow();

};