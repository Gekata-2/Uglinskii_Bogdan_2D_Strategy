#pragma once
#include <iostream>
#include <string>
class TUnit
{
protected:
	float HP = 100;
	float mana = 100;
	int pos_x, pos_y;
	int max_attack_radius = 1;
	std::string name = "\0";
	float base_attack_damage = 25;
private:
	virtual void Attack(TUnit* unit)=0;
	virtual float GetCurrentHP() const;
	virtual float GetBaseDamage() const;
	virtual float GetMaxAttackRadius() const;
	virtual int* GetPos() const;
	virtual int GetX() const;
	virtual int GetY() const;
	virtual void SetCurrentHP(float new_hp);
	virtual void SetBaseDamage(float new_base_damage);
	virtual void SetMaxAttackRadius(float new_max_radius);
	virtual void SetPos(int x,int y);
	
	friend class TBattleground;
public:
	virtual void PrintInfo();
};

