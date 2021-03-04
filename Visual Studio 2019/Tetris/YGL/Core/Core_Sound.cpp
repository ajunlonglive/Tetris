#include "Core_Sound.hpp"


// 初期化処理を行う
HRESULT Core_Sound::Init() {

	HRESULT hr = S_OK;

	// DirectSoundを生成する
	hr = DirectSoundCreate(NULL, &pDirectSound, NULL);
	if (FAILED(hr)) {
		return hr;
	}

	// 協調レベルを設定する
	hr = pDirectSound->SetCooperativeLevel(hWnd, DSSCL_NORMAL);
	if (FAILED(hr)) {
		return hr;
	}

	return S_OK;

}

// 終了処理を行う
VOID Core_Sound::Quit() {

	SafeRelease(&pDirectSound);

}

IDirectSound* Core_Sound::pDirectSound = NULL;	// DirectSound