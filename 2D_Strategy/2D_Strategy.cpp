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
72 255 213 зелёный
14 42 71 синий
*/
int main()
{
    TBattleground bg;
    RenderWindow window(sf::VideoMode(1000, 900), "Lesson 11. kychka-pc.ru");

	

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Image focus_tile_image;
	focus_tile_image.loadFromFile("images/focus_tile_tr.png");
	Texture focus_tile_texture;
	focus_tile_texture.loadFromImage(focus_tile_image);
	Sprite s_focus_tile;
	s_focus_tile.setTexture(focus_tile_texture);



	Image empty_image;
	empty_image.loadFromFile("images/empty_tile.png");
	Texture empty_texture;
	empty_texture.loadFromImage(empty_image);
	Sprite s_empty_tile;
	s_empty_tile.setTexture(empty_texture);

	Texture unit_map;
	unit_map.loadFromImage(map_image);

	Sprite s_unit_map;
	s_unit_map.setTexture(unit_map);

	TSwordsman SwA;
	TSwordsman SwB;

	TArcher ArA;
	TArcher ArB;
	

	bg.AddUnit(&ArA, 4, 4);
	bg.PrintUnits();
	bg.AddUnit(&ArB, 1, 0);
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

	Font font;
	font.loadFromFile("CyrilicOld.ttf");

	Text tab_text("", font, 100);
	tab_text.setFillColor(Color(72, 255, 213));

	Text text("", font, 35);
	text.setFillColor(Color::Blue);

	Text unit_info_text("", font, 35);
	unit_info_text.setFillColor(Color(72, 255, 213));

	Text focus_tile_text("", font, 22);
	focus_tile_text.setFillColor(Color::White);

	Text unit_abilities("", font, 25);
	unit_abilities.setFillColor(Color::White);

	Clock clock;
	TKeyPressEvent key_pressed;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		//std::cout << "time =" << time << std::endl;

		clock.restart();
				time = time / 800;

		sf::Event event;//переменная-событие
		
	
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			std::cout << "window is closed";
			window.close();
		}
	
	//	window.setView(view);

		window.clear(Color(14, 42 ,71));
		///////////////////////////////Рисуем карту/////////////////////

	
		

		
		while (window.pollEvent(event))//если никакого события не произошло, то в цикл не попадаем
		{
			if (event.type == sf::Event::Closed)//если мы  каким то способом сгенерировали  событие "закрытие" , то закрываем окно
			{
				std::cout << "window is closed";
				window.close();
			}
			if (event.type == Event::KeyPressed)
			{
				if ((event.key.code == Keyboard::Tab))
				{//если клавиша ТАБ
					key_pressed.PressedTab(&tab_text, &unit_info_text,bg.GetInfoAboutTile(), 32, HEIGHT_MAP * 64 - 20);
				}
				if ((event.key.code == Keyboard::Left) || (event.key.code == Keyboard::Right)|| (event.key.code == Keyboard::Up)|| (event.key.code == Keyboard::Down))
				{//если нажаты стрелки
					key_pressed.ArrowsPressd(&bg, &focus_tile_text, &s_focus_tile, event,WIDTH_MAP * 64, 0);
					/*if (bg.GetFocusUnit()!=NULL)
					{
						key_pressed.PressedTab(&tab_text, &unit_info_text, bg.GetInfoAboutTile(), 32, HEIGHT_MAP * 64 - 20);
					}*/					
				}
				if ((event.key.code == Keyboard::Enter))
				{//если клавиша ТАБ
					key_pressed.PressedEnter(&bg,&unit_abilities);
				}
				if ((event.key.code == Keyboard::M))
				{//если клавиша ТАБ
					key_pressed.PressedM(&bg, &unit_abilities);
				}
				
			
			}
		}
		for (int i = 0; i < HEIGHT_MAP; i++)
		{
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				//std::cout << (char)bg.TileUnitsMap[i][j]<<" ";
				if ((bg.TileBackgroundMap[i][j] == '0')) s_map.setTextureRect(IntRect(128, 0, 64, 64));
				if ((bg.TileBackgroundMap[i][j] == ' ')) s_map.setTextureRect(IntRect(0, 0, 64, 64));
				if ((bg.TileBackgroundMap[i][j] == 's')) s_map.setTextureRect(IntRect(64, 0, 64, 64));
				
				
				s_map.setPosition(j * 64, i * 64);
				window.draw(s_map);
			}
		}
		bg.FillUnitsMap();
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
				std::cout << "\n";
		}
		
	
		
		window.draw(tab_text);
		window.draw(focus_tile_text);
		window.draw(unit_info_text);
		window.draw(unit_abilities);
		window.draw(s_focus_tile);
		window.display();
	
	}

	std::cout<<bg.GetInfoAboutTile(1,0).getData();
	


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
