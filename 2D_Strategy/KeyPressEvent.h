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

	sf::String PressedTab(sf::Text* tab_text, sf::Text* unit_info_text, sf::String unit_info_str,int x,int y)
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

	sf::Vector2i ArrowsPressd(TBattleground* bg,sf::Text* focus_tile_txt,sf::Sprite* sprite, sf::Event event, int x, int y)
	{
		std::cout << "Arrow is pressed" << (char)event.key.code << std::endl;
		bg->MoveFocusTile(event);
		focus_tile_txt->setPosition(x, y);
		Vector2i v_f = bg->GetFocusTile();
	    sf:String tmp_s = "Focus tile :" + std::to_string(v_f.x) + "  " + std::to_string(v_f.y);
		focus_tile_txt->setString(tmp_s);
		sprite->setTextureRect(sf::IntRect(0, 0, 64, 64));
		sprite->setPosition((v_f.x +1)* 64, (v_f.y +1)* 64);
		//std::cout << "Focus tile :" << std::to_string(v_f.x) << "  " << std::to_string(v_f.y);
		return v_f;
	}

};

