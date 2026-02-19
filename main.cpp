#include "DxLib.h"
#include "UI.h"
#include "Stage.h"
#include "Chara.h"

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
	SetupCamera_Ortho(400.0f);
	int mdl = MV1LoadModel("model/chest15_grid.mqoz");
	int playerModel = MV1LoadModel("model/Capsule.mqoz");

	const VECTOR CAM_POS = VGet(600.0f, 565.0f, 0.0f);
	const VECTOR OBJ_MAP = VGet(0.0f, 0.0f, 600.0f);
	VECTOR ObjTar = VGet(0.0f, 10.0f, 600.0f);
	enum PlayStage { START, PLAY, CLEAR, OVER };
	PlayStage currentStage = START;
	float size = 30.0f;

	Chara player;
	player.charaPos = ObjTar;

	while (true)
	{
		ClearDrawScreen();


		switch (currentStage)
		{
		case START:
			SetCameraPositionAndTarget_UpVecY(CAM_POS, OBJ_MAP); 
			if (mdl == -1)
			{
				drawTextC(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.2f, "no model", 0xffffff, 20);
			}
			else
			{
				MV1SetPosition(mdl, OBJ_MAP);
				MV1DrawModel(mdl);
				player.CreateChara();
				MV1SetPosition(playerModel, ObjTar);
				MV1SetScale(playerModel, VGet(0.2f, 0.2f, 0.2f));
				MV1DrawModel(playerModel);
			}

			drawTextC(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.7f, "PRESS SPACE", 0xffffff, 50);
			//if (CheckHitKey(KEY_INPUT_SPACE) == 1) currentScene = STAGE1;
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