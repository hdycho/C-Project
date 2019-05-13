#pragma once
#include "Character.h"
class Enemy : public Character
{
private:
	enum class STATE
	{
		IDLE,
		BLINK,
		DIE
	} state;

public:
	Enemy(const char * face, int position, unsigned int hp,class Screen*screen);
	~Enemy();

	// GameObject을(를) 통해 상속됨
	void Update(const int screen_size) override;

private:
	float blinkTime;
	float moveTime = 0;
};

