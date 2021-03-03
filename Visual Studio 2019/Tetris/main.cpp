#include <Windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>

#include "YGL/YGL.hpp"
#include "sub.hpp"


using namespace std;

double DropSpeed = 0.0;	// �������x(BlockPerSecond�A1�ɂȂ��1�b�Ԃ�1�}�X�u���b�N��������)
int timeCount = 0;
int random = 0;
long score = 0, highScore = 0;
int deleted = 0;

int scene = 0;

Text *text_size20, *text_size30;
Picture *titlePic, *framePic, *gamePic, *scoreBoardPic;
Sound *se1, *se2, *se3, *se4, *se5, *se6, *se7, *se8;
Sound *bgm1;
fstream fs;

int TetrisLoad();
void TetrisRelease();
bool TetrisDown();
bool TitleScene();
void GameScene();
void ScoreBoard();
void GameResultScene();
void BlackScene();


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

	Config::SetWindowSize(SizeU(800, 600));
	Config::SetWindowTitle(L"�e�g���X");
	Config::SetCanvasSize(SizeU(800, 600));
	Config::SetWindowMode(true);

	int ret = 0;

	// �Q�[��������������
	ret = Game::Init();
	if (0 < ret) {
		return ret;
	}

	// �e�g���X�ɗp���郊�\�[�X�����[�h����
	ret = TetrisLoad();
	if (0 < ret) {
		return ret;
	}

#ifdef _DEBUG
	// �f�o�b�O�p�e�L�X�g
	Text* debugText = new Text;
	if (0 < debugText->Load(L"���C���I", 20))
		return __LINE__;
	debugText->SetColor(ColorF(1.0f, 0.0f, 0.0f, 1.0f));
#endif	

	// �����V�[�h���Z�b�g����
	srand((unsigned)time(NULL));

	// �Z�[�u�t�@�C�����J��
	fs.open("score.sav", ios::in | ios::binary);
	if (!fs) {
		fs.open("score.sav", ios::out | ios::binary);
		fs.write((const char*)&highScore, sizeof(highScore));
		fs.close();
	}
	fs.read((char*)&highScore, sizeof(highScore));	// �n�C�X�R�A��ǂݍ���
	fs.close();

	bgm1->Play(true);

	// �Q�[�����[�v
	while (Game::GameLoop()) {
		Game::LoopStart();

		if (scene == 0) {
			if (!TitleScene()) {
				bgm1->Stop();
				break;
			}
		}
		else if (scene == 1) {
			// �Q�[�����
			GameScene();
		}
		else if (scene == 2) {
			// �X�R�A�m�F���
			ScoreBoard();
		}
		else if (scene == 3) {
			// ���Z���
			GameResultScene();
		}
		else if (scene == 4) {
			// ���Z��ʂ̂��Ƃ̃E�F�C�g
			BlackScene();
		}



#ifdef _DEBUG
		// �f�o�b�O�p�̐��l��\������
		{
			WCHAR str[256] = { 0 };
			SecureZeroMemory(&str, sizeof(str));
			swprintf(str, 256, L"FPS = %lf", Time::GetActualFPS());
			debugText->Draw(CoordinatesI(0, 0), SizeU(800, 600), str);
			SecureZeroMemory(&str, sizeof(str));
			swprintf(str, 256, L"DropSpeed = %lf", DropSpeed);
			debugText->Draw(CoordinatesI(0, 20), SizeU(800, 600), str);
			SecureZeroMemory(&str, sizeof(str));
		}
#endif
		Game::LoopEnd();
	}

	// �e�g���X�ɗp�������\�[�X���������
	TetrisRelease();

#ifdef _DEBUG
	delete debugText;
#endif

	Game::Quit();

	return 0;

}

