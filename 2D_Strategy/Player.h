#pragma once

#include <iostream>
#include <list>

#include <SFML\Graphics.hpp>

#include "Unit.h"
#include "Archer.h"
#include "Swordsman.h"



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

	int GetID();
	std::string GetName();
	
	int GetNumberOfUnits();
	
	void AddUnit(TUnit* unit);//добавляем юнита в конец	
	void DeleteUnit(TUnit* unit);//ищем юнита и убираем
	
	void PrintInfo();

};

