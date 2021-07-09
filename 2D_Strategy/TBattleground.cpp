#include "TBattleground.h"



void TBattleground::Attack(TUnit* attack_unit, TUnit* attacked_unit)
{
	int tmp_x, tmp_y;
	int units_distance_x, units_distance_y;

	if (!attack_unit->IsOnBattleground())
	{
		std::cout << "Attack is failed/Unit <"<< attack_unit->GetName() <<"> is not on the battleground"<< std::endl;
		return;
	}
	if(!attacked_unit->IsOnBattleground())
	{
		std::cout << "Attack is failed/Unit <" << attacked_unit->GetName() << "> is not on the battleground" << std::endl;
		return;
	}

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

	if ( (pos_x>=bg_size) || (pos_y >= bg_size) || (pos_x < 0) || (pos_y < 0) )
	{
		std::cout << "Unit is placed out of battleground!\n";
		return;
	}
	
	tiles[pos_x][pos_y] = unit;
	unit->SetPos(pos_x, pos_y);
	unit->SetOnBattleground();
	tiles[pos_x][pos_y]->PrintInfo();
}

void TBattleground::Move(TUnit* unit,int x,int y)
{
	int tmp_x=0, tmp_y=0;

	tmp_x = abs(x - unit->GetX());
	tmp_y = abs(y - unit->GetY());

	if ((tmp_x+tmp_y)>(unit->GetMaxMoveTiles()))
	{
		std::cout << "Unit cant go this far\n";
		return;
	}
	else if(tiles[x][y]!=NULL)
	{
		std::cout << "This tile ["<<x<<"]["<<y<<"] already taken\n";
	}
	else if((x >= bg_size) || (y >= bg_size) || (x < 0) || (y < 0))
	{
		std::cout << "Incorrect distinaition to move\n";
		return;
	}
	else
	{	
		tiles[unit->GetX()][unit->GetY()] = NULL;
		tiles[x][y] = unit;
		std::cout << "Unit <" << unit->GetName() << "> is moved : [" << unit->GetX() << "][" << unit->GetY();
		unit->SetPos(x, y);
		std::cout <<"] --> ["<<x<<"]["<<y<<"]\n";
	}
}

void TBattleground::Print() const
{
	for (size_t i = 0; i < bg_size; i++)
	{
		for (size_t j = 0; j < bg_size; j++)
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