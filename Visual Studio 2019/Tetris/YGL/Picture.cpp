#include "Picture.hpp"


// �R���X�g���N�^
Picture::Picture() {

	pBitmap = NULL;

}

// �f�X�g���N�^
Picture::~Picture() {

	Unload();

}

// �摜�t�@�C������f�[�^��ǂݍ���
YGL_ERROR Picture::Load(const wchar_t* FileName) {

	HRESULT hr = S_OK;

	// �摜�t�@�C������Ƀf�R�[�_�[���쐬����
	IWICBitmapDecoder* pWICBitmapDecoder = NULL;
	hr = pWICImagingFactory->CreateDecoderFromFilename(FileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pWICBitmapDecoder);
	if (FAILED(hr)) {
		return Convert_HRESULT_ToError(hr);
	}

	// �r�b�g�}�b�v�t���[���𐶐�����
	IWICBitmapFrameDecode* pWICBitmapFrame = NULL;
	hr = pWICBitmapDecoder->GetFrame(0, &pWICBitmapFrame);
	if (FAILED(hr)) {
		SafeRelease(&pWICBitmapDecoder);	// �r�b�g�}�b�v�f�R�[�_�[���������
		return Convert_HRESULT_ToError(hr);
	}

	// �t�H�[�}�b�g�R���o�[�^�𐶐�����
	IWICFormatConverter* pFormatConverter = NULL;
	hr = pWICImagingFactory->CreateFormatConverter(&pFormatConverter);
	if (FAILED(hr)) {
		SafeRelease(&pWICBitmapFrame);	// �r�b�g�}�b�v�t���[�����������
		SafeRelease(&pWICBitmapDecoder);	// �r�b�g�}�b�v�f�R�[�_�[���������
		return Convert_HRESULT_ToError(hr);
	}

	// �t�H�[�}�b�g�R���o�[�^������������
	hr = pFormatConverter->Initialize(pWICBitmapFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 1.0f, WICBitmapPaletteTypeMedianCut);
	if (FAILED(hr)) {
		SafeRelease(&pFormatConverter);	// �t�H�[�}�b�g�R���o�[�^���������
		SafeRelease(&pWICBitmapFrame);	// �r�b�g�}�b�v�t���[�����������
		SafeRelease(&pWICBitmapDecoder);	// �r�b�g�}�b�v�f�R�[�_�[���������
		return Convert_HRESULT_ToError(hr);
	}

	// �r�b�g�}�b�v���쐬����
	hr = pRenderTarget->CreateBitmapFromWicBitmap(pFormatConverter, NULL, &pBitmap);
	if (FAILED(hr)) {
		SafeRelease(&pFormatConverter);	// �t�H�[�}�b�g�R���o�[�^���������
		SafeRelease(&pWICBitmapFrame);	// �r�b�g�}�b�v�t���[�����������
		SafeRelease(&pWICBitmapDecoder);	// �r�b�g�}�b�v�f�R�[�_�[���������
		return Convert_HRESULT_ToError(hr);
	}


	SafeRelease(&pFormatConverter);	// �t�H�[�}�b�g�R���o�[�^���������
	SafeRelease(&pWICBitmapFrame);	// �r�b�g�}�b�v�t���[�����������
	SafeRelease(&pWICBitmapDecoder);	// �r�b�g�}�b�v�f�R�[�_�[���������

	return YGL_ERROR_SUCCESS;

}

// �ǂݍ��񂾉摜�t�@�C���̃f�[�^���������
void Picture::Unload() {

	SafeRelease(&pBitmap);

}

// �摜��\������
void Picture::Draw(COORDINATES_INT Coordinates, SIZE_UINT Size) {
	
	this->Draw(Coordinates, Size, 1.0f);

}

// �摜�̈ꕔ��\������
void Picture::Draw(COORDINATES_INT Coordinates, SIZE_UINT Size, COORDINATES_INT sCoordinates, SIZE_UINT sSize) {

	this->Draw(Coordinates, Size, 1.0f, sCoordinates, sSize);

}

// �����x���w�肵�ĉ摜��\������
void Picture::Draw(COORDINATES_INT Coordinates, SIZE_UINT Size, float Opacity) {

	// �`���`���w�肷��
	D2D1_RECT_F DrawRect = TranslateCoordinates(Coordinates, Size);

	// �r�b�g�}�b�v��`�悷��
	pRenderTarget->DrawBitmap(pBitmap, DrawRect, Opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);

}

// �����x���w�肵�ĉ摜�̈ꕔ��\������
void Picture::Draw(COORDINATES_INT Coordinates, SIZE_UINT Size, float Opacity, COORDINATES_INT sCoordinates, SIZE_UINT sSize) {

	// �`���`���w�肷��
	D2D1_RECT_F DrawRect = TranslateCoordinates(Coordinates, Size);

	// �r�b�g�}�b�v��`�悷��
	pRenderTarget->DrawBitmap(pBitmap, DrawRect, Opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF((FLOAT)sCoordinates.X, (FLOAT)sCoordinates.Y, (FLOAT)sCoordinates.X + (FLOAT)sSize.Width, (FLOAT)sCoordinates.Y + (FLOAT)sSize.Height));

}

// ���S����Ƃ������W�ɉ摜��\������
void Picture::DrawC(COORDINATES_INT Coordinates, SIZE_UINT Size) {

	this->DrawC(Coordinates, Size, 1.0f);

}

// ���S����Ƃ������W�ɉ摜�̈ꕔ��\������
void Picture::DrawC(COORDINATES_INT Coordinates, SIZE_UINT Size, COORDINATES_INT sCoordinates, SIZE_UINT sSize) {

	this->DrawC(Coordinates, Size, 1.0f, sCoordinates, sSize);

}

// �����x���w�肵�Ē��S����Ƃ������W�ɉ摜��\������
void Picture::DrawC(COORDINATES_INT Coordinates, SIZE_UINT Size, float Opacity) {

	// �`���`���w�肷��
	D2D1_RECT_F DrawRect = TranslateCoordinatesC(Coordinates, Size);

	// �r�b�g�}�b�v��`�悷��
	pRenderTarget->DrawBitmap(pBitmap, DrawRect, Opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);

}

// �����x���w�肵�Ē��S����Ƃ������W�ɉ摜�̈ꕔ��\������
void Picture::DrawC(COORDINATES_INT Coordinates, SIZE_UINT Size, float Opacity, COORDINATES_INT sCoordinates, SIZE_UINT sSize) {

	// �`���`���w�肷��
	D2D1_RECT_F DrawRect = TranslateCoordinatesC(Coordinates, Size);

	// �r�b�g�}�b�v��`�悷��
	pRenderTarget->DrawBitmap(pBitmap, DrawRect, Opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF((FLOAT)sCoordinates.X, (FLOAT)sCoordinates.Y, (FLOAT)sCoordinates.X + (FLOAT)sSize.Width, (FLOAT)sCoordinates.Y + (FLOAT)sSize.Height));

}