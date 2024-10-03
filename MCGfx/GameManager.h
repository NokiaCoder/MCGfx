#pragma once
#include <string>
#include <vector>
#include "MCGraphics.cpp"
#include "TBWorld.cpp"
#include "TBGlobals.h"
#include <thread>
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
	bool startShown = false;
	float mainThrust = -5.0f;
	float sideThrust = 4.0f;

public:

	void Initialize()
	{
		world.Load();
		StartTimer();
	}
	void ShowStartScreen()
	{
		TBSprite start;
		start.Create(g_pixelWidth / 2, g_pixelHeight / 2, 500, 300, { 255, 255, 255 });
		start.SetName("startText");
		start.SetSpriteText("TanLander\nwritten by\nTanner Boudreau\n2024");
		start.SetIsTextSprite(true);
		start.SetVisible(true);
		start.SetLayer(LAYER::layer_FRONT);
		start.SetHasAnimation(false);
		start.setPhysics(false);
		start.Process(0.0f);
		start.Draw(pGfx);
	}

	bool HandleStartScreen()
	{
		if (!startShown)
		{
			if (GetElapsedSeconds() <= 3.0f)
			{
				ShowStartScreen();
				return false;
			}
		}
		return true;
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
}

void Render(HWND hwnd)
{
	if (HandleStartScreen() == false)
	{
		pGfx->Present(hwnd);
		return;
	}
	startShown = true;
	//Get Master Timeslice
	double  elapsedTimeSec = GetElapsedFrameSeconds();

	//Test for collision
	world.TestCollision();


	// sets amount of thrust for fire
	world.SetSpriteVisible("fire", thrustKeyDown);
	world.SetParticleSystemActive("thrust", thrustKeyDown);
	float thrust = (mainThrust * (float)elapsedTimeSec);
	if (!thrustKeyDown)
	{
		thrust = 0;
	}
	///failed so far. trying to push lander left faster while on
	world.SetSpriteVisible("right", rightKeyDown);
	float thrustLeft = (-sideThrust * (float)elapsedTimeSec);
	if (!rightKeyDown)
	{
		thrustLeft = 0;
	}

	world.SetSpriteVisible("left", leftKeyDown);
	float thrustRight = (sideThrust * (float)elapsedTimeSec);
	if (!leftKeyDown)
	{
		thrustRight = 0;
	}

	// lander forces 
	world.SetSpriteForce("lander", thrust, false);
	world.SetSpriteForce("lander", thrustRight, true);
	world.SetSpriteForce("lander", thrustLeft, true);
	world.Process(elapsedTimeSec);
	world.Draw(pGfx);
	pGfx->Present(hwnd);
}


};

