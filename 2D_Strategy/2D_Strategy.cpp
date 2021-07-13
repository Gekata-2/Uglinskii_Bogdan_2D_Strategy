#include <iostream>
#include <vector>
#include <sstream>
#include "TBattleground.h"
#include "TArcher.h"
#include "TSwordsman.h"
#include "KeyPressEvent.h"
#include <windows.h>
//#include "TView.h"
#include <SFML/Graphics.hpp>
using namespace sf;



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


	bg.AddUnit(&ArA, 4, 4);
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
	bg.PrintUnits();


    RenderWindow window(sf::VideoMode(1000, 900), "Lesson 11. kychka-pc.ru");


	TKeyPressEvent key_pressed;
	
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
	Font font;
	font.loadFromFile("MilknBalls-BlackDemo.ttf");//�����

	Text tab_text("", font, 75);
	tab_text.setFillColor(Color(72, 255, 213));//����� ��� ���������

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

	Clock clock;
	
	///�������� ������
	Clock exception_clock;

	bool show_exceptions=false;
	int exceptions_time = 0;


	while (window.isOpen())
	{
		if (show_exceptions==true)
		{
			exceptions_time+= exception_clock.getElapsedTime().asMicroseconds();
			std::cout << "exceptions_time=" + std::to_string(exceptions_time)<<std::endl;
		}
		if (exceptions_time>=3000000)
		{
	
			key_pressed.SetException(ALL_OK);
			exceptions_time = 0;
		}
		float time = clock.getElapsedTime().asMicroseconds();
	//	std::cout << "time =" << time << std::endl;

		exception_clock.restart();
		clock.restart();
		
		window.clear(Color(14, 42 ,71));

		///////////////////////////////��������� ������/////////////////////
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			std::cout << "window is closed";
			window.close();
		}

		sf::Event event;//����������-�������

		while (window.pollEvent(event))//���� �������� ������� �� ���������, �� � ���� �� ��������
		{
			if (event.type == sf::Event::Closed)//���� ��  ����� �� �������� �������������  ������� "��������" , �� ��������� ����
			{
				std::cout << "window is closed";
				window.close();
			}
			if (event.type == Event::KeyPressed)
			{
				if ((event.key.code == Keyboard::Tab))
				{//���� ������� ���
					key_pressed.PressedTab(&tab_text, &unit_info_text,bg.GetInfoAboutTile(), 32, HEIGHT_MAP * 64 - 20);
				}
				if ((event.key.code == Keyboard::Left) || (event.key.code == Keyboard::Right)|| (event.key.code == Keyboard::Up)|| (event.key.code == Keyboard::Down))
				{//���� ������ �������
					key_pressed.ArrowsPressd(&bg, &s_focus_tile, event);						
				}
				if ((event.key.code == Keyboard::Enter))
				{//���� ������� Enter
					key_pressed.PressedEnter(&bg,&unit_abilities);
				}
				if ((event.key.code == Keyboard::M))
				{//���� ������� M
					key_pressed.PressedM(&bg);
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
		for (int i = 0; i < HEIGHT_MAP-2; i++)
		{
			for (int j = 0; j < WIDTH_MAP-2; j++)
			{	
			    if (bg.TileUnitsMap[i][j] == 'A')  s_unit_map.setTextureRect(IntRect(192, 0, 64, 64));
				if (bg.TileUnitsMap[i][j] == 'S')  s_unit_map.setTextureRect(IntRect(256, 0, 64, 64));

				if(bg.TileUnitsMap[i][j] == ' ')
				{
					continue;
				}
				s_unit_map.setPosition((j * 64)+64, (i * 64)+64);
				window.draw(s_unit_map);
			}
				
		}
		///////////////////////////////��������� ������/////////////////////
		key_pressed.UpdateTilesText(&bg, &focus_tile_text, &tab_text, &unit_info_text, bg.GetInfoAboutTile());
		key_pressed.UpdateUnitAbilitiesText(&unit_abilities);
		key_pressed.UpdateExceptions(&exceptions, &show_exceptions, &exceptions_time);
		
		///������ ������ ///
		window.draw(tab_text);
		window.draw(focus_tile_text);
		window.draw(unit_info_text);
		window.draw(unit_abilities);
		///������ ��������� ������///
		window.draw(s_focus_tile);

		///������ ����������///
		window.draw(exceptions);
		
		window.display();
	}


   /* bg.Attack(&SwA, &ArA);
    bg.Attack(&SwB, &ArA);
    bg.Attack(&ArA, &SwA);
    bg.Attack(&SwB, &ArA);
    bg.Attack(&SwB, &ArA);

    SwA.PrintInfo();
    SwB.PrintInfo();
    ArA.PrintInfo();
    bg.PrintUnits();*/

  
    std::cout << "Hello World!\n";
}
