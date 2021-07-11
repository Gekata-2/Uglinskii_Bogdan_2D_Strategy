#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "TBattleground.h"
using namespace sf;
class TKeyPressEvent
{
	bool showTab = true;
public:
	void KeyPressed(sf::Event event)
	{
		if ((event.key.code == Keyboard::Tab))
		{//если клавиша ТАБ
			/*PressedTab();		*/	
		}
	}

	sf::String PressedTab(sf::Text* tab_text, sf::Text* unit_info_text,sf::String unit_info_str,int x,int y)
	{
		sf::String str;
	
		
		switch (showTab)
		{
			case true: 
			{
				std::cout << "Key  TAB  is pressed\n";
				Sleep(100);
				str = "TAB";
		
				tab_text->setPosition(x, y);
				tab_text->setString(str);
				unit_info_text->setPosition(x - 32, y + 96);
				unit_info_text->setString(unit_info_str);
				showTab = false;
				break;
			}
			case false: 
			{
				Sleep(100);
				std::cout << "Key  TAB  is pressed twice\n";
				str = "";
				tab_text->setString(str);
				unit_info_text->setString("");
				showTab = true;
				break;
			}
		}

		return str;
	}


};

