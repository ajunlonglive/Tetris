#include "Picture.hpp"


// コンストラクタ
Picture::Picture() {

	pBitmap = NULL;

}

// デストラクタ
Picture::~Picture() {

	Unload();

}

// 画像ファイルからデータを読み込む
YGL_ERROR Picture::Load(const wchar_t* FileName) {

	HRESULT hr = S_OK;

	// 画像ファイルを基にデコーダーを作成する
	IWICBitmapDecoder* pWICBitmapDecoder = NULL;
	hr = pWICImagingFactory->CreateDecoderFromFilename(FileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pWICBitmapDecoder);
	if (FAILED(hr)) {
		return Convert_HRESULT_ToError(hr);
	}

	// ビットマップフレームを生成する
	IWICBitmapFrameDecode* pWICBitmapFrame = NULL;
	hr = pWICBitmapDecoder->GetFrame(0, &pWICBitmapFrame);
	if (FAILED(hr)) {
		SafeRelease(&pWICBitmapDecoder);	// ビットマップデコーダーを解放する
		return Convert_HRESULT_ToError(hr);
	}

	// フォーマットコンバータを生成する
	IWICFormatConverter* pFormatConverter = NULL;
	hr = pWICImagingFactory->CreateFormatConverter(&pFormatConverter);
	if (FAILED(hr)) {
		SafeRelease(&pWICBitmapFrame);	// ビットマップフレームを解放する
		SafeRelease(&pWICBitmapDecoder);	// ビットマップデコーダーを解放する
		return Convert_HRESULT_ToError(hr);
	}

	// フォーマットコンバータを初期化する
	hr = pFormatConverter->Initialize(pWICBitmapFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 1.0f, WICBitmapPaletteTypeMedianCut);
	if (FAILED(hr)) {
		SafeRelease(&pFormatConverter);	// フォーマットコンバータを解放する
		SafeRelease(&pWICBitmapFrame);	// ビットマップフレームを解放する
		SafeRelease(&pWICBitmapDecoder);	// ビットマップデコーダーを解放する
		return Convert_HRESULT_ToError(hr);
	}

	// ビットマップを作成する
	hr = pRenderTarget->CreateBitmapFromWicBitmap(pFormatConverter, NULL, &pBitmap);
	if (FAILED(hr)) {
		SafeRelease(&pFormatConverter);	// フォーマットコンバータを解放する
		SafeRelease(&pWICBitmapFrame);	// ビットマップフレームを解放する
		SafeRelease(&pWICBitmapDecoder);	// ビットマップデコーダーを解放する
		return Convert_HRESULT_ToError(hr);
	}


	SafeRelease(&pFormatConverter);	// フォーマットコンバータを解放する
	SafeRelease(&pWICBitmapFrame);	// ビットマップフレームを解放する
	SafeRelease(&pWICBitmapDecoder);	// ビットマップデコーダーを解放する

	return YGL_ERROR_SUCCESS;

}

// 読み込んだ画像ファイルのデータを解放する
void Picture::Unload() {

	SafeRelease(&pBitmap);

}

// 画像を表示する
void Picture::Draw(COORDINATES_INT Coordinates, SIZE_UINT Size) {
	
	this->Draw(Coordinates, Size, 1.0f);

}

// 画像の一部を表示する
void Picture::Draw(COORDINATES_INT Coordinates, SIZE_UINT Size, COORDINATES_INT sCoordinates, SIZE_UINT sSize) {

	this->Draw(Coordinates, Size, 1.0f, sCoordinates, sSize);

}

// 透明度を指定して画像を表示する
void Picture::Draw(COORDINATES_INT Coordinates, SIZE_UINT Size, float Opacity) {

	// 描画矩形を指定する
	D2D1_RECT_F DrawRect = TranslateCoordinates(Coordinates, Size);

	// ビットマップを描画する
	pRenderTarget->DrawBitmap(pBitmap, DrawRect, Opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);

}

// 透明度を指定して画像の一部を表示する
void Picture::Draw(COORDINATES_INT Coordinates, SIZE_UINT Size, float Opacity, COORDINATES_INT sCoordinates, SIZE_UINT sSize) {

	// 描画矩形を指定する
	D2D1_RECT_F DrawRect = TranslateCoordinates(Coordinates, Size);

	// ビットマップを描画する
	pRenderTarget->DrawBitmap(pBitmap, DrawRect, Opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF((FLOAT)sCoordinates.X, (FLOAT)sCoordinates.Y, (FLOAT)sCoordinates.X + (FLOAT)sSize.Width, (FLOAT)sCoordinates.Y + (FLOAT)sSize.Height));

}

// 中心を基準とした座標に画像を表示する
void Picture::DrawC(COORDINATES_INT Coordinates, SIZE_UINT Size) {

	this->DrawC(Coordinates, Size, 1.0f);

}

// 中心を基準とした座標に画像の一部を表示する
void Picture::DrawC(COORDINATES_INT Coordinates, SIZE_UINT Size, COORDINATES_INT sCoordinates, SIZE_UINT sSize) {

	this->DrawC(Coordinates, Size, 1.0f, sCoordinates, sSize);

}

// 透明度を指定して中心を基準とした座標に画像を表示する
void Picture::DrawC(COORDINATES_INT Coordinates, SIZE_UINT Size, float Opacity) {

	// 描画矩形を指定する
	D2D1_RECT_F DrawRect = TranslateCoordinatesC(Coordinates, Size);

	// ビットマップを描画する
	pRenderTarget->DrawBitmap(pBitmap, DrawRect, Opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);

}

// 透明度を指定して中心を基準とした座標に画像の一部を表示する
void Picture::DrawC(COORDINATES_INT Coordinates, SIZE_UINT Size, float Opacity, COORDINATES_INT sCoordinates, SIZE_UINT sSize) {

	// 描画矩形を指定する
	D2D1_RECT_F DrawRect = TranslateCoordinatesC(Coordinates, Size);

	// ビットマップを描画する
	pRenderTarget->DrawBitmap(pBitmap, DrawRect, Opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF((FLOAT)sCoordinates.X, (FLOAT)sCoordinates.Y, (FLOAT)sCoordinates.X + (FLOAT)sSize.Width, (FLOAT)sCoordinates.Y + (FLOAT)sSize.Height));

}