int TetrisLoad() {

	// �t�H���g��ǂݍ���
	text_size20 = new Text;
	if (0 < text_size20->Load(L"HG��������-PRO", 20))
		return __LINE__;
	text_size20->SetColor(ColorF(1.0f, 1.0f, 1.0f, 1.0f));
	text_size30 = new Text;
	if (0 < text_size30->Load(L"HG��������-PRO", 30))
		return __LINE__;
	text_size30->SetColor(ColorF(1.0f, 1.0f, 1.0f, 1.0f));

	// �摜��ǂݍ���
	titlePic = new Picture;
	if (0 < titlePic->Load(L"picture/title.png"))
		return __LINE__;
	framePic = new Picture;
	if (0 < framePic->Load(L"picture/frame.png"))
		return __LINE__;
	gamePic = new Picture;
	if (0 < gamePic->Load(L"picture/game.png"))
		return __LINE__;
	scoreBoardPic = new Picture;
	if (scoreBoardPic->Load(L"picture/score.png"))
		return __LINE__;

	// �����t�@�C����ǂݍ���
	se1 = new Sound;
	if (0 < se1->Load(L"sound/se1.wav"))
		return __LINE__;
	se2 = new Sound;
	if (0 < se2->Load(L"sound/se2.wav"))
		return __LINE__;
	se3 = new Sound;
	if (0 < se3->Load(L"sound/se3.wav"))
		return __LINE__;
	se4 = new Sound;
	if (0 < se4->Load(L"sound/se4.wav"))
		return __LINE__;
	se5 = new Sound;
	if (0 < se5->Load(L"sound/se5.wav"))
		return __LINE__;
	se6 = new Sound;
	if (0 < se6->Load(L"sound/se6.wav"))
		return __LINE__;
	se7 = new Sound;
	if (0 < se7->Load(L"sound/se7.wav"))
		return __LINE__;
	se8 = new Sound;
	if (0 < se8->Load(L"sound/se8.wav"))
		return __LINE__;

	// BGM��ǂݍ���
	bgm1 = new Sound;
	if (0 < bgm1->Load(L"sound/bgm1.wav"))
		return __LINE__;

	// �u���b�N�摜��ǂݍ���
	if (0 < Block::Load(L"picture/block.png", 80))
		return __LINE__;

	return 0;

}

void TetrisRelease() {

	delete text_size20;
	delete text_size30;
	delete titlePic;
	delete framePic;
	delete gamePic;
	delete scoreBoardPic;

	delete se1;
	delete se2;
	delete se3;
	delete se4;
	delete se5;
	delete se6;
	delete se7;
	delete se8;
	delete bgm1;

}

