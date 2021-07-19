#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "TBattleground.h"

#define BATTLE_WIDTH_OFFSET 545
#define BATTLE_HEIGHT_OFFSET 50
#define HISTORY_SIZE 9

#define MAX_NUMBER_OF_PLAYERS 2
using namespace sf;

class TKeyPressEvent
{
	

	bool showTab = true;
	bool enter_pressed = false;
	bool move = false;

	int turn;
	int ids[MAX_NUMBER_OF_PLAYERS];
	std::string name="\0";
	std::string names[MAX_NUMBER_OF_PLAYERS];
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

	std::string history[HISTORY_SIZE] = {"\0"};
	int number_of_history_notes = 0;
	

	TUnit* focus_unit=NULL;
	TUnit* memorized_unit=NULL;

	int exceptions=0;
public:

	void Initialization(int* players_id,std::string* nmes)//говорим какие игроки есть
	{
		for (size_t i = 0; i < MAX_NUMBER_OF_PLAYERS; i++)
		{
			ids[i] = players_id[i];
			names[i] = nmes[i];
		}
		turn = ids[0];
		name = names[0];
	}

	void NextTurn()//следующий ход(циклично)
	{
		i_id = (i_id + 1) % MAX_NUMBER_OF_PLAYERS;
		turn = ids[i_id];
		name = names[i_id];
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
	std::string GetName()
	{
		return name;
	}

	

	int GetMenuState()
	{
		return menu;
	}
	int GetExit()
	{
		return exit;
	}

	std::string GetHistory()
	{
		std::string temp_string = "\0";

		for (size_t i = 0; i < number_of_history_notes; i++)
		{
			temp_string += history[i];
		}
		return temp_string;
	}

	void ClearHistory()
	{
		for (size_t i = 0; i < number_of_history_notes; i++)
		{
		  history[i]="\0";
		}
	}

	void RepackHistory(std::string str_to_ins)
	{
		std::string temp_string = "\0";
		
		for(size_t i = number_of_history_notes-1; i>0; i--)//передвинули все элементы на 1
		{
			history[i] = history[i - 1];
		}
		history[0] = str_to_ins;
	}

	void UpdateSelectMenu(sf::Text* txt_play, sf::Text* txt_exit)
	{
		switch (menu)
		{

		case 2:
			{
				txt_play->setScale(1.15, 1.15);
				txt_exit->setScale(1.0, 1.0);

				break;
			}
		case 1:
			{
				txt_exit->setScale(1.15, 1.15); 
				txt_play->setScale(1.0, 1.0);
		
				break;
			}
		default:
			break;
		}

	}

	void UpdateExitConfirm(sf::Text* txt_yes, sf::Text* txt_no)
	{

		switch (exit)
		{

			case true:
			{
				txt_yes->setScale(1.2, 1.2);
				txt_no->setScale(1.0, 1.0);
				break;
			}
			case false:
			{
				txt_no->setScale(1.2, 1.2);
				txt_yes->setScale(1.0, 1.0);
				break;
			}
			default:
			break;
		}

	}


	void UpdateTilesText(TBattleground* bg,sf::Text* focus_tile_txt, sf::Text* tab_text, sf::String unit_info_str)
	{
		////////////////Инфа о текущей клетке
		Vector2i v_f = bg->GetFocusTile();
		String tmp_s = "Selected tile :" + std::to_string(v_f.x) + "  " + std::to_string(v_f.y)+"\n" ;
		
		if (bg->GetInfoAboutTile()=="NULL")
		{
			tmp_s += "Empty tile";
		}
		else
		{
			tmp_s += bg->GetInfoAboutTile();
		}
		std::string focus_unit_pos = "";

		if (EState==MOVE)// и если нажата M 
		{
			focus_unit_pos = "\n\nFrom[" + std::to_string(memorized_unit->GetX()) + "][" + std::to_string(memorized_unit->GetY()) +
				"] to [" + std::to_string(bg->GetFocusTile().x) + "][" + std::to_string(bg->GetFocusTile().y) + "]";
			tmp_s = "Focus tile :" + std::to_string(v_f.x) + "  " + std::to_string(v_f.y);
		}
		
		focus_tile_txt->setString(tmp_s + focus_unit_pos);
	}

	void UpdateUnitAbilitiesText(sf::Text* unit_abilities)
	{
		std::string all_abilities = "\0";
	

		if (focus_unit != NULL)
		{
			if (enter_pressed == true)
			{
				all_abilities = "M-move character\nA-attack";
			}
			if (enter_pressed == false)
			{
				all_abilities = "";
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
		switch (showTab)
		{
		case true:
		{

			str = "Time(TAB)" + std::to_string(*time / 60) + ":" + std::to_string(*time - (*time / 60) * 60);
			//str += "	In seconds :" + std::to_string(*time);
			
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
			
		}
		if (event.key.code == sf::Keyboard::Right)
		{
			exit = false;		
		}
	}


	sf::Vector2i ArrowsPressd(TBattleground* bg,sf::Sprite* sprite, sf::Event event)
	{
		std::cout << "Arrow is pressed" << (char)event.key.code << std::endl;
		bg->MoveFocusTile(event);

		focus_unit = bg->GetFocusUnit();
	
		
		Vector2i v_f = bg->GetFocusTile();

		sprite->setPosition((v_f.y +1)* 83+ BATTLE_WIDTH_OFFSET-3, (v_f.x +1)* 83+ BATTLE_HEIGHT_OFFSET-3);

		return v_f;
	}

	void PressedEnter(TBattleground* bg)
	{		
		if(focus_unit!=NULL) //навели на юнита
		{
			if((focus_unit->GetSide() != turn)&&(EState!=ATTACK))//если навели на вражеского юнита
			{
				exceptions = ENEMY_UNIT;
				return;
			}
			//std::cout << "ENTER:" << focus_unit->GetInfo() << std::endl;
			switch (enter_pressed)
			{
			case false://если до этого энтер не был нажат
				{
					bg->StopFocus();//запрещаем игроку передвигать фокус
					enter_pressed = true;//говорим что энтер нажат
					break;
				}
			case true://чтобы вновь позволить игроку передвигать фокус
				{
					if (EState==NOTHING)//если игрок не выбрал никакого действия то возвращаем фокус
					{
						bg->ReleaseFocus(); 
						enter_pressed = false;
						break;
					}
					
					if (EState == MOVE)// и если пытаемся переместиться на место занятое другим юнитом
					{
						exceptions = ALREADY_TAKEN;
						break;
					}
					if ((EState==ATTACK)&&(memorized_unit!=focus_unit))//если мы атакуем юнита и при этом только вражеского
					{
						float damage = focus_unit->GetCurrentHP();
						exceptions=bg->Attack(memorized_unit, focus_unit);
						
						damage = damage - focus_unit->GetCurrentHP();

						if (exceptions==FRIENDLY_UNIT)
						{
							break;
						}

						if (number_of_history_notes== HISTORY_SIZE)
						{
							std::string tmp_h_str = "attack:  " + memorized_unit->GetName() + "-->" + focus_unit->GetName() + "\ndamage:" + std::to_string(damage) + ";\n";
							RepackHistory(tmp_h_str);
						}
						else 
						{
							history[number_of_history_notes] += "attack:  " + memorized_unit->GetName() + "-->" + focus_unit->GetName() + "\ndamage:" + std::to_string(damage) + ";\n";
							number_of_history_notes++;
						}
						

						focus_unit = bg->GetFocusUnit();//перемещаем фокус на атакованного юнита
						

						memorized_unit = NULL;//забываем атаковавшего юнита
						EState = NOTHING;//атака завершена и персонаж переходит в нейтральное состояние
						enter_pressed = false;//отпускаем энтер
						NextTurn();

					}			
					break;
				}
			default:
				break;
			}
		}
		else//если место фокуса не персонаж
		{
			if (enter_pressed == false)
			{
				exceptions = NOT_A_UNIT;
			}
			if (EState==MOVE)// и если нажата M 
			{
				sf::Vector2i history_move = memorized_unit->GetPos();

				exceptions = bg->Move(memorized_unit, bg->GetFocusTile().x, bg->GetFocusTile().y);//перемещаем юнита в новое место
				
				
				if (exceptions==ALL_OK)
				{
					if (number_of_history_notes == HISTORY_SIZE)
					{
						std::string tmp_h_str = "move:" + memorized_unit->GetName() + "\n[" + std::to_string(history_move.x) + "][" + std::to_string(history_move.y)
							+ "] -> [" + std::to_string(memorized_unit->GetPos().x) + "][" + std::to_string(memorized_unit->GetPos().y) + "];\n";
						RepackHistory(tmp_h_str);
					}
					else 
					{
						history[number_of_history_notes] = "move:" + memorized_unit->GetName() + "\n[" + std::to_string(history_move.x) + "][" + std::to_string(history_move.y)
							+ "] -> [" + std::to_string(memorized_unit->GetPos().x) + "][" + std::to_string(memorized_unit->GetPos().y) + "];\n";
						number_of_history_notes++;
					}
					
					
					NextTurn();
					focus_unit = bg->GetFocusUnit();//т.к. юнит переместился, то нужно перевести указатель на "новое место" юнита


					memorized_unit = NULL;

					EState = NOTHING;
					enter_pressed = false;//отпускаем энтер
				}

			}
			if (EState==ATTACK)
			{
				exceptions = NOT_A_UNIT;
			}
		}		
	}

	void PressedM(TBattleground* bg)
	{
		if (enter_pressed==true)//если энтер нажат
		{
		
			if (EState == MOVE)//если нажимаем повторно, то отменяем действие
			{
				EState = NOTHING;
				enter_pressed = false;
				memorized_unit = NULL;
				return;
			}
			EState = MOVE;//говорим,что мы теперь двигаем юнита
			memorized_unit= bg->GetFocusUnit();//запоминаем указатель на юнит, который нужно передвинуть
			bg->ReleaseFocus();//позволяем игроку выбрать место куда переместиться
			//enter_pressed = false;
		}
		else
		{
			exceptions = NO_CHARACTERS_SELECTED;
		}

	}

	void PressedA(TBattleground* bg)
	{
		if (enter_pressed==true)//если энтер нажат то можно выполнять атаку
		{
			if (EState == ATTACK)//если нажимаем повторно, то отменяем действие
			{
				EState = NOTHING;
				enter_pressed = false;
				memorized_unit = NULL;
				return;
			}
			EState = ATTACK;//говорим что совершается атака
			memorized_unit = bg->GetFocusUnit();//запоминаем кто атакует
			bg->ReleaseFocus();//позволяем игроку выбрать место кого атаковать
		}
		else//если энтер не нажат то говорим что персонаж не выбран
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

