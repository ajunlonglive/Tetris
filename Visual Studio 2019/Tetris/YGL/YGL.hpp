#pragma once

#include "Core/Core.hpp"
#include "Core/Core_Window.hpp"
#include "Core/Core_Graphic.hpp"
#include "Core/Core_Sound.hpp"
#include "Core/Core_Time.hpp"
#include "Config.hpp"
#include "Graphic.hpp"
#include "Picture.hpp"
#include "Text.hpp"
#include "Sound.hpp"
#include "Time.hpp"


// **************************************************
// Gameクラス
// **************************************************
/*
	【概要】
	　YGLを動作させるためにベースとなるウィンドウの作成やDirect2D等の初期化と終了処理を受けつけ、
	またゲームループなどのゲームの基本的な処理を提供する。

	【メモ】
	　このクラスは Core_Windowクラス、Core_Graphicクラス、Core_Soundクラス、Core_Timeクラス によってフレンドクラスとして指定されている。
	 そのためこのクラスは上記のクラスのprivateメンバとprotectedメンバにもアクセスできる。
*/

class Game : private Core {

public:
	// YGLの初期化処理を行う
	static YGL_ERROR Init();

	// ゲームループを実行するかを返す
	static bool GameLoop();

	// ゲームループの開始処理を行う
	static void LoopStart();

	// ゲームループの終了処理を行う
	static void LoopEnd();

	// YGLの終了処理を行う
	static void Quit();

};