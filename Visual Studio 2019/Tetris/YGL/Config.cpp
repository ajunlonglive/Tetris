#include "Config.hpp"


// ウィンドウモードであるかを設定する
void Config::SetWindowMode(bool b) {

	if (b == true) {
		Core_Window::Windowed = TRUE;
	}
	else {
		Core_Window::Windowed = FALSE;
	}

}

// ウィンドウのタイトルを設定する
void Config::SetWindowTitle(const wchar_t* str) {

	Core_Window::WindowTitle = str;

}

// ウィンドウのサイズ(正確にはクライアント領域のサイズ)を設定する
void Config::SetWindowSize(SIZE_UINT Size) {

	Core_Window::WindowSize.Width = Size.Width;
	Core_Window::WindowSize.Height = Size.Height;

}

// キャンバスのサイズを設定する
void Config::SetCanvasSize(SIZE_UINT Size) {

	Core_Graphic::CanvasSize.Width = Size.Width;
	Core_Graphic::CanvasSize.Height = Size.Height;

}