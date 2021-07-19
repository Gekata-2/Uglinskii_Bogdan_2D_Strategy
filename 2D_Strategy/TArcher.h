#pragma once
#include "TUnit.h"
class TArcher : public TUnit
{
public:
	TArcher(std::string def_name = "\0",int position_x=-1, int position_y=-1)
	{
		current_HP = 75;
		max_HP = 75;
		mana = 60;
		base_attack_damage = 15;
		max_attack_radius = 3;
		max_move_tiles = 7;
	
		if (def_name == "\0")//генерац€ имени
		{
			for (size_t i = 0; i < 10; i++)
			{
				char c = 97 + rand() % 26;
				name = name + c;
			}
		}
		else
		{
			name = def_name;
		}


		pos_x = position_x;
		pos_y = position_y;

		type = "Archer";

		PrintInfo();
	}

	void PrintInfo() const override;
	
	std::string  GetInfo() const;
};

