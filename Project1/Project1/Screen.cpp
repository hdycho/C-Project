#include "stdafx.h"
#include "Screen.h"

Screen::Screen(int size)
	:size(size), screen(new char[size + 1])
{

}

Screen::~Screen()
{
	delete[] screen;
}

void Screen::Draw(int pos, const char * face)
{
	int len = strlen(face);


	if (pos < 0 || pos >= size-len/2)return;

	strncpy(&screen[pos], face, strlen(face));
}

void Screen::Render()
{
	printf("%s\n", screen);
}

void Screen::Clear()
{
	memset(screen, ' ', size);
	screen[size] = 0;
	system("cls");
}

