#pragma once

class Chara
{
	public:
		VECTOR charaPos;
		VECTOR thisGridsPos[4];
		void CreateChara();
		void IsMouseOverGrid();
};