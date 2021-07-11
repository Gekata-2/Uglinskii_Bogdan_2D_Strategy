#pragma once

#include "TUnit.h"

class TSwordsman : public TUnit
{
private:

public:
	TSwordsman(int position_x=-1,int position_y=-1,std::string def_name = "\0")
	{
		current_HP = 100;
		max_HP = 100;
		mana = 50;
		base_attack_damage = 25;
		max_attack_radius = 1;

		if (def_name =="\0")
		{
			name = "Swordsman ";
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

		type = "swordsman";

		PrintInfo();

	}
	void PrintInfo() const override;

	std::string  GetInfo() const;
	

	

};

