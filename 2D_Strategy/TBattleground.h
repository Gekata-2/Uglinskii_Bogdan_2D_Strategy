#pragma once
#include <iostream>
//#include "TSwordsman.h"
#include "TUnit.h"
#include "math.h"
#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 8;//размер карты высота
const int WIDTH_MAP = 8;//размер карты ширина 




class TBattleground
{
	int bg_size = 8;
	TUnit*** tiles = new TUnit** [bg_size];

public:	sf::String TileBackgroundMap[HEIGHT_MAP] = {
	"00000000",
	"0   sss0",
	"0   s  0",
	"0    s 0",
	"0 s    0",
	"0      0",
	"0     s0",
	"00000000",
	};

	  sf::String TileUnitsMap[HEIGHT_MAP] = {
	"        ",
	"        ",
	"        ",
	"        ",
	"        ",
	"        ",
	"        ",
	"        ",
	  };
	
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

	void PrintUnits() const;

	void FillUnitsMap();

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

