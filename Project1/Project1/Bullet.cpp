#include "stdafx.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Screen.h"
#include "Player.h"



Bullet::Bullet(const char * face, class Screen*screen)
	: GameObject(face,-1,screen),
	speed(0)
{
	bType = Bullet::BulletType::Lazer;
	activeTime = 0;
}


Bullet::~Bullet()
{
}

void Bullet::BulletInit()
{
	position = -1;
	speed = 0;
	activeTime = 0;
	isActive = false;
}


void Bullet::Update(const int screen_size, int targetPos)
{
	if (isActive == false) return;

	switch (bType)
	{
		case Bullet::BulletType::Normal:
		{
			ChangeFace("*");
			if (position < 0 || position >= screen_size - 1)
			{
				BulletInit();
				return;
			}

			position += speed;
		}
		break;
		case Bullet::BulletType::Lazer:
		{
			static int lazerValue=1;
			length = abs(position - targetPos);

			char*lazerFace=new char[length+4];

			for (int i = 0; i < length+4; i++)
			{
				if (lazerValue == 1)
				{
					if (i % 2 == 0) lazerFace[i] = '=';
					else lazerFace[i] = '*';
				}
				else
				{
					if (i % 2 == 0) lazerFace[i] = '*';
					else lazerFace[i] = '=';
				}
			}

			lazerFace[length+3] = 0;

			ChangeFace(lazerFace);
			
			activeTime += 0.05f;
			static float checkTime = 0;
			checkTime += 0.12f;
			
			if (checkTime > 0.25f)
			{
				checkTime = 0;
				lazerValue *= -1;
			}
			
			if (activeTime > 2)
			{
				BulletInit();
				delete[] lazerFace;
			}
			
		}
		break;
	}
}

bool Bullet::Collision(Enemy * enemy)
{
	if (position < 0) return false;
	if (isActive == false) return false;
	if (enemy->GetHP() <= 0) return false;

	switch (bType)
	{
		case Bullet::BulletType::Normal:
		{
			float distance = fabsf(position - enemy->GetPosition());

			if (distance <= 1)
			{
				BulletInit();

				int hp = enemy->GetHP();
				enemy->SetHP(hp - 1);

				return true;
			}
		}
		break;
		case Bullet::BulletType::Lazer:
		{
			float distance = fabsf(position - enemy->GetPosition());

			if (length > distance)
			{
				int hp = enemy->GetHP();
				enemy->SetHP(hp - 1);
			}

			return true;
			
		}
		break;
	}


	return false;
}

void Bullet::Fire(int startPos, int targetPos)
{
	position = startPos;

	isActive = true;

	if (targetPos > startPos)
		speed = 1;
	else
		speed = -1;
}

void Bullet::Fire(Player * player)
{
	if (player->GetDir() == Player::Direction::Left)
	{
		position = player->GetPosition() - 7;
		speed = -1;
	}
	else
	{
		position = player->GetPosition() + 7;
		speed = 1;
	}


	isActive = true;
}
