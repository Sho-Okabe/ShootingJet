#include "DxLib.h"

//const int mdl = MV1LoadModel("model/chest15_grid.obj");
const int mdl = MV1LoadModel("model/fighter.mqoz");
const VECTOR CAM_POS = VGet(0.0f, 200.0f, 0.0f);
///const VECTOR CAM_TAR = VGet(0.0f, 199.5f, 1.0f);
const VECTOR OBJ_TAR = VGet(0.0f, 0.0f, 400.0f);

void setCam() //カメラ設置スクルト
{
	SetCameraPositionAndTarget_UpVecY(CAM_POS, OBJ_TAR);
}
void loadMap()
{
	MV1SetScale(mdl, VGet(1.0f, 1.0f, 1.0f));
	MV1SetPosition(mdl, OBJ_TAR);
	MV1DrawModel(mdl);
}