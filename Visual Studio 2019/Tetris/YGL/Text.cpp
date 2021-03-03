#include "Text.hpp"

// コンストラクタ
Text::Text() {

	pTextFormat = nullptr;
	pSolidBrush = nullptr;
	pDXGISurface = nullptr;

}

// フォントを読み込む
YGL_ERROR Text::Load(const wchar_t* FontName, float FontSize) {

	HRESULT hr = Load(FontName, FontSize, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);

	return Convert_HRESULT_ToError(hr);
	
}

// 太さ・スタイル・幅を指定してフォントを読み込む
YGL_ERROR Text::Load(const wchar_t* FontName, float FontSize, DWRITE_FONT_WEIGHT Weight, DWRITE_FONT_STYLE Style, DWRITE_FONT_STRETCH Stretch) {

	HRESULT hr = S_OK;

	// テキストフォーマットを作成する
	hr = pDWriteFactory->CreateTextFormat(FontName, NULL, Weight, Style, Stretch, FontSize, L"", pTextFormat.GetAddressOf());
	if (FAILED(hr)) {
		return Convert_HRESULT_ToError(hr);
	}

	// テキストの配置を設定する
	hr = pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	if (FAILED(hr)) {
		return Convert_HRESULT_ToError(hr);
	}

	// 白のブラシを作成する
	hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), pSolidBrush.GetAddressOf());
	if (FAILED(hr)) {
		return Convert_HRESULT_ToError(hr);
	}

	return YGL_ERROR_SUCCESS;

}

// 座標と表示エリアの面積を指定して文字列を表示する
void Text::Draw(COORDINATES_INT Coordinates, SIZE_UINT Size, const wchar_t* str) {

	pRenderTarget->DrawText(str, lstrlen(str), pTextFormat.Get(), TranslateCoordinates(Coordinates, Size), pSolidBrush.Get(), D2D1_DRAW_TEXT_OPTIONS_NONE);

}

// 表示色を変更する
void Text::SetColor(COLOR_FLOAT Color) {

	pSolidBrush->SetColor(D2D1::ColorF(Color.Red, Color.Green, Color.Blue, Color.Alpha));

}