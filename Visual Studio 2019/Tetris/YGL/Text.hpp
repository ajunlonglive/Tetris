#pragma once

#include "Core/Core.hpp"
#include "Core/Core_Graphic.hpp"


class Text : private Core, private Core_Graphic {

private:
	IDWriteTextFormat* pTextFormat;	// �e�L�X�g�t�H�[�}�b�g
	ID2D1SolidColorBrush* pSolidBrush;	// �P�F�u���V

public:
	// �R���X�g���N�^
	Text();

	// �f�X�g���N�^
	~Text();

	// �t�H���g�f�[�^��ǂݍ���
	YGL_ERROR Load(const wchar_t* FontName, float FontSize);

	// �ǂݍ��񂾃t�H���g�f�[�^���������
	void Unload();

	// �����E�X�^�C���E�����w�肵�ăt�H���g��ǂݍ���
	YGL_ERROR Load(const wchar_t* FontName, float FontSize, DWRITE_FONT_WEIGHT Weight, DWRITE_FONT_STYLE Style, DWRITE_FONT_STRETCH Stretch);

	// ���W�ƕ\���G���A�̖ʐς��w�肵�ĕ������\������
	void Draw(COORDINATES_INT Coordinates, SIZE_UINT Size, const wchar_t* str);

	// �\���F��ύX����
	void SetColor(COLOR_FLOAT Color);

};