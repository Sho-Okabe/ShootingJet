#pragma once

class Chara
{
	public:
		int model;
		VECTOR charaPos;
		VECTOR thisGridsPos[4];
		void CreateChara();
		void IsMouseOverGrid();
};