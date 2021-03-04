#include "Sound.hpp"


// コンストラクタ
Sound::Sound() {

	pSoundBuffer = NULL;
	pData = NULL;
	DataSize = 0;

}

// デストラクタ
Sound::~Sound() {

	Unload();

}

// 音声ファイルからデータを読み込む
YGL_ERROR Sound::Load(const wchar_t* FileName) {

	// ファイルを開く
	HMMIO hmmio = mmioOpen((LPTSTR)FileName, NULL, MMIO_READ);
	if (hmmio == NULL) {
		return YGL_ERROR_UNKNOWN;
	}


	MMCKINFO mmckRiff = { 0 };
	mmckRiff.fccType = mmioStringToFOURCC(TEXT("WAVE"), 0);
	if (mmioDescend(hmmio, &mmckRiff, NULL, MMIO_FINDRIFF) != MMSYSERR_NOERROR) {	// RIFFチャンクに進入する
		// 対象ファイルがWAVファイルでなかった場合
		mmioClose(hmmio, MMIO_FHOPEN);	// ファイルを閉じる
		return YGL_ERROR_UNKNOWN;
	}

	WAVEFORMATEX pwfxFormat = { 0 };	// 波形フォーマット
	MMCKINFO mmckFmt = { 0 };
	mmckFmt.ckid = mmioStringToFOURCC(TEXT("fmt "), 0);
	if (mmioDescend(hmmio, &mmckFmt, NULL, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {	// fmt チャンクに進入する
		// fmt チャンクに進入できなかった場合
		mmioClose(hmmio, MMIO_FHOPEN);	// ファイルを閉じる
		return YGL_ERROR_UNKNOWN;
	}
	mmioRead(hmmio, (HPSTR)&pwfxFormat, mmckFmt.cksize);	// チャンクの内容を読み込む
	mmioAscend(hmmio, &mmckFmt, 0);	// fmt チャンクから退出する
	if (pwfxFormat.wFormatTag != WAVE_FORMAT_PCM) {
		// 対象ファイルのフォーマットがPCMでなかった場合
		mmioClose(hmmio, MMIO_FHOPEN);	// ファイルを閉じる
		return YGL_ERROR_UNKNOWN;
	}


	MMCKINFO mmckData = { 0 };
	mmckData.ckid = mmioStringToFOURCC(TEXT("data"), 0);
	if (mmioDescend(hmmio, &mmckData, NULL, MMIO_FINDCHUNK) != MMSYSERR_NOERROR) {	// dataチャンクに進入する
		// 失敗した場合
		mmioClose(hmmio, MMIO_FHOPEN);	// ファイルを閉じる
		return YGL_ERROR_UNKNOWN;
	}
	pData = (LPBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, mmckData.cksize);	// WAVデータを格納するためにヒープメモリを割り当てる
	mmioRead(hmmio, (HPSTR)pData, mmckData.cksize);	// WAVデータを読み込み、割り当てられたメモリに書き出す
	mmioAscend(hmmio, &mmckData, 0);	// dataチャンクから退出する
	DataSize = mmckData.cksize;	// 音声データのサイズを設定する

	mmioAscend(hmmio, &mmckRiff, 0);	// RIFFチャンクから退出する
	mmioClose(hmmio, MMIO_FHOPEN);	// ファイルを閉じる


	// サウンドバッファの情報を設定する
	DSBUFFERDESC DSBufferDesc = { 0 };
	DSBufferDesc.dwSize = sizeof(DSBUFFERDESC);
	DSBufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
	DSBufferDesc.dwBufferBytes = DataSize;	// WAVデータのサイズ
	DSBufferDesc.guid3DAlgorithm = DS3DALG_DEFAULT;
	DSBufferDesc.lpwfxFormat = &pwfxFormat;	// 波形フォーマット

	// サウンドバッファを作成する
	HRESULT hr = S_OK;
	hr = pDirectSound->CreateSoundBuffer(&DSBufferDesc, &pSoundBuffer, NULL);
	if (FAILED(hr)) {
		// ヒープメモリを解放する
		HeapFree(GetProcessHeap(), 0, pData);
		pData = NULL;
		DataSize = 0;
		return Convert_HRESULT_ToError(hr);
	}

	LPVOID pAudioPtr = NULL;
	DWORD pAudioBytes = 0;
	// 波形データを書き込むためにサウンドバッファをロックする
	hr = pSoundBuffer->Lock(0, mmckData.cksize, &pAudioPtr, &pAudioBytes, NULL, NULL, 0);
	if (FAILED(hr)) {
		// ヒープメモリを解放する
		HeapFree(GetProcessHeap(), 0, pData);
		pData = NULL;
		DataSize = 0;
		return Convert_HRESULT_ToError(hr);
	}

	// セカンダリバッファに音データをコピーする
	memcpy(pAudioPtr, pData, DataSize);

	// バッファをアンロックする
	pSoundBuffer->Unlock(&pAudioPtr, pAudioBytes, NULL, NULL);


	return YGL_ERROR_SUCCESS;
}

// 読み込んだ音声ファイルのデータを解放する
void Sound::Unload() {

	// サウンドバッファを解放する
	SafeRelease(&pSoundBuffer);

	// ヒープメモリを解放する
	if (pData != NULL) {
		HeapFree(GetProcessHeap(), 0, pData);
		pData = NULL;
	}

	// データサイズを0と設定する
	DataSize = 0;

}

// 音声を再生する
void Sound::Play(bool repeat) {

	if (repeat) {
		pSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
	}
	else {
		pSoundBuffer->Play(0, 0, 0);
	}

}

// 音声を停止する
void Sound::Stop() {

	pSoundBuffer->Stop();

}