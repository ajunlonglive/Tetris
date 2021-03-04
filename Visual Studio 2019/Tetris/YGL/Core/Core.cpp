#include "Core.hpp"


// HRESULT�̃G���[�l��YGL�̃G���[�l�ɕϊ�����
YGL_ERROR Core::Convert_HRESULT_ToError(HRESULT hr) {

	switch (hr) {
	case S_OK:
		return YGL_ERROR_SUCCESS;
	default:
		return YGL_ERROR_UNKNOWN;
	}

}


// �F�̍\���̂�Ԃ�
COLOR_FLOAT ColorF(float r, float g, float b, float a) {

	COLOR_FLOAT color = { 0 };
	color.Red = r;
	color.Green = g;
	color.Blue = b;
	color.Alpha = a;

	return color;

}

// ���W�̍\���̂�Ԃ�
COORDINATES_INT CoordinatesI(int X, int Y) {

	COORDINATES_INT coordinates;
	coordinates.X = X;
	coordinates.Y = Y;

	return coordinates;

}

// �T�C�Y�̍\���̂�Ԃ�
SIZE_UINT SizeU(unsigned int Width, unsigned int Height) {

	SIZE_UINT size;
	size.Width = Width;
	size.Height = Height;

	return size;

}