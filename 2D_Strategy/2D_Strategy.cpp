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
72 255 213 ������
14 42 71 �����
*/
int main()
{
    TBattleground bg;

	TSwordsman SwA;
	TSwordsman SwB;

	TArcher ArA;
	TArcher ArB;


	TPlayer P1(58, "Bogdan");
	TPlayer P2(69, "ZXC");

	

	int players_id[MAX_NUMBER_OF_PLAYERS] = {P1.GetID(),P2.GetID()};//������ � id �������

	int player_size = 1;//���������� ���������� � ������

	//��������� �� ���� �������
	bg.AddPlayer(&P1);
	bg.AddPlayer(&P2);

	//���������� ������ ��� 1-�� ������
	std::vector<TUnit*> unit_vec1;
	unit_vec1.resize(player_size);
	CreateSetOfUnits(&unit_vec1, P1.GetID());
	
	for (size_t i = 0; i < player_size; i++)
	{
		P1.AddUnit(unit_vec1[i]);
		bg.AddUnit(unit_vec1[i], i, 0);
		
	}

	//���������� ������ ��� 2-�� ������
	std::vector<TUnit*> unit_vec2;
	unit_vec2.resize(player_size);
	CreateSetOfUnits(&unit_vec2, P2.GetID());

	for (size_t i = 0; i < player_size; i++)
	{
		P2.AddUnit(unit_vec2[i]);
		bg.AddUnit(unit_vec2[i], i, 7);

	}
	std::string winner = "\0";//��� ����������

	std::cout << "|||||||||||||||||||||||||||||||||||||||||||||\n";
	P1.PrintInfo();
	std::cout << "|||||||||||||||||||||||||||||||||||||||||||||\n";
	P2.PrintInfo();


    RenderWindow window(sf::VideoMode(1920, 1080), "Swords and other stuff...");


	TKeyPressEvent key_pressed;
	key_pressed.Initialization(players_id);

	/////////������ �����/////////
	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	/////////����� ��������� ������/////////
	Image focus_tile_image;
	focus_tile_image.loadFromFile("images/focus_tile_tr.png");
	Texture focus_tile_texture;
	focus_tile_texture.loadFromImage(focus_tile_image);
	Sprite s_focus_tile;
	s_focus_tile.setTexture(focus_tile_texture);

	s_focus_tile.setTextureRect(sf::IntRect(0, 0, 64, 64));
	s_focus_tile.setPosition(64, 64);

	key_pressed.SetFocusUnit(bg.GetFocusUnit());//�� ��������� ��������� ������ - 0,0

	/////////������ ������/////////
	Texture unit_map;
	unit_map.loadFromImage(map_image);

	Sprite s_unit_map;
	s_unit_map.setTexture(unit_map);

	
	///////////����� � ������/////////////
	Font font_SalsaRegular;
	font_SalsaRegular.loadFromFile("Salsa-Regular.ttf");

	Font font_IMFellEnglishSCRegular;
	font_IMFellEnglishSCRegular.loadFromFile("IMFellEnglishSC-Regular.ttf");
	/*
	Text text("", font, 35);
	text.setFillColor(Color::Blue);//������ ������ ������
	*/

	//------------------Main Menu---------------------//
	
	    /***������****/

	//������������� changelog
	sf::RectangleShape rectangle_changelog(sf::Vector2f(432.f, 568.f));
	rectangle_changelog.setFillColor(Color(255,255,255,150));
	rectangle_changelog.setPosition(97, 305);

	//������������� play
	sf::RectangleShape rectangle_play(sf::Vector2f(781.f, 268.f));
	rectangle_play.setFillColor(Color(255, 255, 255, 150));
	rectangle_play.setPosition(570, 305);

	//������������� exit
	sf::RectangleShape rectangle_exit(sf::Vector2f(781.f, 268.f));
	rectangle_exit.setFillColor(Color(255, 255, 255, 150));
	rectangle_exit.setPosition(570, 605);

	//������������� feedback
	sf::RectangleShape rectangle_feedback(sf::Vector2f(432.f, 568.f));
	rectangle_feedback.setFillColor(Color(255, 255, 255, 150));
	rectangle_feedback.setPosition(1391, 305);

		/***�����****/

	//������ ������
	Text text_play("", font_IMFellEnglishSCRegular, 288);
	text_play.setString("Play");
	text_play.setFillColor(Color::Black);//������ ������ ������
	text_play.setPosition(687, 225);
	//����� ������
	Text text_exit("", font_IMFellEnglishSCRegular, 288);
	text_exit.setString("Exit");
	text_exit.setFillColor(Color::Black);//������ ������ ������
	text_exit.setPosition(672, 535);
	//�������� ����
	Text text_name("", font_IMFellEnglishSCRegular, 96);
	text_name.setString("Swords and other stuff...");
	text_name.setFillColor(Color::Red);//������ ������ ������
	text_name.setPosition(465, 50);
	//feedback
	Text text_feedback("", font_IMFellEnglishSCRegular, 60);
	text_feedback.setString("FEEDBACK");
	text_feedback.setFillColor(Color::Black);//������ ������ ������
	text_feedback.setPosition(1425, 230);
	//feedback text
	Text text_feedback_text("", font_SalsaRegular, 36);
	text_feedback_text.setString("Do you have any bugs,\ncool ideas or general\nfeedback?\nSend me a massage \non my mail:\nsosorii2002@gmail.ru");
	text_feedback_text.setFillColor(Color::Red);//������ ������ ������
	text_feedback_text.setPosition(1400, 305);
	//changelog
	Text text_changelog("", font_IMFellEnglishSCRegular, 60);
	text_changelog.setString("CHANGELOG");
	text_changelog.setFillColor(Color::Black);//������ ������ ������
	text_changelog.setPosition(100, 230);
	//changelog text
	Text text_changelog_text("", font_SalsaRegular, 36);
	text_changelog_text.setString("v 0.1.\n -added TUnit class.\n");
	text_changelog_text.setFillColor(Color::Red);//������ ������ ������
	text_changelog_text.setPosition(105, 305);

	//------------------Exit Menu---------------------//

		/***������****/

	//������� �������������
	sf::RectangleShape rectangle_exit_confirm(sf::Vector2f(736.f, 187.f));
	rectangle_exit_confirm.setFillColor(Color(255, 255, 255, 250));
	rectangle_exit_confirm.setPosition(590, 445);

	//������������� ��
	sf::RectangleShape rectangle_yes(sf::Vector2f(250.f, 130.f));
	rectangle_yes.setFillColor(Color(255, 150, 255, 150));
	rectangle_yes.setPosition(640, 472);

	//������������� ���
	sf::RectangleShape rectangle_no(sf::Vector2f(250.f, 130.f));
	rectangle_no.setFillColor(Color(255, 150, 255, 150));
	rectangle_no.setPosition(1005, 472);

		/***�����****/
	//������������� ������
	Text text_exit_confirm("", font_IMFellEnglishSCRegular, 48);
	text_exit_confirm.setString("Are you sure that you want to exit?");
	text_exit_confirm.setFillColor(Color::Red);
	text_exit_confirm.setPosition(590, 390);

	//��
	Text text_yes("", font_IMFellEnglishSCRegular, 80);
	text_yes.setString("Yes");
	text_yes.setFillColor(Color::Red);
	text_yes.setPosition(675, 472);

	//���
	Text text_no("", font_IMFellEnglishSCRegular, 80);
	text_no.setString("No");
	text_no.setFillColor(Color::Red);
	text_no.setPosition(1040, 472);

	///////////////
	Font font;
	font.loadFromFile("MilknBalls-BlackDemo.ttf");//�����

	Text tab_text("", font, 20);
	tab_text.setFillColor(Color(255, 10, 10));//����� ��� ���������

	Text text("", font, 35);
	text.setFillColor(Color::Blue);//������ ������ ������

	Text unit_info_text("", font, 20);
	unit_info_text.setFillColor(Color(72, 255, 213));//���������� � �����

	Text focus_tile_text("", font, 22);
	focus_tile_text.setFillColor(Color::White);//���������� � ������� ��������� ������

	Text unit_abilities("", font, 25);
	unit_abilities.setFillColor(Color::White);//���������� � ������������ �����

	Text exceptions("", font, 25);
	exceptions.setFillColor(Color::Red);//���������� �� �������


	Text text_winner("", font, 25);
	text_winner.setFillColor(Color::Red);//���������� �� �������

	Text t_turn("", font, 25);
	t_turn.setFillColor(Color::Red);//���������� �� �������

	Clock clock;
	
	///�������� ������
	Clock exception_clock;

	bool show_exceptions=false;
	int exceptions_time = 0;

	int time_s=0;

	EDislpay = MENU;

	bool show_exit=false;

	while (window.isOpen())//3 ����� ���������
	{
		sf::Event event;//����������-�������
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
				if (event.type == sf::Event::Closed)//���� ��  ����� �� �������� �������������  ������� "��������" , �� ��������� ����
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
						case true://���� ��� ���������� ������������� ������ �� ������� �� ����� ����				
						{
							show_exit = false;
							break;
						}
						case false://���� �� ���������� ����� ������,�� �������� ��� ����������
						{
							show_exit = true;
							break;
						}
						default:
							break;
						}

					}
					if ((event.key.code == Keyboard::Up) || (event.key.code == Keyboard::Down))
					{//���� ������ �������
						if (show_exit==false)
						{
							key_pressed.ArrowsPressdMenu(event);
						}
					}
					if ((event.key.code == Keyboard::Left) || (event.key.code == Keyboard::Right))
					{//���� ������ �������
						if (show_exit==true)
						{
							key_pressed.ArrowsPressedExit(event);
						}		
					}
					if(event.key.code == Keyboard::Enter)
					{//���� ������� Enter

						switch (show_exit)
						{
								case true://���� ��� ���������� ������������� ������ �� ������� �� ����� ����				
								{
									switch (key_pressed.GetExit())
									{
									case true://���� ������������ �� �������
									{
										EDislpay = CLOSE;
										break;
									}
									case false://����� ������� �� ������������� ������
									{
										show_exit = false;
										break;
									}
									default:
										break;
									}
									break;
								}

								case false://���� �� ���������� ����� ������,�� �������� ��� ����������
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
			
			
			window.draw(rectangle_changelog);
			window.draw(rectangle_feedback);
			window.draw(rectangle_play); 
			window.draw(rectangle_exit);

			window.draw(text_play);
			window.draw(text_exit);
			window.draw(text_name);
			window.draw(text_changelog_text);
			window.draw(text_changelog);
			window.draw(text_feedback);
			window.draw(text_feedback_text);

			if (show_exit == true)
			{
				key_pressed.UpdateExitConfirm(&text_yes, &text_no);

				window.draw(rectangle_exit_confirm);
				window.draw(rectangle_yes);
				window.draw(rectangle_no);
				window.draw(text_exit_confirm);
				window.draw(text_yes);
				window.draw(text_no);	

			}
			
			window.display(); 
		}

		while (EDislpay == BATTLE)
		{
			///////////////////////////////����������� ����������/////////////////////
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

			///////////////////////////////��������� ������/////////////////////
			while (window.pollEvent(event))//���� �������� ������� �� ���������, �� � ���� �� ��������
			{
				if (event.type == sf::Event::Closed)//���� ��  ����� �� �������� �������������  ������� "��������" , �� ��������� ����
				{
					EDislpay = CLOSE;
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
					{//���� ������� ���
						key_pressed.PressedTab(&tab_text, &time_s);
					}
					if ((event.key.code == Keyboard::Left) || (event.key.code == Keyboard::Right) || (event.key.code == Keyboard::Up) || (event.key.code == Keyboard::Down))
					{//���� ������ �������
						key_pressed.ArrowsPressd(&bg, &s_focus_tile, event);
					}
					if ((event.key.code == Keyboard::Enter))
					{//���� ������� Enter
						key_pressed.PressedEnter(&bg);
					}
					if ((event.key.code == Keyboard::M))
					{//���� ������� M
						key_pressed.PressedM(&bg);
					}
					if (event.key.code == Keyboard::A)
					{//���� ������� A
						key_pressed.PressedA(&bg);
					}
				}
			}

			///////////////////////////////������ �����/////////////////////
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
			///////////////////////////////������ ������/////////////////////
			bg.FillUnitsMap();//��������� ����� �������
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

			///////////////////////////////�������� �� ������/////////////////////
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
				EDislpay = WIN;
			}

			std::cout << "Number of units P2: " << P2.GetNumberOfUnits() << "\n";
			///////////////////////////////��������� ������/////////////////////
			key_pressed.UpdateTilesText(&bg, &focus_tile_text, &tab_text, &unit_info_text, bg.GetInfoAboutTile());
			key_pressed.UpdateUnitAbilitiesText(&unit_abilities);
			key_pressed.UpdateExceptions(&exceptions, &show_exceptions, &exceptions_time);
			key_pressed.UpdateTimer(&tab_text, &time_s);

			t_turn.setPosition(100, 20);
			t_turn.setString(std::to_string(key_pressed.GetTurn()));

			///������ ������ ///
			window.draw(focus_tile_text);
			window.draw(unit_info_text);
			window.draw(unit_abilities);
			window.draw(tab_text);
			window.draw(t_turn);
			///������ ��������� ������///
			window.draw(s_focus_tile);

			///������ ����������///
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
				if (event.type == sf::Event::Closed)//���� ��  ����� �� �������� �������������  ������� "��������" , �� ��������� ����
				{
					EDislpay = CLOSE;
				}
			}

			text_winner.setPosition(900, 500);
			text_winner.setString("The winner is: "+winner);

			window.draw(text_winner);
			window.display();
		}
	}
  
    std::cout << "Hello World!\n";
}
