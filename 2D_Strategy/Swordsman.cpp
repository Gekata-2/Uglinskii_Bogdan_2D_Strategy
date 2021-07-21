#include "Swordsman.h"

void TSwordsman::PrintInfo() const
{
	std::cout <<"Type: Swordsman\n" <<"Name : " << name <<"  Side : "<<side<< "\nHP = " << current_HP<<"/"<<max_HP << "\nmana = " << mana << "\nBase attack damage = " << base_attack_damage
		<< "\nMax attack radius = " << max_attack_radius << "\nPosition : [" << pos_x << "][" << pos_y << "]\n\n";
}

std::string TSwordsman::GetInfo() const
{
	std::string str;
	str = "Type:" + type + "\nName : " + name + +"\nSide : " + owner_name +
		"\nHP : " + std::to_string(current_HP) + "/"+std::to_string(max_HP) + "\nmana = " + std::to_string(mana)+ 
		"\nBase attack damage = " + std::to_string(base_attack_damage)
		+ "\nMax attack radius = " + std::to_string(max_attack_radius) + 
		"\nPosition : [" + std::to_string(pos_x) + "][" + std::to_string(pos_y)+ "]\n\n";
	
	return str;
}