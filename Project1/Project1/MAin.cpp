#include "stdafx.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Screen.h"



int main()
{
	srand(time(NULL));
	const int screen_size = 80;
	//char screen[screen_size + 1];

	Screen*screen=new Screen(80);

	Player * player = new Player( "(^_^)->", 20, 10,screen);
	Enemy *  enemy[5];
	
	for(int i=0; i<5; i++)
		enemy[i]=new Enemy("(*__*)", 60+i*rand()%10, 5,screen);

	Bullet * bullet[100];

	for (int i = 0; i < 100; i++)
		bullet[i] = new Bullet("+", screen);

	int bulletIndex = 0;
	float playTime = 0;
	int killEnemyNum = 0;

	while (true)
	{
		if (player->GetActive() == false)
		{
			for (int i = 0; i < 5; i++)
			{
				if (!enemy[i]->GetActive())killEnemyNum++;
			}
			break;
		}

		int dieEnemyNum = 0;
		for (int i = 0; i < 5; i++)
		{
			if (!enemy[i]->GetActive())dieEnemyNum++;
		}

		if (dieEnemyNum == 5) 
		{
			killEnemyNum = 5;
			break;
		}

		playTime += 0.12f;
		//	Update
		{
			player->Update(screen_size);
			for(int i=0; i<5; i++)
				enemy[i]->Update(screen_size);
			if (player->IsFire() == true)
				bullet[bulletIndex++]->Fire(player);
			if (bulletIndex >= 100)
				bulletIndex = 0;
			for (int i = 0; i < 100; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					bullet[i]->Collision(enemy[j]);
					bullet[i]->Update(screen_size, enemy[j]->GetPosition());
				}
			}

			if (player->ChangeBullet())
			{
				for (int i = 0; i < 100; i++)
				{
					if (bullet[i]->GetBulletType() != Bullet::BulletType::Normal)
						bullet[i]->GetBulletType() = Bullet::BulletType::Normal;
					else
						bullet[i]->GetBulletType() = Bullet::BulletType::Lazer;
				}
				player->ChangeBullet() = false;
			}
		}

		//	Clear
		screen->Clear();

		//	Render
		{
			player->Render();
			for (int j = 0; j < 5; j++)
				enemy[j]->Render();
			for (int i = 0; i < 100; i++)
				bullet[i]->Render();

			screen->Render();
		}
		
		// ÃÑ¾ËÁ¤º¸
		{
			cout << endl;
			if (bullet[0]->GetBulletType() == Bullet::BulletType::Lazer)
			{
				cout << "Bullet Type : LazerGun" << endl;
			}
			else
			{
				cout << "Bullet Type : NormalGun" << endl;
			}
		}


		Sleep(66);
	}

	cout << "Game Clear" << endl;
	cout << "Play Time :" << playTime << endl;
	cout << "Kill Enemy Count:" << killEnemyNum << endl;
	

	delete player;
	for(int i=0; i<5; i++)
		delete enemy[i];

	for (int i = 0; i<100; i++)
		delete bullet[i];

	delete screen;

	system("pause");
	return 0;
}