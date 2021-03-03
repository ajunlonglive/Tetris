#pragma once

#include "Core.hpp"
#include "Core_Window.hpp"


class Core_Sound : private Core, private Core_Window {

private:
	// Core_Sound�N���X������������
	static HRESULT Init();

protected:
	static Microsoft::WRL::ComPtr<IDirectSound> pDirectSound;	// DirectSound


	friend class Game;	// Game�N���X���t�����h�N���X�Ɏw�肷��

};