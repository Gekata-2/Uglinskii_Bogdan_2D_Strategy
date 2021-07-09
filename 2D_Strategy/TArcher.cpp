#include "TArcher.h"


void TArcher::PrintInfo() const
{
	std::cout << "Type: Archer\n" << "Name : " << name << "\nHP = " << HP << "\nmana = " << mana << "\nBase attack damage = " << base_attack_damage
		<< "\nMax attack radius = " << max_attack_radius <<"\nMax distance of move :"<<max_move_tiles<< "\nPosition : [" << pos_x << "][" << pos_y << "]\n\n";
}