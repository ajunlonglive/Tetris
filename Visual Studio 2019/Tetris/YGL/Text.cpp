#include "Text.hpp"

// �R���X�g���N�^
Text::Text() {

	pTextFormat = nullptr;
	pSolidBrush = nullptr;
	pDXGISurface = nullptr;

}

// �t�H���g��ǂݍ���
HRESULT Text::Load(LPCTSTR FontName, FLOAT Size) {

	return this->Load(FontName, Size, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);
	
}

// �����E�X�^�C���E�����w�肵�ăt�H���g��ǂݍ���
HRESULT Text::Load(LPCTSTR FontName, FLOAT Size, DWRITE_FONT_WEIGHT Weight, DWRITE_FONT_STYLE Style, DWRITE_FONT_STRETCH Stretch) {

	HRESULT hr = S_OK;

	// �e�L�X�g�t�H�[�}�b�g���쐬����
	hr = pDWriteFactory->CreateTextFormat(FontName, NULL, Weight, Style, Stretch, Size, TEXT(""), &pTextFormat);
	if (FAILED(hr))
		return hr;

	// �e�L�X�g�̔z�u��ݒ肷��
	hr = pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	if (FAILED(hr))
		return hr;

	// �u���V���쐬����(��)
	hr = pRenderTarget->CreateSolidColorBrush(ColorF(1.0f, 1.0f, 1.0f, 1.0f), &pSolidBrush);
	if (FAILED(hr))
		return hr;

	return S_OK;

}

// ���W�ƕ\���G���A�̖ʐς��w�肵�ĕ������\������
VOID Text::Draw(UINT X, UINT Y, UINT Width, UINT Height, LPCTSTR str) {

	pRenderTarget->DrawText(str, lstrlen(str), pTextFormat.Get(), TranslateCoordinates(X, Y, Width, Height), pSolidBrush.Get(), D2D1_DRAW_TEXT_OPTIONS_NONE);

}

// �\���F��ύX����
VOID Text::SetColor(ColorF Color) {

	pSolidBrush->SetColor(Color);

}