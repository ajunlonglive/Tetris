#pragma once

#include "Core.hpp"


// **************************************************
// Core_Time�N���X
// **************************************************
/*
	�y�T�v�z
	�@���̃N���X�̓Q�[�����[�v���̓K�؂ȃX���[�v���Ԃ̎Z�o�ƁA���A���^�C����FPS�l�̌v�����s���B
	 YGL���p�҂͂��̃N���X���p������Time�N���X��p����FPS�l�̗��p���ׂ��B

	 �y�����z
	 �@���̃N���X����������ɂ������� http://dioltista.blogspot.com/2019/04/c-directx11-fps.html ���Q�l�ɂ����B
*/

class Core_Time : private Core {

private:
	static LARGE_INTEGER Frequency;	// �^�C�}�[(�p�t�H�[�}���X�J�E���^)�̎��g��
	static LARGE_INTEGER StartTime;	// FPS�v���J�n���̃^�C���X�^���v
	static LARGE_INTEGER NowTime;	// FPS�v���I�����̃^�C���X�^���v
	static INT Count;	// �t���[���̃J�E���g(0~���t���b�V�����[�g) ��������x�����s���鏉���������̓s����A�����l��-1�ƒ�߂�

	// �������������s��
	static HRESULT Init();

	// �I���������s��
	static VOID Quit();

	// ���݂�FPS���v�Z����
	static VOID CalculateFPS();

	// �Q�[�����[�v�ɂăX���[�v���s������[ms]�𓾂�
	static DWORD GetSleepTime();

protected:
	static DWORD RefreshRate;	// ���j�^�[�̃��t���b�V�����[�g
	static DOUBLE FPS;	// 1�b������̏�����


	friend class Game;	// Game�N���X���t�����h�N���X�Ɏw�肷��

};