#pragma once

#include "Core.hpp"
#include "Core_Window.hpp"


class Core_Sound : private Core, private Core_Window {

private:
	// Core_Soundクラスを初期化する
	static HRESULT Init();

protected:
	static Microsoft::WRL::ComPtr<IDirectSound> pDirectSound;	// DirectSound


	friend class Game;	// Gameクラスをフレンドクラスに指定する

};