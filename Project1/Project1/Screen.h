#pragma once
class Screen
{
public:
	Screen(int size);

	~Screen();

	void Draw(int pos, const char*face);

	void Render();

	void Clear();

	int GetScreenSize()
	{
		return size;
	}

private:
	int size;
	char*screen;
};