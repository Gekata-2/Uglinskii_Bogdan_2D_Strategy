#include "TUnit.h"


float TUnit::GetBaseDamage() const
{
	return base_attack_damage;
}

float TUnit::GetCurrentHP() const
{
	return HP;
}


float TUnit::GetMaxAttackRadius() const
{
	return max_attack_radius;
}

int* TUnit::GetPos() const
{
	int tmp[2] = { pos_x ,pos_y };
	return tmp;
}

int TUnit::GetX() const
{
	return pos_x;
}

int TUnit::GetY() const
{
	return pos_y;
}



void TUnit::SetCurrentHP(float new_hp)
{
	HP = new_hp;
}

void TUnit::SetBaseDamage(float new_base_damage)
{
	base_attack_damage = new_base_damage;
}

void TUnit::SetMaxAttackRadius(float new_max_radius)
{
	max_attack_radius = new_max_radius;
}

void TUnit::SetPos(int x, int y)
{
	pos_x = x;
	pos_y = y;
}

void TUnit::PrintInfo()
{
	std::cout << "Type: Swordsman\n" << "Name : " << name << "\nHP = " << HP << "\nmana = " << mana << "\nBase attack damage = " << base_attack_damage
		<< "\nMax attack radius = " << max_attack_radius << "\nPosition : [" << pos_x << "][" << pos_y << "]\n\n";
}