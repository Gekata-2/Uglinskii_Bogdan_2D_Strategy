#include "Player.h"


int TPlayer::GetID()
{
	return id;
}

std::string TPlayer::GetName()
{
	return name;
}

int TPlayer::GetNumberOfUnits()
{
	return number_of_units;
}

void TPlayer::AddUnit(TUnit* unit)//��������� ����� � �����
{
	units.push_back(unit);
	number_of_units++;
}


void TPlayer::DeleteUnit(TUnit* unit)//���� ����� � �������
{
	std::list<TUnit*>::iterator it = units.begin();

	for (it = units.begin(); it != units.end(); it++)
	{
		if ((*it) == unit)
		{
			it = units.erase(it);
			number_of_units--;
			break;
		}
	}
}


void TPlayer::PrintInfo()
{
	std::list<TUnit*>::iterator it = units.begin();

	for (it = units.begin(); it != units.end(); it++)
	{
		(*it)->PrintInfo();
	}
}
