#pragma once

#include "Core/Core.hpp"
#include "Core/Core_Sound.hpp"


class Sound : private Core, private Core_Sound {

private:
	IDirectSoundBuffer* pSoundBuffer;	// �T�E���h�o�b�t�@
	LPBYTE pData;	// �T�E���h�̐��f�[�^
	DWORD DataSize;	// ���f�[�^�̃T�C�Y

public:
	// �R���X�g���N�^
	Sound();

	// �f�X�g���N�^
	~Sound();

	// �����t�@�C������f�[�^��ǂݍ���
	YGL_ERROR Load(const wchar_t* FileName);

	// �ǂݍ��񂾉����t�@�C���̃f�[�^���������
	void Unload();

	// �Đ�����
	void Play(bool repeat);

	// ��~����
	void Stop();

};