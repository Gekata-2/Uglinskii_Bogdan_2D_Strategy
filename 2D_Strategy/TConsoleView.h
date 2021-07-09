#pragma once
#include "TSwordsman.h"
#include "TArcher.h"
#include "TBattleground.h"
#include <conio.h>
#include <iostream>


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
class ConsoleView
{
	TBattleground bg;
	char ch;

public:
	void Display()
	{
		do
		{
			
			std::cout << ">, v, ^, Home, Ins, Del, Enter, Esc, *";
	
			ch = getchar();
			if (ch==ESC)
			{
				break;
			} 
			if (ch != ENTER)//если не выходим ,то продолжаем манипул¤цию 
			{
				ch = getchar();
			}
			switch (ch)
			{
			default:
				break;
			}
		
		} while (ch!=ESC);
	}
};

