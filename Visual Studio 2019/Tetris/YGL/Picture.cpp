#include "Picture.hpp"


// コンストラクタ
Picture::Picture() {

	pWICBitmapDecoder = nullptr;
	pWICBitmapFrame = nullptr;
	pFormatConverter = nullptr;
	pBitmap = nullptr;

}

// 画像を読み込む
HRESULT Picture::Load(LPCTSTR FileName) {

	HRESULT hr = S_OK;

	// 画像ファイルを基にデコーダーを作成する
	hr = pWICImagingFactory->CreateDecoderFromFilename(FileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pWICBitmapDecoder);
	if (FAILED(hr))
		return hr;

	// フレームを得る
	hr = pWICBitmapDecoder->GetFrame(0, &pWICBitmapFrame);
	if (FAILED(hr))
		return hr;

	// フォーマットコンバータを生成する
	hr = pWICImagingFactory->CreateFormatConverter(&pFormatConverter);
	if (FAILED(hr))
		return hr;

	// フォーマットコンバータを初期化する
	hr = pFormatConverter->Initialize(pWICBitmapFrame.Get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 1.0f, WICBitmapPaletteTypeMedianCut);
	if (FAILED(hr))
		return hr;

	// ビットマップを作成する
	hr = pRenderTarget->CreateBitmapFromWicBitmap(pFormatConverter.Get(), NULL, &pBitmap);
	if (FAILED(hr))
		return hr;

	return S_OK;

}

// 画像を表示する
VOID Picture::Draw(INT X, INT Y, UINT Width, UINT Height) {
	
	this->Draw(X, Y, Width, Height, 1.0f);

}

// 画像の一部を表示する
VOID Picture::Draw(INT X, INT Y, UINT Width, UINT Height, INT sX, INT sY, UINT sWidth, UINT sHeight) {

	this->Draw(X, Y, Width, Height, 1.0f, sX, sY, sWidth, sHeight);

}

// 透明度を指定して画像を表示する
VOID Picture::Draw(INT X, INT Y, UINT Width, UINT Height, FLOAT Opacity) {

	// 描画矩形を指定する
	D2D1_RECT_F DrawRect = TranslateCoordinates(X, Y, Width, Height);

	// ビットマップを描画する
	pRenderTarget->DrawBitmap(pBitmap.Get(), DrawRect, Opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);

}

// 透明度を指定して画像の一部を表示する
VOID Picture::Draw(INT X, INT Y, UINT Width, UINT Height, FLOAT Opacity, INT sX, INT sY, UINT sWidth, UINT sHeight) {

	// 描画矩形を指定する
	D2D1_RECT_F DrawRect = TranslateCoordinates(X, Y, Width, Height);

	// ビットマップを描画する
	pRenderTarget->DrawBitmap(pBitmap.Get(), DrawRect, Opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, RectF((FLOAT)sX, (FLOAT)sY, (FLOAT)sX + sWidth, (FLOAT)sY + sHeight));

}

// 中心を基準とした座標に画像を表示する
VOID Picture::DrawC(INT X, INT Y, UINT Width, UINT Height) {

	this->DrawC(X, Y, Width, Height, 1.0f);

}

// 中心を基準とした座標に画像の一部を表示する
VOID Picture::DrawC(INT X, INT Y, UINT Width, UINT Height, INT sX, INT sY, UINT sWidth, UINT sHeight) {

	this->DrawC(X, Y, Width, Height, 1.0f, sX, sY, sWidth, sHeight);

}

// 透明度を指定して中心を基準とした座標に画像を表示する
VOID Picture::DrawC(INT X, INT Y, UINT Width, UINT Height, FLOAT Opacity) {

	// 描画矩形を指定する
	D2D1_RECT_F DrawRect = TranslateCenterCoordinates(X, Y, Width, Height);

	// ビットマップを描画する
	pRenderTarget->DrawBitmap(pBitmap.Get(), DrawRect, Opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);

}

// 透明度を指定して中心を基準とした座標に画像の一部を表示する
VOID Picture::DrawC(INT X, INT Y, UINT Width, UINT Height, FLOAT Opacity, INT sX, INT sY, UINT sWidth, UINT sHeight) {

	// 描画矩形を指定する
	D2D1_RECT_F DrawRect = TranslateCenterCoordinates(X, Y, Width, Height);

	// ビットマップを描画する
	pRenderTarget->DrawBitmap(pBitmap.Get(), DrawRect, Opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, RectF((FLOAT)sX, (FLOAT)sY, (FLOAT)sX + sWidth, (FLOAT)sY + sHeight));

}