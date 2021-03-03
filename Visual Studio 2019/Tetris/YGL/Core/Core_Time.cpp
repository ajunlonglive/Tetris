#include "Core_Time.hpp"


LARGE_INTEGER Core_Time::Frequency = { 0 };	// タイマー(パフォーマンスカウンタ)の周波数
LARGE_INTEGER Core_Time::StartTime = { 0 };	// FPS計測開始時のタイムスタンプ
LARGE_INTEGER Core_Time::NowTime = { 0 };	// FPS計測終了時のタイムスタンプ
INT Core_Time::Count = -1;	// フレームのカウント(0~リフレッシュレート) ただし一度だけ行われる初期化処理の都合上、初期値を-1と定める

// 初期化処理を行う
HRESULT Core_Time::Init() {

	DEVMODE mode = { 0 };
	// ディスプレイの情報を得る
	EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &mode);
	RefreshRate = mode.dmDisplayFrequency;	// 得られたリフレッシュレートの値を代入する

	// パフォーマンスカウンタの周波数を得る
	QueryPerformanceFrequency(&Frequency);

	return S_OK;

}

// 現在のFPSを計算する
VOID Core_Time::CalculateFPS() {

	// ゲームループ内でこの関数が呼び出される場合、約1秒おきに現在のFPSを計算することになる

	// **注意**
	// モニターのリフレッシュレートが60である(RefreshRate == 60)と仮定して話を進める

	if (Count == -1) {	// カウントが-1なら

		// 1フレーム目の時間を取得する
		QueryPerformanceCounter(&StartTime);
		Count = 0;
	}
	else if ((unsigned)Count == RefreshRate) {	// カウントが60なら

		QueryPerformanceCounter(&NowTime);	// 60フレーム目の時間を取得する
		// FPS = 1秒 / 1フレームの描画にかかる時間 であるから、
		//     = 1000ms / ((60フレーム目の時間[ms] - 1フレーム目の時間[ms]) / 60[frame]) が成り立つ
		FPS = 1000.0 / (((NowTime.QuadPart - StartTime.QuadPart) * 1000 / Frequency.QuadPart) / (DOUBLE)RefreshRate);	// 変数FPSに代入する
		Count = 0;	// カウントを初期値に戻す
		StartTime = NowTime;
	}

	Count++;	// カウント+1

}

// ゲームループにてスリープを行う時間[ms]を取得する
DWORD Core_Time::GetSleepTime() {

	// **注意**
	// モニターのリフレッシュレートが60である(RefreshRate == 60)と仮定して話を進める

	QueryPerformanceCounter(&NowTime);	// 現在の時間を取得する
	// Sleepさせる時間[ms] = 1フレーム目から現在のフレームまでの描画に本来かかるべき時間[ms] - 1フレーム目から現在のフレームまで実際にかかった時間[ms]
	//                     = (1000ms / 60)*フレーム数 - (現在の時間[ms] - 1フレーム目の時間[ms])
	DWORD SleepTime = static_cast<DWORD>((1000 / RefreshRate) * Count - ((NowTime.QuadPart - StartTime.QuadPart) * 1000 / Frequency.QuadPart));

	// CalculateFPS()関数が初めて実行された直後にSleepTimeの値がとても大きくなってしまうため、それを検知しSleepTimeを返さないようにする
	if ((1000 / RefreshRate) < SleepTime) {	// もしSleepTimeが1フレームあたりの時間[ms]よりも大きかったら
		return 1;
	}
	else {
		return SleepTime;
	}

}

DWORD Core_Time::RefreshRate = 0;	// モニターのリフレッシュレート
DOUBLE Core_Time::FPS = 0;	// 1秒あたりの処理回数