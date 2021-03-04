#pragma once

#include "Core/Core.hpp"
#include "Core/Core_Graphic.hpp"


class Picture : private Core, private Core_Graphic {

private:
	ID2D1Bitmap* pBitmap;	// �r�b�g�}�b�v�f�[�^

public:
	// �R���X�g���N�^
	Picture();

	// �f�X�g���N�^
	~Picture();

	// �摜�t�@�C������f�[�^��ǂݍ���
	YGL_ERROR Load(const wchar_t* FileName);

	// �ǂݍ��񂾉摜�t�@�C���̃f�[�^���������
	void Unload();

	// �摜��\������
	void Draw(COORDINATES_INT Coordinates, SIZE_UINT Size);

	// �摜�̈ꕔ��\������
	void Draw(COORDINATES_INT Coordinates, SIZE_UINT Size, COORDINATES_INT sCoordinates, SIZE_UINT sSize);

	// �����x���w�肵�ĉ摜��\������
	void Draw(COORDINATES_INT Coordinates, SIZE_UINT Size, float Opacity);

	// �����x���w�肵�ĉ摜�̈ꕔ��\������
	void Draw(COORDINATES_INT Coordinates, SIZE_UINT Size, float Opacity, COORDINATES_INT sCoordinates, SIZE_UINT sSize);

	// ���S����Ƃ������W�ɉ摜��\������
	void DrawC(COORDINATES_INT Coordinates, SIZE_UINT Size);

	// ���S����Ƃ������W�ɉ摜�̈ꕔ��\������
	void DrawC(COORDINATES_INT Coordinates, SIZE_UINT Size, COORDINATES_INT sCoordinates, SIZE_UINT sSize);

	// �����x���w�肵�Ē��S����Ƃ������W�ɉ摜��\������
	void DrawC(COORDINATES_INT Coordinates, SIZE_UINT Size, float Opacity);

	// �����x���w�肵�Ē��S����Ƃ������W�ɉ摜�̈ꕔ��\������
	void DrawC(COORDINATES_INT Coordinates, SIZE_UINT Size, float Opacity, COORDINATES_INT sCoordinates, SIZE_UINT sSize);

};