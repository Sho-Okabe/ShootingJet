#include "DxLib.h";
#include "UI.h";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const int WIN_WIDTH = 1200, WIN_HEIGHT = 720;

	SetWindowText("Shooting Jet");
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);//描画に裏の画面（表示されていない画面）をする
	ChangeLightTypeDir(VGet(1.0f, -1.0f, 0.0f));

	const int FPS = 60;
	int mdl = MV1LoadModel("model/chest15_grid.mqoz");
	const VECTOR CAM_POS = VGet(0.0f, 200.0f, 0.0f);
	const VECTOR OBJ_TAR = VGet(0.0f, 0.0f, 400.0f);
	enum Scene { START, SELECT, STAGE1, STAGE2, STAGE3, OVER, CLEAR };
	Scene currentScene = START;

	while (true)
	{
		ClearDrawScreen();


		switch (currentScene)
		{
		case START:
			SetCameraPositionAndTarget_UpVecY(CAM_POS, OBJ_TAR); 
			if (mdl == -1)
			{
				drawTextC(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.2f, "no model", 0xffffff, 20);
			}
			else
			{
				MV1SetPosition(mdl, OBJ_TAR);
				MV1DrawModel(mdl);
			}
			drawTextC(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.7f, "PRESS SPACE", 0xffffff, 50);
			if (CheckHitKey(KEY_INPUT_SPACE) == 1) currentScene = STAGE1;
			break;
		case SELECT:
			drawTextC(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.7f, "SELECT STAGE", 0xffffff, 50);  
			break;
		case STAGE1:
			drawTextC(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.7f, "STAGE1", 0xffffff, 50);
			//if (CheckHitKey(KEY_INPUT_SPACE) == 1) currentScene = CLEAR;
			break;
		case STAGE2:
			break;
		case STAGE3:
			break;
		case OVER:
			break;
		case CLEAR:
			drawTextC(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.7f, "CLEAR", 0xffffff, 50);
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