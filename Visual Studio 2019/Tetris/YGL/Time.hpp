#pragma once

#include "Core/Core.hpp"


class Time {

	/*

	　1秒間にゲームループが実行される回数はモニターのリフレッシュレートの値(通常は60、稀に120)と同じである。
	この1秒間に処理が行われる回数はフレームレート(FPS)と呼びばれており、これに基づいて時間を扱うべきである。
	そのため、このクラスはリアルタイムのFPSの値を計測し、時間の扱いを簡易化させる(加えてゲームループ内でのスリープ時間の調整も行う)。

	　このクラスを実装するにあたって http://dioltista.blogspot.com/2019/04/c-directx11-fps.html を参考にした。
	変数の命名が完璧でないため、またアルゴリズムが多少複雑であるため改変する際には上記URLを参照せよ。

	*/

private:
	static DWORD RefreshRate;	// モニターのリフレッシュレート
	static DOUBLE FPS;	// 1秒あたりの処理回数
	static LARGE_INTEGER Frequency;	// タイマー(パフォーマンスカウンタ)の周波数
	static LARGE_INTEGER StartTime;	// FPS計測開始時のタイムスタンプ
	static LARGE_INTEGER NowTime;	// FPS計測終了時のタイムスタンプ
	static INT Count;	// フレームのカウント(0~リフレッシュレート) ただし一度だけ行われる初期化処理の都合上、初期値を-1と定める

protected:
	// 初期化処理を行う
	static HRESULT InitTime();

	// 現在のFPSを計算する
	static VOID CalculateFPS();

	// ゲームループにてスリープを行う時間[ms]を得る
	static DWORD GetSleepTime();

public:
	// 理論上のFPS値を取得する
	static DWORD GetTheoreticalFPS();

	// 現在のFPS値を取得する
	static DOUBLE GetActualFPS();

};