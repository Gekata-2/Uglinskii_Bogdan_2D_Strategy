#pragma once
#include "TUnit.h"
class TArcher : public TUnit
{
public:
	TArcher(int position_x=-1, int position_y=-1, std::string def_name = "\0")
	{
		current_HP = 75;
		max_HP = 75;
		mana = 60;
		base_attack_damage = 15;
		max_attack_radius = 3;
		max_move_tiles = 7;
	
		if (def_name == "\0")//генерац€ имени
		{
			name = "Archer ";
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
		type = "archer";

		pos_x = position_x;
		pos_y = position_y;

		PrintInfo();
	}

	void PrintInfo() const override;
	

};

