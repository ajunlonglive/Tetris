#include "Picture.hpp"


// �R���X�g���N�^
Picture::Picture() {

	pWICBitmapDecoder = nullptr;
	pWICBitmapFrame = nullptr;
	pFormatConverter = nullptr;
	pBitmap = nullptr;

}

// �摜��ǂݍ���
HRESULT Picture::Load(LPCTSTR FileName) {

	HRESULT hr = S_OK;

	// �摜�t�@�C������Ƀf�R�[�_�[���쐬����
	hr = pWICImagingFactory->CreateDecoderFromFilename(FileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pWICBitmapDecoder);
	if (FAILED(hr))
		return hr;

	// �t���[���𓾂�
	hr = pWICBitmapDecoder->GetFrame(0, &pWICBitmapFrame);
	if (FAILED(hr))
		return hr;

	// �t�H�[�}�b�g�R���o�[�^�𐶐�����
	hr = pWICImagingFactory->CreateFormatConverter(&pFormatConverter);
	if (FAILED(hr))
		return hr;

	// �t�H�[�}�b�g�R���o�[�^������������
	hr = pFormatConverter->Initialize(pWICBitmapFrame.Get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 1.0f, WICBitmapPaletteTypeMedianCut);
	if (FAILED(hr))
		return hr;

	// �r�b�g�}�b�v���쐬����
	hr = pRenderTarget->CreateBitmapFromWicBitmap(pFormatConverter.Get(), NULL, &pBitmap);
	if (FAILED(hr))
		return hr;

	return S_OK;

}

// �摜��\������
VOID Picture::Draw(INT X, INT Y, UINT Width, UINT Height) {
	
	this->Draw(X, Y, Width, Height, 1.0f);

}

// �摜�̈ꕔ��\������
VOID Picture::Draw(INT X, INT Y, UINT Width, UINT Height, INT sX, INT sY, UINT sWidth, UINT sHeight) {

	this->Draw(X, Y, Width, Height, 1.0f, sX, sY, sWidth, sHeight);

}

// �����x���w�肵�ĉ摜��\������
VOID Picture::Draw(INT X, INT Y, UINT Width, UINT Height, FLOAT Opacity) {

	// �`���`���w�肷��
	D2D1_RECT_F DrawRect = TranslateCoordinates(X, Y, Width, Height);

	// �r�b�g�}�b�v��`�悷��
	pRenderTarget->DrawBitmap(pBitmap.Get(), DrawRect, Opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);

}

// �����x���w�肵�ĉ摜�̈ꕔ��\������
VOID Picture::Draw(INT X, INT Y, UINT Width, UINT Height, FLOAT Opacity, INT sX, INT sY, UINT sWidth, UINT sHeight) {

	// �`���`���w�肷��
	D2D1_RECT_F DrawRect = TranslateCoordinates(X, Y, Width, Height);

	// �r�b�g�}�b�v��`�悷��
	pRenderTarget->DrawBitmap(pBitmap.Get(), DrawRect, Opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, RectF((FLOAT)sX, (FLOAT)sY, (FLOAT)sX + sWidth, (FLOAT)sY + sHeight));

}

// ���S����Ƃ������W�ɉ摜��\������
VOID Picture::DrawC(INT X, INT Y, UINT Width, UINT Height) {

	this->DrawC(X, Y, Width, Height, 1.0f);

}

// ���S����Ƃ������W�ɉ摜�̈ꕔ��\������
VOID Picture::DrawC(INT X, INT Y, UINT Width, UINT Height, INT sX, INT sY, UINT sWidth, UINT sHeight) {

	this->DrawC(X, Y, Width, Height, 1.0f, sX, sY, sWidth, sHeight);

}

// �����x���w�肵�Ē��S����Ƃ������W�ɉ摜��\������
VOID Picture::DrawC(INT X, INT Y, UINT Width, UINT Height, FLOAT Opacity) {

	// �`���`���w�肷��
	D2D1_RECT_F DrawRect = TranslateCenterCoordinates(X, Y, Width, Height);

	// �r�b�g�}�b�v��`�悷��
	pRenderTarget->DrawBitmap(pBitmap.Get(), DrawRect, Opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);

}

// �����x���w�肵�Ē��S����Ƃ������W�ɉ摜�̈ꕔ��\������
VOID Picture::DrawC(INT X, INT Y, UINT Width, UINT Height, FLOAT Opacity, INT sX, INT sY, UINT sWidth, UINT sHeight) {

	// �`���`���w�肷��
	D2D1_RECT_F DrawRect = TranslateCenterCoordinates(X, Y, Width, Height);

	// �r�b�g�}�b�v��`�悷��
	pRenderTarget->DrawBitmap(pBitmap.Get(), DrawRect, Opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, RectF((FLOAT)sX, (FLOAT)sY, (FLOAT)sX + sWidth, (FLOAT)sY + sHeight));

}