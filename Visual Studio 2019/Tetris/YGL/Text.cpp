#include "Text.hpp"

// コンストラクタ
Text::Text() {

	pTextFormat = nullptr;
	pSolidBrush = nullptr;
	pDXGISurface = nullptr;

}

// フォントを読み込む
HRESULT Text::Load(LPCTSTR FontName, FLOAT Size) {

	return this->Load(FontName, Size, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
	
}

// 太さ・スタイル・幅を指定してフォントを読み込む
HRESULT Text::Load(LPCTSTR FontName, FLOAT Size, DWRITE_FONT_WEIGHT Weight, DWRITE_FONT_STYLE Style, DWRITE_FONT_STRETCH Stretch) {

	HRESULT hr = S_OK;

	// テキストフォーマットを作成する
	hr = pDWriteFactory->CreateTextFormat(FontName, NULL, Weight, Style, Stretch, Size, TEXT(""), &pTextFormat);
	if (FAILED(hr))
		return hr;

	// テキストの配置を設定する
	hr = pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	if (FAILED(hr))
		return hr;

	// ブラシを作成する(白)
	hr = pRenderTarget->CreateSolidColorBrush(ColorF(1.0f, 1.0f, 1.0f, 1.0f), &pSolidBrush);
	if (FAILED(hr))
		return hr;

	return S_OK;

}

// 座標と表示エリアの面積を指定して文字列を表示する
VOID Text::Draw(UINT X, UINT Y, UINT Width, UINT Height, LPCTSTR str) {

	pRenderTarget->DrawText(str, lstrlen(str), pTextFormat.Get(), TranslateCoordinates(X, Y, Width, Height), pSolidBrush.Get(), D2D1_DRAW_TEXT_OPTIONS_NONE);

}

// 表示色を変更する
VOID Text::SetColor(ColorF Color) {

	pSolidBrush->SetColor(Color);

}