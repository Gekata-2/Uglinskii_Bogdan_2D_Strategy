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
	int max_attack_radius = 1;//максимальный радиус атаки
	int max_move_tiles=1;//максимальное чилсло клеток, которые юнит может пройти за ход
	std::string name = "\0";
	float base_attack_damage = 1;
	std::string type = "\0";
	int side = 0;
	bool is_on_battleground = false;//находится ли юнит на доске
public:
	//геттеры
	virtual float		GetCurrentHP() const;//здоровья
	virtual float		GetMaxHP() const;//здоровья
	virtual float		GetBaseDamage() const;//базовый урон
	virtual float		GetMaxAttackRadius() const;//максимальный радиус атаки

	virtual sf::Vector2i GetPos() const;//получить текущую позицию на доске в виде массива
	virtual int			 GetX() const;//получить координату X
	virtual int		     GetY() const;//получить координату Y
	virtual int		     GetMaxMoveTiles() const;
	virtual int			 GetSide() const;
	virtual bool		 IsOnBattleground() const;//находится ли сейчас юнит на доске
	virtual std::string GetName() const;//имя
	virtual std::string GetType() const;
	virtual std::string GetInfo() const = 0;

	//сеттеры
	virtual void SetOnBattleground();//установить что юнит теперь находится на доске
	virtual void SetCurrentHP(float new_hp);//здоровье
	virtual void SetBaseDamage(float new_base_damage);//базовый урон
	virtual void SetMaxAttackRadius(float new_max_radius);//радиус атаки
	virtual void SetMaxMoveTiles(int new_max_move_tiles);
	virtual void SetSide(int sd);

	virtual void PrintInfo() const =0 ;//вывести информацию о юните

private:
	 virtual void SetPos(int x, int y);//установить позицию.Никто кроме доски не может пользоваться 

	friend class TBattleground;
};

