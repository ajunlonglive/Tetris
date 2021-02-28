#pragma once

#include "Core/Core.hpp"
#include "Core/Window.hpp"
#include "Graphic.hpp"


// 設定クラス
class Config : private Window, private Graphic {

public:
	// ウィンドウのサイズを設定する(ウィンドウモードの場合のみに影響する)
	static VOID SetWindowSize(UINT Width, UINT Height);

	// ウィンドウのタイトルを設定する(ウィンドウモードの場合のみに影響する)
	static VOID SetWindowTitle(LPCWSTR str);

	// キャンバスのサイズを設定する
	static VOID SetCanvasSize(UINT Width, UINT Height);

	// ウィンドウモードにするかどうかを設定する
	static VOID SetWindowMode(BOOL b);

};