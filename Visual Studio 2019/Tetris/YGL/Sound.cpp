#include "Sound.hpp"


// �R���X�g���N�^
Sound::Sound() {

	pSoundBuffer = NULL;
	pData = NULL;
	DataSize = 0;

}

// �f�X�g���N�^
Sound::~Sound() {

	Unload();

}

// �����t�@�C������f�[�^��ǂݍ���
YGL_ERROR Sound::Load(const wchar_t* FileName) {

	// �t�@�C�����J��
	HMMIO hmmio = mmioOpen((LPTSTR)FileName, NULL, MMIO_READ);
	if (hmmio == NULL) {
		return YGL_ERROR_UNKNOWN;
	}


	MMCKINFO mmckRiff = { 0 };
	mmckRiff.fccType = mmioStringToFOURCC(TEXT("WAVE"), 0);
	if (mmioDescend(hmmio, &mmckRiff, NULL, MMIO_FINDRIFF) != MMSYSERR_NOERROR) {	// RIFF�`�����N�ɐi������
		// �Ώۃt�@�C����WAV�t�@�C���łȂ������ꍇ
		mmioClose(hmmio, MMIO_FHOPEN);	// �t�@�C�������
		return YGL_ERROR_UNKNOWN;
	}

	WAVEFORMATEX pwfxFormat = { 0 };	// �g�`�t�H�[�}�b�g
	MMCKINFO mmckFmt = { 0 };
	mmckFmt.ckid = mmioStringToFOURCC(TEXT("fmt "), 0);
	if (mmioDescend(hmmio, &mmckFmt, NULL, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {	// fmt �`�����N�ɐi������
		// fmt �`�����N�ɐi���ł��Ȃ������ꍇ
		mmioClose(hmmio, MMIO_FHOPEN);	// �t�@�C�������
		return YGL_ERROR_UNKNOWN;
	}
	mmioRead(hmmio, (HPSTR)&pwfxFormat, mmckFmt.cksize);	// �`�����N�̓��e��ǂݍ���
	mmioAscend(hmmio, &mmckFmt, 0);	// fmt �`�����N����ޏo����
	if (pwfxFormat.wFormatTag != WAVE_FORMAT_PCM) {
		// �Ώۃt�@�C���̃t�H�[�}�b�g��PCM�łȂ������ꍇ
		mmioClose(hmmio, MMIO_FHOPEN);	// �t�@�C�������
		return YGL_ERROR_UNKNOWN;
	}


	MMCKINFO mmckData = { 0 };
	mmckData.ckid = mmioStringToFOURCC(TEXT("data"), 0);
	if (mmioDescend(hmmio, &mmckData, NULL, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {	// data�`�����N�ɐi������
		// ���s�����ꍇ
		mmioClose(hmmio, MMIO_FHOPEN);	// �t�@�C�������
		return YGL_ERROR_UNKNOWN;
	}
	pData = (LPBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, mmckData.cksize);	// WAV�f�[�^���i�[���邽�߂Ƀq�[�v�����������蓖�Ă�
	mmioRead(hmmio, (HPSTR)pData, mmckData.cksize);	// WAV�f�[�^��ǂݍ��݁A���蓖�Ă�ꂽ�������ɏ����o��
	mmioAscend(hmmio, &mmckData, 0);	// data�`�����N����ޏo����
	DataSize = mmckData.cksize;	// �����f�[�^�̃T�C�Y��ݒ肷��

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
		// �q�[�v���������������
		HeapFree(GetProcessHeap(), 0, pData);
		pData = NULL;
		DataSize = 0;
		return Convert_HRESULT_ToError(hr);
	}

	LPVOID pAudioPtr = NULL;
	DWORD pAudioBytes = 0;
	// �g�`�f�[�^���������ނ��߂ɃT�E���h�o�b�t�@�����b�N����
	hr = pSoundBuffer->Lock(0, mmckData.cksize, &pAudioPtr, &pAudioBytes, NULL, NULL, 0);
	if (FAILED(hr)) {
		// �q�[�v���������������
		HeapFree(GetProcessHeap(), 0, pData);
		pData = NULL;
		DataSize = 0;
		return Convert_HRESULT_ToError(hr);
	}

	// �Z�J���_���o�b�t�@�ɉ��f�[�^���R�s�[����
	memcpy(pAudioPtr, pData, DataSize);

	// �o�b�t�@���A�����b�N����
	pSoundBuffer->Unlock(&pAudioPtr, pAudioBytes, NULL, NULL);


	return YGL_ERROR_SUCCESS;
}

// �ǂݍ��񂾉����t�@�C���̃f�[�^���������
void Sound::Unload() {

	// �T�E���h�o�b�t�@���������
	SafeRelease(&pSoundBuffer);

	// �q�[�v���������������
	if (pData != NULL) {
		HeapFree(GetProcessHeap(), 0, pData);
		pData = NULL;
	}

	// �f�[�^�T�C�Y��0�Ɛݒ肷��
	DataSize = 0;

}

// �������Đ�����
void Sound::Play(bool repeat) {

	if (repeat) {
		pSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
	}
	else {
		pSoundBuffer->Play(0, 0, 0);
	}

}

// �������~����
void Sound::Stop() {

	pSoundBuffer->Stop();

}