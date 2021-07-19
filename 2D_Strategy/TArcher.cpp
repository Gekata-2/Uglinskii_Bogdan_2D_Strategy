#include "TArcher.h"


void TArcher::PrintInfo() const
{
	std::cout << "Type: Archer\n" << "Name : " << name << "  Side : " << side<< "\nHP = " << current_HP <<"/"<<max_HP<< "\nmana = " << mana << "\nBase attack damage = " << base_attack_damage
		<< "\nMax attack radius = " << max_attack_radius <<"\nMax distance of move :"<<max_move_tiles<< "\nPosition : [" << pos_x << "][" << pos_y << "]\n\n";
}

std::string TArcher::GetInfo() const
{
	std::string str;
	str = "Type:" + type + "\nName : " + name + "\nSide : "+ std::to_string(side)+
		"\nHP : " + std::to_string(current_HP) + "/" + std::to_string(max_HP) +
		"\nmana = " + std::to_string(mana) + 
		"\nBase attack damage = " + std::to_string(base_attack_damage)
		+ "\nMax attack radius = " + std::to_string(max_attack_radius) + 
		"\nPosition : ["
		+ std::to_string(pos_x) + "][" + std::to_string(pos_y) + "]";

	return str;
}