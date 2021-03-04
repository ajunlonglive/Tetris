#pragma once

#include "Core.hpp"
#include "Core_Window.hpp"


class Core_Graphic : private Core, private Core_Window {

private:
	// 初期化処理を行う
	static HRESULT Init();

	// 終了処理を行う
	static VOID Quit();

protected:
	static SIZE_UINT CanvasSize;	// キャンバスのサイズ
	static ID2D1Factory* pD2DFactory;	// Direct2Dファクトリ
	static ID2D1HwndRenderTarget* pRenderTarget;	// Direct2Dレンダーターゲット
	static ID2D1SolidColorBrush* pSolidBrush;	// 汎用単色ブラシ
	static IWICImagingFactory* pWICImagingFactory;	// WICファクトリ
	static IDWriteFactory* pDWriteFactory;	// DirectWriteファクトリ

	// 左上を基準としたキャンバス座標をD2D1_RECT_Fに変換する
	static D2D1_RECT_F TranslateCoordinates(COORDINATES_INT Coordinates, SIZE_UINT Size);

	// 中心を基準としたキャンバス座標をD2D1_RECT_Fに変換する
	static D2D1_RECT_F TranslateCoordinatesC(COORDINATES_INT Coordinates, SIZE_UINT Size);


	friend class Game;	// Gameクラスをフレンドクラスに指定する
	friend class Config;	// Configクラスをフレンドクラスに指定する

};