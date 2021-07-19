#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "TBattleground.h"

#define BATTLE_WIDTH_OFFSET 545
#define BATTLE_HEIGHT_OFFSET 50
#define HISTORY_SIZE 9

#define MAX_NUMBER_OF_PLAYERS 2


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

	std::string history[HISTORY_SIZE] = {"\0"};
	int number_of_history_notes = 0;
	
	TUnit* focus_unit=NULL;
	TUnit* memorized_unit=NULL;

	int exceptions=0;

public:
	void Initialization(int* players_id, std::string* nmes);
	
	void SetException(int i);
	void SetFocusUnit(TUnit* f_u);

	void SetTurn(int tn);
	int GetTurn();
	void NextTurn();//следующий ход(циклично)

	int GetMenuState();
	int GetExit();
	std::string GetName();
	std::string GetHistory();

	void ClearHistory();
	void RepackHistory(std::string str_to_ins);

	void UpdateSelectMenu(sf::Text* txt_play, sf::Text* txt_exit);
	void UpdateExitConfirm(sf::Text* txt_yes, sf::Text* txt_no);
	void UpdateTilesText(TBattleground* bg, sf::Text* focus_tile_txt, sf::Text* tab_text, sf::String unit_info_str);
	void UpdateUnitAbilitiesText(sf::Text* unit_abilities);
	void UpdateTimer(sf::Text* tab_text, int* time);
	void UpdateExceptions(sf::Text* exception_text, bool* show_exception, int* exceptions_time);

	void ArrowsPressdMenu(sf::Event event);
	void ArrowsPressedExit(sf::Event event);
	sf::Vector2i ArrowsPressd(TBattleground* bg, sf::Sprite* sprite, sf::Event event);

	void PressedEnter(TBattleground* bg);
	void PressedM(TBattleground* bg);
	void PressedA(TBattleground* bg);
	sf::String PressedTab(sf::Text* tab_text, int* time);
	
	
};

