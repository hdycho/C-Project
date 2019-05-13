#pragma once
#include "GameObject.h"
class Character:public GameObject
{
public:
	Character(const char * face, int position, unsigned int hp,class Screen*screen);
	virtual ~Character();

	virtual void Update(const int screen_size, int c) {};

public:
	void SetHP(unsigned int val) { hp = val; }
	unsigned int GetHP() { return hp; }

protected:
	unsigned int hp;
};

