#pragma once

#include "Core.hpp"


class Core_Window : private Core {

private:
	static BOOL Windowed;	// �E�B���h�E���[�h�ł��邩
	static LPCWSTR WindowTitle;	// �E�B���h�E�̃^�C�g��
	static MSG msg;	// �E�B���h�E���b�Z�[�W
	static UINT SideSpaceSize, VerticalSpaceSize;	// �t���X�N���[�����ɃE�B���h�E�̏c����ƃX�N���[���̏c���䂪��v���Ȃ������Ƃ��ɐ����鍕���X�y�[�X�̃T�C�Y

	// �Q�[���E�B���h�E���쐬����
	static HRESULT CreateGameWindow();

	// �E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	static SIZE_UINT WindowSize;	// �E�B���h�E�̃T�C�Y(���m�ɂ̓N���C�A���g�̈�̃T�C�Y)
	static HWND hWnd;	// �E�B���h�E�n���h��


	friend class Game;	// Game�N���X���t�����h�N���X�Ɏw�肷��
	friend class Config;	// Config�N���X���t�����h�N���X�Ɏw�肷��

};