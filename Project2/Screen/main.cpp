// Screen.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>

using namespace std;

void draw(char* loc, const char* face)
{
	strncpy(loc, face, strlen(face));
}

class Screen {
	int size;
	char* screen;

public:
	Screen(int sz) : size(sz), screen(new char[sz + 1]) 
	{
		printf("Screen constructor\n");
	}
	~Screen() 
	{ 
		printf("Screen destructor\n");
		if (screen) {
			delete[] screen;
			screen = nullptr;
		}
	}

	void draw(int pos, const char* face) 
	{
		if (face == nullptr) return;
		if (pos < 0 || pos >= size) return;
		strncpy(&screen[pos], face, strlen(face));
	}

	void render() 
	{
		printf("%s\r", screen);
	}

	void clear()
	{
		memset(screen, ' ', size);
		screen[size] = '\0';
	}

	int length()
	{
		return size;
	}

};

class GameObject {
	int pos;
	char face[20];
	Screen&screen;

public:
	GameObject(int pos, const char* face, Screen&screen)
		: pos(pos), screen(screen)
	{
		printf("GameObject constructor\n");
		strcpy(this->face, face);
	}

	~GameObject()
	{
		printf("GameObject destructor\n");
	}

	
	int getPosition()
	{
		return pos;
	}
	void setPosition(int pos)
	{
		this->pos = pos;
	}
	void draw()
	{
		screen.draw(pos, face);
	}

	virtual void update() {}
};

class Player : public GameObject {
	
public:
	Player(int pos, const char* face, Screen&screen) 
		: GameObject(pos, face, screen)
	{	
		printf("Player constructor\n");
	}

	~Player()
	{
		printf("Player destructor\n");
	}

	
	void moveLeft()
	{
		setPosition(getPosition() - 1);
	}

	void moveRight()
	{
		setPosition(getPosition() + 1);
	}

	void update() override
	{

	}

};

class Enemy : public GameObject {
	
public:
	Enemy(int pos, const char* face, Screen&screen) 
		: GameObject(pos, face, screen)
	{
		printf("Enemy constructor\n");
	}

	~Enemy()
	{
		printf("Enemy destructor\n");
	}

	void moveRandom()
	{
		setPosition( getPosition() + rand() % 3 - 1);
	}

	void update() override
	{
		moveRandom();
	}
};

class Bullet : public GameObject {
	bool isFiring;
	Enemy&enemy;

public:
	Bullet(int pos, const char* face, Screen&screen,Enemy&enemy) 
		: GameObject(pos, face, screen), isFiring(false),enemy(enemy)
	{
		printf("Bullet constructor\n");
	}
	~Bullet()
	{
		printf("Bullet destructor\n");
	}



	void moveLeft()
	{
		setPosition(getPosition() - 1);
	}

	void moveRight()
	{
		setPosition(getPosition() + 1);
	}

	void draw()
	{
		if (isFiring == false) return;
		GameObject::draw();
	}

	void fire(int player_pos)
	{
		isFiring = true;
		setPosition(player_pos);
	}

	void update() override
	{
		if (isFiring == false) return;
		int pos = getPosition();
		if (pos < enemy.getPosition()) {
			pos = pos + 1;
		}
		else if (pos > enemy.getPosition()) {
			pos = pos - 1;
		}
		else {
			isFiring = false;
		}
		setPosition(pos);
	}

	void update(int enemy_pos)
	{
		if (isFiring == false) return;
		int pos = getPosition();
		if (pos < enemy_pos) {
			pos = pos + 1;
		}
		else if (pos > enemy_pos) {
			pos = pos - 1;
		}
		else {
			isFiring = false;
		}
		setPosition(pos);
	}
};

#define NORMAL_PLAY 0

#if NORMAL_PLAY
int main()
{
	Screen screen{ 80 };
	Player player = { 30, "(^_^)", &screen };
	Enemy enemy{ 60, "(*--*)", &screen };
	Bullet bullet( -1, "+", &screen);

	while (true)
	{
		screen.clear();

		if (_kbhit())
		{
			int c = _getch();
			switch (c) {
			case 'a':
				player.moveLeft();
				break;
			case 'd':
				player.moveRight();
				break;
			case ' ':
				bullet.fire(player.getPosition());
				break;
			}
		}
		player.draw();
		enemy.draw();
		bullet.draw();

		player.update();
		enemy.update();
		bullet.update(enemy.getPosition());
		
		screen.render();
		Sleep(66);
	}

	return 0;
}
#else

enum OjbectType
{
	PLAYER=0,
	ENEMY,
	BULLET
};

void test()
{
	Screen*screen = nullptr;

	screen = new Screen(80);

	Player player = { 30, "(^_^)", *screen };
	Enemy enemy{ 60, "(*--*)", *screen };
	Bullet bullet(-1, "+", *screen,enemy);

	vector<GameObject*> objects;

	objects.push_back(&player);
	objects.push_back(&enemy);
	objects.push_back(&bullet);

	while (true)
	{
		screen->clear();

		//부모가 Polymorphic클래스 이므로 dynamic_cast로 다운케스팅 가능
		Player*playerPtr = dynamic_cast<Player*>(objects[OjbectType::PLAYER]);
		Bullet*bulletPtr = dynamic_cast<Bullet*>(objects[OjbectType::BULLET]);

		if (_kbhit())
		{
			int c = _getch();
			switch (c) {
				case 'a':
					playerPtr->moveLeft();
					break;
				case 'd':
					playerPtr->moveRight();
					break;
				case ' ':
					bulletPtr->fire(player.getPosition());
					break;
			}
		}

		for (GameObject*obj : objects)
		{
			obj->draw();
			obj->update();
		}

		screen->render();
		Sleep(66);
	}
}

int main()
{
	test();

	return 0;
}

#endif