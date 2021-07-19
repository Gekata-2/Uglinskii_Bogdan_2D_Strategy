#pragma once
#include <iostream>
#include <string>

#include <SFML\Graphics.hpp>

class TUnit
{
protected:
	float current_HP = 1;
	float max_HP = 1;
	float mana = 1;
	int pos_x, pos_y;
	int max_attack_radius = 1;//������������ ������ �����
	int max_move_tiles=1;//������������ ������ ������, ������� ���� ����� ������ �� ���
	std::string name = "\0";
	float base_attack_damage = 1;
	std::string type = "\0";
	int side = 0;
	bool is_on_battleground = false;//��������� �� ���� �� �����
public:
	//�������
	virtual float		GetCurrentHP() const;//��������
	virtual float		GetMaxHP() const;//��������
	virtual float		GetBaseDamage() const;//������� ����
	virtual float		GetMaxAttackRadius() const;//������������ ������ �����

	virtual sf::Vector2i GetPos() const;//�������� ������� ������� �� ����� � ���� �������
	virtual int			 GetX() const;//�������� ���������� X
	virtual int		     GetY() const;//�������� ���������� Y
	virtual int		     GetMaxMoveTiles() const;
	virtual int			 GetSide() const;
	virtual bool		 IsOnBattleground() const;//��������� �� ������ ���� �� �����
	virtual std::string GetName() const;//���
	virtual std::string GetType() const;
	virtual std::string GetInfo() const = 0;

	//�������
	virtual void SetOnBattleground();//���������� ��� ���� ������ ��������� �� �����
	virtual void SetCurrentHP(float new_hp);//��������
	virtual void SetBaseDamage(float new_base_damage);//������� ����
	virtual void SetMaxAttackRadius(float new_max_radius);//������ �����
	virtual void SetMaxMoveTiles(int new_max_move_tiles);
	virtual void SetSide(int sd);

	virtual void PrintInfo() const =0 ;//������� ���������� � �����

private:
	 virtual void SetPos(int x, int y);//���������� �������.����� ����� ����� �� ����� ������������ 

	friend class TBattleground;
};

