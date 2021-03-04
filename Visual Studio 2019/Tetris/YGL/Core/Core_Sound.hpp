#pragma once

#include "Core.hpp"
#include "Core_Window.hpp"


class Core_Sound : private Core, private Core_Window {

private:
	// �������������s��
	static HRESULT Init();

	// �I���������s��
	static VOID Quit();

protected:
	static IDirectSound* pDirectSound;	// DirectSound


	friend class Game;	// Game�N���X���t�����h�N���X�Ɏw�肷��

};