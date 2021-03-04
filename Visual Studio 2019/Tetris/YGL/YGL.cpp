#include "YGL.hpp"


// �������������s��
YGL_ERROR Game::Init() {

	HRESULT hr = S_OK;

	// COM������������
	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr)) {
		return Convert_HRESULT_ToError(hr);
	}

	// Core_Window�N���X������������
	hr = Core_Window::Init();
	if (FAILED(hr)) {
		CoUninitialize();	// COM���I������
		return Convert_HRESULT_ToError(hr);
	}

	// Core_Graphic�N���X������������
	hr = Core_Graphic::Init();
	if (FAILED(hr)) {
		Core_Window::Quit();	// Core_Window�N���X���I������
		CoUninitialize();	// COM���I������
		return Convert_HRESULT_ToError(hr);
	}

	// Core_Sound�N���X������������
	hr = Core_Sound::Init();
	if (FAILED(hr)) {
		Core_Graphic::Quit();	// Core_Graphic�N���X���I������
		Core_Window::Quit();	// Core_Window�N���X���I������
		CoUninitialize();	// COM���I������
		return Convert_HRESULT_ToError(hr);
	}

	// Core_Time�N���X������������
	hr = Core_Time::Init();
	if (FAILED(hr)) {
		Core_Sound::Quit();	// Core_Sound�N���X���I������
		Core_Graphic::Quit();	// Core_Graphic�N���X���I������
		Core_Window::Quit();	// Core_Window�N���X���I������
		CoUninitialize();	// COM���I������
		return Convert_HRESULT_ToError(hr);
	}

	// �E�B���h�E����������
	ShowWindow(Core_Window::hWnd, SW_SHOW);


	return YGL_ERROR_SUCCESS;

}

// �I���������s��
void Game::Quit() {

	Core_Time::Quit();	// Core_Time�N���X���I������
	Core_Sound::Quit();	// Core_Sound�N���X���I������
	Core_Graphic::Quit();	// Core_Graphic�N���X���I������
	Core_Window::Quit();	// Core_Window�N���X���I������
	CoUninitialize();	// COM���I������

}

// �Q�[�����[�v�����s���邩��Ԃ�
bool Game::GameLoop() {

	// ���b�Z�[�W�̗L�����擾����
	if (PeekMessageW(&Core_Window::msg, NULL, 0, 0, PM_NOREMOVE)) {
		// ���b�Z�[�W������ꍇ

		// ���b�Z�[�W���擾����
		if (0 == GetMessageW(&Core_Window::msg, NULL, 0, 0)) {
			return false;	// ���b�Z�[�W��WM_QUIT�ł���ꍇ�Afalse��Ԃ�
		}

		TranslateMessage(&Core_Window::msg);
		DispatchMessageW(&Core_Window::msg);
	}

	return true;

}

// �Q�[�����[�v�̊J�n�������s��
void Game::LoopStart() {

	// FPS���v�Z����
	Core_Time::CalculateFPS();

	// Direct2D1�̕`����J�n����
	Core_Graphic::pRenderTarget->BeginDraw();

	// �w�i���N���A����
	Core_Graphic::pRenderTarget->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 1.0f));

}

// �Q�[�����[�v�̏I���������s��
void Game::LoopEnd() {

	// Direct2D1�̕`����I������
	Core_Graphic::pRenderTarget->EndDraw();

	// �X���[�v���͂���
	timeBeginPeriod(1);
	Sleep(Core_Time::GetSleepTime());
	timeEndPeriod(1);

}