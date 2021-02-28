#include "Sound.hpp"


ComPtr<IDirectSound> Sound::pDirectSound = nullptr;

HRESULT Sound::Init() {
	
	HRESULT hr = S_OK;

	// DirectSound�𐶐�����
	hr = DirectSoundCreate(NULL, pDirectSound.GetAddressOf(), NULL);
	if (FAILED(hr))
		return hr;

	// �������x����ݒ肷��
	hr = pDirectSound->SetCooperativeLevel(hWnd, DSSCL_NORMAL);
	if (FAILED(hr))
		return hr;

	return S_OK;

}

// �R���X�g���N�^
SE::SE() {
	pSoundBuffer = nullptr;
	pData = NULL;
	DataSize = 0;
}

// �f�X�g���N�^
SE::~SE() {

	if (pData != NULL) {
		HeapFree(GetProcessHeap(), 0, pData);
	}

}

// WAV�t�@�C����ǂݍ���
HRESULT SE::Load(LPCTSTR FileName) {
	
	// �t�@�C�����J��
	HMMIO hmmio = mmioOpen((LPTSTR)FileName, NULL, MMIO_READ);
	if (hmmio == NULL)
		return E_FAIL;


	MMCKINFO mmckRiff = { 0 };
	mmckRiff.fccType = mmioStringToFOURCC(TEXT("WAVE"), 0);
	if (mmioDescend(hmmio, &mmckRiff, NULL, MMIO_FINDRIFF) != MMSYSERR_NOERROR) {	// RIFF�`�����N�ɐi������
		// �Ώۃt�@�C����WAV�t�@�C���łȂ������ꍇ
		mmioClose(hmmio, MMIO_FHOPEN);	// �t�@�C�������
		return E_FAIL;
	}

	WAVEFORMATEX pwfxFormat = { 0 };	// �g�`�t�H�[�}�b�g
	MMCKINFO mmckFmt = { 0 };
	mmckFmt.ckid = mmioStringToFOURCC(TEXT("fmt "), 0);
	if (mmioDescend(hmmio, &mmckFmt, NULL, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {	// fmt �`�����N�ɐi������
		// fmt �`�����N�ɐi���ł��Ȃ������ꍇ
		mmioClose(hmmio, MMIO_FHOPEN);	// �t�@�C�������
		return E_FAIL;
	}
	mmioRead(hmmio, (HPSTR)&pwfxFormat, mmckFmt.cksize);	// �`�����N�̓��e��ǂݍ���
	mmioAscend(hmmio, &mmckFmt, 0);	// fmt �`�����N����ޏo����
	if (pwfxFormat.wFormatTag != WAVE_FORMAT_PCM) {
		// �Ώۃt�@�C���̃t�H�[�}�b�g��PCM�łȂ������ꍇ
		mmioClose(hmmio, MMIO_FHOPEN);	// �t�@�C�������
		return E_FAIL;
	}


	MMCKINFO mmckData = { 0 };
	mmckData.ckid = mmioStringToFOURCC(TEXT("data"), 0);
	if (mmioDescend(hmmio, &mmckData, NULL, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {	// data�`�����N�ɐi������
		// ���s�����ꍇ
		mmioClose(hmmio, MMIO_FHOPEN);	// �t�@�C�������
		return E_FAIL;
	}
	pData = (LPBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, mmckData.cksize);	// WAV�f�[�^���i�[���邽�߂Ƀq�[�v�����������蓖�Ă�
	mmioRead(hmmio, (HPSTR)pData, mmckData.cksize);	// WAV�f�[�^��ǂݍ��݁A���蓖�Ă�ꂽ�������ɏ����o��
	mmioAscend(hmmio, &mmckData, 0);	// data�`�����N����ޏo����
	DataSize = mmckData.cksize;

	mmioAscend(hmmio, &mmckRiff, 0);	// RIFF�`�����N����ޏo����
	mmioClose(hmmio, MMIO_FHOPEN);	// �t�@�C�������


	// �T�E���h�o�b�t�@�̏���ݒ肷��
	DSBUFFERDESC DSBufferDesc = { 0 };
	DSBufferDesc.dwSize = sizeof(DSBUFFERDESC);
	DSBufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	DSBufferDesc.dwBufferBytes = DataSize;	// WAV�f�[�^�̃T�C�Y
	DSBufferDesc.guid3DAlgorithm = DS3DALG_DEFAULT;
	DSBufferDesc.lpwfxFormat = &pwfxFormat;	// �g�`�t�H�[�}�b�g

	// �T�E���h�o�b�t�@���쐬����
	HRESULT hr = S_OK;
	hr = pDirectSound->CreateSoundBuffer(&DSBufferDesc, &pSoundBuffer, NULL);
	if (FAILED(hr)) {
		return hr;
	}

	LPVOID pAudioPtr = NULL;
	DWORD pAudioBytes = 0;
	// �g�`�f�[�^���������ނ��߂ɃT�E���h�o�b�t�@�����b�N����
	hr = pSoundBuffer->Lock(0, mmckData.cksize, &pAudioPtr, &pAudioBytes, NULL, NULL, 0);
	if (FAILED(hr)) {
		return hr;
	}

	// �Z�J���_���o�b�t�@�ɉ��f�[�^���R�s�[����
	memcpy(pAudioPtr, pData, DataSize);

	// �o�b�t�@���A�����b�N����
	pSoundBuffer->Unlock(&pAudioPtr, pAudioBytes, NULL, NULL);


	return S_OK;
}

// �������Đ�����
VOID SE::Play() {

	pSoundBuffer->Play(0, 0, 0);

}


// �R���X�g���N�^
BGM::BGM() {
	pSoundBuffer = nullptr;
	pData = NULL;
	DataSize = 0;
}

// �f�X�g���N�^
BGM::~BGM() {

	if (pData != NULL) {
		HeapFree(GetProcessHeap(), 0, pData);
	}

}

// WAV�t�@�C����ǂݍ���
HRESULT BGM::Load(LPCTSTR FileName) {

	// �t�@�C�����J��
	HMMIO hmmio = mmioOpen((LPTSTR)FileName, NULL, MMIO_READ);
	if (hmmio == NULL)
		return E_FAIL;


	MMCKINFO mmckRiff = { 0 };
	mmckRiff.fccType = mmioStringToFOURCC(TEXT("WAVE"), 0);
	if (mmioDescend(hmmio, &mmckRiff, NULL, MMIO_FINDRIFF) != MMSYSERR_NOERROR) {	// RIFF�`�����N�ɐi������
		// �Ώۃt�@�C����WAV�t�@�C���łȂ������ꍇ
		mmioClose(hmmio, MMIO_FHOPEN);	// �t�@�C�������
		return E_FAIL;
	}

	WAVEFORMATEX pwfxFormat = { 0 };	// �g�`�t�H�[�}�b�g
	MMCKINFO mmckFmt = { 0 };
	mmckFmt.ckid = mmioStringToFOURCC(TEXT("fmt "), 0);
	if (mmioDescend(hmmio, &mmckFmt, NULL, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {	// fmt �`�����N�ɐi������
		// fmt �`�����N�ɐi���ł��Ȃ������ꍇ
		mmioClose(hmmio, MMIO_FHOPEN);	// �t�@�C�������
		return E_FAIL;
	}
	mmioRead(hmmio, (HPSTR)&pwfxFormat, mmckFmt.cksize);	// �`�����N�̓��e��ǂݍ���
	mmioAscend(hmmio, &mmckFmt, 0);	// fmt �`�����N����ޏo����
	if (pwfxFormat.wFormatTag != WAVE_FORMAT_PCM) {
		// �Ώۃt�@�C���̃t�H�[�}�b�g��PCM�łȂ������ꍇ
		mmioClose(hmmio, MMIO_FHOPEN);	// �t�@�C�������
		return E_FAIL;
	}


	MMCKINFO mmckData = { 0 };
	mmckData.ckid = mmioStringToFOURCC(TEXT("data"), 0);
	if (mmioDescend(hmmio, &mmckData, NULL, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {	// data�`�����N�ɐi������
		// ���s�����ꍇ
		mmioClose(hmmio, MMIO_FHOPEN);	// �t�@�C�������
		return E_FAIL;
	}
	pData = (LPBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, mmckData.cksize);	// WAV�f�[�^���i�[���邽�߂Ƀq�[�v�����������蓖�Ă�
	mmioRead(hmmio, (HPSTR)pData, mmckData.cksize);	// WAV�f�[�^��ǂݍ��݁A���蓖�Ă�ꂽ�������ɏ����o��
	mmioAscend(hmmio, &mmckData, 0);	// data�`�����N����ޏo����
	DataSize = mmckData.cksize;

	mmioAscend(hmmio, &mmckRiff, 0);	// RIFF�`�����N����ޏo����
	mmioClose(hmmio, MMIO_FHOPEN);	// �t�@�C�������


	// �T�E���h�o�b�t�@�̏���ݒ肷��
	DSBUFFERDESC DSBufferDesc = { 0 };
	DSBufferDesc.dwSize = sizeof(DSBUFFERDESC);
	DSBufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	DSBufferDesc.dwBufferBytes = DataSize;	// WAV�f�[�^�̃T�C�Y
	DSBufferDesc.guid3DAlgorithm = DS3DALG_DEFAULT;
	DSBufferDesc.lpwfxFormat = &pwfxFormat;	// �g�`�t�H�[�}�b�g

	// �T�E���h�o�b�t�@���쐬����
	HRESULT hr = S_OK;
	hr = pDirectSound->CreateSoundBuffer(&DSBufferDesc, &pSoundBuffer, NULL);
	if (FAILED(hr)) {
		return hr;
	}

	LPVOID pAudioPtr = NULL;
	DWORD pAudioBytes = 0;
	// �g�`�f�[�^���������ނ��߂ɃT�E���h�o�b�t�@�����b�N����
	hr = pSoundBuffer->Lock(0, mmckData.cksize, &pAudioPtr, &pAudioBytes, NULL, NULL, 0);
	if (FAILED(hr)) {
		return hr;
	}

	// �Z�J���_���o�b�t�@�ɉ��f�[�^���R�s�[����
	memcpy(pAudioPtr, pData, DataSize);

	// �o�b�t�@���A�����b�N����
	pSoundBuffer->Unlock(&pAudioPtr, pAudioBytes, NULL, NULL);


	return S_OK;
}

// �������Đ�����
VOID BGM::Play() {

	pSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);

}

// �������~����
VOID BGM::Stop() {

	pSoundBuffer->Stop();

}