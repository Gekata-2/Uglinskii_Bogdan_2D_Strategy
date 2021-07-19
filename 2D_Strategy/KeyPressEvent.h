#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "TBattleground.h"



#define MAX_NUMBER_OF_PLAYERS 2
using namespace sf;

class TKeyPressEvent
{
	

	bool showTab = true;
	bool enter_pressed = false;
	bool move = false;

	int turn;
	int ids[MAX_NUMBER_OF_PLAYERS];
	int i_id = 0;

	enum{NOTHING,MOVE,ATTACK} EState;
	enum{PLAY=0,EXIT} EMenu;

	int menu=2;
	bool exit = false;
	const int menu_size = 2;
	sf::Vector2i select_pos = { 733,300 };
	sf::Vector2i exit_pos = { 733,300 };
	const sf::Vector2i max_pos = { 700,520 };
	const sf::Vector2i min_pos = { 733,300 };

	TUnit* focus_unit=NULL;
	TUnit* memorized_unit=NULL;

	int exceptions=0;
public:

	void Initialization(int* players_id)//������� ����� ������ ����
	{
		for (size_t i = 0; i < MAX_NUMBER_OF_PLAYERS; i++)
		{
			ids[i] = players_id[i];
		}
		turn = ids[0];
	}

	void NextTurn()//��������� ���(��������)
	{
		i_id = (i_id + 1) % MAX_NUMBER_OF_PLAYERS;
		turn = ids[i_id];
	}
	
	void SetException(int i)
	{
		exceptions = i;
	}

	void SetFocusUnit(TUnit* f_u)
	{
		focus_unit = f_u;
	}

	void SetTurn(int tn)
	{
		turn = tn;
	}

	int GetTurn()
	{
		return turn;
	}

	

	int GetMenuState()
	{
		return menu;
	}
	int GetExit()
	{
		return exit;
	}

	void UpdateSelectMenu(sf::Text* txt_play, sf::Text* txt_exit)
	{

		switch (menu)
		{

		case 2:
			{
				txt_play->setScale(1.1, 1.1);
				txt_exit->setScale(1.0, 1.0);

				break;
			}
		case 1:
			{
				txt_exit->setScale(1.1, 1.1); 
				txt_play->setScale(1.0, 1.0);
		
				break;
			}
		

		default:
			break;
		}

	}

	/*void UpdateSelectMenu(sf::Sprite* select)
	{
		select->setPosition(select_pos.x, select_pos.y);
	}*/
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

	void UpdateTimer(sf::Text* tab_text, int* time)
	{
		std::string str = "\0";
		tab_text->setPosition(WIDTH_MAP * 64 / 2 - 64, 0);
		switch (showTab)
		{
		case true:
		{

			str = "Time(TAB)" + std::to_string(*time / 60) + ":" + std::to_string(*time - (*time / 60) * 60);
			str += "	In seconds :" + std::to_string(*time);
			
			tab_text->setString(str);
			break;
		}
		case false:
		{
			tab_text->setString("");
			break;
		}
		}
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
		case FRIENDLY_UNIT:
			{
			exception_text->setString("You can't attack friendly unit");
			*show_exception = true;
			break;
			}
			case ENEMY_UNIT:
			{
				exception_text->setString("Enemy Unit");
				*show_exception = true;
				break;
			}	
		default:
			break;
		}
	}

	void ArrowsPressdMenu(sf::Event event)
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			if (menu< menu_size)
			{
				menu += 1;
				select_pos.y -= 180;
			}
					
		}
		if (event.key.code == sf::Keyboard::Down)
		{
			if (menu>1)
			{
				menu -= 1;
				select_pos.y += 180;
			}
				
		}
	}
	void ArrowsPressedExit(sf::Event event)
	{
		if (event.key.code == sf::Keyboard::Left)
		{
			exit = true;

			exit_pos = { 733,300 };

		}
		if (event.key.code == sf::Keyboard::Right)
		{
			exit = false;
			exit_pos = { 933,300 };
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
		if(focus_unit!=NULL) //������ �� �����
		{
			if((focus_unit->GetSide() != turn)&&(EState!=ATTACK))//���� ������ �� ���������� �����
			{
				exceptions = ENEMY_UNIT;
				return;
			}
			//std::cout << "ENTER:" << focus_unit->GetInfo() << std::endl;
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
					if (EState==NOTHING)//���� ����� �� ������ �������� �������� �� ���������� �����
					{
						bg->ReleaseFocus(); 
						enter_pressed = false;
						break;
					}
					
					if (EState == MOVE)// � ���� �������� ������������� �� ����� ������� ������ ������
					{
						exceptions = ALREADY_TAKEN;
						break;
					}
					if ((EState==ATTACK)&&(memorized_unit!=focus_unit))//���� �� ������� ����� � ��� ���� ������ ����������
					{
						exceptions=bg->Attack(memorized_unit, focus_unit);
						
						if (exceptions==FRIENDLY_UNIT)
						{
							break;
						}

						focus_unit = bg->GetFocusUnit();//���������� ����� �� ������������ �����

						memorized_unit = NULL;//�������� ������������ �����
						EState = NOTHING;//����� ��������� � �������� ��������� � ����������� ���������
						enter_pressed = false;//��������� �����
						NextTurn();
					}			
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
				NextTurn();
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
		
			if (EState == MOVE)//���� �������� ��������, �� �������� ��������
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
			if (EState == ATTACK)//���� �������� ��������, �� �������� ��������
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


	sf::String PressedTab(sf::Text* tab_text,int* time)
	{
		sf::String str;

		if( (EState == MOVE)||(EState == ATTACK))
		{
			showTab = false;
		}
		switch (showTab)
		{
			case true:
			{

				str = "Time(TAB)"+std::to_string(*time/60)+":"+ std::to_string(*time - (*time / 60)*60);
				str += "	In seconds :" + std::to_string(*time) ;
				tab_text->setPosition(WIDTH_MAP*64/2-64,0);
				tab_text->setString(str);


				showTab = false;
				break;
			}
			case false:
			{
			
				tab_text->setString("");
				showTab = true;
				break;
			}
		}

		return str;
	}
};

