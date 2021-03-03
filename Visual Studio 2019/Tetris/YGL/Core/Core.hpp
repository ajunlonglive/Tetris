#pragma once

#include <Windows.h>
#include <wrl/client.h>	// ComPtrを使用するため
#include <d2d1.h>	// Direct2D 1
#include <wincodec.h>	// 画像関連
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


// 色の構造体
struct COLOR_FLOAT {
	float Red, Green, Blue, Alpha;
};

// 座標の構造体
struct COORDINATES_INT {
	int X, Y;
};

// サイズの構造体
struct SIZE_UINT {
	unsigned int Width, Height;
};


class Core {

protected:
	// HRESULTのエラー値をYGLのエラー値に変換する
	static YGL_ERROR Convert_HRESULT_ToError(HRESULT hr);

};


// 色の構造体を返す
COLOR_FLOAT ColorF(float r, float g, float b, float a);

// 座標の構造体を返す
COORDINATES_INT CoordinatesI(int X, int Y);

// サイズの構造体を返す
SIZE_UINT SizeU(unsigned int Width, unsigned int Height);