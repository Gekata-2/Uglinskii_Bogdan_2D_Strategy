#include "TSwordsman.h"

void TSwordsman::PrintInfo() const
{
	std::cout <<"Type: Swordsman\n" <<"Name : " << name << "\nHP = " << current_HP << "\nmana = " << mana << "\nBase attack damage = " << base_attack_damage
		<< "\nMax attack radius = " << max_attack_radius << "\nPosition : [" << pos_x << "][" << pos_y << "]\n\n";
}