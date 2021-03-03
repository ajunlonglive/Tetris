#pragma once

#include "Core/Core.hpp"
#include "Core/Core_Graphic.hpp"


class Picture : private Core, private Core_Graphic {

private:
	Microsoft::WRL::ComPtr<ID2D1Bitmap> pBitmap;

public:
	// �R���X�g���N�^
	Picture();

	// �摜��ǂݍ���
	YGL_ERROR Load(const wchar_t* FileName);

	// �摜��\������
	void Draw(COORDINATES_INT Coordinates, SIZE_UINT Size);

	// �摜�̈ꕔ��\������
	void Draw(COORDINATES_INT Coordinates, SIZE_UINT Size, COORDINATES_INT sCoordinates, SIZE_UINT sSize);

	// �����x���w�肵�ĉ摜��\������
	void Draw(COORDINATES_INT Coordinates, SIZE_UINT Size, float Opacity);

	// �����x���w�肵�ĉ摜�̈ꕔ��\������
	void Draw(COORDINATES_INT Coordinates, SIZE_UINT Size, float Opacity, COORDINATES_INT sCoordinates, SIZE_UINT sSize);

	// ���S����Ƃ������W�ɉ摜��\������
	void DrawC(COORDINATES_INT Coordinates, SIZE_UINT Size);

	// ���S����Ƃ������W�ɉ摜�̈ꕔ��\������
	void DrawC(COORDINATES_INT Coordinates, SIZE_UINT Size, COORDINATES_INT sCoordinates, SIZE_UINT sSize);

	// �����x���w�肵�Ē��S����Ƃ������W�ɉ摜��\������
	void DrawC(COORDINATES_INT Coordinates, SIZE_UINT Size, float Opacity);

	// �����x���w�肵�Ē��S����Ƃ������W�ɉ摜�̈ꕔ��\������
	void DrawC(COORDINATES_INT Coordinates, SIZE_UINT Size, float Opacity, COORDINATES_INT sCoordinates, SIZE_UINT sSize);

};