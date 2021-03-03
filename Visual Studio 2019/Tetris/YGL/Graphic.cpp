#include "Graphic.hpp"


// �F���w�肵��ʂ�h��Ԃ�
void Graphic::PaintCanvas(COLOR_FLOAT Color) {

	FillRect(CoordinatesI(0, 0), CanvasSize, Color);

}

// �h��Ԃ��ꂽ�l�p�`��\������
void Graphic::FillRect(COORDINATES_INT Coordinates, SIZE_UINT Size, COLOR_FLOAT Color) {

	// �`���`���w�肷��
	D2D1_RECT_F rect = TranslateCoordinates(Coordinates, Size);

	// �ėp�P�F�u���V�̐F��ύX����
	pSolidBrush->SetColor(D2D1::ColorF(Color.Red, Color.Green, Color.Blue, Color.Alpha));

	// �l�p�`��`�悷��
	pRenderTarget->FillRectangle(&rect, pSolidBrush.Get());

}

// �h��Ԃ���Ă��Ȃ��l�p�`��\������
void Graphic::DrawRect(COORDINATES_INT Coordinates, SIZE_UINT Size, COLOR_FLOAT Color, float StrokeWidth) {

	// �`���`���w�肷��
	D2D1_RECT_F rect = TranslateCoordinates(Coordinates, Size);

	// �ėp�P�F�u���V�̐F��ύX����
	pSolidBrush->SetColor(D2D1::ColorF(Color.Red, Color.Green, Color.Blue, Color.Alpha));

	// �l�p�`��`�悷��
	pRenderTarget->DrawRectangle(&rect, pSolidBrush.Get(), StrokeWidth);

}

// �h��Ԃ��ꂽ�l�p�`�𒆐S����Ƃ������W�ɕ\������
void Graphic::FillRectC(COORDINATES_INT Coordinates, SIZE_UINT Size, COLOR_FLOAT Color) {

	// �`���`���w�肷��
	D2D1_RECT_F rect = TranslateCoordinatesC(Coordinates, Size);

	// �ėp�P�F�u���V�̐F��ύX����
	pSolidBrush->SetColor(D2D1::ColorF(Color.Red, Color.Green, Color.Blue, Color.Alpha));

	// �l�p�`��`�悷��
	pRenderTarget->FillRectangle(&rect, pSolidBrush.Get());

}

// �h��Ԃ���Ă��Ȃ��l�p�`�𒆐S����Ƃ������W�ɕ\������
void Graphic::DrawRectC(COORDINATES_INT Coordinates, SIZE_UINT Size, COLOR_FLOAT Color, float StrokeWidth) {

	// �`���`���w�肷��
	D2D1_RECT_F rect = TranslateCoordinatesC(Coordinates, Size);

	// �ėp�P�F�u���V�̐F��ύX����
	pSolidBrush->SetColor(D2D1::ColorF(Color.Red, Color.Green, Color.Blue, Color.Alpha));

	// �l�p�`��`�悷��
	pRenderTarget->DrawRectangle(&rect, pSolidBrush.Get(), StrokeWidth);

}