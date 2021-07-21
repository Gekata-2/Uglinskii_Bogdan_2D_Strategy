#include "KeyPressEvent.h"

void TKeyPressEvent::Initialization(int* players_id, std::string* nmes)//говорим какие игроки есть
{
	for (size_t i = 0; i < MAX_NUMBER_OF_PLAYERS; i++)
	{
		ids[i] = players_id[i];
		names[i] = nmes[i];
	}
	turn = ids[0];
	name = names[0];
}

void TKeyPressEvent::NextTurn()//следующий ход(циклично)
{
	i_id = (i_id + 1) % MAX_NUMBER_OF_PLAYERS;
	turn = ids[i_id];
	name = names[i_id];
}

void TKeyPressEvent::SetException(int i)
{
	exceptions = i;
}

void TKeyPressEvent::SetFocusUnit(TUnit* f_u)
{
	focus_unit = f_u;
}

void TKeyPressEvent::SetTurn(int tn)
{
	turn = tn;
}

int TKeyPressEvent::GetTurn()
{
	return turn;
}
std::string TKeyPressEvent::GetName()
{
	return name;
}



int TKeyPressEvent::GetMenuState()
{
	return menu;
}
int TKeyPressEvent::GetExit()
{
	return exit;
}

std::string TKeyPressEvent::GetHistory()
{
	std::string temp_string = "\0";

	for (size_t i = 0; i < HISTORY_SIZE; i++)
	{
		temp_string += history[i];
	}
	return temp_string;
}

void TKeyPressEvent::ClearHistory()
{
	for (size_t i = 0; i < number_of_history_notes; i++)
	{
		history[i] = "\0";
	}
}

void TKeyPressEvent::RepackHistory(std::string str_to_ins)
{
	for (size_t i = number_of_history_notes - 1; i > 0; i--)//передвинули все элементы на 1
	{
		history[i] = history[i - 1];
	}

	history[0] = str_to_ins;
}

void TKeyPressEvent::AddHistory(std::string str_to_ins)
{
	history[history_pos] = str_to_ins;

	history_pos++;
	
	if (history_pos== HISTORY_SIZE)
	{
		history_pos = 0;
	}
}

void TKeyPressEvent::UpdateSelectMenu(sf::Text* txt_play, sf::Text* txt_exit)
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

void TKeyPressEvent::UpdateExitConfirm(sf::Text* txt_yes, sf::Text* txt_no)
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


void TKeyPressEvent::UpdateTilesText(TBattleground* bg, sf::Text* focus_tile_txt, sf::Text* tab_text, sf::String unit_info_str)
{
	////////////////Инфа о текущей клетке
	sf::Vector2i v_f = bg->GetFocusTile();
	sf::String tmp_s = "Selected tile :" + std::to_string(v_f.x) + "  " + std::to_string(v_f.y) + "\n";

	if (bg->GetInfoAboutTile() == "NULL")
	{
		tmp_s += "Empty tile";
	}
	else
	{
		tmp_s += bg->GetInfoAboutTile();
	}
	std::string focus_unit_pos = "";

	if (EState == MOVE)// и если нажата M 
	{
		focus_unit_pos = "\n\nFrom[" + std::to_string(memorized_unit->GetX()) + "][" + std::to_string(memorized_unit->GetY()) +
			"] to [" + std::to_string(bg->GetFocusTile().x) + "][" + std::to_string(bg->GetFocusTile().y) + "]";
		tmp_s = "Focus tile :" + std::to_string(v_f.x) + "  " + std::to_string(v_f.y);
	}

	focus_tile_txt->setString(tmp_s + focus_unit_pos);
}

void TKeyPressEvent::UpdateUnitAbilitiesText(sf::Text* unit_abilities)
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
	if (EState == MOVE)
	{

		all_abilities = "[M-move character]\nPress M to cancel action";
	}
	if (EState == ATTACK)
	{
		all_abilities = "[A-move attack]\nPress A to cancel action";
	}
	unit_abilities->setString(all_abilities);

}

