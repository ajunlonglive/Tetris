#include <Windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>

#include "YGL/YGL.hpp"
#include "sub.hpp"


using namespace std;

double DropSpeed = 0.0;	// 落下速度(BlockPerSecond、1になると1秒間に1マスブロックが落ちる)
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
	Config::SetWindowTitle(L"テトリス");
	Config::SetCanvasSize(SizeU(800, 600));
	Config::SetWindowMode(true);

	int ret = 0;

	// ゲームを初期化する
	ret = Game::Init();
	if (0 < ret) {
		return ret;
	}

	// テトリスに用いるリソースをロードする
	ret = TetrisLoad();
	if (0 < ret) {
		return ret;
	}

#ifdef _DEBUG
	// デバッグ用テキスト
	Text* debugText = new Text;
	if (0 < debugText->Load(L"メイリオ", 20))
		return __LINE__;
	debugText->SetColor(ColorF(1.0f, 0.0f, 0.0f, 1.0f));
#endif	

	// 乱数シードをセットする
	srand((unsigned)time(NULL));

	// セーブファイルを開く
	fs.open("score.sav", ios::in | ios::binary);
	if (!fs) {
		fs.open("score.sav", ios::out | ios::binary);
		fs.write((const char*)&highScore, sizeof(highScore));
		fs.close();
	}
	fs.read((char*)&highScore, sizeof(highScore));	// ハイスコアを読み込む
	fs.close();

	bgm1->Play(true);

	// ゲームループ
	while (Game::GameLoop()) {
		Game::LoopStart();

		if (scene == 0) {
			if (!TitleScene()) {
				bgm1->Stop();
				break;
			}
		}
		else if (scene == 1) {
			// ゲーム画面
			GameScene();
		}
		else if (scene == 2) {
			// スコア確認画面
			ScoreBoard();
		}
		else if (scene == 3) {
			// 決算画面
			GameResultScene();
		}
		else if (scene == 4) {
			// 決算画面のあとのウェイト
			BlackScene();
		}



#ifdef _DEBUG
		// デバッグ用の数値を表示する
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

	// テトリスに用いたリソースを解放する
	TetrisRelease();

#ifdef _DEBUG
	delete debugText;
#endif

	Game::Quit();

	return 0;

}

