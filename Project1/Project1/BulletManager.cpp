#include "BulletManager.h"


BulletManager*BulletManager::instacne = nullptr;

BulletManager * BulletManager::GetInstance()
{
	if (instacne == nullptr)
		instacne = new BulletManager();

	return instacne;
}

void BulletManager::DeleteInstance()
{
}
