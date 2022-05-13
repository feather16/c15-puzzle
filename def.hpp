#pragma once

using namespace std;

#include "DxLib.h"
#include "MT.h"
#include <time.h>
#include <vector>
#include <string>
#include <tuple>

//ウィンドウ
#define WINDOW_MESSAGE "15Puzzle"
#define SPACE 100
#define SCREEN_X 600
#define SCREEN_Y 600
#define SCREEN_BIT 32

#define EMPTY 0

#define TIMES 20000

//色
#define WHITE   GetColor(255, 255, 255)
#define BLACK   GetColor(  0,   0,   0)
#define RED     GetColor(255,   0,   0)
#define GREEN   GetColor(  0, 255,   0)
#define BLUE    GetColor(  0,   0, 255)
#define YELLOW  GetColor(255, 255,   0)
#define MAGENTA GetColor(255,   0, 255)
#define CYAN    GetColor(  0, 255, 255)

//サイズ
#define MIN_SIZE 3
#define MAX_SIZE 10

#define Case break;case

// 方向
#define NONE 0
#define U 1
#define L 2
#define D 3
#define R 4
#define RANDOM 5
#define DIR_NUM 5

// enumが使えないっぽいので代わりにこれを使う
typedef int8_t dir;

void PerFrame();
void TrytoMove(const dir);
tuple<int, int> getLocation(const int);
void Draw();

void WindowSettings() {
	SetMainWindowText(WINDOW_MESSAGE);
	SetGraphMode(SCREEN_X, SCREEN_Y, SCREEN_BIT); //画面の解像度指定
	SetWindowSizeChangeEnableFlag(FALSE); //画面サイズ変更不可
}

void WaitEnter() {
	int key;
	while (key = WaitKey()) {
		if (key == KEY_INPUT_RETURN) {
			break;
		}
	}
}

int digits(const int n) {
	return to_string(n).size();
}

int col_to_color(const int col) {
	switch (col % 6) {
		case 0: return RED;
		case 1: return GREEN;
		case 2: return BLUE;
		case 3: return YELLOW;
		case 4: return MAGENTA;
		case 5: return CYAN;
		default: return WHITE;
	}
}

/*
void Draw(const int x, const int y, const int handle) {
	DrawGraph(x, y, handle, TRUE);
}
*/

/*
void DrawTurn(const int x, const int y, const int handle) {
	DrawTurnGraph(x, y, handle, TRUE);
}
*/

/*
void Play(const int handle) {
	PlaySoundMem(handle, DX_PLAYTYPE_BACK);
}
*/

/*
void NowLoading() {
	SetFontSize(96);
	DrawString(520, 760, "Now Loading...", WHITE);
}
*/

/*
vector<string> AllFile(const string directory) {
	vector<string> ret;
	HANDLE hFind;
	WIN32_FIND_DATA win32fd;

	string search = directory + "\\*";

	hFind = FindFirstFile(search.c_str(), &win32fd);

	do {
		if (win32fd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) {
		}
		else {
			ret.push_back(win32fd.cFileName);
		}
	} while (FindNextFile(hFind, &win32fd));

	FindClose(hFind);

	return ret;
}
*/