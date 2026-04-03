#include <iostream>
#include <vector>
#include "DxLib.h"
#include "UI.h"

void DrawGrid(VECTOR pos, unsigned int Color, int FillFlag)//ŽlŠpŒ`‚ð•`‰æ‚·‚é
{
	float gridSize = 30.0f;
	VECTOR v1 = VAdd(VGet(1.0f * gridSize, 0.0f, 1.0f * gridSize), pos);
	VECTOR v2 = VAdd(VGet(1.0f * gridSize, 0.0f, -1.0f * gridSize), pos);
	VECTOR v3 = VAdd(VGet(-1.0f * gridSize, 0.0f, -1.0f * gridSize), pos);
	VECTOR v4 = VAdd(VGet(-1.0f * gridSize, 0.0f, 1.0f * gridSize), pos);
	DrawTriangle3D(v1, v2, v3, Color, FillFlag);
	DrawTriangle3D(v3, v4, v1, Color, FillFlag);
}
bool InHitDistance(VECTOR v1, VECTOR v2)
{
	float dx = v1.x - v2.x;
	float dz = v1.z - v2.z;
	float distanceSquared = (dx * dx) + (dz * dz);

	if (distanceSquared < 84.85f) return true;
	else return false;
}

class Chara
{
	public :
		int model;
		VECTOR charaPos;
		VECTOR thisGridsPos[4];
		
		int hp = 2;

		virtual void CreateChara()
		{
			MV1SetPosition(model, charaPos);
			MV1SetScale(model, VGet(0.2f, 0.2f, 0.2f));
			MV1DrawModel(model);
		}
};

class Player;
class Enemy;

#pragma region PlayerClass
class Player : public Chara
{
public:
	void CreateChara() override;
	void IsMouseOverGrid(Enemy* enemy);
};
void Player::CreateChara()
{
	float gridRange = 60.0f;

	int x, z;
	int x_coords[] = { 1, 0, -1,  0 };
	int z_coords[] = { 0, 1,  0, -1 };

	for (int i = 0; i < 4; ++i)
	{
		x = x_coords[i % 4];
		z = z_coords[i % 4];
		VECTOR gridPos = VAdd(VGet(x * gridRange, 0.0f, z * gridRange), charaPos);
		thisGridsPos[i] = gridPos;
		DrawGrid(gridPos, GetColor(200, 200, 200), true);
	}

	VECTOR renderPos = VGet(charaPos.x, charaPos.y + 70.0f, charaPos.z);
	MV1SetPosition(model, renderPos);
	MV1SetScale(model, VGet(0.05f, 0.05f, 0.05f));
	MV1DrawModel(model);
	//Chara::CreateChara();
}

void Player::IsMouseOverGrid(Enemy* enemy)
{
	float gridSize = 30.0f;

	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	VECTOR lineStart = ConvScreenPosToWorldPos(VGet((float)mouseX, (float)mouseY, 0.0f));
	VECTOR lineEnd = ConvScreenPosToWorldPos(VGet((float)mouseX, (float)mouseY, 1.0f));

	for (int i = 0; i < 4; i++)
	{
		VECTOR v1 = VAdd(VGet(1.0f * gridSize, 0.0f, 1.0f * gridSize), thisGridsPos[i]);
		VECTOR v2 = VAdd(VGet(1.0f * gridSize, 0.0f, -1.0f * gridSize), thisGridsPos[i]);
		VECTOR v3 = VAdd(VGet(-1.0f * gridSize, 0.0f, -1.0f * gridSize), thisGridsPos[i]);
		VECTOR v4 = VAdd(VGet(-1.0f * gridSize, 0.0f, 1.0f * gridSize), thisGridsPos[i]);

		HITRESULT_LINE Result_1, Result_2;
		Result_1 = HitCheck_Line_Triangle(lineStart, lineEnd, v1, v2, v3);
		Result_2 = HitCheck_Line_Triangle(lineStart, lineEnd, v3, v4, v1);
		if (Result_1.HitFlag == 1 || Result_2.HitFlag == 1)
		{
			DrawTriangle3D(v1, v2, v3, GetColor(200, 0, 0), true);
			DrawTriangle3D(v3, v4, v1, GetColor(200, 0, 0), true);

			if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
			{				
				charaPos = thisGridsPos[i];
			}
		}
	}
}

#pragma endregion

#pragma region EnemyClass

class Enemy : public Chara
{
public:
	bool isDestroy = false;
	void DestroyCheck(Player* player);
	void CreateChara();
};
void Enemy::DestroyCheck(Player* player)
{

	if (InHitDistance(player->charaPos, this->charaPos))
	{
		isDestroy = true;
	}
}
void Enemy::CreateChara()
{
	if (!isDestroy)
	{
		Chara::CreateChara();
	}
}

#pragma endregion