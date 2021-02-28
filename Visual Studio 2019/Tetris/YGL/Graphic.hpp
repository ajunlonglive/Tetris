#pragma once

#include "Core/Core.hpp"
#include "Core/Window.hpp"


class Graphic : private Window {

private:
	static ComPtr<ID2D1SolidColorBrush> pBrush;	// このクラス内のみで用いられる単色ブラシ

protected:
	static UINT CanvasWidth, CanvasHeight;	// キャンバスのサイズ
	static BOOL Windowed;	// ウィンドウモードか?
	static ComPtr<ID2D1Factory> pD2DFactory;
	static ComPtr<ID2D1HwndRenderTarget> pRenderTarget;
	static ComPtr<IWICImagingFactory> pWICImagingFactory;	// WICファクトリ
	static ComPtr<IDWriteFactory> pDWriteFactory;	// DirectWriteファクトリ

	// 初期化処理を行う
	static HRESULT InitGraphic();

	// 左上を基準としたキャンバス座標を変換する
	static D2D1_RECT_F TranslateCoordinates(INT X, INT Y, UINT Width, UINT Height);

	// 中心を基準としたキャンバス座標を変換する
	static D2D1_RECT_F TranslateCenterCoordinates(INT X, INT Y, UINT Width, UINT Height);


public:
	// 色を指定し画面を塗りつぶす
	static VOID PaintCanvas(D2D1_COLOR_F Color);

	// 塗りつぶされた四角形を表示する
	static VOID FillRect(INT X, INT Y, UINT Width, UINT Height, D2D1_COLOR_F Color);

	// 塗りつぶされていない四角形を表示する
	static VOID DrawRect(INT X, INT Y, UINT Width, UINT Height, D2D1_COLOR_F Color, FLOAT StrokeWidth);

	// 塗りつぶされた四角形を中心を基準とした座標に表示する
	static VOID FillRectC(INT X, INT Y, UINT Width, UINT Height, D2D1_COLOR_F Color);

	// 塗りつぶされていない四角形を中心を基準とした座標に表示する
	static VOID DrawRectC(INT X, INT Y, UINT Width, UINT Height, D2D1_COLOR_F Color, FLOAT StrokeWidth);

};