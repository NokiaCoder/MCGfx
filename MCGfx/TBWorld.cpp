#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "MCGraphics.cpp"
#include "TBSprite.cpp"
#include "TBGlobals.h"

using namespace std;

class TBWorld
{
private:
	vector<TBSprite> sprites;

public:
	// constructor / destructor
	TBWorld()
	{
	
	}
	~TBWorld()
	{
	}

	int GetSpriteIndex(const string& name)
	{
		for (int i = 0; i < sprites.size(); i++)
		{
			if (sprites[i].GetName() == name)
			{
				return i;
			}
		}
		return -1;
	}

	// public functions
	void Load()
	{
		sprites.clear();

		//pre allocate to avoid stale pointers
		sprites.reserve(1000);
		int index = -1;
		RGBTRIPLE NearColor = { 105, 100, 75 };
		RGBTRIPLE MidColor = DarkenColor({ 105, 100, 75 }, 25);
		RGBTRIPLE FIRECOLOR = { 0, 0, 255 };
		RGBTRIPLE LANDERCOLOR = { 255, 255, 255 };

		float mountMidSpeed = -0.01f;
		float mountNearSpeed = -0.03f;
		float landerSpeed = -0.0f;
		float scrollSpeed = -0.0f;
		TBSprite s;

		//mid mountains
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 4 + 10 , g_pixelHeight/2 - 15 , 50, g_pixelHeight/2 , MidColor);
		sprites.back().SetName("mtAMid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::Layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 4 + 48, g_pixelHeight / 2 - 15, 40, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("mtBMid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::Layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 4 + 55, g_pixelHeight / 2 - 25, 20, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("mtB1Mid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::Layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 288, g_pixelHeight / 2 - 25, 40, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("mtCMid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::Layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 268, g_pixelHeight / 2 - 35, 20, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("mtC1Mid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::Layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 48, g_pixelHeight / 2 - 25, 48, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("mtDMid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::Layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 28, g_pixelHeight / 2 - 35, 28, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("mtD1Mid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::Layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight / 2 - 10, g_pixelWidth, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("groundMid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::Layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(false);


		//Near mountains
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 4, g_pixelHeight - 59, 50, g_pixelHeight / 2 -10 , NearColor);
		sprites.back().SetName("mtANear");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed * scrollSpeed);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(true);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 5 + 5, g_pixelHeight - 69, 50, g_pixelHeight / 2 - 10, NearColor);
		sprites.back().SetName("mtBNear");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed * scrollSpeed);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(true);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 3 + 20 , g_pixelHeight - 52, 50, g_pixelHeight / 2 - 10, NearColor);
		sprites.back().SetName("mtCNear");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed * scrollSpeed);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(true);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth + 15, g_pixelHeight - 55, 50, g_pixelHeight / 2 - 10, NearColor);
		sprites.back().SetName("mtDNear");
		sprites.back().SetWrap(true); 
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed * scrollSpeed);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(true);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 4 + 180, g_pixelHeight - 69, 36, g_pixelHeight / 2 - 5, NearColor);
		sprites.back().SetName("mtENear");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed * scrollSpeed);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(true);

sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 4 + 206, g_pixelHeight - 74, 10, g_pixelHeight / 2 - 5, NearColor);
		sprites.back().SetName("mtE1Near");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed* scrollSpeed);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(true);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 4 + 130, g_pixelHeight - 60, 35, g_pixelHeight / 2 - 30, NearColor);
		sprites.back().SetName("mtFNear");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed * scrollSpeed);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(true);
		sprites.push_back(s);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 288, g_pixelHeight - 89, 30, g_pixelHeight / 2 - 10, NearColor);
		sprites.back().SetName("mtGNear");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed* scrollSpeed);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(true);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 278, g_pixelHeight - 68, 30, g_pixelHeight / 2 - 10, NearColor);
		sprites.back().SetName("mtG1Near");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed* scrollSpeed);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(true);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 274, g_pixelHeight - 98, 10, g_pixelHeight / 2 - 10, NearColor);
		sprites.back().SetName("mtG2Near");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed* scrollSpeed);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(true);
		
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 220, g_pixelHeight - 76, 14, g_pixelHeight / 2 - 10, NearColor);
		sprites.back().SetName("mtHNear");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed* scrollSpeed);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(true);



	

		



		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 50, g_pixelWidth, 50, NearColor); //for each change color with 3 last values in {}. { blue, green, red}
		sprites.back().SetName("ground");
		sprites.back().SetLayer(LAYER::layer_BACK);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(true);


		sprites.push_back(s);
		sprites.back().Create(140, 0, 4, 4, LANDERCOLOR);
		sprites.back().SetName("lander");
		sprites.back().SetGravityOn(true);
		sprites.back().SetVx(landerSpeed);
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_FRONT);
		sprites.back().SetStayAboveGround(true);
		sprites.back().SetHasAnimation(true);
		sprites.back().setPhysics(true);
		sprites.back().SetCollide(true);

		sprites.push_back(s);
		sprites.back().Create(1, 5, 2, 2, FIRECOLOR);
		sprites.back().SetName("fire");
		index = GetSpriteIndex("lander");
		if (index >= 0)
		{
			sprites.back().SetParent(&sprites[index]);
		}
		sprites.back().SetVisible(false);
		sprites.back().SetLayer(LAYER::layer_NONE);
		sprites.back().SetHasAnimation(true);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(5, 1, 2, 2, FIRECOLOR);
		sprites.back().SetName("right");
		index = GetSpriteIndex("lander");
		if (index >= 0)
		{
			sprites.back().SetParent(&sprites[index]);
		}
		sprites.back().SetVisible(false);
		sprites.back().SetLayer(LAYER::layer_NONE);
		sprites.back().SetHasAnimation(true);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(-3, 1, 2, 2, FIRECOLOR);
		sprites.back().SetName("left");
		index = GetSpriteIndex("lander");
		if (index >= 0)
		{
			sprites.back().SetParent(&sprites[index]);
		}
		sprites.back().SetVisible(false);
		sprites.back().SetLayer(LAYER::layer_NONE);
		sprites.back().SetHasAnimation(true);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(1, -3, 2, 2, FIRECOLOR);
		sprites.back().SetName("Up");
		index = GetSpriteIndex("lander");
		if (index >= 0)
		{
			sprites.back().SetParent(&sprites[index]);
		}
		sprites.back().SetVisible(false);
		sprites.back().SetLayer(LAYER::layer_NONE);
		sprites.back().SetHasAnimation(true);
		sprites.back().setPhysics(false);


		SetScrollSpeed(scrollSpeed);
	}
	//Sets scroll speed for each layer
	void SetScrollSpeed(float v) 
	{
		for (int i = 0; i < (int)sprites.size(); i++)
		{
			if (sprites[i].GetLayer() == LAYER::layer_FRONT)
			{
				sprites[i].SetVx(v);
			}
			else if (sprites[i].GetLayer() == LAYER::layer_NEAR)
			{
				sprites[i].SetVx(v * 0.075f);
			}
			else if (sprites[i].GetLayer() == LAYER::Layer_MID)
			{
				sprites[i].SetVx(v * 0.05f);
			}
			else if (sprites[i].GetLayer() == LAYER::layer_BACK)
			{
				sprites[i].SetVx(0.0f);
			}
		}
	}

	void SetSpriteVisible(string name, bool show)
	{
		for (int i = 0; i < (int)sprites.size(); i++)
		{
			if (sprites[i].GetName() == name)
			{
				sprites[i].SetVisible(show);
			}
		}
	}

	void SetSpriteForce(string name, float force, bool isX)
	{
		for (int i = 0; i < (int)sprites.size(); i++)
		{
			if (sprites[i].GetName() == name)
			{
				if (isX)
				{
					sprites[i].SetFx(force);
				}
				else
				{
					sprites[i].SetFy(force);
				}
			}
		}
	}

	void TestCollision()
	{
		int id = GetSpriteIndex("lander");
		if (id > -1)
		{
			sprites[id].TestCollision(sprites);
		}
	}

	void Process(double elapsedTimeSec)
	{
		for (int i = 0; i < (int)sprites.size(); i++)
		{
			sprites[i].Process(elapsedTimeSec);
		}
	}
	//Draw Function
	void Draw(MCGraphics* pGFX)
	{
		pGFX->Clear();
		for (int i = 0; i < (int)sprites.size(); i++)
		{
			sprites[i].Draw(pGFX);
		}
	}

};