#pragma once

#include <iostream>
#include <list>

#include <SFML\Graphics.hpp>

#include "TUnit.h"
#include "TArcher.h"
#include "TSwordsman.h"


void GenerateUnit(TUnit* unit,std::string type,int side)
{
	if (type == "Archer")
	{
		unit = new TArcher;
		unit->SetSide(side);
	}
	if (type == "Swordsman")
	{
		unit = new TSwordsman;
		unit->SetSide(side);
	}
}


class TPlayer
{
private:
	size_t max_number_of_units = 5;
	size_t number_of_units = 0;
	std::list<TUnit*> units;
	std::string name;
	int id;

public:

	TPlayer(int i,std::string nm)
	{
		id = i;
		name = nm;
	}

	void AddUnit(TUnit* unit)//добавляем юнита в конец
	{
		units.push_back(unit);
		number_of_units++;

		std::list<TUnit*>::iterator it = units.end();
		it--;
		std::cout << (*it)->GetInfo();
	}

	//void CreateUnit(std::string type,std::string name="\0")
	//{
	//	if (type=="Archer")
	//	{
	//		TArcher* ar;
	//		ar->SetSide(id);
	//		AddUnit(ar);
	//	
	//	}
	//	if (type == "Swordsman")
	//	{
	//		TSwordsman* sw;
	//		sw->SetSide(id);
	//		AddUnit(sw);
	//	}
	//	
	//}

	//void GenerateUnits(size_t size)
	//{
	//	int tp;
	//	for (size_t i = 0; i < size; i++)
	//	{
	//		std::cout << "i=" << i << "\n";
	//		tp = rand() % 2;
	//		if (tp==0)
	//		{
	//			CreateUnit("Swordsman",std::to_string(i));
	//		}
	//		if (tp == 1)
	//		{
	//			CreateUnit("Archer", std::to_string(i));
	//		}
	//	}
	//}

	void DeleteUnit(TUnit* unit)//ищем юнита и убираем
	{
		std::list<TUnit*>::iterator it = units.begin();

		for (it = units.begin(); it!=units.end(); it++)
		{
			if ((*it)==unit)
			{
				it = units.erase(it);
				number_of_units--;
				break;		
			}
		}
	}


	void PrintInfo()
	{

		std::list<TUnit*>::iterator it = units.begin();

		for (it = units.begin(); it != units.end(); it++)
		{
			(*it)->PrintInfo();
		}
	}


};

