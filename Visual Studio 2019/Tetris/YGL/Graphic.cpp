#include "Graphic.hpp"


ComPtr<ID2D1SolidColorBrush> pSolidBrush = nullptr;
UINT Graphic::CanvasWidth = 640, Graphic::CanvasHeight = 480;
BOOL Graphic::Windowed = TRUE;
ComPtr<ID2D1Factory> Graphic::pD2DFactory = nullptr;
ComPtr<ID2D1HwndRenderTarget> Graphic::pRenderTarget = nullptr;
ComPtr<IWICImagingFactory> Graphic::pWICImagingFactory = nullptr;	// WICファクトリ
ComPtr<IDWriteFactory> Graphic::pDWriteFactory = nullptr;	// DirectWriteファクトリ

// 初期化処理を行う
HRESULT Graphic::InitGraphic() {

	HRESULT hr = S_OK;
	
	// Direct2Dファクトリを生成する
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, pD2DFactory.GetAddressOf());
	if (FAILED(hr))
		return hr;

	// レンダーターゲットを生成する
	hr = pD2DFactory->CreateHwndRenderTarget(RenderTargetProperties(), HwndRenderTargetProperties(Window::hWnd, SizeU(WindowWidth, WindowHeight)), &pRenderTarget);
	if (FAILED(hr))
		return hr;

	// 単色ブラシを生成する
	hr = pRenderTarget->CreateSolidColorBrush(ColorF(1.0f, 1.0f, 1.0f, 1.0f), pSolidBrush.GetAddressOf());
	if (FAILED(hr))
		return hr;

	// WICファクトリを生成する
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pWICImagingFactory);
	if (FAILED(hr))
		return hr;

	// DirectWriteファクトリを生成する
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(pDWriteFactory.GetAddressOf()));
	if (FAILED(hr))
		return hr;

	return S_OK;

}

// 左上を基準としたキャンバス座標を変換する
D2D1_RECT_F Graphic::TranslateCoordinates(INT X, INT Y, UINT Width, UINT Height) {

	return RectF(	// それぞれの値に ウィンドウサイズ/キャンバスサイズ をかけることで座標を調整しD2D1_RECT_Fに変換する
		(FLOAT)WindowWidth / (FLOAT)CanvasWidth * (FLOAT)X,
		(FLOAT)WindowHeight / (FLOAT)CanvasHeight * (FLOAT)Y,
		(FLOAT)WindowWidth / (FLOAT)CanvasWidth * ((FLOAT)X + (FLOAT)Width),
		(FLOAT)WindowHeight / (FLOAT)CanvasHeight * ((FLOAT)Y + (FLOAT)Height)
	);

}

// 中心を基準としたキャンバス座標を変換する
D2D1_RECT_F Graphic::TranslateCenterCoordinates(INT X, INT Y, UINT Width, UINT Height) {

	return TranslateCoordinates(X - Width / 2, Y - Height / 2, Width, Height);

}

// 色を指定し画面を塗りつぶす
VOID Graphic::PaintCanvas(D2D1_COLOR_F Color) {

	FillRect(0, 0, CanvasWidth, CanvasHeight, Color);

}

// 塗りつぶされた四角形を表示する
VOID Graphic::FillRect(INT X, INT Y, UINT Width, UINT Height, D2D1_COLOR_F Color) {

	// 描画矩形を指定する
	D2D1_RECT_F rect = TranslateCoordinates(X, Y, Width, Height);

	// 単色ブラシの色を変更する
	pSolidBrush->SetColor(Color);

	// 四角形を描画する
	pRenderTarget->FillRectangle(&rect, pSolidBrush.Get());

}

// 塗りつぶされていない四角形を表示する
VOID Graphic::DrawRect(INT X, INT Y, UINT Width, UINT Height, D2D1_COLOR_F Color, FLOAT StrokeWidth) {

	// 描画矩形を指定する
	D2D1_RECT_F rect = TranslateCoordinates(X, Y, Width, Height);

	// 単色ブラシの色を変更する
	pSolidBrush->SetColor(Color);

	// 四角形を描画する
	pRenderTarget->DrawRectangle(&rect, pSolidBrush.Get(), StrokeWidth);

}

// 塗りつぶされた四角形を中心を基準とした座標に表示する
VOID Graphic::FillRectC(INT X, INT Y, UINT Width, UINT Height, D2D1_COLOR_F Color) {

	// 描画矩形を指定する
	D2D1_RECT_F rect = TranslateCenterCoordinates(X, Y, Width, Height);

	// 単色ブラシの色を変更する
	pSolidBrush->SetColor(Color);

	// 四角形を描画する
	pRenderTarget->FillRectangle(&rect, pSolidBrush.Get());

}

// 塗りつぶされていない四角形を中心を基準とした座標に表示する
VOID Graphic::DrawRectC(INT X, INT Y, UINT Width, UINT Height, D2D1_COLOR_F Color, FLOAT StrokeWidth) {

	// 描画矩形を指定する
	D2D1_RECT_F rect = TranslateCenterCoordinates(X, Y, Width, Height);

	// 単色ブラシの色を変更する
	pSolidBrush->SetColor(Color);

	// 四角形を描画する
	pRenderTarget->DrawRectangle(&rect, pSolidBrush.Get(), StrokeWidth);

}