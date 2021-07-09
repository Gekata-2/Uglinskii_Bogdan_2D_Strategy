#pragma once
#include <iostream>
//#include "TSwordsman.h"
#include "TUnit.h"
#include "math.h"
class TBattleground
{
	int bg_size = 8;
	TUnit*** tiles = new TUnit** [bg_size];
	
	//TUnit* tiles[8][8] = {0};
	
public:
	TBattleground()
	{
		for (size_t i = 0; i < bg_size; i++)
		{
			tiles[i] = new TUnit* [bg_size];
		}

		for (size_t i = 0; i < bg_size; i++)
		{
			for (size_t j = 0; j < bg_size; j++)
			{

				tiles[i][j] = NULL;
			}
			
		}

	}
	

	void AddUnit(TUnit* unit, int pos_x, int pos_y);

	void Print() const;

	void Move(TUnit* unit,int x,int y);

	void Attack(TUnit* attack_unit, TUnit* attacked_unit);
	void Death(TUnit* unit);
	
	~TBattleground()
	{
		std::cout << "~Destrucor is called\n";
		for (size_t i = 0; i < bg_size; i++)
		{
			delete[] tiles[i];
		}
		delete tiles;
	}
	
};

