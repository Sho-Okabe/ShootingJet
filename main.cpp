#include "DxLib.h";
#include "UI.h";

const int WIN_WIDTH = 1200, WIN_HEIGHT = 720;
const int FPS = 60;

enum Scene { START, SELECT, STAGE1, OVER, CLEAR };
Scene currentScene = START;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetWindowText("Shooting Jet");
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);//描画に裏の画面（表示されていない画面）をする

	while (true)
	{
		ClearDrawScreen();


		switch (currentScene)
		{
		case START:
			drawTextC(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.7f, "Press A", 0xffffff, 50);
			break;
		case SELECT:
			break;
		case STAGE1:
			break;
		case OVER:
			break;
		case CLEAR:
			break;
		default:
			break;
		}

		ScreenFlip(); //裏画面の内容が表画面に反映させる
		WaitTimer(1000 / FPS);// 一定時間待つ
		if (ProcessMessage() == -1) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	DxLib_End();
	return 0;
}