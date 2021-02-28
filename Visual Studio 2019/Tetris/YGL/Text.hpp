#pragma once

#include "Core/Core.hpp"
#include "Graphic.hpp"

class Text : private Graphic {

private:
	ComPtr<IDWriteTextFormat> pTextFormat;
	ComPtr<ID2D1SolidColorBrush> pSolidBrush;
	ComPtr<IDXGISurface> pDXGISurface;

public:
	// �R���X�g���N�^
	Text();

	// �t�H���g��ǂݍ���
	HRESULT Load(LPCTSTR FontName, FLOAT FontSize);

	// �����E�X�^�C���E�����w�肵�ăt�H���g��ǂݍ���
	HRESULT Load(LPCTSTR FontName, FLOAT Size, DWRITE_FONT_WEIGHT Weight, DWRITE_FONT_STYLE Style, DWRITE_FONT_STRETCH Stretch);

	// ���W�ƕ\���G���A�̖ʐς��w�肵�ĕ������\������
	VOID Draw(UINT X, UINT Y, UINT Width, UINT Height, LPCTSTR str);

	// �\���F��ύX����
	VOID SetColor(ColorF Color);

};