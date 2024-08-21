#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "MCGraphics.cpp"
#include "TBSprite.cpp"

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

	// public functions
	void Load()
	{
		TBSprite s;
		sprites.push_back(s);
		sprites.back().Create(0, 400, 800, 200, { 205, 100, 100 });
		sprites.back().SetName("ground");
		sprites.back().SetLayer(LAYER::layer_BACK);


		sprites.push_back(s);
		sprites.back().Create(400, 380, 300, 220, { 205, 100, 100 });
		sprites.back().SetName("mtA2");
		sprites.back().SetVx(-0.05f);
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::Layer_MID);

		//mountains
		sprites.push_back(s);
		sprites.back().Create(400, 300, 100, 300, { 205, 100, 100 });
		sprites.back().SetName("mtA");
		sprites.back().SetVx(-0.1f);
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);

		sprites.push_back(s);
		sprites.back().Create(600, 250, 50, 350, { 205, 100, 100 });
		sprites.back().SetName("mtB");
		sprites.back().SetVx(-0.1f);
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);

		sprites.push_back(s);
		sprites.back().Create(0, 250, 50, 350, { 205, 100, 100 });
		sprites.back().SetName("mtC");
		sprites.back().SetVx(-0.1f);
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);

		sprites.push_back(s);
		sprites.back().Create(250,250, 50, 350, { 205, 100, 100 });
		sprites.back().SetName("mtD");
		sprites.back().SetVx(-0.1f);
		sprites.back().SetWrap(true); 
		sprites.back().SetLayer(LAYER::layer_NEAR);


		sprites.push_back(s);
		sprites.back().Create(400, 0, 20, 20, { 255, 255, 255 });
		sprites.back().SetName("lander");
		sprites.back().SetGravityOn(true);
		sprites.back().SetVx(-0.1f);
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_FRONT);
		sprites.back().SetStayAboveGround(true);

		sprites.push_back(s);
		sprites.back().Create(8, 21, 5, 15, { 0, 0, 255});  
		sprites.back().SetName("fire");
		sprites.back().SetParent(&sprites[6]);
		sprites.back().SetVisible(false);
		sprites.back().SetLayer(LAYER::layer_NONE);

		SetScrollSpeed(-0.1f);
	}

	void SetScrollSpeed(float v) 
	{
		for (int i = 0; i < sprites.size(); i++)
		{
			if (sprites[i].GetLayer() == LAYER::layer_FRONT)
			{
				sprites[i].SetVx(v);
			}
			else if (sprites[i].GetLayer() == LAYER::layer_NEAR)
			{
				sprites[i].SetVx(v * 0.75f);
			}
			else if (sprites[i].GetLayer() == LAYER::Layer_MID)
			{
				sprites[i].SetVx(v * 0.5f);
			}
			else if (sprites[i].GetLayer() == LAYER::layer_BACK)
			{
				sprites[i].SetVx(0.0f);
			}
		}
	}

	void SetSpriteVisible(string name, bool show)
	{
		for (int i = 0; i < sprites.size(); i++)
		{
			if (sprites[i].GetName() == name)
			{
				sprites[i].SetVisible(show);
			}
		}
	}

	void SetSpriteForce(string name, float force, bool isX)
	{
		for (int i = 0; i < sprites.size(); i++)
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


	void Process()
	{
		for (int i = 0; i < sprites.size(); i++)
		{
			sprites[i].Process();
		}
	}

	void Draw(MCGraphics* pGFX)
	{
		pGFX->Clear();
		for (int i = 0; i < sprites.size(); i++)
		{
			sprites[i].Draw(pGFX);
		}
	}

};