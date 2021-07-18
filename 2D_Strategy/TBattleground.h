#pragma once
#include <iostream>
//#include "TSwordsman.h"
#include "TUnit.h"
#include "math.h"
#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 10;//размер карты высота
const int WIDTH_MAP = 10;//размер карты ширина 

#define ALL_OK 0
#define TOO_FAR 1
#define ALREADY_TAKEN 2
#define INCORRECT_DISTINATION 3
#define NO_CHARACTERS_SELECTED 4
#define NOT_A_UNIT 5
#define NOT_ON_BATTLEGROUND 6
#define TOO_FAR_TO_ATTACK 7
#define FRIENDLY_UNIT 8

class TBattleground
{
	size_t bg_size = 8;
	TUnit*** tiles = new TUnit** [bg_size];
	bool focus_stoped = false;

public:	 std::string TileBackgroundMap[HEIGHT_MAP] =
    {
		"0000000000",
		"0     sss0",
		"0    s   0",
		"0     s  0",
		"0 s      0",
		"0        0",
		"0       s0",
		"0        0",
		"0     sss0",
		"0000000000",
	};
	  sf::Vector2i focus_tile;
	  TUnit* p_focus_tile = NULL;
	 std::string TileUnitsMap[HEIGHT_MAP-2] = 
	  {
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
		focus_tile.x = 0;
		focus_tile.y = 0;
		p_focus_tile = tiles[0][0];
		
	}
	
	void StopFocus()
	{
		focus_stoped = true;
	}

	void ReleaseFocus()
	{
		focus_stoped = false;
	}

	void AddUnit(TUnit* unit, int pos_x, int pos_y);

	void PrintUnits() const;

	void FillUnitsMap();

	sf::String GetInfoAboutTile(int x=0,int y=0) const;

	int Move(TUnit* unit,int x,int y);

	sf::Vector2i MoveFocusTile(sf::Event event);
	
	sf::Vector2i GetFocusTile()
	{
		return focus_tile;
	}
	TUnit* GetFocusUnit();

	int Attack(TUnit* attack_unit, TUnit* attacked_unit);
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

