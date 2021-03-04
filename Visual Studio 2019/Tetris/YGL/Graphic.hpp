#pragma once

#include "Core/Core.hpp"
#include "Core/Core_Graphic.hpp"


class Graphic : private Core, private Core_Graphic {

public:
	// 色を指定し画面を塗りつぶす
	static void PaintCanvas(COLOR_FLOAT Color);

	// 塗りつぶされた四角形を表示する
	static void FillRect(COORDINATES_INT Coordinates, SIZE_UINT Size, COLOR_FLOAT Color);

	// 塗りつぶされていない四角形を表示する
	static void DrawRect(COORDINATES_INT Coordinates, SIZE_UINT Size, COLOR_FLOAT Color, float StrokeWidth);

	// 塗りつぶされた四角形を中心を基準とした座標に表示する
	static void FillRectC(COORDINATES_INT Coordinates, SIZE_UINT Size, COLOR_FLOAT Color);

	// 塗りつぶされていない四角形を中心を基準とした座標に表示する
	static void DrawRectC(COORDINATES_INT Coordinates, SIZE_UINT Size, COLOR_FLOAT Color, float StrokeWidth);

};