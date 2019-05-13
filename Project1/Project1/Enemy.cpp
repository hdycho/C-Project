#include "stdafx.h"
#include "Enemy.h"



Enemy::Enemy(const char * face, int position, unsigned int hp, class Screen*screen)
	: Character(face, position, hp, screen)
	, blinkTime(0.0f)
{
	state = STATE::IDLE;
}


Enemy::~Enemy()
{
}

void Enemy::Update(const int screen_size)
{
	switch (state)
	{
	case Enemy::STATE::IDLE:
		{
			moveTime += 0.12f;
			
			if (moveTime > 2)
			{
				position--;
				moveTime = 0;
			}

			if (hp <= 0)
				state = STATE::BLINK;
		}
		break;
	case Enemy::STATE::BLINK:
	{
		blinkTime += 0.016f;
		isActive = !isActive;
		if (blinkTime >= 1.0f)
		{
			blinkTime = 0.0f;
			state = STATE::DIE;
		}
		}
		break;
	case Enemy::STATE::DIE:
		isActive = false;
		break;
	}
}
