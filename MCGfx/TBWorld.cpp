#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "MCGraphics.cpp"
#include "TBSprite.cpp"
#include "TBGlobals.h"
#include "ParticleSystem.h"

using namespace std;

class TBWorld
{
private:
	vector<TBSprite> sprites;
	vector<ParticleSystem> particles;


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

	int GetParticleSystemIndex(const string& name)
	{
		for (int i = 0; i < particles.size(); i++)
		{
			if (particles[i].GetName() == name)
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
		particles.clear();

		//pre allocate to avoid stale pointers
		sprites.reserve(1000);
		int index = -1;
		//mountain/fire/lander color
		RGBTRIPLE NearColor = { 105, 100, 75 };
		RGBTRIPLE MidColor = DarkenColor({ 105, 100, 75 }, 25);
		RGBTRIPLE FarColor = DarkenColor({ 105, 100, 75 }, 10);
		RGBTRIPLE SkyBoxColor = DarkenColor({ 105, 100, 75 }, 100);
		RGBTRIPLE FIRECOLOR = { 0, 0, 255 };
		RGBTRIPLE LANDERCOLOR = { 255, 255, 255 };
		RGBTRIPLE TargetCOLOR = { 0, 255, 0 };

		//Speed settings
		float mountMidSpeed = -0.01f;
		float mountNearSpeed = -0.03f;
		float landerSpeed = GetRandNorm() * 0.5f;
		float scrollSpeed = -0.0f;
		TBSprite s;

		//skylimit
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 305, g_pixelWidth, g_pixelHeight / 3, SkyBoxColor);
		sprites.back().SetName("skybox");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
	

		//Far mountains
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 4 + 10, g_pixelHeight / 2 - 35, 50, g_pixelHeight / 2, FarColor);
		sprites.back().SetName("mtAFar");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_FAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 4 + 48, g_pixelHeight / 2 - 15, 40, g_pixelHeight / 2, FarColor);
		sprites.back().SetName("mtBFar");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_FAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 4 - 15, g_pixelHeight / 2 - 25, 20, g_pixelHeight / 2, FarColor);
		sprites.back().SetName("mtB1Far");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_FAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 258, g_pixelHeight / 2 - 25, 40, g_pixelHeight / 2, FarColor);
		sprites.back().SetName("mtCFar");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_FAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 288, g_pixelHeight / 2 - 35, 20, g_pixelHeight / 2, FarColor);
		sprites.back().SetName("mtC1Far");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_FAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 28, g_pixelHeight / 2 - 25, 48, g_pixelHeight / 2, FarColor);
		sprites.back().SetName("mtDFar");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_FAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 28, g_pixelHeight / 2 - 35, 28, g_pixelHeight / 2, FarColor);
		sprites.back().SetName("mtD1far");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_FAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		//Far ground
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight / 2, g_pixelWidth, g_pixelHeight / 2, FarColor);
		sprites.back().SetName("groundFar");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_FAR);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		


		//mid mountains
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 4 + 10 , g_pixelHeight/2 + 35 , 50, g_pixelHeight/2 , MidColor);
		sprites.back().SetName("mtAMid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::Layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 4 + 48, g_pixelHeight / 2 + 30, 40, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("mtBMid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::Layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 4 + 55, g_pixelHeight / 2 + 35, 20, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("mtB1Mid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::Layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 288, g_pixelHeight / 2 + 25, 40, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("mtCMid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::Layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 268, g_pixelHeight / 2 + 15, 20, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("mtC1Mid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::Layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 48, g_pixelHeight / 2 + 25, 48, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("mtDMid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::Layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 28, g_pixelHeight / 2 + 15, 28, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("mtD1Mid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::Layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		//Mid ground
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight / 2 + 50, g_pixelWidth, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("groundMid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::Layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);



		//Near mountains
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 4, g_pixelHeight - 29, 50, g_pixelHeight / 2 -10 , NearColor);
		sprites.back().SetName("mtANear");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed * scrollSpeed);
		sprites.back().setPhysics(false);


		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 5 + 5, g_pixelHeight - 39, 50, g_pixelHeight / 2 - 10, NearColor);
		sprites.back().SetName("mtBNear");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed * scrollSpeed);
		sprites.back().setPhysics(false);


		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 3 + 20 , g_pixelHeight - 22, 50, g_pixelHeight / 2 - 10, NearColor);
		sprites.back().SetName("mtCNear");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed * scrollSpeed);
		sprites.back().setPhysics(false);


		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth + 15, g_pixelHeight - 25, 50, g_pixelHeight / 2 - 10, NearColor);
		sprites.back().SetName("mtDNear");
		sprites.back().SetWrap(true); 
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed * scrollSpeed);
		sprites.back().setPhysics(false);


		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 4 + 180, g_pixelHeight - 19, 36, g_pixelHeight / 2 - 5, NearColor);
		sprites.back().SetName("mtENear");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed * scrollSpeed);
		sprites.back().setPhysics(false);


		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 4 + 206, g_pixelHeight - 24, 10, g_pixelHeight / 2 - 5, NearColor);
		sprites.back().SetName("mtE1Near");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed* scrollSpeed);
		sprites.back().setPhysics(false);


		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 4 + 130, g_pixelHeight - 10, 35, g_pixelHeight / 2 - 30, NearColor);
		sprites.back().SetName("mtFNear");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 288, g_pixelHeight - 39, 30, g_pixelHeight / 2 - 10, NearColor);
		sprites.back().SetName("mtGNear");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed* scrollSpeed);
		sprites.back().setPhysics(false);


		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 278, g_pixelHeight - 18, 30, g_pixelHeight / 2 - 10, NearColor);
		sprites.back().SetName("mtG1Near");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed* scrollSpeed);
		sprites.back().setPhysics(false);


		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 274, g_pixelHeight - 48, 10, g_pixelHeight / 2 - 10, NearColor);
		sprites.back().SetName("mtG2Near");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed* scrollSpeed);
		sprites.back().setPhysics(false);

		
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 220, g_pixelHeight - 26, 14, g_pixelHeight / 2 - 10, NearColor);
		sprites.back().SetName("mtHNear");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountNearSpeed* scrollSpeed);
		sprites.back().setPhysics(false);
	

		//Near Ground
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 30, g_pixelWidth + 30, 50, NearColor); //for each change color with 3 last values in {}. { blue, green, red}
		sprites.back().SetName("ground");
		sprites.back().SetLayer(LAYER::layer_BACK);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(GetRandomH(), g_pixelHeight - 35, 8, 8, TargetCOLOR); //for each change color with 3 last values in {}. { blue, green, red}
		sprites.back().SetName("target");
		sprites.back().SetLayer(LAYER::layer_FRONT);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Win);

		
		

		//Lander and fire
		sprites.push_back(s);
		sprites.back().Create(140, 0, 4, 4, LANDERCOLOR);
		sprites.back().SetName("lander");
		sprites.back().SetGravityOn(true);
		sprites.back().SetVx(landerSpeed);
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_FRONT);
		sprites.back().SetStayAboveGround(true);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(true);
		sprites.back().SetCollide(CollideType::Win);
		
		//OLD THRUST SPRITE
		//sprites.push_back(s);
		//sprites.back().Create(1, 5, 2, 2, FIRECOLOR);
		//sprites.back().SetName("fire");
		//index = GetSpriteIndex("lander");
		//if (index >= 0)
		//{
		//	sprites.back().SetParent(&sprites[index]);
		//}
		//sprites.back().SetVisible(false);
		//sprites.back().SetLayer(LAYER::layer_NONE);
		//sprites.back().SetHasAnimation(true);
		//sprites.back().setPhysics(false);

		//sprites.push_back(s);
		//sprites.back().Create(5, 1, 2, 2, FIRECOLOR);
		//sprites.back().SetName("right");
		//index = GetSpriteIndex("lander");
		//if (index >= 0)
		//{
		//	sprites.back().SetParent(&sprites[index]);
		//}
		//sprites.back().SetVisible(false);
		//sprites.back().SetLayer(LAYER::layer_NONE);
		//sprites.back().SetHasAnimation(true);
		//sprites.back().setPhysics(false);

		//sprites.push_back(s);
		//sprites.back().Create(-3, 1, 2, 2, FIRECOLOR);
		//sprites.back().SetName("left");
		//index = GetSpriteIndex("lander");
		//if (index >= 0)
		//{
		//	sprites.back().SetParent(&sprites[index]);
		//}
		//sprites.back().SetVisible(false);
		//sprites.back().SetLayer(LAYER::layer_NONE);
		//sprites.back().SetHasAnimation(true);
		//sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(300, g_pixelHeight -10 , 400, 300, FIRECOLOR);
		sprites.back().SetName("winText");
		sprites.back().SetSpriteText("YOU WIN!!!!\nHit SPACE to play again.");
		sprites.back().SetIsTextSprite(true);
		sprites.back().SetVisible(false);
		sprites.back().SetLayer(LAYER::layer_FRONT);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetLifeTime(50.0f);

		sprites.push_back(s);
		sprites.back().Create(720, 10, 400, 300, FIRECOLOR);
		sprites.back().SetName("scoreText");
		sprites.back().SetSpriteText("SCORE\n<score>");
		sprites.back().SetIsTextSprite(true);
		sprites.back().SetVisible(true);
		sprites.back().SetLayer(LAYER::layer_FRONT);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);

		//set pointers
		int targetIndex = GetSpriteIndex("target");
		index = GetSpriteIndex("winText");
		if (index >= 0)
		{
			sprites[targetIndex].SetShowOnCollide(&sprites[index]);
		}

		//add particle systems
		ParticleSystem ps;
		particles.push_back(ps);
		particles.back().Create(138, 141, "volcano");
		particles.back().SetParticleColor({ 100,255,255 });
		particles.back().SetMag(10.0f);
		particles.back().SetRangeDeg(240, 300);
		particles.back().SetLifespan(4.0f);
		particles.back().SetGravityOn(true);

		particles.push_back(ps);
		particles.back().Create(138, 141, "volcano1");
		particles.back().SetParticleColor({ 100,100,255 });
		particles.back().SetMag(10.0f);
		particles.back().SetRangeDeg(240, 300);
		particles.back().SetLifespan(4.0f);
		particles.back().SetGravityOn(true);

		particles.push_back(ps);
		particles.back().Create(2, 5, "thrust");
		particles.back().SetParticleColor({ 0,0,255 });
		particles.back().SetMag(60.0f);
		particles.back().SetRangeDeg(80, 100);
		particles.back().SetLifespan(0.1f);
		particles.back().SetGravityOn(false);
		index = GetSpriteIndex("lander");
		if (index >= 0)
		{
			particles.back().SetParent(&sprites[index]);
		}

		particles.push_back(ps);
		particles.back().Create(6, 1, "thrust2");
		particles.back().SetParticleColor({ 0,0,255 });
		particles.back().SetMag(60.0f);
		particles.back().SetRangeDeg(20, -20);
		particles.back().SetLifespan(0.1f);
		particles.back().SetGravityOn(false);
		index = GetSpriteIndex("lander");
		if (index >= 0)
		{
			particles.back().SetParent(&sprites[index]);
		}

		particles.push_back(ps);
		particles.back().Create(-1, 1, "thrust3");
		particles.back().SetParticleColor({ 0,0,255 });
		particles.back().SetMag(60.0f);
		particles.back().SetRangeDeg(160, 200);
		particles.back().SetLifespan(0.1f);
		particles.back().SetGravityOn(false);
		index = GetSpriteIndex("lander");
		if (index >= 0)
		{
			particles.back().SetParent(&sprites[index]);
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

	void SetParticleSystemActive(string name, bool on)
	{
		int index = GetParticleSystemIndex(name);
		if (index >= 0)
		{
			particles[index].SetActive(on);
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

		for (int i = 0; i < (int)particles.size(); i++)
		{
			particles[i].Process(elapsedTimeSec);
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

		for (int i = 0; i < (int)particles.size(); i++)
		{
			particles[i].Draw(pGFX);
			
		}
	}

};