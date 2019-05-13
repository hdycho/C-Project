#include "GameObject.h"
#include "Screen.h"


GameObject::GameObject(const char * face, int position, class Screen*screen)
	:face(face), 
	position(position),
	isActive(true), 
	screen(screen)
{
}


GameObject::~GameObject()
{
}


void GameObject::Render()
{
	if (screen == nullptr)return;
	if (isActive == false) return;

	screen->Draw(position, face);
}
