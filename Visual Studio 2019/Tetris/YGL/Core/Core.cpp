#include "Core.hpp"


// HRESULTのエラー値をYGLのエラー値に変換する
YGL_ERROR Core::Convert_HRESULT_ToError(HRESULT hr) {

	switch (hr) {
	case S_OK:
		return YGL_ERROR_SUCCESS;
	default:
		return YGL_ERROR_UNKNOWN;
	}

}


// 色の構造体を返す
COLOR_FLOAT ColorF(float r, float g, float b, float a) {

	COLOR_FLOAT color = { 0 };
	color.Red = r;
	color.Green = g;
	color.Blue = b;
	color.Alpha = a;

	return color;

}

// 座標の構造体を返す
COORDINATES_INT CoordinatesI(int X, int Y) {

	COORDINATES_INT coordinates;
	coordinates.X = X;
	coordinates.Y = Y;

	return coordinates;

}

// サイズの構造体を返す
SIZE_UINT SizeU(unsigned int Width, unsigned int Height) {

	SIZE_UINT size;
	size.Width = Width;
	size.Height = Height;

	return size;

}