#include "stdafx.h"
#include "Character.h"
#include "Screen.h"



Character::Character(const char * face, int position, unsigned int hp, class Screen*screen)
	: GameObject(face,position,screen),
	hp(hp)
{

}


Character::~Character()
{
}
