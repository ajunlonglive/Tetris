# Tetris

【概要】
C++でテトリスを作成しました。
Windowsで動作させるためにWin32API、高速な2D描画が可能なDirect2DとDirectWrite、遅延が少ないDirectSoundを用いて、汎用ゲームライブラリYGL(Yamato Game Library)を構築しそれを用いてアプリケーションを作成しています。
YGLについて保守性を意識しクラスごとに機能を適切に分散させています。またオーバーヘッドも可能な限り少なくしています。

コンパイル済みのアプリケーション本体は "/Release" ディレクトリ内に、ソースコードは "/Visual Studio 2019" ディレクトリ内にあります。
アプリケーション本体に関してはZip形式で圧縮を行ったものもリリースしてあります。

【環境】
開発ソフト:Microsoft Visual Studio 2019
言語:C++
使用したライブラリ:Win32API、Direct2D1、DirectWrite、DirectSound
動作環境:Windows10