// �^�C�g�����
bool TitleScene() {

	static int frameX = 300, frameY = 350;

	titlePic->Draw(CoordinatesI(0, 0), SizeU(800, 600));
	framePic->Draw(CoordinatesI(frameX, frameY), SizeU(210, 50));

	if (GetAsyncKeyState(VK_UP) & 1) {
		se2->Play(false);
		if (frameY == 350) {
			frameY += 100;
		}
		else {
			frameY -= 50;
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 1) {
		se2->Play(false);
		if (frameY == 450) {
			frameY -= 100;
		}
		else {
			frameY += 50;
		}
	}
	if (GetAsyncKeyState(VK_SPACE) & 1) {
		se1->Play(false);
		if (frameY == 350) {
			
			DropSpeed = 0.5;	// �������x��ݒ肷��
			timeCount = 0;	// �J�E���^��0�ɁB
			random = rand() % 7 + 1;// �����𐶐�����
			score = 0, deleted = 0;	// �X�R�A�֌W�̕ϐ������Z�b�g

			Field::Clear();	// �t�B�[���h�f�[�^���N���A����

			Tetrimino::CompyMino(random);	// �������ꂽ�����ɉ����čŏ��̃~�m�����
			random = rand() % 7 + 1;	// ���̃~�m��\�������𐶐�����

			scene = 1;
		}
		else if (frameY == 400) {
			scene = 2;
		}
		else {
			return false;
		}
	}

	return true;
}

// �Q�[���̃��C������
void GameScene() {

	// �w�i�摜��\������
	gamePic->Draw(CoordinatesI(0, 0), SizeU(800, 600));

	// �t�B�[���h�p�̎l�p�`��\������
	Graphic::FillRect(CoordinatesI(150, 20), SizeU(400, 560), ColorF(0.0f, 0.0f, 0.0f, 0.5f));
	Graphic::FillRect(CoordinatesI(555, 20), SizeU(240, 240), ColorF(0.0f, 0.0f, 0.0f, 0.5f));
	Graphic::FillRect(CoordinatesI(555, 280), SizeU(240, 160), ColorF(0.0f, 0.0f, 0.0f, 0.5f));
	Graphic::FillRect(CoordinatesI(555, 460), SizeU(240, 120), ColorF(0.0f, 0.0f, 0.0f, 0.5f));

	// ������\������
	text_size30->Draw(CoordinatesI(600, 200), SizeU(300, 30), L"NEXT is ...");
	WCHAR str[256] = { 0 };
	SecureZeroMemory(&str, sizeof(str));
	swprintf(str, 256, L"HIGH SCORE\n            : %ld\nSCORE : %ld\nDELETED : %d", highScore, score, deleted);
	text_size30->Draw(CoordinatesI(555, 300), SizeU(300, 300), str);
	text_size20->Draw(CoordinatesI(555, 490), SizeU(300, 300), L"�����L�[�ňړ��A\n�����L�[�ŉ�]�A\n�X�y�[�X�L�[�ŉ���");



	if (GetAsyncKeyState(VK_SPACE)) {
		// �X�y�[�X�L�[��������Ă���Ƃ�
		if (DropSpeed <= 6.0) {
			if ((double)timeCount / Time::GetTheoreticalFPS() >= 1.0 / 6.0) {
				if (!TetrisDown()) {
					scene = 3;
					return;
				}
			}
		}
		else {
			if ((double)timeCount / Time::GetTheoreticalFPS() >= 1.0 / DropSpeed) {
				if (!TetrisDown()) {
					scene = 3;
					return;
				}
			}
		}
	}
	else {
		if ((double)timeCount / Time::GetTheoreticalFPS() >= 1.0 / DropSpeed) {
			if (!TetrisDown()) {
				scene = 3;
				return;
			}
		}
	}

	if (GetAsyncKeyState(VK_UP) & 1) {
		if (Tetrimino::TurnRight()) {
			se4->Play(false);
		}
		else {
			se5->Play(false);
		}
	}
	if (GetAsyncKeyState(VK_DOWN) & 1) {
		if (Tetrimino::TurnLeft()) {
			se4->Play(false);
		}
		else {
			se5->Play(false);
		}
	}
	if (GetAsyncKeyState(VK_LEFT) & 1) {
		if (!Tetrimino::MoveLeft()) {
			se5->Play(false);
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) & 1) {
		if (!Tetrimino::MoveRight()) {
			se5->Play(false);
		}
	}

	Field::Draw();
	Tetrimino::Draw();
	DrawNextMino(random);


	timeCount++;
}

// �������x�ɔ�Ⴕ�Ĉ�莞�ԂɌĂяo�����
bool TetrisDown() {

	// ���̊֐����Ăяo�����Ƃ������Ƃ͗����������s����Ƃ������Ƃł���
	// �~�m�������ł��Ȃ��Ȃ�����A�~�m���t�B�[���h�f�[�^�ɔ��f���V�����~�m���t�B�[���h�㕔�ɐ�������
	// ���̍ۂɃu���b�N�̍폜������s���A1��ł��u���b�N���폜���ꂽ�痎�����x���኱�ɂ߁A�폜���ꂽ�u���b�N���ɉ������X�R�A�����Z����
	if (!Tetrimino::MoveDown()) {
		// �~�m�����n������
		se6->Play(false);
		Tetrimino::Transcribe();

		int del = Field::Delete();	// ��̏��������݂�

		if (del > 0) {
			// �������u���b�N�̗����������
			se7->Play(false);
			deleted += del;
			score += del * del * 100 + deleted * 10;	// �폜���ꂽ�u���b�N���ɉ������X�R�A�����Z����
			if (DropSpeed > 0.5 && DropSpeed < 1.0) {
				DropSpeed = DropSpeed - 0.25;
			}
			else if (DropSpeed > 1.0) {
				DropSpeed = DropSpeed - 0.45 - DropSpeed * 0.05;	// �������x�𗎂Ƃ�
			}
		}

		Tetrimino::ClearMino();	// ���݂̃~�m���N���A����
		if (!Tetrimino::CompyMino(random)) {
			se8->Play(false);
			// �Q�[���I�[�o�[
			return false;
		}
		Tetrimino::ResetCoordinates();	// �~�m�̍��W�������ʒu�ɖ߂�
		DropSpeed = DropSpeed + DropSpeed * 0.1;	// �������x��10%����������
		random = rand() % 7 + 1;	// 1~7�̗����𐶐�����
	}
	timeCount = 0;

	return true;
}

// �X�R�A�{�[�h
void ScoreBoard() {

	// �摜��\������
	scoreBoardPic->Draw(CoordinatesI(0, 0), SizeU(800, 600));

	// ��ʑS�̂𓧖��x50%�̍��œh��
	Graphic::PaintCanvas(ColorF(0.0f, 0.0f, 0.0f, 0.5f));

	// �e�L�X�g��\������
	WCHAR str[256] = { 0 };
	SecureZeroMemory(&str, sizeof(str));
	swprintf(str, 256, L"�n�C�X�R�A : %ld", highScore);
	text_size30->Draw(CoordinatesI(200, 250), SizeU(500, 500), str);
	text_size30->Draw(CoordinatesI(200, 400), SizeU(500, 500), L"�X�y�[�X�L�[�������Ɩ߂�");

	if (GetAsyncKeyState(VK_SPACE) & 1) {
		se3->Play(false);
		scene = 0;
		Sleep(1);
	}

}

// �Q�[�����Z���
void GameResultScene() {

	// �w�i�摜��\������
	gamePic->Draw(CoordinatesI(0, 0), SizeU(800, 600));

	// �t�B�[���h�p�̎l�p�`��\������
	Graphic::FillRect(CoordinatesI(150, 20), SizeU(400, 560), ColorF(0.0f, 0.0f, 0.0f, 0.5f));
	Graphic::FillRect(CoordinatesI(555, 20), SizeU(240, 240), ColorF(0.0f, 0.0f, 0.0f, 0.5f));
	Graphic::FillRect(CoordinatesI(555, 280), SizeU(240, 160), ColorF(0.0f, 0.0f, 0.0f, 0.5f));
	Graphic::FillRect(CoordinatesI(555, 460), SizeU(240, 120), ColorF(0.0f, 0.0f, 0.0f, 0.5f));

	// ������\������
	text_size30->Draw(CoordinatesI(600, 200), SizeU(300, 30), L"NEXT is ...");
	WCHAR str[256] = { 0 };
	SecureZeroMemory(&str, sizeof(str));
	swprintf(str, 256, L"HIGH SCORE\n            : %ld\nSCORE : %ld\nDELETED : %d", highScore, score, deleted);
	text_size30->Draw(CoordinatesI(555, 300), SizeU(300, 300), str);
	text_size20->Draw(CoordinatesI(555, 490), SizeU(300, 300), L"�����L�[�ňړ��A\n�����L�[�ŉ�]�A\n�X�y�[�X�L�[�ŉ���");

	// �u���b�N��\������
	Field::Draw();
	Tetrimino::Draw();
	DrawNextMino(random);

	// ��ʑS�̂𓧖��x50%�̍��œh��
	Graphic::PaintCanvas(ColorF(0.0f, 0.0f, 0.0f, 0.5f));

	SecureZeroMemory(&str, sizeof(str));
	if (score > highScore) {
		swprintf(str, 256, L"�X�R�A : %ld (�L�^�X�V!)\n��������̐� : %d", score, deleted);
	}
	else {
		swprintf(str, 256, L"�X�R�A : %ld\n��������̐� : %d", score, deleted);
	}
	text_size30->Draw(CoordinatesI(200, 250), SizeU(500, 500), str);
	text_size30->Draw(CoordinatesI(200, 400), SizeU(500, 500), L"�X�y�[�X�L�[�������Ɩ߂�");

	if (GetAsyncKeyState(VK_SPACE) & 1) {
		se3->Play(false);
		timeCount = 0;
		scene = 4;
		Sleep(1);
	}

}

// �����(���̊֐����Ăяo���ۂɂ͕K��timeCount��0�������Ă�������)
void BlackScene() {

	if (timeCount == 0) {

		highScore = score;

		// �n�C�X�R�A���Z�[�u����
		fs.open("score.sav", ios::out | ios::binary);
		if (fs) {
			fs.write((const char*)&highScore, sizeof(highScore));	// �n�C�X�R�A����������
			fs.close();
		}
	}

	// 1�b�҂�
	if (timeCount >= Time::GetTheoreticalFPS()) {
		scene = 0;
	}

	timeCount++;
}