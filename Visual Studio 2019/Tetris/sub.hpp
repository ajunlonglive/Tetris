#pragma once

#include "YGL/YGL.hpp"


void DrawNextMino(int n);

class Field {
public:
	static int Data[14][18];	// �{�̂�10*14�A���͂Ɍ���2�̕ǂ�z�u����
	static void Draw();
	static int Delete();
	static void Clear();
};

class Tetrimino {
public:
	static int X, Y;
	static int Mino[4][4];
	static const int DefaultMino[7][4][4];
	static void ClearMino();
	static bool CompyMino(int n);
	static void ResetCoordinates();
	static bool MoveLeft();
	static bool MoveRight();
	static bool MoveDown();
	static bool TurnLeft();
	static bool TurnRight();
	static void Transcribe();	// �~�m�\�����t�B�[���h�f�[�^�ɏ����o��
	static void Draw();
};

class Block {
public:
	static Picture *pic;
	static unsigned int Size;
	static unsigned int ImageSize;

	static int Load(const wchar_t* FileName, unsigned int n);
	static void Unload();
	static void Draw(int x, int y, int n);
	static void DrawSub(int x, int y, int n);
};

class Area {
public:
	static int X_Main, Y_Main;
	static int X_Sub, Y_Sub;
};