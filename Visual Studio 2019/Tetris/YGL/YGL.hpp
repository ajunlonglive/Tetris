#pragma once

#include "Core/Core.hpp"
#include "Core/Window.hpp"
#include "Config.hpp"
#include "Time.hpp"
#include "Graphic.hpp"
#include "Picture.hpp"
#include "Text.hpp"
#include "Sound.hpp"


class Game : private Window, private Graphic, private Time, private Sound {

public:
	// 初期化処理を行う
	static HRESULT Init();

	// ゲームループを実行するかどうかを返す
	static BOOL GameLoop();

	// ゲームループの開始処理を行う
	static VOID LoopStart();

	// ゲームループの終了処理を行う
	static VOID LoopEnd();

	// 終了処理を行う
	static VOID Quit();

};