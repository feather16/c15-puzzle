#include "def.hpp"
#include "Panel.hpp"
#include "KeyState.hpp"

vector<vector<Panel>> panel;

int Size = MIN_SIZE;
int t;
KeyState old;

void PerFrame() {
	t++;
	KeyState now = KeyState();

	int x, y;
	if (!old.w&&now.w) TrytoMove(U);
	if (!old.s&&now.s) TrytoMove(D);
	if (!old.a&&now.a) TrytoMove(L);
	if (!old.d&&now.d) TrytoMove(R);

	old = now;
}

void TrytoMove(const dir d) {
	int x, y;
	switch (d) {
	Case U :
		tie(x, y) = getLocation(EMPTY);
		if (y != 0) {
			swap(panel[x][y], panel[x][y - 1]);
		}
	Case D :
		tie(x, y) = getLocation(EMPTY);
		if (y != Size - 1) {
			swap(panel[x][y], panel[x][y + 1]);
		}
	Case L :
		tie(x, y) = getLocation(EMPTY);
		if (x != 0) {
			swap(panel[x][y], panel[x - 1][y]);
		}
	Case R :
		tie(x, y) = getLocation(EMPTY);
		if (x != Size - 1) {
			swap(panel[x][y], panel[x + 1][y]);
		}
	default:break;
	}
}

tuple<int, int> getLocation(const int number) {
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			if (panel[i][j].number == number) return { i,j };
		}
	}
	return{ -1,-1 };
}

void Draw() {
	SetDrawScreen(DX_SCREEN_BACK);
	ClearDrawScreen();

	//背景
	DrawBox(0, 0, SCREEN_X, SCREEN_Y, WHITE, TRUE);

	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			int width = (SCREEN_X - 2 * SPACE) / Size;
			int height = (SCREEN_Y - 2 * SPACE) / Size;
			int d = digits(panel[i][j].number);
			int x = SPACE + i * width + i - Size / 2;
			int y = SPACE + j * height + j - Size / 2;
			DrawBox(x, y, x + width, y + height, panel[i][j].color, true);
			DrawFormatString(
				x - 0.27 * width + 0.12 * d * width,
				y + 0.25 * height,
				BLACK, "%3d", panel[i][j].number);
		}
	}

	ScreenFlip();
}

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE); //ウィンドウモードで起動

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	WindowSettings();

	while (ProcessMessage() == 0) {
		//背景
		DrawBox(0, 0, SCREEN_X, SCREEN_Y, WHITE, TRUE);
		SetFontSize(26);

		old = KeyState();

		//タイトル
		while (ProcessMessage() == 0) {
			KeyState now = KeyState();

			if (!old.s && now.s) Size = min(Size + 1, MAX_SIZE);
			if (!old.w && now.w) Size = max(Size - 1, MIN_SIZE);
			if (!old.enter && now.enter) break;

			SetDrawScreen(DX_SCREEN_BACK);
			ClearDrawScreen();

			//背景
			DrawBox(0, 0, SCREEN_X, SCREEN_Y, WHITE, TRUE);

			DrawString(150, 30, "Press Enter to start", BLACK);
			for (int i = MIN_SIZE; i <= MAX_SIZE; i++) {
				DrawFormatString(250, i * 60 - 70, BLACK, "Size %2d", i);
			}
			DrawString(190, Size * 60 - 70, "→", BLACK);
			ScreenFlip();

			old = now;
		}
		ClearDrawScreen();

		SetFontSize(0.5 * (SCREEN_X - 2 * SPACE) / Size);
		t = 0;
		old = KeyState(false);

		//パネルの生成
		for (int i = 0; i < Size; i++) {
			vector<Panel> row;
			for (int j = 0; j < Size; j++) {
				Panel p = Panel(i + j * Size + 1, col_to_color(j));
				if (i == Size - 1 && j == Size - 1) {
					p = Panel(EMPTY, BLACK);
				}
				row.push_back(p);
			}
			panel.push_back(row);
		}

		//パネルのシャッフル
		for (int i = 0; i < TIMES; i++) {
			TrytoMove(genrand_int32() % 4 + 1);
		}

		while (ProcessMessage() == 0) {
			PerFrame();
			Draw();
			bool cleared = true;
			for (int i = 0; i < Size; i++) {
				for (int j = 0; j < Size; j++) {
					if (i == Size - 1 && j == Size - 1) {
						if (panel[i][j].number != EMPTY) {
							cleared = false;
						}
					}
					else {
						if (panel[i][j].number != i + j * Size + 1) {
							cleared = false;
						}
					}
				}
			}
			if (cleared) {
				for (int i = 0; i < Size; i++) panel.pop_back();
				WaitEnter();
				break;
			}
		}
	}

	//WaitKey();				// キー入力待ち

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}