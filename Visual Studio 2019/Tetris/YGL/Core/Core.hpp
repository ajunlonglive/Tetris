#pragma once

#include <Windows.h>
#include <wrl/client.h>	// ComPtr���g�p���邽��
#include <d2d1.h>	// Direct2D 1
#include <wincodec.h>	// �摜�֘A
#include <dwrite.h>	// DirectWrite
#include <dsound.h>	// DirectSound

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "dsound.lib")

#pragma warning(disable:4584)
#pragma warning(disable:26812)


enum YGL_ERROR : int {

	YGL_ERROR_SUCCESS = 0,
	YGL_ERROR_UNKNOWN = 1

};


// �F�̍\����
struct COLOR_FLOAT {
	float Red, Green, Blue, Alpha;
};

// ���W�̍\����
struct COORDINATES_INT {
	int X, Y;
};

// �T�C�Y�̍\����
struct SIZE_UINT {
	unsigned int Width, Height;
};


class Core {

protected:
	// HRESULT�̃G���[�l��YGL�̃G���[�l�ɕϊ�����
	static YGL_ERROR Convert_HRESULT_ToError(HRESULT hr);

};


// �F�̍\���̂�Ԃ�
COLOR_FLOAT ColorF(float r, float g, float b, float a);

// ���W�̍\���̂�Ԃ�
COORDINATES_INT CoordinatesI(int X, int Y);

// �T�C�Y�̍\���̂�Ԃ�
SIZE_UINT SizeU(unsigned int Width, unsigned int Height);