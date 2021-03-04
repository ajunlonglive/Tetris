#pragma once

#include "Core.hpp"


class Core_Window : private Core {

private:
	static BOOL Windowed;	// ウィンドウモードであるか
	static LPCWSTR WindowTitle;	// ウィンドウのタイトル
	static MSG msg;	// ウィンドウメッセージ
	static UINT SideSpaceSize, VerticalSpaceSize;	// フルスクリーン時にウィンドウの縦横比とスクリーンの縦横比が一致しなかったときに生じる黒いスペースのサイズ

	// 初期化処理を行う
	static HRESULT Init();

	// 終了処理を行う
	static VOID Quit();

	// ウィンドウプロシージャ
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	static SIZE_UINT WindowSize;	// ウィンドウのサイズ(正確にはクライアント領域のサイズ)
	static HWND hWnd;	// ウィンドウハンドル


	friend class Game;	// Gameクラスをフレンドクラスに指定する
	friend class Config;	// Configクラスをフレンドクラスに指定する

};