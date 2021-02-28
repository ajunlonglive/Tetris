#pragma once

#include "Core/Core.hpp"
#include "Core/Window.hpp"
#include "Graphic.hpp"


// �ݒ�N���X
class Config : private Window, private Graphic {

public:
	// �E�B���h�E�̃T�C�Y��ݒ肷��(�E�B���h�E���[�h�̏ꍇ�݂̂ɉe������)
	static VOID SetWindowSize(UINT Width, UINT Height);

	// �E�B���h�E�̃^�C�g����ݒ肷��(�E�B���h�E���[�h�̏ꍇ�݂̂ɉe������)
	static VOID SetWindowTitle(LPCWSTR str);

	// �L�����o�X�̃T�C�Y��ݒ肷��
	static VOID SetCanvasSize(UINT Width, UINT Height);

	// �E�B���h�E���[�h�ɂ��邩�ǂ�����ݒ肷��
	static VOID SetWindowMode(BOOL b);

};