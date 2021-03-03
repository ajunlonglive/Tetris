#include "Core_Time.hpp"


LARGE_INTEGER Core_Time::Frequency = { 0 };	// �^�C�}�[(�p�t�H�[�}���X�J�E���^)�̎��g��
LARGE_INTEGER Core_Time::StartTime = { 0 };	// FPS�v���J�n���̃^�C���X�^���v
LARGE_INTEGER Core_Time::NowTime = { 0 };	// FPS�v���I�����̃^�C���X�^���v
INT Core_Time::Count = -1;	// �t���[���̃J�E���g(0~���t���b�V�����[�g) ��������x�����s���鏉���������̓s����A�����l��-1�ƒ�߂�

// �������������s��
HRESULT Core_Time::Init() {

	DEVMODE mode = { 0 };
	// �f�B�X�v���C�̏��𓾂�
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &mode);
	RefreshRate = mode.dmDisplayFrequency;	// ����ꂽ���t���b�V�����[�g�̒l��������

	// �p�t�H�[�}���X�J�E���^�̎��g���𓾂�
	QueryPerformanceFrequency(&Frequency);

	return S_OK;

}

// ���݂�FPS���v�Z����
VOID Core_Time::CalculateFPS() {

	// �Q�[�����[�v���ł��̊֐����Ăяo�����ꍇ�A��1�b�����Ɍ��݂�FPS���v�Z���邱�ƂɂȂ�

	// **����**
	// ���j�^�[�̃��t���b�V�����[�g��60�ł���(RefreshRate == 60)�Ɖ��肵�Ęb��i�߂�

	if (Count == -1) {	// �J�E���g��-1�Ȃ�

		// 1�t���[���ڂ̎��Ԃ��擾����
		QueryPerformanceCounter(&StartTime);
		Count = 0;
	}
	else if ((unsigned)Count == RefreshRate) {	// �J�E���g��60�Ȃ�

		QueryPerformanceCounter(&NowTime);	// 60�t���[���ڂ̎��Ԃ��擾����
		// FPS = 1�b / 1�t���[���̕`��ɂ����鎞�� �ł��邩��A
		//     = 1000ms / ((60�t���[���ڂ̎���[ms] - 1�t���[���ڂ̎���[ms]) / 60[frame]) �����藧��
		FPS = 1000.0 / (((NowTime.QuadPart - StartTime.QuadPart) * 1000 / Frequency.QuadPart) / (DOUBLE)RefreshRate);	// �ϐ�FPS�ɑ������
		Count = 0;	// �J�E���g�������l�ɖ߂�
		StartTime = NowTime;
	}

	Count++;	// �J�E���g+1

}

// �Q�[�����[�v�ɂăX���[�v���s������[ms]���擾����
DWORD Core_Time::GetSleepTime() {

	// **����**
	// ���j�^�[�̃��t���b�V�����[�g��60�ł���(RefreshRate == 60)�Ɖ��肵�Ęb��i�߂�

	QueryPerformanceCounter(&NowTime);	// ���݂̎��Ԃ��擾����
	// Sleep�����鎞��[ms] = 1�t���[���ڂ��猻�݂̃t���[���܂ł̕`��ɖ{��������ׂ�����[ms] - 1�t���[���ڂ��猻�݂̃t���[���܂Ŏ��ۂɂ�����������[ms]
	//                     = (1000ms / 60)*�t���[���� - (���݂̎���[ms] - 1�t���[���ڂ̎���[ms])
	DWORD SleepTime = static_cast<DWORD>((1000 / RefreshRate) * Count - ((NowTime.QuadPart - StartTime.QuadPart) * 1000 / Frequency.QuadPart));

	// CalculateFPS()�֐������߂Ď��s���ꂽ�����SleepTime�̒l���ƂĂ��傫���Ȃ��Ă��܂����߁A��������m��SleepTime��Ԃ��Ȃ��悤�ɂ���
	if ((1000 / RefreshRate) < SleepTime) {	// ����SleepTime��1�t���[��������̎���[ms]�����傫��������
		return 1;
	}
	else {
		return SleepTime;
	}

}

DWORD Core_Time::RefreshRate = 0;	// ���j�^�[�̃��t���b�V�����[�g
DOUBLE Core_Time::FPS = 0;	// 1�b������̏�����