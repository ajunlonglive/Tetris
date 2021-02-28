#include "YGL.hpp"


// �������������s��
HRESULT Game::Init() {

	HRESULT hr = S_OK;

	// COM������������
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr))
		return hr;

	// �Q�[���E�B���h�E���쐬����
	hr = CreateGameWindow();
	if (FAILED(hr))
		return hr;

	// Graphic�N���X������������
	hr = InitGraphic();
	if (FAILED(hr))
		return hr;

	// Sound�N���X������������
	hr = Sound::Init();
	if (FAILED(hr))
		return hr;

	// Time�N���X������������
	hr = InitTime();
	if (FAILED(hr))
		return hr;

	// �E�B���h�E����������
	ShowWindow(hWnd, SW_SHOW);

	return S_OK;

}

// �Q�[�����[�v�����s���邩�ǂ�����Ԃ�
BOOL Game::GameLoop() {

	// ���b�Z�[�W�̗L�����擾����
	if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
		// ���b�Z�[�W������ꍇ

		// ���b�Z�[�W���擾����
		if (0 == GetMessage(&msg, NULL, 0, 0))
			return false;	// ���b�Z�[�W��WM_QUIT�ł���ꍇ�Afalse��Ԃ�

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;

}

// �Q�[�����[�v�̊J�n�������s��
VOID Game::LoopStart() {

	// FPS���v�Z����
	Time::CalculateFPS();

	// Direct2D1�̕`����J�n����
	pRenderTarget->BeginDraw();

	// �w�i���N���A����
	pRenderTarget->Clear(ColorF(0.0f, 0.0f, 0.0f, 1.0f));

}

// �Q�[�����[�v�̏I���������s��
VOID Game::LoopEnd() {

	pRenderTarget->EndDraw();

	// �X���[�v���͂���
	timeBeginPeriod(1);
	Sleep(Time::GetSleepTime());
	timeEndPeriod(1);

}

// �I���������s��
VOID Game::Quit() {

}