#include <iostream>
#include <vector>
#include <sstream>
#include "TBattleground.h"
#include "TArcher.h"
#include "TSwordsman.h"
#include "KeyPressEvent.h"
#include "Player.h"
#include <windows.h>
//#include "TView.h"
#include <SFML/Graphics.hpp>
using namespace sf;

enum { MENU, INITIALISATION, BATTLE, WIN, CLOSE }EDislpay;

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

/**
72 255 213 зелёный
14 42 71 синий
*/
int main()
{
    TBattleground bg;

	TSwordsman SwA;
	TSwordsman SwB;

	TArcher ArA;
	TArcher ArB;

	TPlayer P1(1, "Bogdan");
	TPlayer P2(2, "ZXC");
	int player_size = 2;

	bg.AddPlayer(&P1);
	bg.AddPlayer(&P2);

	std::vector<TUnit*> unit_vec1;
	unit_vec1.resize(player_size);
	CreateSetOfUnits(&unit_vec1, P1.GetID());
	
	for (size_t i = 0; i < player_size; i++)
	{
		P1.AddUnit(unit_vec1[i]);
		bg.AddUnit(unit_vec1[i], i, 0);
		
	}

	std::vector<TUnit*> unit_vec2;
	unit_vec2.resize(player_size);
	CreateSetOfUnits(&unit_vec2, P2.GetID());

	for (size_t i = 0; i < player_size; i++)
	{
		P2.AddUnit(unit_vec2[i]);
		bg.AddUnit(unit_vec2[i], i, 7);

	}
	std::string winner = "\0";

	std::cout << "|||||||||||||||||||||||||||||||||||||||||||||\n";
	P1.PrintInfo();
	std::cout << "|||||||||||||||||||||||||||||||||||||||||||||\n";
	P2.PrintInfo();

//	P2.DeleteUnit(unit_vec2[2]);

	//TUnit* unit;
	//GenerateUnit(&unit_vec1[0], "Swordsman", 1);

	/*bg.AddUnit(&ArA, 4, 4);
	bg.PrintUnits();
	bg.AddUnit(&ArB, 0, 0);
	bg.PrintUnits();
	bg.GetInfoAboutTile(1, 0);
	bg.PrintUnits();
	bg.Move(&ArA, 5, 5);
	bg.PrintUnits();
	bg.Move(&ArA, 6, 6);
	bg.PrintUnits();
	bg.Move(&ArA, 7, 7);
	bg.PrintUnits();
	bg.Move(&ArA, 0, 7);
	bg.PrintUnits();
	bg.Move(&ArA, 4, 6);
	bg.PrintUnits();
	bg.AddUnit(&SwA, 4, 3);
	bg.AddUnit(&SwB, 5, 7);
	bg.PrintUnits();*/


    RenderWindow window(sf::VideoMode(1920, 1080), "Swords and other stuff...");


	TKeyPressEvent key_pressed;

	/////////Спрайт подтверждения выхода/////////
	Image menu_exit_confirm_image;
	menu_exit_confirm_image.loadFromFile("images/confirm_exit.png");
	Texture menu_exit_confirm_texture;
	menu_exit_confirm_texture.loadFromImage(menu_exit_confirm_image);
	Sprite s_confrim_exit;
	s_confrim_exit.setTexture(menu_exit_confirm_texture);
	/////////Спрайт селектора меню/////////
	Image select_menu_image;
	select_menu_image.loadFromFile("images/selc.png");
	Texture select_menu_texture;
	select_menu_texture.loadFromImage(select_menu_image);
	Sprite s_select_menu;
	s_select_menu.setTexture(select_menu_texture);
	/////////Спрайт меню/////////
	Image menu_image;
	menu_image.loadFromFile("images/menu.png");
	Texture menu;
	menu.loadFromImage(menu_image);
	Sprite s_menu;
	s_menu.setTexture(menu);

	/////////Спрайт карты/////////
	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	/////////Спрат выбранной клетки/////////
	Image focus_tile_image;
	focus_tile_image.loadFromFile("images/focus_tile_tr.png");
	Texture focus_tile_texture;
	focus_tile_texture.loadFromImage(focus_tile_image);
	Sprite s_focus_tile;
	s_focus_tile.setTexture(focus_tile_texture);

	s_focus_tile.setTextureRect(sf::IntRect(0, 0, 64, 64));
	s_focus_tile.setPosition(64, 64);

	key_pressed.SetFocusUnit(bg.GetFocusUnit());//по умолчанию выбранная клетка - 0,0


	/////////Спрайт юнитов/////////
	Texture unit_map;
	unit_map.loadFromImage(map_image);

	Sprite s_unit_map;
	s_unit_map.setTexture(unit_map);

	
	///////////Шрифт и тексты/////////////
	Font font;
	font.loadFromFile("MilknBalls-BlackDemo.ttf");//шрифт

	Text tab_text("", font, 20);
	tab_text.setFillColor(Color(255, 10, 10));//текст при табуляции

	Text text("", font, 35);
	text.setFillColor(Color::Blue);//просто шаблон текста

	Text unit_info_text("", font, 20);
	unit_info_text.setFillColor(Color(72, 255, 213));//информация о юните

	Text focus_tile_text("", font, 22);
	focus_tile_text.setFillColor(Color::White);//информация о текущей выбранной клетки

	Text unit_abilities("", font, 25);
	unit_abilities.setFillColor(Color::White);//информация о возможностях юнита

	Text exceptions("", font, 25);
	exceptions.setFillColor(Color::Red);//информацию об ошибках


	Text text_winner("", font, 25);
	text_winner.setFillColor(Color::Red);//информацию об ошибках

	Clock clock;
	
	///обаботка ошибок
	Clock exception_clock;

	bool show_exceptions=false;
	int exceptions_time = 0;

	int time_s=0;

	EDislpay = MENU;

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
			window.clear(Color(14, 42, 71));

			while (window.pollEvent(event)) 
			{
				if (event.type == sf::Event::Closed)//если мы  каким то способом сгенерировали  событие "закрытие" , то закрываем окно
				{
					std::cout << "window is closed";
					window.close();
				}
				if (event.type == Event::KeyPressed)
				{
					if (event.key.code==Keyboard::Escape)
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
					if ((event.key.code == Keyboard::Up) || (event.key.code == Keyboard::Down))
					{//если нажаты стрелки
						if (show_exit==false)
						{
							key_pressed.ArrowsPressdMenu(event);
						}
					}
					if ((event.key.code == Keyboard::Left) || (event.key.code == Keyboard::Right))
					{//если нажаты стрелки
						if (show_exit==true)
						{
							key_pressed.ArrowsPressedExit(event);
						}		
					}
					if(event.key.code == Keyboard::Enter)
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
			key_pressed.UpdateSelectMenu(&s_select_menu);
			window.draw(s_menu);
			window.draw(s_select_menu);
			if (show_exit==true)
			{
				window.draw(s_confrim_exit);
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

			window.clear(Color(14, 42, 71));

			///////////////////////////////Обработка клавиш/////////////////////
			while (window.pollEvent(event))//если никакого события не произошло, то в цикл не попадаем
			{
				if (event.type == sf::Event::Closed)//если мы  каким то способом сгенерировали  событие "закрытие" , то закрываем окно
				{
					std::cout << "window is closed";
					window.close();
				}
				if (event.type == Event::KeyPressed)
				{
					if (event.key.code == Keyboard::Escape)
					{
						std::cout << "Return to menu";
						EDislpay = MENU;
						//window.close();
					}
					if ((event.key.code == Keyboard::Tab))
					{//если клавиша ТАБ
						key_pressed.PressedTab(&tab_text, &time_s);
					}
					if ((event.key.code == Keyboard::Left) || (event.key.code == Keyboard::Right) || (event.key.code == Keyboard::Up) || (event.key.code == Keyboard::Down))
					{//если нажаты стрелки
						key_pressed.ArrowsPressd(&bg, &s_focus_tile, event);
					}
					if ((event.key.code == Keyboard::Enter))
					{//если клавиша Enter
						key_pressed.PressedEnter(&bg);
					}
					if ((event.key.code == Keyboard::M))
					{//если клавиша M
						key_pressed.PressedM(&bg);
					}
					if (event.key.code == Keyboard::A)
					{//если клавиша A
						key_pressed.PressedA(&bg);
					}
				}
			}

			///////////////////////////////Рисуем карту/////////////////////
			for (int i = 0; i < HEIGHT_MAP; i++)
			{
				for (int j = 0; j < WIDTH_MAP; j++)
				{
					if ((bg.TileBackgroundMap[i][j] == '0')) s_map.setTextureRect(IntRect(128, 0, 64, 64));
					if ((bg.TileBackgroundMap[i][j] == ' ')) s_map.setTextureRect(IntRect(0, 0, 64, 64));
					if ((bg.TileBackgroundMap[i][j] == 's')) s_map.setTextureRect(IntRect(64, 0, 64, 64));


					s_map.setPosition(j * 64, i * 64);
					window.draw(s_map);
				}
			}
			///////////////////////////////Рисуем юнитов/////////////////////
			bg.FillUnitsMap();//заполняем карту юнитами
			for (int i = 0; i < HEIGHT_MAP - 2; i++)
			{
				for (int j = 0; j < WIDTH_MAP - 2; j++)
				{
					if (bg.TileUnitsMap[i][j] == 'A')  s_unit_map.setTextureRect(IntRect(192, 0, 64, 64));
					if (bg.TileUnitsMap[i][j] == 'S')  s_unit_map.setTextureRect(IntRect(256, 0, 64, 64));

					if (bg.TileUnitsMap[i][j] == ' ')
					{
						continue;
					}
					s_unit_map.setPosition((j * 64) + 64, (i * 64) + 64);
					window.draw(s_unit_map);
				}

			}

			///////////////////////////////Проверка на победу/////////////////////
			if ( (P2.GetNumberOfUnits()==0)||(P1.GetNumberOfUnits()==0) )
			{
				if (P2.GetNumberOfUnits() == 0)
				{
					winner = P2.GetName();
				}
				else if (P1.GetNumberOfUnits() == 0)
				{
					winner = P1.GetName();
				}
				EDislpay = WIN;
			}

			std::cout << "Number of units P2: " << P2.GetNumberOfUnits() << "\n";
			///////////////////////////////Обновляем тексты/////////////////////
			key_pressed.UpdateTilesText(&bg, &focus_tile_text, &tab_text, &unit_info_text, bg.GetInfoAboutTile());
			key_pressed.UpdateUnitAbilitiesText(&unit_abilities);
			key_pressed.UpdateExceptions(&exceptions, &show_exceptions, &exceptions_time);
			key_pressed.UpdateTimer(&tab_text, &time_s);

			///Рисуем тексты ///
			window.draw(focus_tile_text);
			window.draw(unit_info_text);
			window.draw(unit_abilities);
			window.draw(tab_text);
			///Рисуем выбраннуб клетку///
			window.draw(s_focus_tile);

			///Рисуем исключения///
			window.draw(exceptions);
			window.display();

		}
		while (EDislpay == INITIALISATION)
		{
			window.clear(Color(14, 42, 71));

			while (window.pollEvent(event))
			{

			}

		}

		while (EDislpay == WIN)
		{
			window.clear(Color(14, 42, 71));
			while (window.pollEvent(event))
			{
				if (event.key.code == Keyboard::Escape)
				{
					std::cout << "Return to menu";
					EDislpay = MENU;
				}
			}

			text_winner.setPosition(900, 500);
			text_winner.setString(winner);

			window.draw(text_winner);
			window.display();
		}
	}
  
    std::cout << "Hello World!\n";
}
