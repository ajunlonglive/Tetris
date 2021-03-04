#include "Core_Window.hpp"


BOOL Core_Window::Windowed = FALSE;	// �E�B���h�E���[�h�ł��邩
LPCWSTR Core_Window::WindowTitle = NULL;	// �E�B���h�E�̃^�C�g��
MSG Core_Window::msg = { 0 };	// �E�B���h�E���b�Z�[�W
UINT Core_Window::SideSpaceSize = 0, Core_Window::VerticalSpaceSize = 0;	// �t���X�N���[�����ɃE�B���h�E�̏c����ƃX�N���[���̏c���䂪��v���Ȃ������Ƃ��ɐ����鍕���X�y�[�X�̃T�C�Y

// �������������s��
HRESULT Core_Window::Init() {

	// �E�B���h�E�N���X��ݒ肷��
	WNDCLASSW WndClass = { 0 };
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = WndClass.cbWndExtra = 0;
	WndClass.hInstance = GetModuleHandle(NULL);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = NULL;
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = L"WINDOW";

	// �E�B���h�E�N���X��o�^����
	if (0 == RegisterClassW(&WndClass)) {
		return E_FAIL;
	}

	// �T�C�Y���w�肹���s���̃E�B���h�E�𐶐�����
	hWnd = CreateWindowW(WndClass.lpszClassName, WindowTitle, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, GetModuleHandle(NULL), NULL);
	if (hWnd == NULL) {
		return E_FAIL;
	}


	// �ȍ~�̓E�B���h�E�̃N���C�A���g�̈��ݒ肷��

	// �E�B���h�E���̂��̂̃T�C�Y�ƃN���C�A���g�̈�̃T�C�Y�𓾂�
	RECT rectW, rectC;
	GetWindowRect(hWnd, &rectW);
	GetClientRect(hWnd, &rectC);

	// ����ꂽ�T�C�Y����K�؂ȃE�B���h�E�T�C�Y�����߂�
	int new_width = (rectW.right - rectW.left) - (rectC.right - rectC.left) + WindowSize.Width;
	int new_height = (rectW.bottom - rectW.top) - (rectC.bottom - rectC.top) + WindowSize.Height;

	// �E�B���h�E�̃T�C�Y�ƈʒu��K�؂Ȃ��̂ɕύX����
	SetWindowPos(hWnd, NULL, 0, 0, new_width, new_height, SWP_NOZORDER);

	return S_OK;

}

// �I���������s��
VOID Core_Window::Quit() {

}

// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK Core_Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);

}

SIZE_UINT Core_Window::WindowSize = { 640, 480 };	// �E�B���h�E�̃T�C�Y(���m�ɂ̓N���C�A���g�̈�̃T�C�Y)
HWND Core_Window::hWnd = NULL;	// �E�B���h�E�n���h��