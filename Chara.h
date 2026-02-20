#pragma once

class Chara
{
	public:
		int model;
		VECTOR charaPos;
		VECTOR thisGridsPos[4];
		virtual void CreateChara();
};

class Player : public Chara
{
	public:
		void CreateChara();
		void IsMouseOverGrid(); 
};

class Enemy : public Chara {};