#pragma once

#include "Core.hpp"
#include "Core_Window.hpp"


class Core_Sound : private Core, private Core_Window {

private:
	// 初期化処理を行う
	static HRESULT Init();

	// 終了処理を行う
	static VOID Quit();

protected:
	static IDirectSound* pDirectSound;	// DirectSound


	friend class Game;	// Gameクラスをフレンドクラスに指定する

};