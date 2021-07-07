#pragma once

#include "TUnit.h"

class TSwordsman : public TUnit
{
private:

public:
	TSwordsman(int position_x,int position_y,std::string def_name = "\0")
	{
		if (def_name =="\0")
		{
			for (size_t i = 0; i < 5; i++)
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
		PrintInfo();
	}
	void Attack(TUnit* unit) override
	{

	}


	

};

