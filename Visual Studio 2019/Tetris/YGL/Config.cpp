#include "Config.hpp"


// �E�B���h�E�̃T�C�Y��ݒ肷��(�E�B���h�E���[�h�̏ꍇ�݂̂ɉe������)
VOID Config::SetWindowSize(UINT Width, UINT Height) {

	WindowWidth = Width;
	WindowHeight = Height;

}

// �E�B���h�E�̃^�C�g����ݒ肷��(�E�B���h�E���[�h�̏ꍇ�݂̂ɉe������)
VOID Config::SetWindowTitle(LPCWSTR str) {

	WindowTitle = str;

}

// �L�����o�X�̃T�C�Y��ݒ肷��
VOID Config::SetCanvasSize(UINT Width, UINT Height) {

	CanvasWidth = Width;
	CanvasHeight = Height;

}

// �E�B���h�E���[�h�ɂ��邩�ǂ�����ݒ肷��
VOID Config::SetWindowMode(BOOL b) {

	Windowed = b;

}