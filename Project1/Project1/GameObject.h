#pragma once
class GameObject
{
public:
	GameObject(const char * face, int position,class Screen*screen);
	~GameObject();

	virtual void Update(const int, int) {};
	virtual void Update(const int ) {};

	virtual void Render();

public:
	void SetPosition(int val) { position = val; }
	int GetPosition() { return position; }

	void SetActive(bool val) { isActive = val; }
	bool GetActive() { return isActive; }

	void ChangeFace(const char*face) { this->face = face; }

protected:
	class Screen*screen;
	const char * face;
	int position;

	bool isActive;
};

