#include "Core_Sound.hpp"


// Core_Sound�N���X������������
HRESULT Core_Sound::Init() {

	HRESULT hr = S_OK;

	// DirectSound�𐶐�����
	hr = DirectSoundCreate(NULL, pDirectSound.GetAddressOf(), NULL);
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

Microsoft::WRL::ComPtr<IDirectSound> Core_Sound::pDirectSound = nullptr;	// DirectSound