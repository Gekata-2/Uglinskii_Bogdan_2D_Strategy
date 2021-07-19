#pragma once

#include "TUnit.h"

class TSwordsman : public TUnit
{
public:
	TSwordsman(std::string def_name = "\0",int position_x=-1,int position_y=-1)
	{
		current_HP = 100;
		max_HP = 100;
		mana = 50;
		base_attack_damage = 25;
		max_attack_radius = 1;
		max_move_tiles = 2;

		if (def_name =="\0")
		{
			for (size_t i = 0; i < 3; i++)
			{
				char c = 65 + rand() % 26;
				name = name + c;
			}
		}
		else
		{
			name = def_name;
		}

		pos_x = position_x;
		pos_y = position_y;

		type = "Swordsman";

		PrintInfo();

	}
	void PrintInfo() const override;

	std::string  GetInfo() const;
	

	

};