void TKeyPressEvent::UpdateTimer(sf::Text* tab_text, int* time)
{
	std::string str = "\0";
	switch (showTab)
	{
	case true:
	{

		str = "Time(TAB) " + std::to_string(*time / 60) + " :" + std::to_string(*time - (*time / 60) * 60);

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

void TKeyPressEvent::UpdateExceptions(sf::Text* exception_text, bool* show_exception, int* exceptions_time)
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
		exception_text->setString("Distance between units is more\nthan maximum\nrange of attack unit");
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

void TKeyPressEvent::ArrowsPressedMenu(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Up)
	{
		if (menu < menu_size)
		{
			menu += 1;
		}

	}
	if (event.key.code == sf::Keyboard::Down)
	{
		if (menu > 1)
		{
			menu -= 1;
		}
	}
}
void TKeyPressEvent::ArrowsPressedExit(sf::Event event)
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


void TKeyPressEvent::ArrowsPressed(TBattleground* bg, sf::Sprite* sprite, sf::Event event)
{
	std::cout << "Arrow is pressed" << (char)event.key.code << std::endl;
	bg->MoveFocusTile(event);

	focus_unit = bg->GetFocusUnit();

	sf::Vector2i v_f = bg->GetFocusTile();
	sprite->setPosition((v_f.y + 1) * 83 + BATTLE_WIDTH_OFFSET - 3, (v_f.x + 1) * 83 + BATTLE_HEIGHT_OFFSET - 3);
}

void TKeyPressEvent::PressedEnter(TBattleground* bg)
{
	if (focus_unit != NULL) //навели на юнита
	{
		if ((focus_unit->GetSide() != turn) && (EState != ATTACK))//если навели на вражеского юнита
		{
			exceptions = ENEMY_UNIT;
			return;
		}

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
			if (EState == NOTHING)//если игрок не выбрал никакого действия то возвращаем фокус
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
			if ((EState == ATTACK) && (memorized_unit != focus_unit))//если мы атакуем юнита и при этом только вражеского
			{
				float damage = focus_unit->GetCurrentHP();
				exceptions = bg->Attack(memorized_unit, focus_unit);

				damage = damage - focus_unit->GetCurrentHP();

				if((exceptions == FRIENDLY_UNIT)||(exceptions == TOO_FAR_TO_ATTACK))
				{
					break;
				}
			
				std::string tmp_h_str = "attack:  " + memorized_unit->GetName() + "->" + focus_unit->GetName() + "\ndamage:" + std::to_string(damage) + ";\n";

				AddHistory(tmp_h_str);

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
		if (EState == MOVE)// и если нажата M 
		{
			sf::Vector2i history_move = memorized_unit->GetPos();

			exceptions = bg->Move(memorized_unit, bg->GetFocusTile().x, bg->GetFocusTile().y);//перемещаем юнита в новое место


			if (exceptions == ALL_OK)
			{
			
				std::string tmp_h_str = "move:" + memorized_unit->GetName() + "\n[" + std::to_string(history_move.x) + "][" + std::to_string(history_move.y)
					+ "] -> [" + std::to_string(memorized_unit->GetPos().x) + "][" + std::to_string(memorized_unit->GetPos().y) + "];\n";
				std::cout << tmp_h_str;
				
				AddHistory(tmp_h_str);

				NextTurn();
				focus_unit = bg->GetFocusUnit();//т.к. юнит переместился, то нужно перевести указатель на "новое место" юнита


				memorized_unit = NULL;

				EState = NOTHING;
				enter_pressed = false;//отпускаем энтер
			}

		}
		if (EState == ATTACK)
		{
			exceptions = NOT_A_UNIT;
		}
	}
}

void TKeyPressEvent::PressedM(TBattleground* bg)
{
	if (enter_pressed == true)//если энтер нажат
	{

		if (EState == MOVE)//если нажимаем повторно, то отменяем действие
		{
			EState = NOTHING;
			enter_pressed = false;
			memorized_unit = NULL;
			return;
		}
		EState = MOVE;//говорим,что мы теперь двигаем юнита
		memorized_unit = bg->GetFocusUnit();//запоминаем указатель на юнит, который нужно передвинуть
		bg->ReleaseFocus();//позволяем игроку выбрать место куда переместиться
	}
	else
	{
		exceptions = NO_CHARACTERS_SELECTED;
	}

}

void TKeyPressEvent::PressedA(TBattleground* bg)
{
	if (enter_pressed == true)//если энтер нажат то можно выполнять атаку
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


void TKeyPressEvent::PressedTab(sf::Text* tab_text, int* time)
{	
	switch (showTab)
	{
	case true:
		{
			showTab = false;
			break;
		}
	case false:
		{
			
			showTab = true;
			break;
		}
	}
}