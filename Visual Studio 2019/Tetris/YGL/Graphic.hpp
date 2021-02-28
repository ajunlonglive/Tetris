#pragma once

#include "Core/Core.hpp"
#include "Core/Window.hpp"


class Graphic : private Window {

private:
	static ComPtr<ID2D1SolidColorBrush> pBrush;	// ���̃N���X���݂̂ŗp������P�F�u���V

protected:
	static UINT CanvasWidth, CanvasHeight;	// �L�����o�X�̃T�C�Y
	static BOOL Windowed;	// �E�B���h�E���[�h��?
	static ComPtr<ID2D1Factory> pD2DFactory;
	static ComPtr<ID2D1HwndRenderTarget> pRenderTarget;
	static ComPtr<IWICImagingFactory> pWICImagingFactory;	// WIC�t�@�N�g��
	static ComPtr<IDWriteFactory> pDWriteFactory;	// DirectWrite�t�@�N�g��

	// �������������s��
	static HRESULT InitGraphic();

	// �������Ƃ����L�����o�X���W��ϊ�����
	static D2D1_RECT_F TranslateCoordinates(INT X, INT Y, UINT Width, UINT Height);

	// ���S����Ƃ����L�����o�X���W��ϊ�����
	static D2D1_RECT_F TranslateCenterCoordinates(INT X, INT Y, UINT Width, UINT Height);


public:
	// �F���w�肵��ʂ�h��Ԃ�
	static VOID PaintCanvas(D2D1_COLOR_F Color);

	// �h��Ԃ��ꂽ�l�p�`��\������
	static VOID FillRect(INT X, INT Y, UINT Width, UINT Height, D2D1_COLOR_F Color);

	// �h��Ԃ���Ă��Ȃ��l�p�`��\������
	static VOID DrawRect(INT X, INT Y, UINT Width, UINT Height, D2D1_COLOR_F Color, FLOAT StrokeWidth);

	// �h��Ԃ��ꂽ�l�p�`�𒆐S����Ƃ������W�ɕ\������
	static VOID FillRectC(INT X, INT Y, UINT Width, UINT Height, D2D1_COLOR_F Color);

	// �h��Ԃ���Ă��Ȃ��l�p�`�𒆐S����Ƃ������W�ɕ\������
	static VOID DrawRectC(INT X, INT Y, UINT Width, UINT Height, D2D1_COLOR_F Color, FLOAT StrokeWidth);

};