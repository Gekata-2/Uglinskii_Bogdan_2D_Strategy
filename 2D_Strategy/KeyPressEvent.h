#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
using namespace sf;
class TKeyPressEvent
{
	bool showTab = true;
public:
	void KeyPressed(sf::Event event)
	{
		if ((event.key.code == Keyboard::Tab))
		{//���� ������� ���
			PressedTab();			
		}
	}

	sf::String PressedTab()
	{
		sf::String str;

		switch (showTab)
		{//�������������, ����������� �� ���������� ���������� showMissionText
			case true: 
			{
				std::cout << "Key  TAB  is pressed\n";
				Sleep(1000);
				str = "TAB";
				showTab = false;// � ��� ������ ��������� ����� ������ ������� ��� � �������� ����� �� �����
				break;
				//	key_pressed.KeyPressed(event);
			}
			case false: 
			{
				Sleep(1000);
				std::cout << "Key  TAB  is pressed twice\n";
				str = "";
				showTab = true;// � ��� ������ ��������� ����� ������ ������� ��� � �������� ����� �� �����
				break;
			}
		}
		return str;
	}


};

