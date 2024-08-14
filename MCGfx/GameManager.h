#pragma once
#include <string>
#include <vector>
#include "MCGraphics.cpp"
#include "TBWorld.cpp"
using namespace std;


class GameManager
{
private:
	MCGraphics* pGfx = nullptr;
	TBWorld world;
	bool lButtonDown = false;
	bool rButtonDown = false;
	bool lButtonClick = false;
	bool rButtonClick = false;
	int mouseX = 0;
	int mouseY = 0;                                                   

public:

	void Initialize()
	{
		world.Load();
	}

void SetPointer(MCGraphics* ptr)
{
	pGfx = ptr;
}

void Update(bool lb, bool rb, int x, int y)
{
	//Handle left Button
	if (lButtonDown != lb)
	{
		lButtonClick = !lb;
	}
	else
	{
		lButtonClick = false;
	}
	lButtonDown = lb;

	//Handle Right Button
	if (rButtonDown != rb)
	{
		rButtonClick = !rb;
	}
	else
	{
		rButtonClick = false;
	}
	rButtonDown = rb;

	mouseX = x;
	mouseY = y;
}

void Render(HWND hwnd)
{
	world.SetSpriteVisible("fire", lButtonDown);
	float thrust = -0.005f;
	if (!lButtonDown)
	{
		thrust = 0;
	}
	world.SetSpriteForce("lander", thrust, false);
	
	world.Process();
	world.Draw(pGfx);
	pGfx->Present(hwnd);
}



};

