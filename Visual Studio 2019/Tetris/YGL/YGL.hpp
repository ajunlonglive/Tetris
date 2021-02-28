#pragma once

#include "Core/Core.hpp"
#include "Core/Window.hpp"
#include "Config.hpp"
#include "Time.hpp"
#include "Graphic.hpp"
#include "Picture.hpp"
#include "Text.hpp"
#include "Sound.hpp"


class Game : private Window, private Graphic, private Time, private Sound {

public:
	// �������������s��
	static HRESULT Init();

	// �Q�[�����[�v�����s���邩�ǂ�����Ԃ�
	static BOOL GameLoop();

	// �Q�[�����[�v�̊J�n�������s��
	static VOID LoopStart();

	// �Q�[�����[�v�̏I���������s��
	static VOID LoopEnd();

	// �I���������s��
	static VOID Quit();

};