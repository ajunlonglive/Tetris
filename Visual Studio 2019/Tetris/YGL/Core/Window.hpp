#pragma once

#include "Core.hpp"


class Window {

private:
	// �E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

protected:
	static UINT WindowWidth, WindowHeight;	// �E�B���h�E�̕��ƍ���(�E�B���h�E���[�h�̏ꍇ�݂̂ɉe������)
	static LPCWSTR WindowTitle;	// �E�B���h�E�̃^�C�g��(�E�B���h�E���[�h�̏ꍇ�݂̂ɉe������)
	static HWND hWnd;	// �E�B���h�E�n���h��
	static MSG msg;	// �E�B���h�E���b�Z�[�W

	// �Q�[���E�B���h�E�𐶐�����
	static HRESULT CreateGameWindow();

};