#include "Core_Sound.hpp"


// Core_SoundƒNƒ‰ƒX‚ð‰Šú‰»‚·‚é
HRESULT Core_Sound::Init() {

	HRESULT hr = S_OK;

	// DirectSound‚ð¶¬‚·‚é
	hr = DirectSoundCreate(NULL, pDirectSound.GetAddressOf(), NULL);
	if (FAILED(hr)) {
		return hr;
	}

	// ‹¦’²ƒŒƒxƒ‹‚ðÝ’è‚·‚é
	hr = pDirectSound->SetCooperativeLevel(hWnd, DSSCL_NORMAL);
	if (FAILED(hr)) {
		return hr;
	}

	return S_OK;

}

Microsoft::WRL::ComPtr<IDirectSound> Core_Sound::pDirectSound = nullptr;	// DirectSound