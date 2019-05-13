#pragma once
#include "GameObject.h"
class Bullet:public GameObject
{
public:
	enum class BulletType
	{
		Normal,
		Lazer
	}bType;
public:
	Bullet(const char * face,class Screen*screen);
	~Bullet();

	void Fire(int startPos, int targetPos);
	void Fire(class Player*player);
	void Update(const int screen_size, int targetPos) override;
	bool Collision(class Enemy * enemy);

	BulletType&GetBulletType() { return bType; }

private:
	void BulletInit();

private:
	int speed;
	float activeTime;

	int length;

};

