#pragma once

#include "Core/Core.hpp"
#include "Graphic.hpp"

class Text : private Graphic {

private:
	ComPtr<IDWriteTextFormat> pTextFormat;
	ComPtr<ID2D1SolidColorBrush> pSolidBrush;
	ComPtr<IDXGISurface> pDXGISurface;

public:
	// コンストラクタ
	Text();

	// フォントを読み込む
	HRESULT Load(LPCTSTR FontName, FLOAT FontSize);

	// 太さ・スタイル・幅を指定してフォントを読み込む
	HRESULT Load(LPCTSTR FontName, FLOAT Size, DWRITE_FONT_WEIGHT Weight, DWRITE_FONT_STYLE Style, DWRITE_FONT_STRETCH Stretch);

	// 座標と表示エリアの面積を指定して文字列を表示する
	VOID Draw(UINT X, UINT Y, UINT Width, UINT Height, LPCTSTR str);

	// 表示色を変更する
	VOID SetColor(ColorF Color);

};