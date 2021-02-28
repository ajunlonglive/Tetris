#pragma once

#include "Core/Core.hpp"
#include "Graphic.hpp"


class Picture : private Graphic {

private:
	ComPtr<IWICBitmapDecoder> pWICBitmapDecoder;
	ComPtr<IWICBitmapFrameDecode> pWICBitmapFrame;
	ComPtr<IWICFormatConverter> pFormatConverter;
	ComPtr<ID2D1Bitmap> pBitmap;

public:
	// �R���X�g���N�^
	Picture();

	// �f�X�g���N�^
	//~Picture();

	// �摜��ǂݍ���
	HRESULT Load(LPCTSTR FileName);

	// �摜��\������
	VOID Draw(INT X, INT Y, UINT Width, UINT Height);

	// �摜�̈ꕔ��\������
	VOID Draw(INT X, INT Y, UINT Width, UINT Height, INT sX, INT sY, UINT sWidth, UINT sHeight);

	// �����x���w�肵�ĉ摜��\������
	VOID Draw(INT X, INT Y, UINT Width, UINT Height, FLOAT Opacity);

	// �����x���w�肵�ĉ摜�̈ꕔ��\������
	VOID Draw(INT X, INT Y, UINT Width, UINT Height, FLOAT Opacity, INT sX, INT sY, UINT sWidth, UINT sHeight);

	// ���S����Ƃ������W�ɉ摜��\������
	VOID DrawC(INT X, INT Y, UINT Width, UINT Height);

	// ���S����Ƃ������W�ɉ摜�̈ꕔ��\������
	VOID DrawC(INT X, INT Y, UINT Width, UINT Height, INT sX, INT sY, UINT sWidth, UINT sHeight);

	// �����x���w�肵�Ē��S����Ƃ������W�ɉ摜��\������
	VOID DrawC(INT X, INT Y, UINT Width, UINT Height, FLOAT Opacity);

	// �����x���w�肵�Ē��S����Ƃ������W�ɉ摜�̈ꕔ��\������
	VOID DrawC(INT X, INT Y, UINT Width, UINT Height, FLOAT Opacity, INT sX, INT sY, UINT sWidth, UINT sHeight);

};