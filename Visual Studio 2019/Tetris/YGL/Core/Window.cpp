#include "Window.hpp"


// �E�B���h�E�v���V�[�W��
LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);

}

UINT Window::WindowWidth = 640, Window::WindowHeight = 480;	// �E�B���h�E�̕��ƍ���(�E�B���h�E���[�h�̏ꍇ�݂̂ɉe������)
LPCWSTR Window::WindowTitle = NULL;	// �E�B���h�E�̃^�C�g��(�E�B���h�E���[�h�̏ꍇ�݂̂ɉe������)
HWND Window::hWnd = NULL;	// �E�B���h�E�n���h��
MSG Window::msg = { 0 };	// �E�B���h�E���b�Z�[�W

// �Q�[���E�B���h�E���쐬����
HRESULT Window::CreateGameWindow() {

	// �E�B���h�E�N���X��ݒ肷��
	WNDCLASS WndClass = { 0 };
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = WndClass.cbWndExtra = 0;
	WndClass.hInstance = GetModuleHandle(NULL);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = NULL;
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = TEXT("WINDOW");

	// �E�B���h�E�N���X��o�^����
	if (0 == RegisterClass(&WndClass))
		return E_FAIL;

	// �T�C�Y���w�肹���s���̃E�B���h�E�𐶐�����
	hWnd = CreateWindow(WndClass.lpszClassName, WindowTitle, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, GetModuleHandle(NULL), NULL);
	if (hWnd == NULL)
		return E_FAIL;


	// �ȍ~�̓E�B���h�E�̃N���C�A���g�̈��ݒ肷��

	// �E�B���h�E���̂��̂̃T�C�Y�ƃN���C�A���g�̈�̃T�C�Y�𓾂�
	RECT rectW, rectC;
	GetWindowRect(hWnd, &rectW);
	GetClientRect(hWnd, &rectC);

	// ����ꂽ�T�C�Y����K�؂ȃE�B���h�E�T�C�Y�����߂�
	int new_width = (rectW.right - rectW.left) - (rectC.right - rectC.left) + WindowWidth;
	int new_height = (rectW.bottom - rectW.top) - (rectC.bottom - rectC.top) + WindowHeight;

	// �E�B���h�E�̃T�C�Y��K�؂Ȃ��̂ɕύX����
	SetWindowPos(hWnd, NULL, 0, 0, new_width, new_height, SWP_NOZORDER);

	return S_OK;

}