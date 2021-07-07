#pragma once
#include <iostream>
#include "TSwordsman.h"
#include "math.h"
class TBattleground
{
	int size = 8;
	TUnit*** tiles = new TUnit** [size];
	
	//TUnit* tiles[8][8] = {0};
	int units_distance_x, units_distance_y;
public:
	TBattleground()
	{
		for (size_t i = 0; i < size; i++)
		{
			tiles[i] = new TUnit* [size];
		}
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++)
			{

				tiles[i][j] = NULL;
			}
			
		}

	}
	void Attack(TUnit* attack_unit, TUnit* attacked_unit);

	void AddUnit(TUnit* unit, int pos_x, int pos_y);

	void Print() const;
	
	
};

