#include "TArcher.h"


void TArcher::PrintInfo() const
{
	std::cout << "Type: Archer\n" << "Name : " << name << "\nHP = " << current_HP << "\nmana = " << mana << "\nBase attack damage = " << base_attack_damage
		<< "\nMax attack radius = " << max_attack_radius <<"\nMax distance of move :"<<max_move_tiles<< "\nPosition : [" << pos_x << "][" << pos_y << "]\n\n";
}

std::string TArcher::GetInfo() const
{
	std::string str;
	str = "Type:" + type + "	;	Name : " + name + "\nHP : " + std::to_string(current_HP) + "/" + std::to_string(max_HP) +
		"	;	mana = " + std::to_string(mana) + "\nBase attack damage = " + std::to_string(base_attack_damage)
		+ "\nMax attack radius = " + std::to_string(max_attack_radius) + "\nPosition : ["
		+ std::to_string(pos_x) + "][" + std::to_string(pos_y) + "]";

	return str;
}