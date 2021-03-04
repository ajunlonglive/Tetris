#pragma once

#include "Core.hpp"


// **************************************************
// Core_Timeクラス
// **************************************************
/*
	【概要】
	　このクラスはゲームループ内の適切なスリープ時間の算出と、リアルタイムのFPS値の計測を行う。
	 YGL利用者はこのクラスを継承したTimeクラスを用いてFPS値の利用すべし。

	 【メモ】
	 　このクラスを実装するにあたって http://dioltista.blogspot.com/2019/04/c-directx11-fps.html を参考にした。
*/

class Core_Time : private Core {

private:
	static LARGE_INTEGER Frequency;	// タイマー(パフォーマンスカウンタ)の周波数
	static LARGE_INTEGER StartTime;	// FPS計測開始時のタイムスタンプ
	static LARGE_INTEGER NowTime;	// FPS計測終了時のタイムスタンプ
	static INT Count;	// フレームのカウント(0~リフレッシュレート) ただし一度だけ行われる初期化処理の都合上、初期値を-1と定める

	// 初期化処理を行う
	static HRESULT Init();

	// 終了処理を行う
	static VOID Quit();

	// 現在のFPSを計算する
	static VOID CalculateFPS();

	// ゲームループにてスリープを行う時間[ms]を得る
	static DWORD GetSleepTime();

protected:
	static DWORD RefreshRate;	// モニターのリフレッシュレート
	static DOUBLE FPS;	// 1秒あたりの処理回数


	friend class Game;	// Gameクラスをフレンドクラスに指定する

};