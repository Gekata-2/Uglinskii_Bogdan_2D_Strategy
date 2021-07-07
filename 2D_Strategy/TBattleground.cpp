#include "TBattleground.h"



void TBattleground::Attack(TUnit* attack_unit, TUnit* attacked_unit)
{
	int tmp_x, tmp_y;
	tmp_x = attack_unit->GetX() - attacked_unit->GetX();
	tmp_y = attack_unit->GetY() - attacked_unit->GetY();
	units_distance_x = abs(tmp_x);
	units_distance_y = abs(tmp_y);
	if ((units_distance_x > attack_unit->GetMaxAttackRadius())
		|| (units_distance_y > attack_unit->GetMaxAttackRadius()))
	{
		std::cout << "Distance between units is more than maximum range of attack unit";
		return;
	}
	else
	{
		std::cout << "Attack" << std::endl;
		attacked_unit->SetCurrentHP(attacked_unit->GetCurrentHP() - attack_unit->GetBaseDamage());
	}

}
void TBattleground::AddUnit(TUnit* unit, int pos_x, int pos_y)
{
	std::cout << "AddUnit is called\n";
	tiles[pos_x][pos_y] = unit;
	unit->SetPos(pos_x, pos_y);
	tiles[pos_x][pos_y]->PrintInfo();
}


void TBattleground::Print() const
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (tiles[i][j]==NULL)
			{
				std::cout << " 0 ";
			}
			else
			{
				std::cout << " 1 ";
			}
		
		}
		std::cout << "\n";
	}
}