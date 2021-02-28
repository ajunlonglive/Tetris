#pragma once

#include "Core/Core.hpp"


class Time {

	/*

	�@1�b�ԂɃQ�[�����[�v�����s�����񐔂̓��j�^�[�̃��t���b�V�����[�g�̒l(�ʏ��60�A�H��120)�Ɠ����ł���B
	����1�b�Ԃɏ������s����񐔂̓t���[�����[�g(FPS)�ƌĂт΂�Ă���A����Ɋ�Â��Ď��Ԃ������ׂ��ł���B
	���̂��߁A���̃N���X�̓��A���^�C����FPS�̒l���v�����A���Ԃ̈������ȈՉ�������(�����ăQ�[�����[�v���ł̃X���[�v���Ԃ̒������s��)�B

	�@���̃N���X����������ɂ������� http://dioltista.blogspot.com/2019/04/c-directx11-fps.html ���Q�l�ɂ����B
	�ϐ��̖����������łȂ����߁A�܂��A���S���Y�����������G�ł��邽�߉��ς���ۂɂ͏�LURL���Q�Ƃ���B

	*/

private:
	static DWORD RefreshRate;	// ���j�^�[�̃��t���b�V�����[�g
	static DOUBLE FPS;	// 1�b������̏�����
	static LARGE_INTEGER Frequency;	// �^�C�}�[(�p�t�H�[�}���X�J�E���^)�̎��g��
	static LARGE_INTEGER StartTime;	// FPS�v���J�n���̃^�C���X�^���v
	static LARGE_INTEGER NowTime;	// FPS�v���I�����̃^�C���X�^���v
	static INT Count;	// �t���[���̃J�E���g(0~���t���b�V�����[�g) ��������x�����s���鏉���������̓s����A�����l��-1�ƒ�߂�

protected:
	// �������������s��
	static HRESULT InitTime();

	// ���݂�FPS���v�Z����
	static VOID CalculateFPS();

	// �Q�[�����[�v�ɂăX���[�v���s������[ms]�𓾂�
	static DWORD GetSleepTime();

public:
	// ���_���FPS�l���擾����
	static DWORD GetTheoreticalFPS();

	// ���݂�FPS�l���擾����
	static DOUBLE GetActualFPS();

};