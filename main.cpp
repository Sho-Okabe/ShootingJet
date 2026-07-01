#include "DxLib.h"
#include "UI.h"
#include "Stage.h"
#include "Chara.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const int WIN_WIDTH = 1200, WIN_HEIGHT = 720;

	SetWindowText("Robo Fight");
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);//描画に裏の画面（表示されていない画面）をする
	ChangeLightTypeDir(VGet(1.0f, -1.0f, 0.0f));

	const int FPS = 60;
	SetupCamera_Ortho(400.0f);
	//モデルインポート
	int mdl = MV1LoadModel("model/chest15_grid.mqoz");
	int playerModel = MV1LoadModel("model/robot_stand.mqoz");
	int enemyModel = MV1LoadModel("model/Sphere.mqoz");
	int bgm = LoadSoundMem("audio/bgm.mp3");
	bool playBGM = false;

	//カメラ設定
	const VECTOR CAM_POS = VGet(600.0f, 565.0f, 0.0f);
	//マップ設定
	const VECTOR OBJ_MAP = VGet(8.0f, 0.0f, 650.0f);
	//ゲームステージ
	enum PlayStage { START, PLAY, CLEAR, OVER };
	PlayStage currentStage = START;

	//プレイヤー表示
	Player *player = new Player();
	player->model = playerModel;
	player->charaStartPos = VGet(-180.0f, 0.0f, 600.0f);
	player->charaPos = player->charaStartPos;

	//敵表示
	Enemy *enemy = new Enemy();
	enemy->model = enemyModel;
	enemy->charaStartPos = VGet(0.0f, 30.0f, 720.0f);
	enemy->charaPos = enemy->charaStartPos;

	while (true)
	{
		ClearDrawScreen();

		//カメラ表示
		SetCameraPositionAndTarget_UpVecY(CAM_POS, OBJ_MAP);
		//マップ表示
		MV1SetPosition(mdl, OBJ_MAP);  
		MV1SetScale(mdl, VGet(1.0f, 1.0f, 1.0f));
		MV1DrawModel(mdl);
		//BGM流し
		if (!playBGM)
		{
			PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
			playBGM = true;
		}

		player->CreateChara();
		enemy->CreateChara();

		switch (currentStage)
		{
			case START:
				//ゲームタイトル画面
				drawTextC(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.4f, "ROBO FIGHT", 0x5500fe, 80);
				drawTextC(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.7f, "PRESS SPACE", 0xffffff, 50);
				enemy->isDestroy = false;
				if (CheckHitKey(KEY_INPUT_SPACE) == 1)
				{
					currentStage = PLAY;
				}
				break;
			case PLAY:
				player->IsMouseOverGrid(enemy); //プレイヤーと敵の当たり判定
				enemy->DestroyCheck(player); //敵は破壊されたか
				if (enemy->isDestroy) currentStage = CLEAR; //破壊されたかされたらゲームクリア
				break;
			case CLEAR:
				//ゲームクリア画面
				drawTextC(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.4f, "GAME CLEAR", 0xffffff, 50);
				drawTextC(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.7f, "PRESS SPACE TO REPLAY", 0xffffff, 50);
				if (CheckHitKey(KEY_INPUT_SPACE) == 1)
				{
					player->charaPos = player->charaStartPos;
					enemy->charaPos = enemy->charaStartPos;
					enemy->isDestroy = false;
					currentStage = PLAY;
				}
				break;
			case OVER:
				//ゲームオーバー画面
				drawTextC(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.7f, "GAME OVER", 0xffffff, 50);
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