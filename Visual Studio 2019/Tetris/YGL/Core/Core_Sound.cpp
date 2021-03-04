#include "Core_Sound.hpp"


// �������������s��
HRESULT Core_Sound::Init() {

	HRESULT hr = S_OK;

	// DirectSound�𐶐�����
	hr = DirectSoundCreate(NULL, &pDirectSound, NULL);
	if (FAILED(hr)) {
		return hr;
	}

	// �������x����ݒ肷��
	hr = pDirectSound->SetCooperativeLevel(hWnd, DSSCL_NORMAL);
	if (FAILED(hr)) {
		return hr;
	}

	return S_OK;

}

// �I���������s��
VOID Core_Sound::Quit() {

	SafeRelease(&pDirectSound);

}

IDirectSound* Core_Sound::pDirectSound = NULL;	// DirectSound