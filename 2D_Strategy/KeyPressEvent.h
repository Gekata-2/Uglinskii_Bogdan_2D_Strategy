#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "TBattleground.h"
using namespace sf;
class TKeyPressEvent
{
	bool showTab = true;
	bool enter_pressed = false;
	bool move = false;
	TUnit* focus_unit=NULL;
public:

	sf::String PressedTab(sf::Text* tab_text, sf::Text* unit_info_text, sf::String unit_info_str,int x,int y)
	{
		sf::String str;
	
		
		switch (showTab)
		{
			case true: 
			{
				std::cout << "Key  TAB  is pressed\n";
			
				str = "info(TAB)";
			

				tab_text->setPosition(x, y);
				tab_text->setString(str);

				unit_info_text->setPosition(x - 32, y + 96);
				unit_info_text->setString(unit_info_str);

				showTab = false;
				break;
			}
			case false: 
			{
				
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

		focus_unit = bg->GetFocusUnit();
	
		focus_tile_txt->setPosition(x, y);
		Vector2i v_f = bg->GetFocusTile();
	    sf:String tmp_s = "Focus tile :" + std::to_string(v_f.x) + "  " + std::to_string(v_f.y);
		focus_tile_txt->setString(tmp_s);

		sprite->setTextureRect(sf::IntRect(0, 0, 64, 64));
		sprite->setPosition((v_f.y +1)* 64, (v_f.x +1)* 64);

		return v_f;
	}

	void PressedEnter(TBattleground* bg, sf::Text* unit_abilities)
	{
		
		if (focus_unit!=NULL)//навели на юнита
		{
			
			switch (enter_pressed)
			{
			case false://если до этого энтер не был нажат
				{
					bg->StopFocus();//запрещаем игроку передвигать фокус
					unit_abilities->setPosition(WIDTH_MAP * 64 + 10, 128);//выводим информацию о возможностях героя
					unit_abilities->setString("M-move character");
					enter_pressed = true;//говорим что энтер нажат
					break;
				}
			case true:
				{
					
					bg->ReleaseFocus();
					unit_abilities->setString("");//убираем информацию о возможностях 
					enter_pressed = false;//отпускаем энтер
				}
			default:
				break;
			}
		}
		else
		{
			if (move == true)//если нажата M 
			{
				std::string focus_unit_pos = "From[" + std::to_string(focus_unit->GetX()) + "][" + std::to_string(focus_unit->GetY()) +
					"] to [" + std::to_string(bg->GetFocusTile().y) + "][" + std::to_string(bg->GetFocusTile().x);

				bg->Move(focus_unit, bg->GetFocusTile().y, bg->GetFocusTile().x);//перемещаем юнита в новое место

			
				unit_abilities->setPosition(WIDTH_MAP * 64 + 10, 128);//выводим информацию о возможностях героя
				unit_abilities->setString("[M-move character]\n" + focus_unit_pos);

				enter_pressed = false;//отпускаем энтер
			
			}
		}
		
	}

	void PressedM(TBattleground* bg, sf::Text* unit_abilities)
	{
		if (enter_pressed==true)//если энтер нажат
		{
			move = true;//говорим,что мы теперь двигаем юнита
			focus_unit = bg->GetFocusUnit();//сохраняем информацию о текущем(перемещаемом) юните
			bg->ReleaseFocus();//позволяем игроку выбрать место куда переместиться
			
			std::string focus_unit_pos = "From[" + std::to_string(focus_unit->GetX()) + "][" + std::to_string(focus_unit->GetY()) +"]"+focus_unit->GetInfo();
			unit_abilities->setPosition(WIDTH_MAP * 64 + 10, 128);//выводим информацию о возможностях героя
			unit_abilities->setString("[M-move character]\n" + focus_unit_pos);
		
			//bg->Move(focus_unit, bg->GetFocusTile().x, bg->GetFocusTile().y);

			//enter_pressed = false;
		}

	}

};

