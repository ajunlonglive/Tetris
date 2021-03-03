#pragma once

#include "Core/Core.hpp"
#include "Core/Core_Window.hpp"
#include "Core/Core_Graphic.hpp"


// **************************************************
// Config�N���X
// **************************************************
/*
	�y�T�v�z
	�@YGL�̐ݒ���󂯂���N���X�B
	 Game::Init()���Ăяo���ꂽ���Ƃɂ��̃N���X�̃��\�b�h���Ăяo�����Ƃ͋֎~�ł���B

	�y�����z
	�@���̃N���X�� Core_Window�N���X�ACore_Graphic�N���X �ɂ���ăt�����h�N���X�Ƃ��Ďw�肳��Ă���B
	 ���̂��߂��̃N���X�͏�L�̃N���X��private�����o��protected�����o�ɂ��A�N�Z�X�ł���B
*/

class Config : private Core {

public:
	// �E�B���h�E���[�h�ł��邩��ݒ肷��
	static void SetWindowMode(bool b);

	// �E�B���h�E�̃^�C�g����ݒ肷��
	static void SetWindowTitle(const wchar_t* str);

	// �E�B���h�E�̃T�C�Y(���m�ɂ̓N���C�A���g�̈�̃T�C�Y)��ݒ肷��
	static void SetWindowSize(SIZE_UINT Size);

	// �L�����o�X�̃T�C�Y��ݒ肷��
	static void SetCanvasSize(SIZE_UINT Size);

};