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

		sprites.push_back(s);
		sprites.back().Create(400, 0, 20, 20, { 255, 255, 255 });
		sprites.back().SetName("lander");
		sprites.back().SetGravityOn(true);
		sprites.back().SetVx(0.1f);
		sprites.back().SetWrap(true);


		sprites.push_back(s);
		sprites.back().Create(8, 21, 5, 15, { 0, 0, 255});
		sprites.back().SetName("fire");
		sprites.back().SetParent(&sprites[1]);
		sprites.back().SetVisible(false);

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