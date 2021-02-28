#include "Config.hpp"


// ウィンドウのサイズを設定する(ウィンドウモードの場合のみに影響する)
VOID Config::SetWindowSize(UINT Width, UINT Height) {

	WindowWidth = Width;
	WindowHeight = Height;

}

// ウィンドウのタイトルを設定する(ウィンドウモードの場合のみに影響する)
VOID Config::SetWindowTitle(LPCWSTR str) {

	WindowTitle = str;

}

// キャンバスのサイズを設定する
VOID Config::SetCanvasSize(UINT Width, UINT Height) {

	CanvasWidth = Width;
	CanvasHeight = Height;

}

// ウィンドウモードにするかどうかを設定する
VOID Config::SetWindowMode(BOOL b) {

	Windowed = b;

}