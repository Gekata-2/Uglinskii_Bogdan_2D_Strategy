#pragma once
#include "TSwordsman.h"
#include "TArcher.h"
#include "TBattleground.h"
#include <conio.h>
#include <iostream>
#include <vector>


//#define ESC 27
//#define LEFT 65
//#define RIGHT 68
//#define UP 87
//#define DOWN 83
//#define ADD 78

#define HOME 71
#define DOWN 80
#define NEXT 77
#define UP 72
#define ESC 27
#define INS 82
#define DEL 83
#define ENTER 13
#define STAR 42
class TConsoleView
{
	TBattleground bg;
	std::vector<TSwordsman> swordsmans;
	std::vector<TArcher> archers;
	char ch;
	int type;

public:
	void Display()
	{
		do
		{
			
			std::cout << ">, v, ^, Home, Ins, Del, Enter, Esc, *\n";
			bg.Print();
			
			ch = _getch();
			if (ch==ESC)
			{
				break;
			} 
			if (ch != ENTER)//если не выходим ,то продолжаем манипуляцию 
			{
				ch = _getch();
			}
			switch (ch)
			{
			case INS:
				{
				int tmp_x, tmp_y;
				std::cout << "Choose a tile to place unit: x = ";
				std::cin >> tmp_x;
				std::cout << " y = ";
				std::cin >> tmp_y;

				std::cout << "What type of unit to add?\n 1- Swordsman, 2- Archer: ";
				std::cin >> type;
				switch (type)
				{
					case 1:
					{
						TSwordsman sw;
					
						swordsmans.push_back(sw);
						int tmp_size = swordsmans.size();
						bg.AddUnit(&swordsmans[tmp_size-1],tmp_x,tmp_y);
						break;
					}
					case 2:
					{
						TArcher ar;
						archers.push_back(ar);
						int tmp_size = archers.size();
						bg.AddUnit(&archers[tmp_size - 1], tmp_x, tmp_y);
						break;
					}
					default:
						break;
					}
				}
				
			break;
			default:
				break;
			}
		
		} while (ch!=ESC);
	}
};

