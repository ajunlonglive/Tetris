#pragma once

#include "Core/Core.hpp"
#include "Core/Core_Window.hpp"
#include "Core/Core_Graphic.hpp"
#include "Core/Core_Sound.hpp"
#include "Core/Core_Time.hpp"
#include "Config.hpp"
#include "Graphic.hpp"
#include "Picture.hpp"
#include "Text.hpp"
#include "Sound.hpp"
#include "Time.hpp"


// **************************************************
// Game�N���X
// **************************************************
/*
	�y�T�v�z
	�@YGL�𓮍삳���邽�߂Ƀx�[�X�ƂȂ�E�B���h�E�̍쐬��Direct2D���̏������ƏI���������󂯂��A
	�܂��Q�[�����[�v�Ȃǂ̃Q�[���̊�{�I�ȏ�����񋟂���B

	�y�����z
	�@���̃N���X�� Core_Window�N���X�ACore_Graphic�N���X�ACore_Sound�N���X�ACore_Time�N���X �ɂ���ăt�����h�N���X�Ƃ��Ďw�肳��Ă���B
	 ���̂��߂��̃N���X�͏�L�̃N���X��private�����o��protected�����o�ɂ��A�N�Z�X�ł���B
*/

class Game : private Core {

public:
	// YGL�̏������������s��
	static YGL_ERROR Init();

	// �Q�[�����[�v�����s���邩��Ԃ�
	static bool GameLoop();

	// �Q�[�����[�v�̊J�n�������s��
	static void LoopStart();

	// �Q�[�����[�v�̏I���������s��
	static void LoopEnd();

	// YGL�̏I���������s��
	static void Quit();

};