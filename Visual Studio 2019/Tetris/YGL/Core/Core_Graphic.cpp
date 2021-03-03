#include "Core_Graphic.hpp"


// Core_Graphicクラスを初期化する
HRESULT Core_Graphic::Init() {

	HRESULT hr = S_OK;

	// Direct2Dファクトリを生成する
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, pD2DFactory.GetAddressOf());
	if (FAILED(hr)) {
		return hr;
	}

	// レンダーターゲットを生成する
	hr = pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(WindowSize.Width, WindowSize.Height)), pRenderTarget.GetAddressOf());
	if (FAILED(hr)) {
		return hr;
	}

	// 単色ブラシを生成する
	hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), pSolidBrush.GetAddressOf());
	if (FAILED(hr)) {
		return hr;
	}

	// WICファクトリを生成する
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)pWICImagingFactory.GetAddressOf());
	if (FAILED(hr)) {
		return hr;
	}

	// DirectWriteファクトリを生成する
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(pDWriteFactory.GetAddressOf()));
	if (FAILED(hr)) {
		return hr;
	}

	return S_OK;

}

SIZE_UINT Core_Graphic::CanvasSize = { 640, 480 };	// キャンバスのサイズ
Microsoft::WRL::ComPtr<ID2D1Factory> Core_Graphic::pD2DFactory = nullptr;	// Direct2Dファクトリ
Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> Core_Graphic::pRenderTarget = nullptr;	// Direct2Dレンダーターゲット
Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> Core_Graphic::pSolidBrush = nullptr;	// 汎用単色ブラシ
Microsoft::WRL::ComPtr<IWICImagingFactory> Core_Graphic::pWICImagingFactory = nullptr;	// WICファクトリ
Microsoft::WRL::ComPtr<IDWriteFactory> Core_Graphic::pDWriteFactory = nullptr;	// DirectWriteファクトリ

// 左上を基準としたキャンバス座標をD2D1_RECT_Fに変換する
D2D1_RECT_F Core_Graphic::TranslateCoordinates(COORDINATES_INT Coordinates, SIZE_UINT Size) {

	return D2D1::RectF(	// それぞれの値に ウィンドウサイズ/キャンバスサイズ をかけることで座標を調整しD2D1_RECT_Fに変換する
		(FLOAT)WindowSize.Width / (FLOAT)CanvasSize.Width * (FLOAT)Coordinates.X,
		(FLOAT)WindowSize.Height / (FLOAT)CanvasSize.Height * (FLOAT)Coordinates.Y,
		(FLOAT)WindowSize.Width / (FLOAT)CanvasSize.Width * ((FLOAT)Coordinates.X + (FLOAT)Size.Width),
		(FLOAT)WindowSize.Height / (FLOAT)CanvasSize.Height * ((FLOAT)Coordinates.Y + (FLOAT)Size.Height)
	);

}

// 中心を基準としたキャンバス座標をD2D1_RECT_Fに変換する
D2D1_RECT_F Core_Graphic::TranslateCoordinatesC(COORDINATES_INT Coordinates, SIZE_UINT Size) {
	
	return TranslateCoordinates(
		CoordinatesI(Coordinates.X - Size.Width / 2, Coordinates.Y - Size.Height / 2),
		SizeU(Size.Width, Size.Height)
	);

}