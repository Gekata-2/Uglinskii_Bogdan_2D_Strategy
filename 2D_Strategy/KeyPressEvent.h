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
	TUnit* unit_to_move=NULL;
	int exceptions=0;
public:

	sf::String PressedTab(sf::Text* tab_text, sf::Text* unit_info_text, sf::String unit_info_str,int x,int y)
	{
		sf::String str;
	
		if (move==true)
		{
			showTab = false;
		}
		switch (showTab)
		{
			case true: 
			{
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
	
		
		Vector2i v_f = bg->GetFocusTile();
		sf:String tmp_s = "Focus tile :" + std::to_string(v_f.x) + "  " + std::to_string(v_f.y)+"\n Focus unit:"+bg->GetInfoAboutTile();

		std::string focus_unit_pos = "";

		if (move == true)// � ���� ������ M 
		{
			 focus_unit_pos = "\n\nFrom[" + std::to_string(unit_to_move->GetX()) + "][" + std::to_string(unit_to_move->GetY()) +
			"] to [" + std::to_string(bg->GetFocusTile().x) + "][" + std::to_string(bg->GetFocusTile().y) + "]";
			 tmp_s = "Focus tile :" + std::to_string(v_f.x) + "  " + std::to_string(v_f.y);
		}
		focus_tile_txt->setPosition(x, y);
		focus_tile_txt->setString(tmp_s+ focus_unit_pos);

		sprite->setTextureRect(sf::IntRect(0, 0, 64, 64));
		sprite->setPosition((v_f.y +1)* 64, (v_f.x +1)* 64);

		return v_f;
	}

	void PressedEnter(TBattleground* bg, sf::Text* unit_abilities, sf::Text* exception,bool* show_exception)
	{		
		if (focus_unit!=NULL)//������ �� �����
		{
			
			switch (enter_pressed)
			{
			case false://���� �� ����� ����� �� ��� �����
				{
					bg->StopFocus();//��������� ������ ����������� �����
					unit_abilities->setPosition(WIDTH_MAP * 64 + 10, 10);//������� ���������� � ������������ �����
					unit_abilities->setString("M-move character");
					enter_pressed = true;//������� ��� ����� �����
					break;
				}
			case true:
				{
					
					bg->ReleaseFocus();
					unit_abilities->setString("");//������� ���������� � ������������ 
					enter_pressed = false;//��������� �����
				}
			default:
				break;
			}
		}
		else//���� ����� ������ �� ��������
		{
			if (move == true)// � ���� ������ M 
			{
				/*std::string focus_unit_pos = "From[" + std::to_string(unit_to_move->GetX()) + "][" + std::to_string(unit_to_move->GetY()) +
					"] to [" + std::to_string(bg->GetFocusTile().x) + "][" + std::to_string(bg->GetFocusTile().y)+"]";*/

				exceptions=bg->Move(unit_to_move, bg->GetFocusTile().x, bg->GetFocusTile().y);//���������� ����� � ����� �����
				exception->setPosition(10, HEIGHT_MAP * 64 + 200);
				if (exceptions==TOO_FAR)
				{
					exception->setString("Unit can't go this far");
					*show_exception = true;
				}
				if (exceptions == ALREADY_TAKEN)
				{
					exception->setString("This tile already taken");
					*show_exception = true;
				}
				if (exceptions == INCORRECT_DISTINATION)
				{
					exception->setString("Incorrect distinaition to move");
					*show_exception = true;
				}
				//unit_abilities->setPosition(WIDTH_MAP * 64 + 10, 10);//������� ���������� � ������������ �����
				unit_abilities->setString("");

				unit_to_move = NULL;

				move = false;
				enter_pressed = false;//��������� �����
			
			}
		}
		
	}

	void PressedM(TBattleground* bg, sf::Text* unit_abilities)
	{
		if (enter_pressed==true)//���� ����� �����
		{
			move = true;//�������,��� �� ������ ������� �����
			unit_to_move= bg->GetFocusUnit();//���������� ��������� �� ����, ������� ����� �����������
			bg->ReleaseFocus();//��������� ������ ������� ����� ���� �������������
			
			std::string focus_unit_pos = "From[" + std::to_string(focus_unit->GetX()) + "][" + std::to_string(focus_unit->GetY()) +"]";
			unit_abilities->setPosition(WIDTH_MAP * 64 + 10,10);//������� ���������� � ������������ �����
			unit_abilities->setString("[M-move character]\n" + focus_unit_pos);
		
			//bg->Move(focus_unit, bg->GetFocusTile().x, bg->GetFocusTile().y);

			//enter_pressed = false;
		}
		else
		{
			unit_abilities->setPosition(WIDTH_MAP * 64 + 10, 10);//������� ���������� � ������������ �����
			unit_abilities->setString("No character selected!");
		}

	}

};

