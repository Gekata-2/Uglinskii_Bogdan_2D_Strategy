#pragma once

#include <iostream>
#include <list>

#include <SFML\Graphics.hpp>

#include "TUnit.h"
#include "TArcher.h"
#include "TSwordsman.h"





class TPlayer
{
private:
	size_t max_number_of_units = 5;
	size_t number_of_units = 0;
	std::list<TUnit*> units;
	std::string name;
	int id;


public:

	TPlayer(int i, std::string nm)
	{
		id = i;
		name = nm;
	}

	int GetID()
	{
		return id;
	}

	std::string GetName()
	{
		return name;
	}

	int GetNumberOfUnits()
	{
		return number_of_units;
	}

	void AddUnit(TUnit* unit)//добавляем юнита в конец
	{
		units.push_back(unit);
		number_of_units++;

		std::list<TUnit*>::iterator it = units.end();
		it--;
		std::cout << (*it)->GetInfo();
	}

	
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

