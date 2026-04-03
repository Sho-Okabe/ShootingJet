#pragma once

class Chara
{
	public:
		int model;
		VECTOR charaPos;
		VECTOR thisGridsPos[4];
		virtual void CreateChara();
};

class Player;
class Enemy;
class Player : public Chara
{
	public:
		void CreateChara();
		void IsMouseOverGrid(Enemy* enemy); 
};

class Enemy : public Chara 
{
	public:
		bool isDestroy;
		void DestroyCheck(Player* player);
		void CreateChara();
};