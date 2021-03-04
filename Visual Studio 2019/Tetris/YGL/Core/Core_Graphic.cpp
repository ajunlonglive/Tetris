#include "Core_Graphic.hpp"


// 初期化処理を行う
HRESULT Core_Graphic::Init() {

	HRESULT hr = S_OK;

	// Direct2Dファクトリを生成する
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);
	if (FAILED(hr)) {
		return hr;
	}

	// レンダーターゲットを生成する
	hr = pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(WindowSize.Width, WindowSize.Height)), &pRenderTarget);
	if (FAILED(hr)) {
		return hr;
	}

	// 単色ブラシを生成する
	hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), &pSolidBrush);
	if (FAILED(hr)) {
		return hr;
	}

	// WICファクトリを生成する
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pWICImagingFactory);
	if (FAILED(hr)) {
		return hr;
	}

	// DirectWriteファクトリを生成する
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDWriteFactory));
	if (FAILED(hr)) {
		return hr;
	}

	return S_OK;

}

// 終了処理を行う
VOID Core_Graphic::Quit() {

	SafeRelease(&pDWriteFactory);
	SafeRelease(&pWICImagingFactory);
	SafeRelease(&pSolidBrush);
	SafeRelease(&pRenderTarget);
	SafeRelease(&pD2DFactory);

}

SIZE_UINT Core_Graphic::CanvasSize = { 640, 480 };	// キャンバスのサイズ
ID2D1Factory* Core_Graphic::pD2DFactory = NULL;	// Direct2Dファクトリ
ID2D1HwndRenderTarget* Core_Graphic::pRenderTarget = NULL;	// Direct2Dレンダーターゲット
ID2D1SolidColorBrush* Core_Graphic::pSolidBrush = NULL;	// 汎用単色ブラシ
IWICImagingFactory* Core_Graphic::pWICImagingFactory = NULL;	// WICファクトリ
IDWriteFactory* Core_Graphic::pDWriteFactory = NULL;	// DirectWriteファクトリ

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