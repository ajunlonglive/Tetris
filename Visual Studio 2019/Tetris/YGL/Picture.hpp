#pragma once

#include "Core/Core.hpp"
#include "Graphic.hpp"


class Picture : private Graphic {

private:
	ComPtr<IWICBitmapDecoder> pWICBitmapDecoder;
	ComPtr<IWICBitmapFrameDecode> pWICBitmapFrame;
	ComPtr<IWICFormatConverter> pFormatConverter;
	ComPtr<ID2D1Bitmap> pBitmap;

public:
	// コンストラクタ
	Picture();

	// デストラクタ
	//~Picture();

	// 画像を読み込む
	HRESULT Load(LPCTSTR FileName);

	// 画像を表示する
	VOID Draw(INT X, INT Y, UINT Width, UINT Height);

	// 画像の一部を表示する
	VOID Draw(INT X, INT Y, UINT Width, UINT Height, INT sX, INT sY, UINT sWidth, UINT sHeight);

	// 透明度を指定して画像を表示する
	VOID Draw(INT X, INT Y, UINT Width, UINT Height, FLOAT Opacity);

	// 透明度を指定して画像の一部を表示する
	VOID Draw(INT X, INT Y, UINT Width, UINT Height, FLOAT Opacity, INT sX, INT sY, UINT sWidth, UINT sHeight);

	// 中心を基準とした座標に画像を表示する
	VOID DrawC(INT X, INT Y, UINT Width, UINT Height);

	// 中心を基準とした座標に画像の一部を表示する
	VOID DrawC(INT X, INT Y, UINT Width, UINT Height, INT sX, INT sY, UINT sWidth, UINT sHeight);

	// 透明度を指定して中心を基準とした座標に画像を表示する
	VOID DrawC(INT X, INT Y, UINT Width, UINT Height, FLOAT Opacity);

	// 透明度を指定して中心を基準とした座標に画像の一部を表示する
	VOID DrawC(INT X, INT Y, UINT Width, UINT Height, FLOAT Opacity, INT sX, INT sY, UINT sWidth, UINT sHeight);

};