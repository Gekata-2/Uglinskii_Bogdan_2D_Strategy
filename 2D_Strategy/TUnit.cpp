#include "TUnit.h"

//--------�������----------//

/**
������� ����
*/
float TUnit::GetBaseDamage() const
{
	return base_attack_damage;
}

/**
��������
*/
float TUnit::GetCurrentHP() const
{
	return current_HP;
}

float TUnit::GetMaxHP() const
{
	return max_HP;
}

/**
������ �����
*/
float TUnit::GetMaxAttackRadius() const
{
	return max_attack_radius;
}

/**
������� �� �����
*/
int* TUnit::GetPos() const
{
	int tmp[2] = { pos_x ,pos_y };
	return tmp;
}

/**
�������������� ���������� ����� �� �����
*/
int TUnit::GetX() const
{
	return pos_x;
}

/**
������������ ���������� ����� �� �����
*/
int TUnit::GetY() const
{
	return pos_y;
}

/**
������������ ����� ������ ,������� ���� ����� ������ �� ���� ���
*/
int TUnit::GetMaxMoveTiles() const
{
	return max_move_tiles;
}

/**
����������� �� �����
*/
bool TUnit::IsOnBattleground() const
{
	return is_on_battleground;
}

/**
���
*/
std::string TUnit::GetName() const
{
	return name;
}

/**
��� �����
*/
std::string TUnit::GetType() const
{
	return type;
}

int TUnit::GetSide() const
{
	return side;
}


//-------�������----------//
void TUnit::SetCurrentHP(float new_hp)
{
	current_HP = new_hp;
}

void TUnit::SetBaseDamage(float new_base_damage)
{
	base_attack_damage = new_base_damage;
}

void TUnit::SetMaxAttackRadius(float new_max_radius)
{
	max_attack_radius = new_max_radius;
}
void TUnit::SetMaxMoveTiles(int new_max_move_tiles)
{
	max_move_tiles = new_max_move_tiles;
}

void TUnit::SetPos(int x, int y)
{
	pos_x = x;
	pos_y = y;
}

void TUnit::SetOnBattleground() 
{
	is_on_battleground = true;
}

void TUnit::SetSide(int sd)
{
	side = sd;
}

