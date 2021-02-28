#pragma once

#include "Core/Core.hpp"
#include "Core/Window.hpp"


class Sound : private Window {

protected:
	static ComPtr<IDirectSound> pDirectSound;

	static HRESULT Init();

};

class SE : public Sound {
private:
	ComPtr<IDirectSoundBuffer> pSoundBuffer;
	LPBYTE pData;
	DWORD DataSize;
public:
	SE();
	~SE();
	HRESULT Load(LPCTSTR FileName);
	VOID Play();
};

class BGM : public Sound {
private:
	ComPtr<IDirectSoundBuffer> pSoundBuffer;
	LPBYTE pData;
	DWORD DataSize;
public:
	BGM();
	~BGM();
	HRESULT Load(LPCTSTR FileName);
	VOID Play();
	VOID Stop();
};