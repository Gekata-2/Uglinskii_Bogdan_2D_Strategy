#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "TBattleground.h"

#define NO_CHARACTERS_SELECTED 4
#define NOT_A_UNIT 5
#define ALL_OK 0

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
	void SetFocusUnit(TUnit* f_u)
	{
		focus_unit = f_u;
	}


	void UpdateTilesText(TBattleground* bg,sf::Text* focus_tile_txt, sf::Text* tab_text, sf::Text* unit_info_text, sf::String unit_info_str)
	{
		////////////////���� � ������� ������
		Vector2i v_f = bg->GetFocusTile();
		sf:String tmp_s = "Focus tile :" + std::to_string(v_f.x) + "  " + std::to_string(v_f.y) + "\n Focus unit:\n" + bg->GetInfoAboutTile();

		std::string focus_unit_pos = "";

		if (move == true)// � ���� ������ M 
		{
			focus_unit_pos = "\n\nFrom[" + std::to_string(unit_to_move->GetX()) + "][" + std::to_string(unit_to_move->GetY()) +
				"] to [" + std::to_string(bg->GetFocusTile().x) + "][" + std::to_string(bg->GetFocusTile().y) + "]";
			tmp_s = "Focus tile :" + std::to_string(v_f.x) + "  " + std::to_string(v_f.y);
		}
		focus_tile_txt->setPosition(10, HEIGHT_MAP * 64 + 10);
		focus_tile_txt->setString(tmp_s + focus_unit_pos);
	}

	void UpdateUnitAbilitiesText(sf::Text* unit_abilities)
	{
		std::string all_abilities = "\0";
		unit_abilities->setPosition(WIDTH_MAP * 64 + 10, 10);

		if (focus_unit != NULL)
		{
			if (enter_pressed == true)
			{
				all_abilities += "M-move character\n";
			}
			if (enter_pressed == false)
			{
				all_abilities = "asdas";
			}
		}
		if (move == true)
		{
		
			all_abilities = "[M-move character]\n";
		}
		unit_abilities->setString(all_abilities);
		
	}

	void SetException(int i)
	{
		exceptions = i;
	}

	void UpdateExceptions(sf::Text* exception_text, bool* show_exception, int* exceptions_time)
	{
		exception_text->setPosition(10, HEIGHT_MAP * 64 + 200);

		switch (exceptions)
		{
		case ALL_OK:
		{
			*show_exception = false;
			exception_text->setString("");
			break;
		}
		case TOO_FAR:
		{
			exception_text->setString("Unit can't go this far");
			*show_exception = true;
			break;
		}
		case ALREADY_TAKEN:
		{
			exception_text->setString("This tile already taken");
			*show_exception = true;
			break;
		}
		case INCORRECT_DISTINATION:
		{
			exception_text->setString("Incorrect distinaition to move");
			*show_exception = true;
			break;
		}
		case NO_CHARACTERS_SELECTED:
		{
			exception_text->setString("No character selected!");
			*show_exception = true;
			break;
		}
		case NOT_A_UNIT:
		{
			exception_text->setString("Not a unit");
			*show_exception = true;
			break;
		}
		default:
			break;
		}
	}

	sf::Vector2i ArrowsPressd(TBattleground* bg,sf::Text* focus_tile_txt,sf::Sprite* sprite, sf::Event event)
	{
		std::cout << "Arrow is pressed" << (char)event.key.code << std::endl;
		bg->MoveFocusTile(event);

		focus_unit = bg->GetFocusUnit();
	
		
		Vector2i v_f = bg->GetFocusTile();

		sprite->setTextureRect(sf::IntRect(0, 0, 64, 64));
		sprite->setPosition((v_f.y +1)* 64, (v_f.x +1)* 64);

		return v_f;
	}

	void PressedEnter(TBattleground* bg, sf::Text* unit_abilities)
	{		
	
		if (focus_unit!=NULL)//������ �� �����
		{
			std::cout << "ENTER:" << focus_unit->GetInfo() << std::endl;
			switch (enter_pressed)
			{
			case false://���� �� ����� ����� �� ��� �����
				{
					bg->StopFocus();//��������� ������ ����������� �����
					enter_pressed = true;//������� ��� ����� �����
					break;
				}
			case true://����� ����� ��������� ������ ����������� �����
				{
					bg->ReleaseFocus();
					if (move == true)// � ���� �������� ������������� �� ����� ������� ������ ������
					{
						exceptions = ALREADY_TAKEN;
						break;
					}
					enter_pressed = false;//��������� �����
					break;
				}
			default:
				break;
			}
		}
		else//���� ����� ������ �� ��������
		{
			if (enter_pressed == false)
			{
				exceptions = NOT_A_UNIT;
			}
			if (move == true)// � ���� ������ M 
			{
				exceptions = bg->Move(unit_to_move, bg->GetFocusTile().x, bg->GetFocusTile().y);//���������� ����� � ����� �����
				
				focus_unit = bg->GetFocusUnit();
				
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
			if (move ==true)
			{
				move = false;
				enter_pressed = false;
				unit_to_move = NULL;
				return;
			}
			move = true;//�������,��� �� ������ ������� �����
			unit_to_move= bg->GetFocusUnit();//���������� ��������� �� ����, ������� ����� �����������
			bg->ReleaseFocus();//��������� ������ ������� ����� ���� �������������
		
			//enter_pressed = false;
		}
		else
		{
			exceptions = NO_CHARACTERS_SELECTED;
		}

	}

};

