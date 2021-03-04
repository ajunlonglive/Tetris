#pragma once

#include "Core/Core.hpp"
#include "Core/Core_Sound.hpp"


class Sound : private Core, private Core_Sound {

private:
	IDirectSoundBuffer* pSoundBuffer;	// サウンドバッファ
	LPBYTE pData;	// サウンドの生データ
	DWORD DataSize;	// 生データのサイズ

public:
	// コンストラクタ
	Sound();

	// デストラクタ
	~Sound();

	// 音声ファイルからデータを読み込む
	YGL_ERROR Load(const wchar_t* FileName);

	// 読み込んだ音声ファイルのデータを解放する
	void Unload();

	// 再生する
	void Play(bool repeat);

	// 停止する
	void Stop();

};