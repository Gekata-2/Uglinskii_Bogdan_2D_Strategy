#include <iostream>
#include <vector>
#include <sstream>
#include "Battleground.h"
#include "Archer.h"
#include "Swordsman.h"
#include "KeyPressEvent.h"
#include "Player.h"
#include <windows.h>
#include <SFML/Graphics.hpp>



void GenerateUnit(TUnit** unit, std::string type, int side,std::string name="\0")
{
	if (type == "Archer")
	{
		*unit = new TArcher(name);
		(*unit)->SetSide(side);
	}
	if (type == "Swordsman")
	{
		*unit = new TSwordsman(name);
		(*unit)->SetSide(side);
	}
}

void CreateSetOfUnits(std::vector<TUnit*>* vec,int side)
{
		int tp;
		for (size_t i = 0; i < vec->size(); i++)
		{
				std::cout << "i=" << i << "\n";
				tp = rand() % 2;
				if (tp==0)
				{
					GenerateUnit(&(*vec)[i],"Archer",side);
				}
				if (tp == 1)
				{
					GenerateUnit(&(*vec)[i], "Swordsman", side);
				}
		}
}



int main()
{
	
    TBattleground bg;

	TSwordsman SwA;
	TSwordsman SwB;

	TArcher ArA;
	TArcher ArB;


	TPlayer P1(58, "Bogdan");
	TPlayer P2(69, "ZXC");

	

	int players_id[MAX_NUMBER_OF_PLAYERS] = {P1.GetID(),P2.GetID()};//массив с id игроков
	std::string players_names[MAX_NUMBER_OF_PLAYERS] = { P1.GetName(), P2.GetName() };

	int player_size = 1;//количество персонажей у игрока

	//добавляем на поле игроков
	bg.AddPlayer(&P1);
	bg.AddPlayer(&P2);

	//генерируем юнитов для 1-го игрока
	std::vector<TUnit*> unit_vec1;
	unit_vec1.resize(player_size);
	CreateSetOfUnits(&unit_vec1, P1.GetID());
	
	for (size_t i = 0; i < player_size; i++)
	{
		P1.AddUnit(unit_vec1[i]);
		bg.AddUnit(unit_vec1[i], i, 0);
		
	}

	//генерируем юнитов для 2-го игрока
	std::vector<TUnit*> unit_vec2;
	unit_vec2.resize(player_size);
	CreateSetOfUnits(&unit_vec2, P2.GetID());

	for (size_t i = 0; i < player_size; i++)
	{
		P2.AddUnit(unit_vec2[i]);
		bg.AddUnit(unit_vec2[i], i, 7);
	}
	std::string winner = "test";//имя победителя

	std::cout << "|||||||||||||||||||||||||||||||||||||||||||||\n";
	P1.PrintInfo();
	std::cout << "|||||||||||||||||||||||||||||||||||||||||||||\n";
	P2.PrintInfo();


    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Swords and frogs...");


	TKeyPressEvent key_pressed;
	key_pressed.Initialization(players_id, players_names);

	/////////Спрайт карты/////////
	sf::Image map_image;
	map_image.loadFromFile("images/map.png");
	sf::Texture map;
	map.loadFromImage(map_image);
	sf::Sprite s_map;
	s_map.setTexture(map);

	/////////Спрат выбранной клетки/////////
	sf::Image focus_tile_image;
	focus_tile_image.loadFromFile("images/focus_tile_tr.png");
	sf::Texture focus_tile_texture;
	focus_tile_texture.loadFromImage(focus_tile_image);
	sf::Sprite s_focus_tile;
	s_focus_tile.setTexture(focus_tile_texture);

	s_focus_tile.setTextureRect(sf::IntRect(0, 0, 90, 90));
	s_focus_tile.setPosition(83+ BATTLE_WIDTH_OFFSET-3, 83+ BATTLE_HEIGHT_OFFSET-3);

	key_pressed.SetFocusUnit(bg.GetFocusUnit());//по умолчанию выбранная клетка - 0,0

	/////////Спрайт юнитов/////////
	sf::Texture unit_map;
	unit_map.loadFromImage(map_image);
	sf::Sprite s_unit_map;
	s_unit_map.setTexture(unit_map);

	
	///////////Шрифт/////////////
	sf::Font font_SalsaRegular;
	font_SalsaRegular.loadFromFile("Salsa-Regular.ttf");

	sf::Font font_IMFellEnglishSCRegular;
	font_IMFellEnglishSCRegular.loadFromFile("IMFellEnglishSC-Regular.ttf");
	/*
	Text text("", font, 35);
	text.setFillColor(Color::Blue);//просто шаблон текста
	*/

	//------------------Main Menu---------------------//
	
	    /***Фигуры****/

	//Прямоугольник changelog
	sf::RectangleShape rectangle_changelog(sf::Vector2f(432.f, 568.f));
	rectangle_changelog.setFillColor(sf::Color(30, 65, 14, 107));
	rectangle_changelog.setOutlineColor(sf::Color(92, 128, 1));
	rectangle_changelog.setOutlineThickness(5);
	rectangle_changelog.setPosition(97, 305);

	//Прямоугольник play
	sf::RectangleShape rectangle_play(sf::Vector2f(781.f, 268.f));
	rectangle_play.setFillColor(sf::Color(255, 255, 255, 250));
	rectangle_play.setOutlineColor(sf::Color(92, 128, 1));
	rectangle_play.setOutlineThickness(5);
	rectangle_play.setPosition(570, 305);

	//Прямоугольник exit
	sf::RectangleShape rectangle_exit(sf::Vector2f(781.f, 268.f));
	rectangle_exit.setFillColor(sf::Color(255, 255, 255, 250));
	rectangle_exit.setOutlineColor(sf::Color(92, 128, 1));
	rectangle_exit.setOutlineThickness(5);
	rectangle_exit.setPosition(570, 605);

	//Прямоугольник feedback
	sf::RectangleShape rectangle_feedback(sf::Vector2f(432.f, 568.f));
	rectangle_feedback.setFillColor(sf::Color(30, 65, 14, 107));
	rectangle_feedback.setOutlineColor(sf::Color(92, 128, 1));
	rectangle_feedback.setOutlineThickness(5);
	rectangle_feedback.setPosition(1391, 305);

		/***Текст****/

	//кнопка играть
	sf::Text text_play("", font_IMFellEnglishSCRegular, 288);
	text_play.setString("Play");
	text_play.setFillColor(sf::Color::Black);//просто шаблон текста
	text_play.setPosition(687, 225);
	//копка выхода
	sf::Text text_exit("", font_IMFellEnglishSCRegular, 288);
	text_exit.setString("Exit");
	text_exit.setFillColor(sf::Color::Black);//просто шаблон текста
	text_exit.setPosition(672, 535);
	//название игры
	sf::Text text_name("", font_IMFellEnglishSCRegular, 96);
	text_name.setString("Swords and frogs...");
	text_name.setFillColor(sf::Color(251, 97, 7));//просто шаблон текста
	text_name.setPosition(600, 50);
	//feedback
	sf::Text text_feedback("", font_IMFellEnglishSCRegular, 60);
	text_feedback.setString("FEEDBACK");
	text_feedback.setFillColor(sf::Color(227, 145, 21));//просто шаблон текста
	text_feedback.setPosition(1425, 230);
	//feedback text
	sf::Text text_feedback_text("", font_SalsaRegular, 36);
	text_feedback_text.setString("Do you have any bugs,\ncool ideas or general\nfeedback?\nSend me a massage \non my mail:\nsosorii2002@gmail.ru");
	text_feedback_text.setFillColor(sf::Color::White);//просто шаблон текста
	text_feedback_text.setPosition(1400, 305);
	//changelog
	sf::Text text_changelog("", font_IMFellEnglishSCRegular, 60);
	text_changelog.setString("CHANGELOG");
	text_changelog.setFillColor(sf::Color(227, 145, 21));//просто шаблон текста
	text_changelog.setPosition(100, 230);
	//changelog text
	sf::Text text_changelog_text("", font_SalsaRegular, 24);
	std::string changelog_str = "v 0.1.1\n -added TUnit, TSwordsman and \n   TBattleGround classes.\n";
	changelog_str += "v 0.2.1\n -added SFML, battleground display\n   and units on it.\n";
	changelog_str += "v 0.2.2\n -added selected tile,\n   info about selected unit\n";
	changelog_str += "v 0.4.1 \n -added main menu\n";
	changelog_str += "v 0.5.1 \n -added win screen, turn mechanic\n";
	changelog_str += "v 0.7.1 \n -added exit confrim display\n";
	changelog_str += "v 0.8.1 \n -added after battle statistic\n";
	changelog_str += "v 0.9.1 \n -added history";
	text_changelog_text.setString(changelog_str);
	text_changelog_text.setFillColor(sf::Color::White);//просто шаблон текста
	text_changelog_text.setPosition(105, 305);

		//***Картинки***//
	sf::Image menu_image;
	menu_image.loadFromFile("images/menu.png");
	sf::Texture meny_texture;
	meny_texture.loadFromImage(menu_image);
	sf::Sprite s_menu;
	s_menu.setTexture(meny_texture);
	//------------------Exit Menu---------------------//

		/***Фигуры****/

	//большой прямоугольнки
	sf::RectangleShape rectangle_exit_confirm(sf::Vector2f(736.f, 187.f));
	rectangle_exit_confirm.setFillColor(sf::Color(255,255,255));
	rectangle_exit_confirm.setOutlineColor(sf::Color(92, 128, 1, 250));
	rectangle_exit_confirm.setOutlineThickness(5);
	rectangle_exit_confirm.setPosition(590, 445);

	//прямоугольник да
	sf::RectangleShape rectangle_yes(sf::Vector2f(250.f, 130.f));
	rectangle_yes.setFillColor(sf::Color(30, 65, 14, 20));
	rectangle_yes.setPosition(640, 472);

	//прямоугольник нет
	sf::RectangleShape rectangle_no(sf::Vector2f(250.f, 130.f));
	rectangle_no.setFillColor(sf::Color(30, 65, 14, 20));
	rectangle_no.setPosition(1005, 472);

		/***Текст****/
	//подтверждение выхода
	sf::Text text_exit_confirm("", font_IMFellEnglishSCRegular, 64);
	text_exit_confirm.setString("Are you sure you want to exit?");
	text_exit_confirm.setFillColor(sf::Color(251, 97, 7));
	text_exit_confirm.setPosition(550, 350);

	//да
	sf::Text text_yes("", font_IMFellEnglishSCRegular, 80);
	text_yes.setString("Yes");
	text_yes.setFillColor(sf::Color(0,0,0));
	text_yes.setPosition(675, 472);

	//нет
	sf::Text text_no("", font_IMFellEnglishSCRegular, 80);
	text_no.setString("No");
	text_no.setFillColor(sf::Color(0, 0,0));
	text_no.setPosition(1040, 472);

	//------------------Battle---------------------//
		/***Фигуры****/

	//История
	sf::RectangleShape rectangle_history(sf::Vector2f(400.f, 830.f));
	rectangle_history.setOutlineColor(sf::Color(92, 128, 1));
	rectangle_history.setOutlineThickness(5);
	rectangle_history.setFillColor(sf::Color(124, 181, 24, 110));
	rectangle_history.setPosition(80, 50);

	//Информация о герое
	sf::RectangleShape rectangle_unit_info(sf::Vector2f(400.f, 280.f));
	rectangle_unit_info.setOutlineColor(sf::Color(92, 128, 1));
	rectangle_unit_info.setOutlineThickness(5);
	rectangle_unit_info.setFillColor(sf::Color(124, 181, 24, 110));
	rectangle_unit_info.setPosition(1440, 50);

	sf::RectangleShape rectangle_unit_abilities(sf::Vector2f(850.f, 100.f));
	rectangle_unit_abilities.setOutlineColor(sf::Color(92, 128, 1));
	rectangle_unit_abilities.setOutlineThickness(5);
	rectangle_unit_abilities.setFillColor(sf::Color(124, 181, 24, 110));
	rectangle_unit_abilities.setPosition(545, 950);

		/***Текст****/
	
	//время по нажатию TAB
	sf::Text tab_text("", font_SalsaRegular, 20);
	tab_text.setFillColor(sf::Color(251, 97, 7));//текст при табуляции
	tab_text.setPosition(875, 10);

	//информация о выбранной клетке
	sf::Text focus_tile_text("", font_SalsaRegular, 25);
	focus_tile_text.setFillColor(sf::Color::White);//информация о текущей выбранной клетки
	focus_tile_text.setPosition(1445, 50);
	//загаловок история 
	sf::Text history_header_text("", font_IMFellEnglishSCRegular, 36);
	 history_header_text.setFillColor(sf::Color(227, 145, 21));//информация о возможностях юнита
	 history_header_text.setString("Actions history:");
	 history_header_text.setPosition(80, 7);

	 //сама истори 
	 sf::Text history_text("", font_SalsaRegular, 36);
	 history_text.setString("test");
	 history_text.setFillColor(sf::Color::White);//информация о возможностях юнита
	 history_text.setPosition(85, 48);

	 //загаловок "информация о юните"
	 sf::Text unit_info_header_text("", font_IMFellEnglishSCRegular, 36);
	 unit_info_header_text.setFillColor(sf::Color(227, 145, 21));//информация о возможностях юнита
	 unit_info_header_text.setString("Unit Information:");
	 unit_info_header_text.setPosition(1442, 7);

	//загаловок "Действия"
	 sf::Text unit_actions_header_text("", font_IMFellEnglishSCRegular, 48);
	unit_actions_header_text.setFillColor(sf::Color(227, 145, 21));//информация о возможностях юнита
	unit_actions_header_text.setString("Actions:");
	unit_actions_header_text.setPosition(550, 890);
	//сами действия
	sf::Text unit_actions("", font_SalsaRegular, 25);
	unit_actions.setFillColor(sf::Color::White);//информация о возможностях юнита
	unit_actions.setPosition(550, 950);

	//исключения
	sf::Text exceptions("", font_SalsaRegular, 22);
	exceptions.setFillColor(sf::Color(251, 97, 7));//информацию об ошибках
	exceptions.setPosition(1440, 530);

	//чья очеред ходить
	sf::Text t_turn("", font_SalsaRegular, 25);
	t_turn.setFillColor(sf::Color(251, 97, 7));//информацию об ошибках
	t_turn.setPosition(1440, 500);
		/***Картинки***/
	sf::Image battle_image;
	battle_image.loadFromFile("images/battle.png");
	sf::Texture battle_texture;
	battle_texture.loadFromImage(battle_image);
	sf::Sprite s_battle;
	s_battle.setTexture(battle_texture);

	//------------------WIN---------------------//
 
		/***Фигуры****/

	//Статистика
	sf::RectangleShape rectangle_statistics(sf::Vector2f(540.f, 652.f));
	rectangle_statistics.setOutlineColor(sf::Color(92, 128, 1));
	rectangle_statistics.setOutlineThickness(5);
	rectangle_statistics.setFillColor(sf::Color(124, 181, 24, 85));
	rectangle_statistics.setPosition(102, 280);

	
		/***Текст****/
	
	sf::Text text_winner("", font_IMFellEnglishSCRegular, 144);
	text_winner.setFillColor(sf::Color(251, 97, 7));//информацию об ошибках
	text_winner.setPosition(370, 20);

	sf::Text statistic_header_text("", font_IMFellEnglishSCRegular, 64);
	statistic_header_text.setString("Statistic:");
	statistic_header_text.setFillColor(sf::Color(227, 145, 21));//информацию об ошибках
	statistic_header_text.setPosition(110, 200);

	sf::Text statistic_text("", font_SalsaRegular, 40);
	statistic_text.setFillColor(sf::Color::White);//информацию об ошибках
	statistic_text.setPosition(116, 292);

	std::string statistic = "test";
	statistic_text.setString(statistic);

	sf::Text exit_to_main_menu_text("", font_SalsaRegular, 36);
	exit_to_main_menu_text.setString("Press Esc to exit to the main menu");
	exit_to_main_menu_text.setFillColor(sf::Color::Black);//информацию об ошибках
	exit_to_main_menu_text.setPosition(711, 963);



		/***Красивая картинка***/
	sf::Image win_image;
	win_image.loadFromFile("images/win_texture.png");
	sf::Texture win_texture;
	win_texture.loadFromImage(win_image);
	sf::Sprite s_win;
	s_win.setTexture(win_texture);
	s_win.setTextureRect(sf::IntRect(0, 0, 1160, 652));
	s_win.setPosition(687,280);


	sf::Image win_b_image;
	win_b_image.loadFromFile("images/win.png");
	sf::Texture win_b_texture;
	win_b_texture.loadFromImage(win_b_image);
	sf::Sprite s_win_b;
	s_win_b.setTexture(win_b_texture);

	sf::Clock clock;
	
	///обаботка ошибок
	sf::Clock exception_clock;

	bool show_exceptions=false;
	int exceptions_time = 0;

	int time_s=0;
	int game_time = 0;

	enum { MENU, BATTLE, WIN, CLOSE }EDislpay;

	EDislpay = WIN;

	bool show_exit=false;

	while (window.isOpen())//3 цикла вложенных
	{
		sf::Event event;//переменная-событие
		std::cout << "window : " << window.isOpen() << "\n";
		if (EDislpay == CLOSE)
		{
			window.close();
		}
		while (EDislpay==MENU)
		{
			window.clear(sf::Color(14, 42, 71));

			while (window.pollEvent(event)) 
			{
				if (event.type == sf::Event::Closed)//если мы  каким то способом сгенерировали  событие "закрытие" , то закрываем окно
				{
					std::cout << "window is closed";
					EDislpay = CLOSE;
				}
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code== sf::Keyboard::Escape)
					{
						switch (show_exit)
						{
						case true://если уже показываем подтверждение выхода то выходим из этого меню				
						{
							show_exit = false;
							break;
						}
						case false://если не показываем меную выхода,то начинаем его показывать
						{
							show_exit = true;
							break;
						}
						default:
							break;
						}

					}
					if ((event.key.code == sf::Keyboard::Up) || (event.key.code == sf::Keyboard::Down))
					{//если нажаты стрелки
						if (show_exit==false)
						{
							key_pressed.ArrowsPressdMenu(event);
						}
					}
					if ((event.key.code == sf::Keyboard::Left) || (event.key.code == sf::Keyboard::Right))
					{//если нажаты стрелки
						if (show_exit==true)
						{
							key_pressed.ArrowsPressedExit(event);
						}		
					}
					if(event.key.code == sf::Keyboard::Enter)
					{//если клавиша Enter

						switch (show_exit)
						{
								case true://если уже показываем подтверждение выхода то выходим из этого меню				
								{
									switch (key_pressed.GetExit())
									{
									case true://если подтверждаем то выходим
									{
										EDislpay = CLOSE;
										break;
									}
									case false://иначе выходим из подтверждения выхода
									{
										show_exit = false;
										break;
									}
									default:
										break;
									}
									break;
								}

								case false://если не показываем меную выхода,то начинаем его показывать
								{
									switch (key_pressed.GetMenuState())
									{
									case 2:
									{
										EDislpay = BATTLE;
										break;
									}
									case 1:
									{
										show_exit = true;
										break;
									}
									default:
										break;
									}
								}
							default:
								break;
							}
					}
				}

			}
		std::cout << "Menu:" << key_pressed.GetMenuState();
		std::cout << "	Exit:" << show_exit << "\n";
			key_pressed.UpdateSelectMenu(&text_play, &text_exit);
			
			///Рисуем задний фон///
			window.draw(s_menu);

			///Рисуем прямоугольнки///
			window.draw(rectangle_changelog);
			window.draw(rectangle_feedback);
			window.draw(rectangle_play); 
			window.draw(rectangle_exit);

			///Рисуем текст///
			window.draw(text_play);
			window.draw(text_exit);
			window.draw(text_name);
			window.draw(text_changelog_text);
			window.draw(text_changelog);
			window.draw(text_feedback);
			window.draw(text_feedback_text);

			///Рисуем выход///
			if (show_exit == true)
			{
				key_pressed.UpdateExitConfirm(&text_yes, &text_no);

				///прямоугольники///
				window.draw(rectangle_exit_confirm);
				window.draw(rectangle_yes);
				window.draw(rectangle_no);

				///текст///
				window.draw(text_exit_confirm);
				window.draw(text_yes);
				window.draw(text_no);	

			}
			
			window.display(); 
		}

		while (EDislpay == BATTLE)
		{
			///////////////////////////////Отображение исключений/////////////////////
			if (show_exceptions == true)
			{
				exceptions_time += exception_clock.getElapsedTime().asMicroseconds();
				//std::cout << "exceptions_time=" + std::to_string(exceptions_time)<<std::endl;
			}
			if (exceptions_time >= 3000000)
			{

				key_pressed.SetException(ALL_OK);
				exceptions_time = 0;
			}

			time_s = clock.getElapsedTime().asSeconds();
		//	std::cout << "time =" << time_s << std::endl;

			exception_clock.restart();
			//	clock.restart();

			window.clear(sf::Color(255,255,255));

			///////////////////////////////Обработка клавиш/////////////////////
			while (window.pollEvent(event))//если никакого события не произошло, то в цикл не попадаем
			{
				if (event.type == sf::Event::Closed)//если мы  каким то способом сгенерировали  событие "закрытие" , то закрываем окно
				{
					EDislpay = CLOSE;
				}
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						std::cout << "Return to menu";
						EDislpay = MENU;
						//window.close();
					}
					if ((event.key.code == sf::Keyboard::Tab))
					{//если клавиша ТАБ
						key_pressed.PressedTab(&tab_text, &time_s);
					}
					if ((event.key.code == sf::Keyboard::Left) || (event.key.code == sf::Keyboard::Right) 
						|| (event.key.code == sf::Keyboard::Up) || (event.key.code == sf::Keyboard::Down))
					{//если нажаты стрелки
						key_pressed.ArrowsPressd(&bg, &s_focus_tile, event);
					}
					if ((event.key.code == sf::Keyboard::Enter))
					{//если клавиша Enter
						key_pressed.PressedEnter(&bg);
					}
					if ((event.key.code == sf::Keyboard::M))
					{//если клавиша M
						key_pressed.PressedM(&bg);
					}
					if (event.key.code == sf::Keyboard::A)
					{//если клавиша A
						key_pressed.PressedA(&bg);
					}
				}
			}

			///////////////////////////////Рисуем карту/////////////////////

			window.draw(s_battle);//рисуем задник

			for (int i = 0; i < HEIGHT_MAP; i++)
			{
				for (int j = 0; j < WIDTH_MAP; j++)
				{
					if ((bg.TileBackgroundMap[i][j] == '0')) s_map.setTextureRect(sf::IntRect(166, 0, 83, 83));
					if ((bg.TileBackgroundMap[i][j] == ' ')) s_map.setTextureRect(sf::IntRect(0, 0, 83, 83));
					if ((bg.TileBackgroundMap[i][j] == 's')) s_map.setTextureRect(sf::IntRect(83, 0, 83, 83));


					s_map.setPosition(j * 83 + BATTLE_WIDTH_OFFSET, i * 83 + BATTLE_HEIGHT_OFFSET);
					window.draw(s_map);
				}
			}
			///////////////////////////////Рисуем юнитов/////////////////////
			bg.FillUnitsMap();//заполняем карту юнитами
			for (int i = 0; i < HEIGHT_MAP - 2; i++)
			{
				for (int j = 0; j < WIDTH_MAP - 2; j++)
				{
					if (bg.TileUnitsMap[i][j] == 'A')  s_unit_map.setTextureRect(sf::IntRect(249, 0, 83, 83));
					if (bg.TileUnitsMap[i][j] == 'S')  s_unit_map.setTextureRect(sf::IntRect(332, 0, 83, 83));

					if (bg.TileUnitsMap[i][j] == ' ')
					{
						continue;
					}
					s_unit_map.setPosition((j * 83) + 83+ BATTLE_WIDTH_OFFSET, (i * 83) + 83 + BATTLE_HEIGHT_OFFSET);
					window.draw(s_unit_map);
				}

			}

			///////////////////////////////Проверка на победу/////////////////////
			if ( (P2.GetNumberOfUnits()==0)||(P1.GetNumberOfUnits()==0) )
			{
				if (P2.GetNumberOfUnits() == 0)
				{
					winner = P1.GetName();
					
				}
				else if (P1.GetNumberOfUnits() == 0)
				{
					winner = P2.GetName();
				}
				
				statistic = "Total time played:  " + std::to_string(time_s / 60) + ":" + std::to_string(time_s - (time_s / 60) * 60) +
					"\nPlayer "+ P1.GetName() + " killed " +
					std::to_string(player_size-P2.GetNumberOfUnits())+" units\n" + "Player " + P2.GetName() + " killed " +
					std::to_string(player_size - P1.GetNumberOfUnits()) + " units\n";
				statistic_text.setString(statistic);
				EDislpay = WIN;
			}

			//std::cout << "Number of units P2: " << P2.GetNumberOfUnits() << "\n";
			///////////////////////////////Обновляем тексты/////////////////////
			key_pressed.UpdateTilesText(&bg, &focus_tile_text, &tab_text, bg.GetInfoAboutTile());
			key_pressed.UpdateUnitAbilitiesText(&unit_actions);
			key_pressed.UpdateExceptions(&exceptions, &show_exceptions, &exceptions_time);
			key_pressed.UpdateTimer(&tab_text, &time_s);
			history_text.setString(key_pressed.GetHistory());

		
			t_turn.setString("Turn: "+ key_pressed.GetName());

		
			///Рисуем прямоугольники///
			window.draw(rectangle_history);
			window.draw(rectangle_unit_info);
			window.draw(rectangle_unit_abilities);
			
			///Рисуем тексты ///
			window.draw(focus_tile_text);
			window.draw(unit_actions_header_text);	
			window.draw(unit_actions);
			window.draw(tab_text);
			window.draw(t_turn);
		
		//	window.draw();

			window.draw(history_header_text);
			window.draw(history_text);
			
			window.draw(unit_info_header_text);
				
			///Рисуем выбраннуб клетку///
			window.draw(s_focus_tile);

			///Рисуем исключения///
			window.draw(exceptions);
			window.display();

		}
		
		while (EDislpay == WIN)
		{
			window.clear(sf::Color(255, 255, 255));
			while (window.pollEvent(event))
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					std::cout << "Return to menu";

					CreateSetOfUnits(&unit_vec1, P1.GetID());
					CreateSetOfUnits(&unit_vec2, P2.GetID());

					if((P1.GetNumberOfUnits()==0)||(P2.GetNumberOfUnits() == 0))
					{
						bg.ClearAllUnits();
						key_pressed.ClearHistory();

						for (size_t i = 0; i < player_size; i++)
						{
							P1.AddUnit(unit_vec1[i]);
							bg.AddUnit(unit_vec1[i], i, 0);

						}

						for (size_t i = 0; i < player_size; i++)
						{
							P2.AddUnit(unit_vec2[i]);
							bg.AddUnit(unit_vec2[i], i, 7);
						}
					}
					

					EDislpay = MENU;
				}
				if (event.type == sf::Event::Closed)//если мы  каким то способом сгенерировали  событие "закрытие" , то закрываем окно
				{
					EDislpay = CLOSE;
				}
			}

			window.draw(s_win_b);
			
			window.draw(rectangle_statistics);
			

		
			text_winner.setString("The winner is: "+winner);

			window.draw(text_winner);
			window.draw(statistic_header_text);
			window.draw(statistic_text);
			
			window.draw(exit_to_main_menu_text);
			

			window.draw(s_win);

			
			
			window.display();
		}
	}
  
    std::cout << "Hello World!\n";
}
