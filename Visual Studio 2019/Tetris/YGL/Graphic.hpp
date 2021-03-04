#pragma once

#include "Core/Core.hpp"
#include "Core/Core_Graphic.hpp"


class Graphic : private Core, private Core_Graphic {

public:
	// �F���w�肵��ʂ�h��Ԃ�
	static void PaintCanvas(COLOR_FLOAT Color);

	// �h��Ԃ��ꂽ�l�p�`��\������
	static void FillRect(COORDINATES_INT Coordinates, SIZE_UINT Size, COLOR_FLOAT Color);

	// �h��Ԃ���Ă��Ȃ��l�p�`��\������
	static void DrawRect(COORDINATES_INT Coordinates, SIZE_UINT Size, COLOR_FLOAT Color, float StrokeWidth);

	// �h��Ԃ��ꂽ�l�p�`�𒆐S����Ƃ������W�ɕ\������
	static void FillRectC(COORDINATES_INT Coordinates, SIZE_UINT Size, COLOR_FLOAT Color);

	// �h��Ԃ���Ă��Ȃ��l�p�`�𒆐S����Ƃ������W�ɕ\������
	static void DrawRectC(COORDINATES_INT Coordinates, SIZE_UINT Size, COLOR_FLOAT Color, float StrokeWidth);

};