#include "Text.hpp"

// �R���X�g���N�^
Text::Text() {

	pTextFormat = nullptr;
	pSolidBrush = nullptr;
	pDXGISurface = nullptr;

}

// �t�H���g��ǂݍ���
YGL_ERROR Text::Load(const wchar_t* FontName, float FontSize) {

	HRESULT hr = Load(FontName, FontSize, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL);

	return Convert_HRESULT_ToError(hr);
	
}

// �����E�X�^�C���E�����w�肵�ăt�H���g��ǂݍ���
YGL_ERROR Text::Load(const wchar_t* FontName, float FontSize, DWRITE_FONT_WEIGHT Weight, DWRITE_FONT_STYLE Style, DWRITE_FONT_STRETCH Stretch) {

	HRESULT hr = S_OK;

	// �e�L�X�g�t�H�[�}�b�g���쐬����
	hr = pDWriteFactory->CreateTextFormat(FontName, NULL, Weight, Style, Stretch, FontSize, L"", pTextFormat.GetAddressOf());
	if (FAILED(hr)) {
		return Convert_HRESULT_ToError(hr);
	}

	// �e�L�X�g�̔z�u��ݒ肷��
	hr = pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	if (FAILED(hr)) {
		return Convert_HRESULT_ToError(hr);
	}

	// ���̃u���V���쐬����
	hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f), pSolidBrush.GetAddressOf());
	if (FAILED(hr)) {
		return Convert_HRESULT_ToError(hr);
	}

	return YGL_ERROR_SUCCESS;

}

// ���W�ƕ\���G���A�̖ʐς��w�肵�ĕ������\������
void Text::Draw(COORDINATES_INT Coordinates, SIZE_UINT Size, const wchar_t* str) {

	pRenderTarget->DrawText(str, lstrlen(str), pTextFormat.Get(), TranslateCoordinates(Coordinates, Size), pSolidBrush.Get(), D2D1_DRAW_TEXT_OPTIONS_NONE);

}

// �\���F��ύX����
void Text::SetColor(COLOR_FLOAT Color) {

	pSolidBrush->SetColor(D2D1::ColorF(Color.Red, Color.Green, Color.Blue, Color.Alpha));

}