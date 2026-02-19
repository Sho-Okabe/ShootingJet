#include "DxLib.h"

void DrawGrid(VECTOR v1, VECTOR v2, VECTOR v3, VECTOR v4, unsigned int Color, int FillFlag)//ŽlŠpŒ`‚ð•`‰æ‚·‚é
{
	DrawTriangle3D(v1, v2, v3, Color, FillFlag);
	DrawTriangle3D(v3, v4, v1, Color, FillFlag);
}

