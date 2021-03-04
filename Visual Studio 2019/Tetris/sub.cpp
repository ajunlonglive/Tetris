#include "sub.hpp"



void DrawNextMino(int n) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Block::DrawSub(i * Block::Size, j * Block::Size, Tetrimino::DefaultMino[n - 1][i][j]);
		}
	}
}

int Field::Data[14][18] = {
	{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
	{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
	{8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8},
	{8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8},
	{8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8},
	{8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8},
	{8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8},
	{8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8},
	{8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8},
	{8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8},
	{8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8},
	{8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8},
	{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8},
	{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8}
};

void Field::Draw() {

	for (int i = 0; i < 14; i++) {
		for (int j = 0; j < 18; j++) {
			Block::Draw(i * 40, j * 40, Data[i][j]);
		}
	}

}

int Field::Delete() {

	int Count = 0;

	for (int i = 0; i < 14; i++) {

		// 横一列を消去可能か判定する
		for (int j = 0; j < 10; j++) {

			if (Data[j + 2][i + 2] == 0) {
				// もし横一列の中に空白が一つでも含まれていたらループを抜ける
				break;
			}

			if (j == 9) {
				// 横一列の中に空白が一つもなかった場合

				// 上の列を下の列にコピーする
				for (int k = 0; k < 10; k++) {
					for (int l = 0; l < i + 1; l++) {
						if (Data[k + 2][2 + i - l - 1] == 8) {
							Data[k + 2][2 + i - l] = 0;
						}
						else {
							Data[k + 2][2 + i - l] = Data[k + 2][2 + i - l - 1];
						}
					}
				}

				Count++;
			}

		}
		
	}

	return Count;
}

void Field::Clear() {

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 14; j++) {
			Data[2 + i][2 + j] = 0;
		}
	}

}

int Tetrimino::X = 5, Tetrimino::Y = 1;
int Tetrimino::Mino[4][4] = {
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0},
	{0, 0, 0, 0}
};
const int Tetrimino::DefaultMino[7][4][4] = {
	{
		{0, 0, 0, 0},
		{0, 1, 1, 0},
		{0, 1, 1, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 2, 0, 0},
		{0, 2, 0, 0},
		{0, 2, 0, 0},
		{0, 2, 0, 0}
	},
	{
		{0, 0, 3, 0},
		{0, 3, 3, 0},
		{0, 0, 3, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0},
		{0, 0, 4, 0},
		{0, 0, 4, 0},
		{0, 4, 4, 0}
	},
	{
		{0, 5, 5, 0},
		{0, 0, 5, 0},
		{0, 0, 5, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 0, 6, 0},
		{0, 6, 6, 0},
		{0, 6, 0, 0},
		{0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0},
		{0, 7, 0, 0},
		{0, 7, 7, 0},
		{0, 0, 7, 0}
	},
};

void Tetrimino::ClearMino() {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Mino[i][j] = 0;
		}
	}

}

bool Tetrimino::CompyMino(int n) {

	if (n > 7 || n <= 0) {
		return false;
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Field::Data[i + 5][j + 1] != 0 && DefaultMino[n - 1][i][j] != 0) {
				return false;
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Mino[i][j] = DefaultMino[n - 1][i][j];
		}
	}

	return true;
}

void Tetrimino::ResetCoordinates() {
	X = 5;
	Y = 1;
}

bool Tetrimino::MoveLeft() {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Field::Data[X + i - 1][Y + j] != 0 && Mino[i][j] != 0) {
				return false;
			}
		}
	}

	X--;
	return true;
}

bool Tetrimino::MoveRight() {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Field::Data[X + i + 1][Y + j] != 0 && Mino[i][j] != 0) {
				return false;
			}
		}
	}

	X++;
	return true;
}

bool Tetrimino::MoveDown() {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Mino[i][j] != 0 && Field::Data[i + X][j + Y + 1] != 0) {
				return false;
			}
		}
	}

	Y++;
	return true;
}

bool Tetrimino::TurnLeft() {

	// 回転可能か判定する
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Mino[i][j] != 0 && Field::Data[j + X][3 - i + Y] != 0) {
				return false;
			}
		}
	}

	// ミノ構造の一時保存用の変数
	int temp[4][4] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};

	// 一時保存を行う
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			temp[i][j] = Mino[3 - j][i];
		}
	}

	// ミノをクリアする
	ClearMino();

	// 一時保存されていたミノ構造を再度代入する
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Mino[i][j] = temp[i][j];
		}
	}

	return true;
}

bool Tetrimino::TurnRight() {

	// 回転可能か判定する
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Mino[i][j] != 0 && Field::Data[3 - j + X][i + Y] != 0) {
				return false;
			}
		}
	}

	// ミノ構造の一時保存用の変数
	int temp[4][4] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0}
	};

	// 一時保存を行う
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			temp[i][j] = Mino[j][3 - i];
		}
	}

	// ミノをクリアする
	ClearMino();

	// 一時保存されていたミノ構造を再度代入する
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Mino[i][j] = temp[i][j];
		}
	}

	return true;
}

void Tetrimino::Transcribe() {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Field::Data[i + X][j + Y] == 0 && Field::Data[i + X][j + Y] != 8) {
				// 壁ブロックを含む他のブロックを上書きしない場合
				Field::Data[i + X][j + Y] = Mino[i][j];
			}
		}
	}

}

void Tetrimino::Draw() {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			Block::Draw((Tetrimino::X + i) * 40, (Tetrimino::Y + j) * 40, Tetrimino::Mino[i][j]);
		}
	}

}

Picture* Block::pic = nullptr;
unsigned int Block::Size = 40;
unsigned int Block::ImageSize = 0;

int Block::Load(const wchar_t* FileName, unsigned int n) {

	ImageSize = n;

	pic = new Picture;
	if (FAILED(pic->Load(FileName)))
		return 1;

	return 0;
}

void Block::Unload() {

	pic->Unload();
	delete pic;
	pic = nullptr;

}

void Block::Draw(int x, int y, int n) {

#ifndef _DEBUG
	if (!(n <= 7)) {
		return;
	}
#endif

	pic->Draw(CoordinatesI(x + Area::X_Main, y + Area::Y_Main), SizeU(Size, Size), CoordinatesI((n - 1) * ImageSize, 0), SizeU(ImageSize, ImageSize));

}

void Block::DrawSub(int x, int y, int n) {

#ifndef _DEBUG
	if (!(n <= 7)) {
		return;
	}
#endif

	pic->Draw(CoordinatesI(x + Area::X_Sub, y + Area::Y_Sub), SizeU(Size, Size), CoordinatesI((n - 1) * ImageSize, 0), SizeU(ImageSize, ImageSize));

}

int Area::X_Main = 70, Area::Y_Main = -60;
int Area::X_Sub = 595, Area::Y_Sub = 60;