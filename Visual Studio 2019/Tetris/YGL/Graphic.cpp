#include "Graphic.hpp"


// 色を指定し画面を塗りつぶす
void Graphic::PaintCanvas(COLOR_FLOAT Color) {

	FillRect(CoordinatesI(0, 0), CanvasSize, Color);

}

// 塗りつぶされた四角形を表示する
void Graphic::FillRect(COORDINATES_INT Coordinates, SIZE_UINT Size, COLOR_FLOAT Color) {

	// 描画矩形を指定する
	D2D1_RECT_F rect = TranslateCoordinates(Coordinates, Size);

	// 汎用単色ブラシの色を変更する
	pSolidBrush->SetColor(D2D1::ColorF(Color.Red, Color.Green, Color.Blue, Color.Alpha));

	// 四角形を描画する
	pRenderTarget->FillRectangle(&rect, pSolidBrush.Get());

}

// 塗りつぶされていない四角形を表示する
void Graphic::DrawRect(COORDINATES_INT Coordinates, SIZE_UINT Size, COLOR_FLOAT Color, float StrokeWidth) {

	// 描画矩形を指定する
	D2D1_RECT_F rect = TranslateCoordinates(Coordinates, Size);

	// 汎用単色ブラシの色を変更する
	pSolidBrush->SetColor(D2D1::ColorF(Color.Red, Color.Green, Color.Blue, Color.Alpha));

	// 四角形を描画する
	pRenderTarget->DrawRectangle(&rect, pSolidBrush.Get(), StrokeWidth);

}

// 塗りつぶされた四角形を中心を基準とした座標に表示する
void Graphic::FillRectC(COORDINATES_INT Coordinates, SIZE_UINT Size, COLOR_FLOAT Color) {

	// 描画矩形を指定する
	D2D1_RECT_F rect = TranslateCoordinatesC(Coordinates, Size);

	// 汎用単色ブラシの色を変更する
	pSolidBrush->SetColor(D2D1::ColorF(Color.Red, Color.Green, Color.Blue, Color.Alpha));

	// 四角形を描画する
	pRenderTarget->FillRectangle(&rect, pSolidBrush.Get());

}

// 塗りつぶされていない四角形を中心を基準とした座標に表示する
void Graphic::DrawRectC(COORDINATES_INT Coordinates, SIZE_UINT Size, COLOR_FLOAT Color, float StrokeWidth) {

	// 描画矩形を指定する
	D2D1_RECT_F rect = TranslateCoordinatesC(Coordinates, Size);

	// 汎用単色ブラシの色を変更する
	pSolidBrush->SetColor(D2D1::ColorF(Color.Red, Color.Green, Color.Blue, Color.Alpha));

	// 四角形を描画する
	pRenderTarget->DrawRectangle(&rect, pSolidBrush.Get(), StrokeWidth);

}