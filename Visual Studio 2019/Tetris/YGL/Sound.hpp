#pragma once

#include "Core/Core.hpp"
#include "Core/Core_Sound.hpp"


class Sound : private Core, private Core_Sound {

private:
	Microsoft::WRL::ComPtr<IDirectSoundBuffer> pSoundBuffer;	// サウンドバッファ
	LPBYTE pData;	// サウンドの生データ
	DWORD DataSize;	// 生データのサイズ

public:
	// コンストラクタ
	Sound();

	// デストラクタ
	~Sound();

	// WAVファイルを読み込む
	YGL_ERROR Load(const wchar_t* FileName);

	// 再生する
	void Play(bool repeat);

	// 停止する
	void Stop();

};