int TetrisLoad() {

	// フォントを読み込む
	text_size20 = new Text;
	if (0 < text_size20->Load(L"HG正楷書体-PRO", 20))
		return __LINE__;
	text_size20->SetColor(ColorF(1.0f, 1.0f, 1.0f, 1.0f));
	text_size30 = new Text;
	if (0 < text_size30->Load(L"HG正楷書体-PRO", 30))
		return __LINE__;
	text_size30->SetColor(ColorF(1.0f, 1.0f, 1.0f, 1.0f));

	// 画像を読み込む
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

	// 音声ファイルを読み込む
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

	// BGMを読み込む
	bgm1 = new Sound;
	if (0 < bgm1->Load(L"sound/bgm1.wav"))
		return __LINE__;

	// ブロック画像を読み込む
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

// タイトル画面
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
			
			DropSpeed = 0.5;	// 落下速度を設定する
			timeCount = 0;	// カウンタを0に。
			random = rand() % 7 + 1;// 乱数を生成する
			score = 0, deleted = 0;	// スコア関係の変数もリセット

			Field::Clear();	// フィールドデータをクリアする

			Tetrimino::CompyMino(random);	// 生成された乱数に応じて最初のミノを作る
			random = rand() % 7 + 1;	// 次のミノを表す乱数を生成する

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

// ゲームのメイン処理
void GameScene() {

	// 背景画像を表示する
	gamePic->Draw(CoordinatesI(0, 0), SizeU(800, 600));

	// フィールド用の四角形を表示する
	Graphic::FillRect(CoordinatesI(150, 20), SizeU(400, 560), ColorF(0.0f, 0.0f, 0.0f, 0.5f));
	Graphic::FillRect(CoordinatesI(555, 20), SizeU(240, 240), ColorF(0.0f, 0.0f, 0.0f, 0.5f));
	Graphic::FillRect(CoordinatesI(555, 280), SizeU(240, 160), ColorF(0.0f, 0.0f, 0.0f, 0.5f));
	Graphic::FillRect(CoordinatesI(555, 460), SizeU(240, 120), ColorF(0.0f, 0.0f, 0.0f, 0.5f));

	// 文字を表示する
	text_size30->Draw(CoordinatesI(600, 200), SizeU(300, 30), L"NEXT is ...");
	WCHAR str[256] = { 0 };
	SecureZeroMemory(&str, sizeof(str));
	swprintf(str, 256, L"HIGH SCORE\n            : %ld\nSCORE : %ld\nDELETED : %d", highScore, score, deleted);
	text_size30->Draw(CoordinatesI(555, 300), SizeU(300, 300), str);
	text_size20->Draw(CoordinatesI(555, 490), SizeU(300, 300), L"←→キーで移動、\n↑↓キーで回転、\nスペースキーで加速");



	if (GetAsyncKeyState(VK_SPACE)) {
		// スペースキーが押されているとき
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

// 落下速度に比例して一定時間に呼び出される
bool TetrisDown() {

	// この関数が呼び出されるということは落下処理が行われるということである
	// ミノが落下できなくなったら、ミノをフィールドデータに反映し新しいミノをフィールド上部に生成する
	// その際にブロックの削除判定を行い、1列でもブロックが削除されたら落下速度を若干緩め、削除されたブロック数に応じたスコアを加算する
	if (!Tetrimino::MoveDown()) {
		// ミノが着地したら
		se6->Play(false);
		Tetrimino::Transcribe();

		int del = Field::Delete();	// 列の消去を試みる

		if (del > 0) {
			// もしもブロックの列を消したら
			se7->Play(false);
			deleted += del;
			score += del * del * 100 + deleted * 10;	// 削除されたブロック数に応じたスコアを加算する
			if (DropSpeed > 0.5 && DropSpeed < 1.0) {
				DropSpeed = DropSpeed - 0.25;
			}
			else if (DropSpeed > 1.0) {
				DropSpeed = DropSpeed - 0.45 - DropSpeed * 0.05;	// 落下速度を落とす
			}
		}

		Tetrimino::ClearMino();	// 現在のミノをクリアする
		if (!Tetrimino::CompyMino(random)) {
			se8->Play(false);
			// ゲームオーバー
			return false;
		}
		Tetrimino::ResetCoordinates();	// ミノの座標を初期位置に戻す
		DropSpeed = DropSpeed + DropSpeed * 0.1;	// 落下速度を10%増加させる
		random = rand() % 7 + 1;	// 1~7の乱数を生成する
	}
	timeCount = 0;

	return true;
}

// スコアボード
void ScoreBoard() {

	// 画像を表示する
	scoreBoardPic->Draw(CoordinatesI(0, 0), SizeU(800, 600));

	// 画面全体を透明度50%の黒で塗る
	Graphic::PaintCanvas(ColorF(0.0f, 0.0f, 0.0f, 0.5f));

	// テキストを表示する
	WCHAR str[256] = { 0 };
	SecureZeroMemory(&str, sizeof(str));
	swprintf(str, 256, L"ハイスコア : %ld", highScore);
	text_size30->Draw(CoordinatesI(200, 250), SizeU(500, 500), str);
	text_size30->Draw(CoordinatesI(200, 400), SizeU(500, 500), L"スペースキーを押すと戻る");

	if (GetAsyncKeyState(VK_SPACE) & 1) {
		se3->Play(false);
		scene = 0;
		Sleep(1);
	}

}

// ゲーム決算画面
void GameResultScene() {

	// 背景画像を表示する
	gamePic->Draw(CoordinatesI(0, 0), SizeU(800, 600));

	// フィールド用の四角形を表示する
	Graphic::FillRect(CoordinatesI(150, 20), SizeU(400, 560), ColorF(0.0f, 0.0f, 0.0f, 0.5f));
	Graphic::FillRect(CoordinatesI(555, 20), SizeU(240, 240), ColorF(0.0f, 0.0f, 0.0f, 0.5f));
	Graphic::FillRect(CoordinatesI(555, 280), SizeU(240, 160), ColorF(0.0f, 0.0f, 0.0f, 0.5f));
	Graphic::FillRect(CoordinatesI(555, 460), SizeU(240, 120), ColorF(0.0f, 0.0f, 0.0f, 0.5f));

	// 文字を表示する
	text_size30->Draw(CoordinatesI(600, 200), SizeU(300, 30), L"NEXT is ...");
	WCHAR str[256] = { 0 };
	SecureZeroMemory(&str, sizeof(str));
	swprintf(str, 256, L"HIGH SCORE\n            : %ld\nSCORE : %ld\nDELETED : %d", highScore, score, deleted);
	text_size30->Draw(CoordinatesI(555, 300), SizeU(300, 300), str);
	text_size20->Draw(CoordinatesI(555, 490), SizeU(300, 300), L"←→キーで移動、\n↑↓キーで回転、\nスペースキーで加速");

	// ブロックを表示する
	Field::Draw();
	Tetrimino::Draw();
	DrawNextMino(random);

	// 画面全体を透明度50%の黒で塗る
	Graphic::PaintCanvas(ColorF(0.0f, 0.0f, 0.0f, 0.5f));

	SecureZeroMemory(&str, sizeof(str));
	if (score > highScore) {
		swprintf(str, 256, L"スコア : %ld (記録更新!)\n消した列の数 : %d", score, deleted);
	}
	else {
		swprintf(str, 256, L"スコア : %ld\n消した列の数 : %d", score, deleted);
	}
	text_size30->Draw(CoordinatesI(200, 250), SizeU(500, 500), str);
	text_size30->Draw(CoordinatesI(200, 400), SizeU(500, 500), L"スペースキーを押すと戻る");

	if (GetAsyncKeyState(VK_SPACE) & 1) {
		se3->Play(false);
		timeCount = 0;
		scene = 4;
		Sleep(1);
	}

}

// 黒画面(この関数を呼び出す際には必ずtimeCountに0を代入しておくこと)
void BlackScene() {

	if (timeCount == 0) {

		highScore = score;

		// ハイスコアをセーブする
		fs.open("score.sav", ios::out | ios::binary);
		if (fs) {
			fs.write((const char*)&highScore, sizeof(highScore));	// ハイスコアを書き込む
			fs.close();
		}
	}

	// 1秒待つ
	if (timeCount >= Time::GetTheoreticalFPS()) {
		scene = 0;
	}

	timeCount++;
}