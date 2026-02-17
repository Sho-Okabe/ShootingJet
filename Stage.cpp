#include "DxLib.h"

const VECTOR CAM_POS = VGet(0.0f, 200.0f, 0.0f);
const VECTOR CAM_TAR = VGet(0.0f, 190.0f, 10.0f);

void setCam() //カメラ設置スクルト
{
	SetCameraPositionAndTarget_UpVecY(CAM_POS, CAM_TAR);
}