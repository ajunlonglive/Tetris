#include "Core_Graphic.hpp"


// Core_Graphic�N���X������������
HRESULT Core_Graphic::Init() {

	HRESULT hr = S_OK;

	// Direct2D�t�@�N�g���𐶐�����
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, pD2DFactory.GetAddressOf());
	if (FAILED(hr)) {
		return hr;
	}

	// �����_�[�^�[�Q�b�g�𐶐�����
	hr = pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(WindowSize.Width, WindowSize.Height)), pRenderTarget.GetAddressOf());
	if (FAILED(hr)) {
		return hr;
	}

	// �P�F�u���V�𐶐�����
	hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), pSolidBrush.GetAddressOf());
	if (FAILED(hr)) {
		return hr;
	}

	// WIC�t�@�N�g���𐶐�����
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)pWICImagingFactory.GetAddressOf());
	if (FAILED(hr)) {
		return hr;
	}

	// DirectWrite�t�@�N�g���𐶐�����
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(pDWriteFactory.GetAddressOf()));
	if (FAILED(hr)) {
		return hr;
	}

	return S_OK;

}

SIZE_UINT Core_Graphic::CanvasSize = { 640, 480 };	// �L�����o�X�̃T�C�Y
Microsoft::WRL::ComPtr<ID2D1Factory> Core_Graphic::pD2DFactory = nullptr;	// Direct2D�t�@�N�g��
Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> Core_Graphic::pRenderTarget = nullptr;	// Direct2D�����_�[�^�[�Q�b�g
Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> Core_Graphic::pSolidBrush = nullptr;	// �ėp�P�F�u���V
Microsoft::WRL::ComPtr<IWICImagingFactory> Core_Graphic::pWICImagingFactory = nullptr;	// WIC�t�@�N�g��
Microsoft::WRL::ComPtr<IDWriteFactory> Core_Graphic::pDWriteFactory = nullptr;	// DirectWrite�t�@�N�g��

// �������Ƃ����L�����o�X���W��D2D1_RECT_F�ɕϊ�����
D2D1_RECT_F Core_Graphic::TranslateCoordinates(COORDINATES_INT Coordinates, SIZE_UINT Size) {

	return D2D1::RectF(	// ���ꂼ��̒l�� �E�B���h�E�T�C�Y/�L�����o�X�T�C�Y �������邱�Ƃō��W�𒲐���D2D1_RECT_F�ɕϊ�����
		(FLOAT)WindowSize.Width / (FLOAT)CanvasSize.Width * (FLOAT)Coordinates.X,
		(FLOAT)WindowSize.Height / (FLOAT)CanvasSize.Height * (FLOAT)Coordinates.Y,
		(FLOAT)WindowSize.Width / (FLOAT)CanvasSize.Width * ((FLOAT)Coordinates.X + (FLOAT)Size.Width),
		(FLOAT)WindowSize.Height / (FLOAT)CanvasSize.Height * ((FLOAT)Coordinates.Y + (FLOAT)Size.Height)
	);

}

// ���S����Ƃ����L�����o�X���W��D2D1_RECT_F�ɕϊ�����
D2D1_RECT_F Core_Graphic::TranslateCoordinatesC(COORDINATES_INT Coordinates, SIZE_UINT Size) {
	
	return TranslateCoordinates(
		CoordinatesI(Coordinates.X - Size.Width / 2, Coordinates.Y - Size.Height / 2),
		SizeU(Size.Width, Size.Height)
	);

}