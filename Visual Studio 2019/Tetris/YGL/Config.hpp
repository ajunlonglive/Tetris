#pragma once

#include "Core/Core.hpp"
#include "Core/Core_Window.hpp"
#include "Core/Core_Graphic.hpp"


// **************************************************
// Configクラス
// **************************************************
/*
	【概要】
	　YGLの設定を受けつけるクラス。
	 Game::Init()が呼び出されたあとにこのクラスのメソッドを呼び出すことは禁止である。

	【メモ】
	　このクラスは Core_Windowクラス、Core_Graphicクラス によってフレンドクラスとして指定されている。
	 そのためこのクラスは上記のクラスのprivateメンバとprotectedメンバにもアクセスできる。
*/

class Config : private Core {

public:
	// ウィンドウモードであるかを設定する
	static void SetWindowMode(bool b);

	// ウィンドウのタイトルを設定する
	static void SetWindowTitle(const wchar_t* str);

	// ウィンドウのサイズ(正確にはクライアント領域のサイズ)を設定する
	static void SetWindowSize(SIZE_UINT Size);

	// キャンバスのサイズを設定する
	static void SetCanvasSize(SIZE_UINT Size);

};