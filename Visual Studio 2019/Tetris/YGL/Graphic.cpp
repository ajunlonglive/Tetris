#include "Graphic.hpp"


ComPtr<ID2D1SolidColorBrush> pSolidBrush = nullptr;
UINT Graphic::CanvasWidth = 640, Graphic::CanvasHeight = 480;
BOOL Graphic::Windowed = TRUE;
ComPtr<ID2D1Factory> Graphic::pD2DFactory = nullptr;
ComPtr<ID2D1HwndRenderTarget> Graphic::pRenderTarget = nullptr;
ComPtr<IWICImagingFactory> Graphic::pWICImagingFactory = nullptr;	// WIC�t�@�N�g��
ComPtr<IDWriteFactory> Graphic::pDWriteFactory = nullptr;	// DirectWrite�t�@�N�g��

// �������������s��
HRESULT Graphic::InitGraphic() {

	HRESULT hr = S_OK;
	
	// Direct2D�t�@�N�g���𐶐�����
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, pD2DFactory.GetAddressOf());
	if (FAILED(hr))
		return hr;

	// �����_�[�^�[�Q�b�g�𐶐�����
	hr = pD2DFactory->CreateHwndRenderTarget(RenderTargetProperties(), HwndRenderTargetProperties(Window::hWnd, SizeU(WindowWidth, WindowHeight)), &pRenderTarget);
	if (FAILED(hr))
		return hr;

	// �P�F�u���V�𐶐�����
	hr = pRenderTarget->CreateSolidColorBrush(ColorF(1.0f, 1.0f, 1.0f, 1.0f), pSolidBrush.GetAddressOf());
	if (FAILED(hr))
		return hr;

	// WIC�t�@�N�g���𐶐�����
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pWICImagingFactory);
	if (FAILED(hr))
		return hr;

	// DirectWrite�t�@�N�g���𐶐�����
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(pDWriteFactory.GetAddressOf()));
	if (FAILED(hr))
		return hr;

	return S_OK;

}

// �������Ƃ����L�����o�X���W��ϊ�����
D2D1_RECT_F Graphic::TranslateCoordinates(INT X, INT Y, UINT Width, UINT Height) {

	return RectF(	// ���ꂼ��̒l�� �E�B���h�E�T�C�Y/�L�����o�X�T�C�Y �������邱�Ƃō��W�𒲐���D2D1_RECT_F�ɕϊ�����
		(FLOAT)WindowWidth / (FLOAT)CanvasWidth * (FLOAT)X,
		(FLOAT)WindowHeight / (FLOAT)CanvasHeight * (FLOAT)Y,
		(FLOAT)WindowWidth / (FLOAT)CanvasWidth * ((FLOAT)X + (FLOAT)Width),
		(FLOAT)WindowHeight / (FLOAT)CanvasHeight * ((FLOAT)Y + (FLOAT)Height)
	);

}

// ���S����Ƃ����L�����o�X���W��ϊ�����
D2D1_RECT_F Graphic::TranslateCenterCoordinates(INT X, INT Y, UINT Width, UINT Height) {

	return TranslateCoordinates(X - Width / 2, Y - Height / 2, Width, Height);

}

// �F���w�肵��ʂ�h��Ԃ�
VOID Graphic::PaintCanvas(D2D1_COLOR_F Color) {

	FillRect(0, 0, CanvasWidth, CanvasHeight, Color);

}

// �h��Ԃ��ꂽ�l�p�`��\������
VOID Graphic::FillRect(INT X, INT Y, UINT Width, UINT Height, D2D1_COLOR_F Color) {

	// �`���`���w�肷��
	D2D1_RECT_F rect = TranslateCoordinates(X, Y, Width, Height);

	// �P�F�u���V�̐F��ύX����
	pSolidBrush->SetColor(Color);

	// �l�p�`��`�悷��
	pRenderTarget->FillRectangle(&rect, pSolidBrush.Get());

}

// �h��Ԃ���Ă��Ȃ��l�p�`��\������
VOID Graphic::DrawRect(INT X, INT Y, UINT Width, UINT Height, D2D1_COLOR_F Color, FLOAT StrokeWidth) {

	// �`���`���w�肷��
	D2D1_RECT_F rect = TranslateCoordinates(X, Y, Width, Height);

	// �P�F�u���V�̐F��ύX����
	pSolidBrush->SetColor(Color);

	// �l�p�`��`�悷��
	pRenderTarget->DrawRectangle(&rect, pSolidBrush.Get(), StrokeWidth);

}

// �h��Ԃ��ꂽ�l�p�`�𒆐S����Ƃ������W�ɕ\������
VOID Graphic::FillRectC(INT X, INT Y, UINT Width, UINT Height, D2D1_COLOR_F Color) {

	// �`���`���w�肷��
	D2D1_RECT_F rect = TranslateCenterCoordinates(X, Y, Width, Height);

	// �P�F�u���V�̐F��ύX����
	pSolidBrush->SetColor(Color);

	// �l�p�`��`�悷��
	pRenderTarget->FillRectangle(&rect, pSolidBrush.Get());

}

// �h��Ԃ���Ă��Ȃ��l�p�`�𒆐S����Ƃ������W�ɕ\������
VOID Graphic::DrawRectC(INT X, INT Y, UINT Width, UINT Height, D2D1_COLOR_F Color, FLOAT StrokeWidth) {

	// �`���`���w�肷��
	D2D1_RECT_F rect = TranslateCenterCoordinates(X, Y, Width, Height);

	// �P�F�u���V�̐F��ύX����
	pSolidBrush->SetColor(Color);

	// �l�p�`��`�悷��
	pRenderTarget->DrawRectangle(&rect, pSolidBrush.Get(), StrokeWidth);

}