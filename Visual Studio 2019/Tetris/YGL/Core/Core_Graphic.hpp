#pragma once

#include "Core.hpp"
#include "Core_Window.hpp"


class Core_Graphic : private Core, private Core_Window {

private:
	// Core_Graphic�N���X������������
	static HRESULT Init();

protected:
	static SIZE_UINT CanvasSize;	// �L�����o�X�̃T�C�Y
	static Microsoft::WRL::ComPtr<ID2D1Factory> pD2DFactory;	// Direct2D�t�@�N�g��
	static Microsoft::WRL::ComPtr<ID2D1HwndRenderTarget> pRenderTarget;	// Direct2D�����_�[�^�[�Q�b�g
	static Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pSolidBrush;	// �ėp�P�F�u���V
	static Microsoft::WRL::ComPtr<IWICImagingFactory> pWICImagingFactory;	// WIC�t�@�N�g��
	static Microsoft::WRL::ComPtr<IDWriteFactory> pDWriteFactory;	// DirectWrite�t�@�N�g��

	// �������Ƃ����L�����o�X���W��D2D1_RECT_F�ɕϊ�����
	static D2D1_RECT_F TranslateCoordinates(COORDINATES_INT Coordinates, SIZE_UINT Size);

	// ���S����Ƃ����L�����o�X���W��D2D1_RECT_F�ɕϊ�����
	static D2D1_RECT_F TranslateCoordinatesC(COORDINATES_INT Coordinates, SIZE_UINT Size);


	friend class Game;	// Game�N���X���t�����h�N���X�Ɏw�肷��
	friend class Config;	// Config�N���X���t�����h�N���X�Ɏw�肷��

};