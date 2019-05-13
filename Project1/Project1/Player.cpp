#include "stdafx.h"
#include "Player.h"
#include "Bullet.h"



Player::Player(const char * face, int position, unsigned int hp, class Screen*screen)
	: Character(face, position, hp, screen)
	, isFire(false), dir(Direction::Right)
{

	ChangeFace("(^_^)->");
	changeBullet = false;
}


Player::~Player()
{
}

void Player::Update(const int screen_size)
{
	UpdateDirection();

	int inputKey = -1;
	//	_getche : echo
	if (_kbhit())
		inputKey = _getch();	//	blocking ÇÔ¼ö

	isFire = false;

	switch (inputKey)
	{
	case 'a':
		dir = Direction::Left;
		position = (position - 1) % screen_size;
		break;
	case 'd':
		dir = Direction::Right;
		position = (position + 1) % screen_size;
		break;
	case ' ':
		isFire = true;
		break;
	case 'm':
		changeBullet = true;
		break;
	}

	if (hp < 0) isActive = false;

	if (position + strlen(face) > screen_size)
		position = screen_size - strlen(face);
	if (position < 0)
		position = 0;
}

void Player::UpdateDirection()
{
	switch (dir)
	{
		case Player::Direction::Left:
			ChangeFace("<-(^_^)");
			break;
		case Player::Direction::Right:
			ChangeFace("(^_^)->");
			break;
	}
}
