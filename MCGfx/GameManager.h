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
	bool leftKeyDown = false;
	bool rightKeyDown = false;
	bool thrustKeyDown = false;
	bool upKeyDown = false;
	bool restart = false;

public:

	void Initialize()
	{
		world.Load();
	}

void SetPointer(MCGraphics* ptr)
{
	pGfx = ptr;
}
void Restart()
{
	Initialize();
}
//Handles mouse click. Left and Right click
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

void HandleKey(int key, bool keyDown)
{
	if (key == VK_SPACE && !keyDown) //restart
	{
		Restart();
	}
	else if (key == 'W') //Thrust
	{
		thrustKeyDown = keyDown;
	}
	else if (key == 'A') //Left
	{
		leftKeyDown = keyDown;
	}
	else if (key == 'D') //Right
	{
		rightKeyDown = keyDown;
	}
	else if (key == 'S') //down thrust
	{
		upKeyDown = keyDown;
	}
}

void Render(HWND hwnd)
{
	// sets amount of thrust for fire
	world.SetSpriteVisible("fire", thrustKeyDown);
	float thrust = -0.001f;
	if (!thrustKeyDown)
	{
		thrust = 0;
	}
	///failed so far. trying to push lander left faster while on
	world.SetSpriteVisible("right", rightKeyDown);
	float thrustLeft = -0.001f;
	if (!rightKeyDown)
	{
		thrustLeft = 0;
	}

	world.SetSpriteVisible("left", leftKeyDown);
	float thrustRight = 0.001f;
	if (!leftKeyDown)
	{
		thrustRight = 0;
	}

	world.SetSpriteVisible("Up", upKeyDown);
	float thrustDown = 0.001f;
	if (!upKeyDown)
	{
		thrustDown = 0;
	}

	// lander forces 
	world.SetSpriteForce("lander", thrust, false);
	world.SetSpriteForce("lander", thrustRight, true);
	world.SetSpriteForce("lander", thrustLeft, true);
	world.SetSpriteForce("lander", thrustDown, false);
	world.Process();
	world.Draw(pGfx);
	pGfx->Present(hwnd);
}


};

