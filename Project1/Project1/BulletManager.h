#pragma once

class BulletManager
{
public:
	static BulletManager*GetInstance();
	void DeleteInstance();

private:
	static BulletManager*instacne;
};

