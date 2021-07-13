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

	enum{NOTHING,MOVE,ATTACK} EState;

	TUnit* focus_unit=NULL;
	TUnit* memorized_unit=NULL;

	int exceptions=0;
public:

	void SetException(int i)
	{
		exceptions = i;
	}

	void SetFocusUnit(TUnit* f_u)
	{
		focus_unit = f_u;
	}


	void UpdateTilesText(TBattleground* bg,sf::Text* focus_tile_txt, sf::Text* tab_text, sf::Text* unit_info_text, sf::String unit_info_str)
	{
		////////////////���� � ������� ������
		Vector2i v_f = bg->GetFocusTile();
		String tmp_s = "Focus tile :" + std::to_string(v_f.x) + "  " + std::to_string(v_f.y) + "\n Focus unit:\n" + bg->GetInfoAboutTile();

		std::string focus_unit_pos = "";

		if (EState==MOVE)// � ���� ������ M 
		{
			focus_unit_pos = "\n\nFrom[" + std::to_string(memorized_unit->GetX()) + "][" + std::to_string(memorized_unit->GetY()) +
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
				all_abilities = "M-move character\nA-attack";
			}
			if (enter_pressed == false)
			{
				all_abilities = "asdas";
			}
		}
		if (EState==MOVE)
		{
		
			all_abilities = "[M-move character]\n";
		}
		if (EState==ATTACK)
		{
			all_abilities = "[A-move attack]\n";
		}
		unit_abilities->setString(all_abilities);
		
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
		case TOO_FAR_TO_ATTACK:
		{
			exception_text->setString("Distance between units is more than maximum\n range of attack unit");
			*show_exception = true;
			break;
		}
		default:
			break;
		}
	}

	sf::Vector2i ArrowsPressd(TBattleground* bg,sf::Sprite* sprite, sf::Event event)
	{
		std::cout << "Arrow is pressed" << (char)event.key.code << std::endl;
		bg->MoveFocusTile(event);

		focus_unit = bg->GetFocusUnit();
	
		
		Vector2i v_f = bg->GetFocusTile();

		sprite->setTextureRect(sf::IntRect(0, 0, 64, 64));
		sprite->setPosition((v_f.y +1)* 64, (v_f.x +1)* 64);

		return v_f;
	}

	void PressedEnter(TBattleground* bg)
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
					if (EState == MOVE)// � ���� �������� ������������� �� ����� ������� ������ ������
					{
						exceptions = ALREADY_TAKEN;
						break;
					}
					if ((EState==ATTACK)&&(memorized_unit!=focus_unit))//���� �� ������� ����� � ��� ���� ������ ����������
					{
						exceptions=bg->Attack(memorized_unit, focus_unit);

						focus_unit = bg->GetFocusUnit();//���������� ����� �� ������������ �����
						memorized_unit = NULL;//�������� ������������ �����
						EState = NOTHING;//����� ��������� � �������� ��������� � ����������� ���������
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
			if (EState==MOVE)// � ���� ������ M 
			{
				exceptions = bg->Move(memorized_unit, bg->GetFocusTile().x, bg->GetFocusTile().y);//���������� ����� � ����� �����
				
				focus_unit = bg->GetFocusUnit();//�.�. ���� ������������, �� ����� ��������� ��������� �� "����� �����" �����
				
				memorized_unit = NULL;

				EState = NOTHING;
				enter_pressed = false;//��������� �����
			}
			if (EState==ATTACK)
			{
				exceptions = NOT_A_UNIT;
			}
		}		
	}

	void PressedM(TBattleground* bg)
	{
		if (enter_pressed==true)//���� ����� �����
		{
		
			if (EState == MOVE)
			{
				EState = NOTHING;
				enter_pressed = false;
				memorized_unit = NULL;
				return;
			}
			EState = MOVE;//�������,��� �� ������ ������� �����
			memorized_unit= bg->GetFocusUnit();//���������� ��������� �� ����, ������� ����� �����������
			bg->ReleaseFocus();//��������� ������ ������� ����� ���� �������������
			//enter_pressed = false;
		}
		else
		{
			exceptions = NO_CHARACTERS_SELECTED;
		}

	}

	void PressedA(TBattleground* bg)
	{
		if (enter_pressed==true)//���� ����� ����� �� ����� ��������� �����
		{
			if (EState == ATTACK)
			{
				EState = NOTHING;
				enter_pressed = false;
				memorized_unit = NULL;
				return;
			}
			EState = ATTACK;//������� ��� ����������� �����
			memorized_unit = bg->GetFocusUnit();//���������� ��� �������
			bg->ReleaseFocus();//��������� ������ ������� ����� ���� ���������
		}
		else//���� ����� �� ����� �� ������� ��� �������� �� ������
		{
			exceptions = NO_CHARACTERS_SELECTED;
		}
	}


	sf::String PressedTab(sf::Text* tab_text, sf::Text* unit_info_text, sf::String unit_info_str, int x, int y)
	{
		sf::String str;

		if (EState == MOVE)
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
};

