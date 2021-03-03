#include "Config.hpp"


// �E�B���h�E���[�h�ł��邩��ݒ肷��
void Config::SetWindowMode(bool b) {

	if (b == true) {
		Core_Window::Windowed = TRUE;
	}
	else {
		Core_Window::Windowed = FALSE;
	}

}

// �E�B���h�E�̃^�C�g����ݒ肷��
void Config::SetWindowTitle(const wchar_t* str) {

	Core_Window::WindowTitle = str;

}

// �E�B���h�E�̃T�C�Y(���m�ɂ̓N���C�A���g�̈�̃T�C�Y)��ݒ肷��
void Config::SetWindowSize(SIZE_UINT Size) {

	Core_Window::WindowSize.Width = Size.Width;
	Core_Window::WindowSize.Height = Size.Height;

}

// �L�����o�X�̃T�C�Y��ݒ肷��
void Config::SetCanvasSize(SIZE_UINT Size) {

	Core_Graphic::CanvasSize.Width = Size.Width;
	Core_Graphic::CanvasSize.Height = Size.Height;

}