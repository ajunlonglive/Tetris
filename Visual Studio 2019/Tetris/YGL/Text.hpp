#pragma once

#include "Core/Core.hpp"
#include "Core/Core_Graphic.hpp"


class Text : private Core, private Core_Graphic {

private:
	IDWriteTextFormat* pTextFormat;	// テキストフォーマット
	ID2D1SolidColorBrush* pSolidBrush;	// 単色ブラシ

public:
	// コンストラクタ
	Text();

	// デストラクタ
	~Text();

	// フォントデータを読み込む
	YGL_ERROR Load(const wchar_t* FontName, float FontSize);

	// 読み込んだフォントデータを解放する
	void Unload();

	// 太さ・スタイル・幅を指定してフォントを読み込む
	YGL_ERROR Load(const wchar_t* FontName, float FontSize, DWRITE_FONT_WEIGHT Weight, DWRITE_FONT_STYLE Style, DWRITE_FONT_STRETCH Stretch);

	// 座標と表示エリアの面積を指定して文字列を表示する
	void Draw(COORDINATES_INT Coordinates, SIZE_UINT Size, const wchar_t* str);

	// 表示色を変更する
	void SetColor(COLOR_FLOAT Color);

};