#pragma once
#include "Character.h"

class Player : public Character
{
public:
	enum class Direction
	{
		Left,
		Right
	}dir;
public:
	Player(const char * face, int position, unsigned int hp,class Screen*screen);
	~Player();

	// GameObject��(��) ���� ��ӵ�
	void Update(const int screen_size) override;

	bool IsFire() { return isFire; }
	Direction GetDir() { return dir; }
	bool&ChangeBullet() { return changeBullet; }

private:
	void UpdateDirection();

private:
	bool isFire;
	bool changeBullet;
};

