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

int main()
{
    TBattleground bg;
    RenderWindow window(sf::VideoMode(800, 800), "Lesson 11. kychka-pc.ru");

	

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Texture unit_map;
	unit_map.loadFromImage(map_image);

	Sprite s_unit_map;
	s_unit_map.setTexture(unit_map);

	TSwordsman SwA;
	TSwordsman SwB;

	TArcher ArA;
	TArcher ArB;
	bool showTab=true;

	bg.AddUnit(&ArA, 4, 4);
	bg.PrintUnits();
	bg.AddUnit(&ArB, 0, 0);
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
	tab_text.setFillColor(Color(0, 0, 0));

	Text text("", font, 35);
	text.setFillColor(Color::Blue);

	Text unit_info_text("", font, 35);
	unit_info_text.setFillColor(Color::Blue);

	Text focus_tile_text("", font, 22);
	focus_tile_text.setFillColor(Color::Green);

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

		window.clear(Color(63,72,204));
		///////////////////////////////Рисуем карту/////////////////////
	/*	for (int i = 0; i < HEIGHT_MAP; i++)
		{
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				std::cout << bg.TileBackgroundMap[i][j] << " ";
				if (bg.TileBackgroundMap[i][j] == 's')  s_map.setTextureRect(IntRect(0, 0, 64, 64));
				if (bg.TileBackgroundMap[i][j] == ' ')  s_map.setTextureRect(IntRect(64, 0, 64, 64));
				if ((bg.TileBackgroundMap[i][j] == '0')) s_map.setTextureRect(IntRect(128, 0, 64, 64));
				s_map.setPosition(j * 64, i * 64);
				window.draw(s_map);
			}
			std::cout << "\n";
		}*/
		bg.FillUnitsMap();

	
		

		
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
					key_pressed.PressedTab(&tab_text, &unit_info_text,bg.GetInfoAboutTile(0,0), 32, HEIGHT_MAP * 64 - 20);
				}
				if ((event.key.code == Keyboard::Left) || (event.key.code == Keyboard::Right)|| (event.key.code == Keyboard::Up)|| (event.key.code == Keyboard::Down))
				{//если клавиша ТАБ
					std::cout << "pointer is pressed" << (char)event.key.code<<std::endl;
					bg.MoveFocusTile(event);
					focus_tile_text.setPosition(WIDTH_MAP * 64, 0);
					Vector2i v_f=bg.GetFocusTile();
				sf:String tmp_s = "Focus tile :" + std::to_string(v_f.x) + "  " + std::to_string(v_f.y);
					focus_tile_text.setString(tmp_s);
				}
				
			
			}//событие нажатия клавиши
				//if ((event.key.code == Keyboard::Tab)) 
				//{//если клавиша ТАБ
				//	switch (showTab) {//переключатель, реагирующий на логическую переменную showMissionText
				//	case true: {
				//		std::cout << "Key  TAB  is pressed\n";
				//		Sleep(500);
				//		std::ostringstream tab;
				//		tab << (char)event.key.code;
				//		занесли в нее число очков, то есть формируем строку
				//		text.setString("TAB");//задаем строку тексту и вызываем сформированную выше строку методом .str() 
				//		text.setPosition(300, 300);//задаем позицию текста, отступая от центра камеры
				//		showTab = false;// а эта строка позволяет снова нажать клавишу таб и получить вывод на экран
				//		break;
				//		key_pressed.KeyPressed(event);
				//	}
				//	case false: {
				//		text.setString("");//если не нажата клавиша таб, то весь этот текст пустой
				//		showTab = true;// а эта строка позволяет снова нажать клавишу таб и получить вывод на экран
				//		break;
				//	}
				//	}
				//}
		}
		for (int i = 0; i < HEIGHT_MAP; i++)
		{
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				//std::cout << (char)bg.TileUnitsMap[i][j]<<" ";
				if (bg.TileUnitsMap[i][j] == 'A')  s_unit_map.setTextureRect(IntRect(192, 0, 64, 64));
				if (bg.TileUnitsMap[i][j] == 'S')  s_unit_map.setTextureRect(IntRect(256, 0, 64, 64));
				if ((bg.TileUnitsMap[i][j] == '0')) s_unit_map.setTextureRect(IntRect(64, 0, 64, 64));
				s_unit_map.setPosition(j * 64, i * 64);
				window.draw(s_unit_map);
			}
			//	std::cout << "\n";
		}
		
		window.draw(tab_text);
		window.draw(focus_tile_text);
		window.draw(unit_info_text);
		window.display();
	
	}





    bg.Attack(&SwA, &ArA);
    bg.Attack(&SwB, &ArA);
    bg.Attack(&ArA, &SwA);
    bg.Attack(&SwB, &ArA);
    bg.Attack(&SwB, &ArA);

    SwA.PrintInfo();
    SwB.PrintInfo();
    ArA.PrintInfo();
    bg.PrintUnits();

  
    std::cout << "Hello World!\n";
}
