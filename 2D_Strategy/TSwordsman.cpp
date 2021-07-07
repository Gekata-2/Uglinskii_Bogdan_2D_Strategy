//#include "TSwordsman.h"
//
//float TSwordsman::GetBaseDamage() const
//{
//	return base_attack_damage;
//}
//float TSwordsman::GetCurrentHP() const
//{
//	return HP;
//}
//
//
//float TSwordsman::GetMaxAttackRadius() const
//{
//	return max_attack_radius;
//}
//
//int* TSwordsman::GetPos() const
//{
//	int tmp[2] = { pos_x ,pos_y };
//	return tmp;
//}
//int TSwordsman::GetX() const
//{
//	return pos_x;
//}
//int TSwordsman::GetY() const
//{
//	return pos_y;
//}
//
//
//
//void TSwordsman::SetCurrentHP(float new_hp)
//{
//	HP = new_hp;
//}
//
//void TSwordsman::SetBaseDamage(float new_base_damage)
//{
//	base_attack_damage = new_base_damage;
//}
//
//void TSwordsman::SetMaxAttackRadius(float new_max_radius)
//{
//	max_attack_radius = new_max_radius;
//}
//
//void TSwordsman::SetPos(int x, int y)
//{
//	pos_x = x;
//	pos_y = y;
//}
//
//void TSwordsman::PrintInfo()
//{
//	std::cout << "Type: Swordsman\n" << "Name : " << name << "\nHP = " << HP << "\nmana = " << mana << "\nBase attack damage = " << base_attack_damage
//		<< "\nMax attack radius = " << max_attack_radius << "\nPosition : [" << pos_x << "][" << pos_y << "]\n\n";
//}