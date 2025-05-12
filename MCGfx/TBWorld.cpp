#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include "MCGraphics.cpp"
#include "TBSprite.cpp"
#include "TBHitTarget.h"
#include "TBGlobals.h"
#include "ParticleSystem.h"

using namespace std;



class TBWorld
{

private:
	vector<TBSprite> sprites;
	vector<TBSprite> tempSprites;
	vector<ParticleSystem> particleSystems;
	deque<CollisionInfo>* pCollisions = nullptr;
	vector<TBTexture> textures;

	//Loading values

	//pre allocate to avoid stale pointers
	//int index = -1;
	//int psIndex = -1;


	//mountain/fire/lander color
	//for each change color with 3 last values in {}.{blue green,red}
	RGBTRIPLE NearColor = { 75, 75, 45 };
	RGBTRIPLE NearGroundColor = { 0, 50, 200 };
	RGBTRIPLE MidColor = DarkenColor({ 105, 100, 75 }, 25);
	RGBTRIPLE FarColor = DarkenColor({ 105, 100, 75 }, 10);
	RGBTRIPLE SkyBoxColor = DarkenColor({ 105, 100, 75 }, 100);
	RGBTRIPLE FIRECOLOR = { 10, 10, 255 };
	RGBTRIPLE LANDERCOLOR = { 100, 201, 200 };
	RGBTRIPLE TargetCOLOR = { 1, 255, 3 };
	RGBTRIPLE MeteorCOLOR = { 255, 200, 200 };
	RGBTRIPLE PowerUpCOLOR = { 255,255, 0 };
	RGBTRIPLE BLACKBOXCOLOR = { 1,0, 0 };
	RGBTRIPLE CANYONWALLCOLOR = DarkenColor({ 0, 50, 100 }, 40);
	RGBTRIPLE ASTEROIDCOLOR = { 81, 81, 85 };

	bool shootKeyDown = false;



	string name;

public:
	// constructor / destructor
	TBWorld()
	{
	
	}
	~TBWorld()
	{
	}


	void MoveParticleSystem(string name, int mx, int my)
	{
		ParticleSystem* pS = GetParticleSystem(name);

		int x = (int)pS->GetEmitterX();
		int y = (int)pS->GetEmitterY();

		pS->SetPosParticleSystem(x + (float)mx, y + (float)my);
	}
	void MoveSprite(string name, int mx, int my)
	{
		TBSprite* pSprite = GetSprite(name);
		int x = (int)pSprite->GetX();
		int y = (int)pSprite->GetY();

		pSprite->SetPos((float)(x + mx), (float)(y + my));

	}
	int GetSpriteCount()
	{
		return (int)sprites.size();
	}
	TBSprite* GetSpriteAtIndex(int index)
	{
		if (index >= 0 && index < GetSpriteCount())
		{
			return &sprites[index];
		}
		return nullptr;
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
	TBSprite* GetSprite(const string& name)
	{
		int index = GetSpriteIndex(name);
		if (index >= 0)
		{
			return &sprites[index];
		}
		return nullptr;
	}
	void SetSpriteText(const string& name, string s)
	{
		TBSprite* pS = GetSprite(name);
		if (pS != nullptr)
		{
			pS->SetSpriteText(s);
		}
	}
	int GetParticleSystemCount()
	{
		return (int)particleSystems.size();
	}
	int GetParticleSystemIndex(const string& name)
	{
		for (int i = 0; i < static_cast<int>(particleSystems.size()); i++)
		{
			if (particleSystems[i].GetName() == name)
			{
				return i;
			}
		}
		return -1;
	}
	ParticleSystem* GetParticleSystem(const string& name)
	{
		int index = GetParticleSystemIndex(name);
		if (index >= 0)
		{
			return &particleSystems[index];
		}
		return nullptr;
	}
	ParticleSystem* GetParticleSystemAtIndex(int index)
	{
		if (index >= 0 && index < GetParticleSystemCount())
		{
			return &particleSystems[index];
		}
		return nullptr;
	}
	void SetParticlesParent(const string& name, const string& parentSpriteName)
	{
		ParticleSystem* pPS = GetParticleSystem(name);
		TBSprite* pS = GetSprite(parentSpriteName);
		pPS->SetParent(pS);
	}
	TBSprite* AddSprite()
	{
		TBSprite s;
		sprites.push_back(s);
		return &sprites.back();
	}
	ParticleSystem* AddParticleSystem()
	{
		ParticleSystem s;
		particleSystems.push_back(s);
		return &particleSystems.back();
	}
	vector<TBSprite>* GetSprites()
	{
		return &sprites;
	}
	vector<ParticleSystem>* GetParticleSystems()
	{
		return &particleSystems;
	}
	vector<TBSprite>* GetTempSprites()
	{
		return &tempSprites;
	}
	bool GetShootKeyDown()
	{
		return shootKeyDown;
	}
	void SetShootKeyDown(bool down)
	{
		shootKeyDown = down;
	}
	

	// public functions
	void PreLoad()
	{
		sprites.clear();
		particleSystems.clear();

		//pre allocate to avoid stale pointers
		sprites.reserve(1000);
		particleSystems.reserve(1000);
		int index = -1;
		int psIndex = -1;

		int enemyCount = 2 * g_LevelOn;

		//mountain/fire/lander color
		RGBTRIPLE NearColor = { 75, 75, 45 };
		RGBTRIPLE NearGroundColor = { 105, 100, 75 };
		RGBTRIPLE MidColor = DarkenColor({ 105, 100, 75 }, 25);
		RGBTRIPLE FarColor = DarkenColor({ 105, 100, 75 }, 10);
		RGBTRIPLE SkyBoxColor = DarkenColor({ 105, 100, 75 }, 100);
		RGBTRIPLE FIRECOLOR = { 10, 10, 255 };
		RGBTRIPLE LANDERCOLOR = { 100, 201, 200 };
		RGBTRIPLE TargetCOLOR = { 1, 255, 3 };
		RGBTRIPLE MeteorCOLOR = { 255, 200, 200 };
		RGBTRIPLE PowerUpCOLOR = { 255,255, 0 };
		RGBTRIPLE LANDERCOLORW = { 0, 0, 0 };

		//Speed settings
		float mountMidSpeed = -0.01f;
		float mountNearSpeed = -0.03f;
		float landerSpeed = GetRandRange(-1.0f, 1.0f);
		float scrollSpeed = -0.0f;
	}

	void Load(MCGraphics* pGFX)
	{
		sprites.clear();
		particleSystems.clear();

		//pre allocate to avoid stale pointers
		int index = -1;
		int psIndex = -1;

		int enemyCount = 2 * g_LevelOn;

		pGFX->SetColorText({ 255, 255, 0 });

		//mountain/fire/lander color
		RGBTRIPLE NearColor = { 75, 75, 45 };
		RGBTRIPLE NearGroundColor = { 105, 100, 75 };
		RGBTRIPLE MidColor = DarkenColor({ 105, 100, 75 }, 25);
		RGBTRIPLE FarColor = DarkenColor({ 105, 100, 75 }, 10);
		RGBTRIPLE SkyBoxColor = DarkenColor({ 105, 100, 75 }, 100);
		RGBTRIPLE FIRECOLOR = { 10, 10, 255 };
		RGBTRIPLE LANDERCOLOR = { 100, 201, 200 };
		RGBTRIPLE TargetCOLOR = { 1, 255, 3 };
		RGBTRIPLE MeteorCOLOR = { 255, 200, 200 };
		RGBTRIPLE PowerUpCOLOR = { 255,255, 0 };
		RGBTRIPLE BLACKBOXCOLOR = { 1,0, 0 };

		//Speed settings
		float mountMidSpeed = -0.01f;
		float mountNearSpeed = -0.03f;
		float landerSpeed = GetRandRange(-0.5f, 0.5f);
		float scrollSpeed = -0.0f;
		TBSprite s;

		//skylimit
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 305, g_pixelWidth, g_pixelHeight / 3, SkyBoxColor);
		sprites.back().SetName("skybox");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(false);
		sprites.back().SetCollide(CollideType::Lose);
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
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 4 + 48, g_pixelHeight / 2 + 30, 40, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("mtBMid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 4 + 55, g_pixelHeight / 2 + 35, 20, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("mtB1Mid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 288, g_pixelHeight / 2 + 25, 40, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("mtCMid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 268, g_pixelHeight / 2 + 15, 20, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("mtC1Mid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 48, g_pixelHeight / 2 + 25, 48, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("mtDMid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 28, g_pixelHeight / 2 + 15, 28, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("mtD1Mid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(true);
		sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		sprites.back().setPhysics(false);

		//Mid ground
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight / 2 + 50, g_pixelWidth, g_pixelHeight / 2, MidColor);
		sprites.back().SetName("groundMid");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_MID);
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

		//Enemies/comets
		for (int i = 0; i < enemyCount; i++)
		{
			sprites.push_back(s);
			sprites.back().Create(0, static_cast<int>(GetRandRange(20.0f, 160.0f)), 2, 2, MeteorCOLOR);
			sprites.back().SetName("meteor" + to_string(i));
			sprites.back().SetWrap(true);
			sprites.back().SetLayer(LAYER::layer_NEAR);
			sprites.back().SetHasAnimation(true);
			sprites.back().SetAnimationX(GetRandRange(-10.0f, 10.0f) * 10.0f);
			sprites.back().setPhysics(false);
			sprites.back().SetCollide(CollideType::Lose);
			sprites.back().SetGravityOn(false);
		}

		//powerup
		for (int i = 0; i < enemyCount; i++)
		{
			sprites.push_back(s);
			sprites.back().Create(0, static_cast<int>(GetRandRange(20.0f, 160.0f)), 2, 2, PowerUpCOLOR);
			sprites.back().SetName("powerup" + to_string(i));
			sprites.back().SetWrap(true);
			sprites.back().SetLayer(LAYER::layer_NEAR);
			sprites.back().SetHasAnimation(true);
			sprites.back().SetAnimationX(GetRandRange(-10.0f, 10.0f) * 10.0f);
			sprites.back().setPhysics(false);
			sprites.back().SetCollide(CollideType::PowerUp);
			sprites.back().SetGravityOn(false);
		}

		//Near Ground
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 30, g_pixelWidth + 30, 50, NearGroundColor); //for each change color with 3 last values in {}. { blue, green, red}
		sprites.back().SetName("ground");
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth/2, g_pixelHeight - 35, 8, 8, TargetCOLOR); //for each change color with 3 last values in {}. { blue, green, red}
		sprites.back().SetName("target");
		sprites.back().SetLayer(LAYER::layer_FRONT);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Win);

		
		

		//Lander and attachments
		sprites.push_back(s);
		sprites.back().Create(140, 0, 4, 4, LANDERCOLOR);
		sprites.back().SetName("lander");
		sprites.back().SetGravityOn(true);
		sprites.back().SetVx(landerSpeed);
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_FRONT);
		sprites.back().SetStayAboveGround(true);
		sprites.back().setPhysics(true);
		sprites.back().SetCollide(CollideType::Win);
		sprites.back().SetExplodeOnCollide(true);

		sprites.push_back(s);
		sprites.back().Create(1, -4, 2, 3, LANDERCOLOR);
		sprites.back().SetName("landerHead");
		sprites.back().SetParent(GetSprite("lander"));
		sprites.back().SetVisible(true);
		sprites.back().SetLayer(LAYER::layer_FRONT);
		sprites.back().setPhysics(false);
		sprites.back().SetWrap(true);
		
		//FOUND ERROR if sprite is in x = -1,-2,-3,etc it will do the corner error
		//broken one
		sprites.push_back(s);
		sprites.back().Create(-1, 2, 2, 2, LANDERCOLOR);
		sprites.back().SetName("Left lander wing1");
		sprites.back().SetParent(GetSprite("lander"));
		sprites.back().SetVisible(true);
		sprites.back().SetLayer(LAYER::layer_FRONT);
		sprites.back().setPhysics(false);
		sprites.back().SetWrap(true);

		sprites.push_back(s);
		sprites.back().Create(3, 2, 2, 2, LANDERCOLOR);
		sprites.back().SetName("right lander wing1");
		sprites.back().SetParent(GetSprite("lander"));
		sprites.back().SetVisible(true);
		sprites.back().SetLayer(LAYER::layer_FRONT);
		sprites.back().setPhysics(false);
		sprites.back().SetWrap(true);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight/3, g_pixelWidth, g_pixelHeight, FIRECOLOR);
		sprites.back().SetName("wintext");
		sprites.back().SetSpriteText("YOU WIN!!!!\n\nHit SPACE\nto play again.");
		sprites.back().SetTextAlign(TEXT_ALIGN::CENTER);
		sprites.back().SetIsTextSprite(true);
		sprites.back().SetVisible(false);
		sprites.back().SetLayer(LAYER::layer_HUD);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetLifeTime(50.0f);
		sprites.back().SetScreen(true);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight / 3, g_pixelWidth, g_pixelHeight, FIRECOLOR);
		sprites.back().SetName("wingametext");
		sprites.back().SetSpriteText("YOU WIN!!!!");
		sprites.back().SetTextAlign(TEXT_ALIGN::CENTER);
		sprites.back().SetIsTextSprite(true);
		sprites.back().SetVisible(false);
		sprites.back().SetLayer(LAYER::layer_HUD);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetLifeTime(50.0f);
		sprites.back().SetScreen(true);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight / 3, g_pixelWidth, g_pixelHeight, FIRECOLOR);
		sprites.back().SetName("losetext");
		sprites.back().SetSpriteText("YOU CRASHED!!\n\nHit SPACE\nto play again.");
		sprites.back().SetTextAlign(TEXT_ALIGN::CENTER);
		sprites.back().SetIsTextSprite(true);
		sprites.back().SetVisible(false);
		sprites.back().SetLayer(LAYER::layer_HUD);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetLifeTime(50.0f);
		sprites.back().SetScreen(true);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight / 3, g_pixelWidth, g_pixelHeight, FIRECOLOR);
		sprites.back().SetTextAlign(TEXT_ALIGN::CENTER);
		sprites.back().SetName("losegametext");
		sprites.back().SetSpriteText("GAME OVER");
		sprites.back().SetIsTextSprite(true);
		sprites.back().SetVisible(false);
		sprites.back().SetLayer(LAYER::layer_HUD);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetLifeTime(50.0f);
		sprites.back().SetScreen(true);

		sprites.push_back(s);
		sprites.back().Create(0, 5, g_pixelWidth-5, g_pixelHeight, FIRECOLOR);
		sprites.back().SetTextAlign(TEXT_ALIGN::RIGHT);
		sprites.back().SetName("scoretext");
		sprites.back().SetSpriteText("");
		sprites.back().SetIsTextSprite(true);
		sprites.back().SetVisible(true);
		sprites.back().SetLayer(LAYER::layer_HUD);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetScreen(true);

		sprites.push_back(s);
		sprites.back().Create(0, 20 , g_pixelWidth - 5, g_pixelHeight + 10, FIRECOLOR);
		sprites.back().SetTextAlign(TEXT_ALIGN::RIGHT);
		sprites.back().SetName("livestext");
		sprites.back().SetSpriteText("");
		sprites.back().SetIsTextSprite(true);
		sprites.back().SetVisible(true);
		sprites.back().SetLayer(LAYER::layer_HUD);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetScreen(true);

		sprites.push_back(s);
		sprites.back().Create(5, 5, g_pixelWidth - 5, g_pixelHeight, FIRECOLOR);
		sprites.back().SetTextAlign(TEXT_ALIGN::LEFT);
		sprites.back().SetName("fueltext");
		sprites.back().SetSpriteText("");
		sprites.back().SetIsTextSprite(true);
		sprites.back().SetVisible(true);
		sprites.back().SetLayer(LAYER::layer_HUD);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetScreen(true);

		//add particle systems
		ParticleSystem ps;
		particleSystems.push_back(ps);
		particleSystems.back().Create(138, 141, "volcano");
		particleSystems.back().SetParticleColor({ 100,255,255 });
		particleSystems.back().SetSpawnRadius(0.0f, 0.0f);
		particleSystems.back().SetParams(240, 300, 15.0f);
		particleSystems.back().SetLifespan(3.0f);
		particleSystems.back().SetGravityOn(true);
		particleSystems.back().SetLayer(LAYER::layer_MID);
		particleSystems.back().SetActive(true);

		particleSystems.push_back(ps);
		particleSystems.back().Create(138, 141, "volcano1");
		particleSystems.back().SetParticleColor({ 100,100,255 });
		particleSystems.back().SetSpawnRadius(0.0f, 0.0f);
		particleSystems.back().SetParams(240, 300, 15.0f);
		particleSystems.back().SetLifespan(3.0f);
		particleSystems.back().SetGravityOn(true);
		particleSystems.back().SetLayer(LAYER::layer_MID);
		particleSystems.back().SetActive(true);

		particleSystems.push_back(ps);
		particleSystems.back().Create(2, 5, "thrust");
		particleSystems.back().SetParticleColor({ 0,0,255 });
		particleSystems.back().SetSpawnRadius(0.0f, 0.0f);
		particleSystems.back().SetParams(80, 100, 20.0f);
		particleSystems.back().SetLifespan(0.2f);
		particleSystems.back().SetGravityOn(false);
		particleSystems.back().SetLayer(LAYER::layer_FRONT);
		particleSystems.back().SetEmitRate(10.0f);

		particleSystems.push_back(ps);
		particleSystems.back().Create(6, 3, "thrust2"); //right
		particleSystems.back().SetParticleColor({ 0,0,255 });
		particleSystems.back().SetSpawnRadius(0.0f, 0.0f);
		particleSystems.back().SetParams(20, -20, 20.0f);
		particleSystems.back().SetLifespan(0.2f);
		particleSystems.back().SetGravityOn(false);
		particleSystems.back().SetLayer(LAYER::layer_FRONT);
		particleSystems.back().SetEmitRate(10.0f);

		particleSystems.push_back(ps);
		particleSystems.back().Create(-2, 3, "thrust3"); //left
		particleSystems.back().SetParticleColor({ 0,0,255 });
		particleSystems.back().SetSpawnRadius(0.0f, 0.0f);
		particleSystems.back().SetParams(160, 200, 20.0f);
		particleSystems.back().SetLifespan(0.2f);
		particleSystems.back().SetGravityOn(false);
		particleSystems.back().SetLayer(LAYER::layer_FRONT);
		particleSystems.back().SetEmitRate(10.0f);

		particleSystems.push_back(ps);
		particleSystems.back().Create((float)g_pixelWidth/2, 20.0f, "Stars");
		particleSystems.back().SetParticleColor({ 180,180,180 });
		particleSystems.back().SetSpawnRadius(0.0f, 300.0f);
		particleSystems.back().SetParams(0, 360, 0.0f);
		particleSystems.back().SetLifespan(-1.0f);
		particleSystems.back().SetGravityOn(false);
		particleSystems.back().SetLayer(LAYER::layer_BACK);
		particleSystems.back().SetEmitRate(100.0f);
		particleSystems.back().SetEmitDurationSec(10.0f);
		particleSystems.back().SetActive(true);

		particleSystems.push_back(ps);
		particleSystems.back().Create(0, 0, "explosion");
		particleSystems.back().SetParticleColor(LANDERCOLOR);
		particleSystems.back().SetSpawnRadius(0.0f, 5.0f);
		particleSystems.back().SetParams(0, 360, 40.0f);
		particleSystems.back().SetLifespan(3.0f);
		particleSystems.back().SetGravityOn(false);
		particleSystems.back().SetLayer(LAYER::layer_FRONT);
		particleSystems.back().SetEmitRate(400.0f);
		particleSystems.back().SetEmitDurationSec(0.5f);
		particleSystems.back().SetActive(false);


		//Set Particle System Parents
		index = GetSpriteIndex("lander");
		psIndex = GetParticleSystemIndex("thrust");
		particleSystems[psIndex].SetParent(&sprites[index]);
		psIndex = GetParticleSystemIndex("thrust2");
		particleSystems[psIndex].SetParent(&sprites[index]);
		psIndex = GetParticleSystemIndex("thrust3");
		particleSystems[psIndex].SetParent(&sprites[index]);
	}

	//TODO STAGE ADDITIONAL GAMES
	void Load2(MCGraphics* pGFX)
	{
		sprites.clear();
		particleSystems.clear();
		textures.clear();

		pGFX->SetColorText({ 0, 255, 255 });

		//pre allocate to avoid stale pointers
		int index = -1;
		int psIndex = -1;

		int enemyCount = 2 * g_LevelOn;

		//LoadTextures
		textures.reserve(100);
		TBTexture tex;
		textures.push_back(tex);
		textures.back().Load(GetContentFolder() + "\\ship.bmp");
		textures.push_back(tex);
		textures.back().Load(GetContentFolder() + "\\Untitled.bmp");
		textures.push_back(tex);
		textures.back().Load(GetContentFolder() + "\\bullet.bmp");

		pGFX->SetBackgroundColor(DarkenColor({ 80, 120, 180 },50));

		//Speed settings
		float landerSpeed = GetRandRange(-1.0f, 1.0f);
		float scrollSpeed = -0.0f;



		TBSprite s;



		//Bullet
		sprites.push_back(s);
		sprites.back().Create(0, 0, 4, 1, { 255, 255, 255 });
		sprites.back().SetVisible(false);
		sprites.back().SetName("bullet");
		sprites.back().SetLayer(LAYER::layer_FRONT);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);

		//target
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth/2, g_pixelHeight - 94, 8, 8, TargetCOLOR); //for each change color with 3 last values in {}. { blue, green, red}
		sprites.back().SetName("target");
		sprites.back().SetLayer(LAYER::layer_FRONT);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Win);
		sprites.back().SetVisible(false);
		
		//Lander and attachments
		sprites.push_back(s);
		sprites.back().Create(140, 0, 5, 5, LANDERCOLOR);
		sprites.back().SetName("lander");
		sprites.back().SetGravityOn(true);
		sprites.back().SetVx(landerSpeed);
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_FRONT);
		sprites.back().SetStayAboveGround(true);
		sprites.back().setPhysics(true);
		sprites.back().SetCollide(CollideType::Win);
		sprites.back().SetExplodeOnCollide(true);
		sprites.back().SetTexture(&textures[0]);

		//Load2Terrain
		Load2_Terrain(pGFX);

		//text
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight / 3, g_pixelWidth, g_pixelHeight, FIRECOLOR);
		sprites.back().SetName("wintext");
		sprites.back().SetSpriteText("YOU WIN!!!!\n\nHit SPACE\nto play again.");
		sprites.back().SetTextAlign(TEXT_ALIGN::CENTER);
		sprites.back().SetIsTextSprite(true);
		sprites.back().SetVisible(false);
		sprites.back().SetLayer(LAYER::layer_HUD);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetLifeTime(50.0f);
		sprites.back().SetScreen(true);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight / 3, g_pixelWidth, g_pixelHeight, FIRECOLOR);
		sprites.back().SetName("wingametext");
		sprites.back().SetSpriteText("YOU WIN!!!!");
		sprites.back().SetTextAlign(TEXT_ALIGN::CENTER);
		sprites.back().SetIsTextSprite(true);
		sprites.back().SetVisible(false);
		sprites.back().SetLayer(LAYER::layer_HUD);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetLifeTime(50.0f);
		sprites.back().SetScreen(true);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight / 3, g_pixelWidth, g_pixelHeight, FIRECOLOR);
		sprites.back().SetName("losetext");
		sprites.back().SetSpriteText("YOU CRASHED!!\n\nHit SPACE\nto play again.");
		sprites.back().SetTextAlign(TEXT_ALIGN::CENTER);
		sprites.back().SetIsTextSprite(true);
		sprites.back().SetVisible(false);
		sprites.back().SetLayer(LAYER::layer_HUD);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetLifeTime(50.0f);
		sprites.back().SetScreen(true);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight / 3, g_pixelWidth, g_pixelHeight, FIRECOLOR);
		sprites.back().SetTextAlign(TEXT_ALIGN::CENTER);
		sprites.back().SetName("losegametext");
		sprites.back().SetSpriteText("GAME OVER");
		sprites.back().SetIsTextSprite(true);
		sprites.back().SetVisible(false);
		sprites.back().SetLayer(LAYER::layer_HUD);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetLifeTime(50.0f);
		sprites.back().SetScreen(true);

		sprites.push_back(s);
		sprites.back().Create(0, 5, g_pixelWidth - 5, g_pixelHeight, FIRECOLOR);
		sprites.back().SetTextAlign(TEXT_ALIGN::RIGHT);
		sprites.back().SetName("scoretext");
		sprites.back().SetSpriteText("");
		sprites.back().SetIsTextSprite(true);
		sprites.back().SetVisible(true);
		sprites.back().SetLayer(LAYER::layer_HUD);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetScreen(true);

		sprites.push_back(s);
		sprites.back().Create(0, 20, g_pixelWidth - 5, g_pixelHeight + 10, FIRECOLOR);
		sprites.back().SetTextAlign(TEXT_ALIGN::RIGHT);
		sprites.back().SetName("livestext");
		sprites.back().SetSpriteText("");
		sprites.back().SetIsTextSprite(true);
		sprites.back().SetVisible(true);
		sprites.back().SetLayer(LAYER::layer_HUD);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetScreen(true);

		sprites.push_back(s);
		sprites.back().Create(5, 5, g_pixelWidth - 5, g_pixelHeight, FIRECOLOR);
		sprites.back().SetTextAlign(TEXT_ALIGN::LEFT);
		sprites.back().SetName("fueltext");
		sprites.back().SetSpriteText("");
		sprites.back().SetIsTextSprite(true);
		sprites.back().SetVisible(true);
		sprites.back().SetLayer(LAYER::layer_HUD);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetScreen(true);

		//add particle systems
		ParticleSystem ps;
		particleSystems.push_back(ps);
		particleSystems.back().Create(100, (float)(g_pixelHeight - 30), "volcano");
		particleSystems.back().SetParticleColor({ 100,255,255 });
		particleSystems.back().SetSpawnRadius(0.0f, 0.0f);
		particleSystems.back().SetParams(220, 320, 10.0f);
		particleSystems.back().SetLifespan(1.5f);
		particleSystems.back().SetGravityOn(true);
		particleSystems.back().SetLayer(LAYER::layer_MID);
		particleSystems.back().SetActive(true);

		particleSystems.push_back(ps);
		particleSystems.back().Create(100, (float)(g_pixelHeight - 30), "volcano1");
		particleSystems.back().SetParticleColor({ 100,100,255 });
		particleSystems.back().SetSpawnRadius(0.0f, 0.0f);
		particleSystems.back().SetParams(220, 320, 10.0f);
		particleSystems.back().SetLifespan(1.5f);
		particleSystems.back().SetGravityOn(true);
		particleSystems.back().SetLayer(LAYER::layer_MID);
		particleSystems.back().SetActive(true);

		//Smoke
		particleSystems.push_back(ps);
		particleSystems.back().Create(6, 5, "smoke1");
		particleSystems.back().SetParticleColor({ 50,50,50 });
		particleSystems.back().SetSpawnRadius(0.0f, 0.0f);
		particleSystems.back().SetParams(0, 360, 0.5f);
		particleSystems.back().SetLifespan(15.0f);
		particleSystems.back().SetGravityOn(false);
		particleSystems.back().SetLayer(LAYER::layer_MID);
		particleSystems.back().SetActive(true);
		particleSystems.back().SetDeleteOnWin(true);
		particleSystems.back().SetParent(GetSprite("lander"));

		particleSystems.push_back(ps);
		particleSystems.back().Create(6, 5, "smoke2");
		particleSystems.back().SetParticleColor({ 100,100,100 });
		particleSystems.back().SetSpawnRadius(0.0f, 0.0f);
		particleSystems.back().SetParams(0, 360, 0.5f);
		particleSystems.back().SetLifespan(15.0f);
		particleSystems.back().SetGravityOn(false);
		particleSystems.back().SetLayer(LAYER::layer_MID);
		particleSystems.back().SetActive(true);
		particleSystems.back().SetDeleteOnWin(true);
		particleSystems.back().SetParent(GetSprite("lander"));


		particleSystems.push_back(ps);
		particleSystems.back().Create(6, 5, "thrust");
		particleSystems.back().SetParticleColor({ 0,0,255 });
		particleSystems.back().SetSpawnRadius(0.0f, 0.0f);
		particleSystems.back().SetParams(80, 100, 20.0f);
		particleSystems.back().SetLifespan(0.2f);
		particleSystems.back().SetGravityOn(false);
		particleSystems.back().SetLayer(LAYER::layer_FRONT);
		particleSystems.back().SetEmitRate(10.0f);

		particleSystems.push_back(ps);
		particleSystems.back().Create(6, 5, "thrust2"); //right
		particleSystems.back().SetParticleColor({ 0,0,255 });
		particleSystems.back().SetSpawnRadius(0.0f, 0.0f);
		particleSystems.back().SetParams(20, -20, 20.0f);
		particleSystems.back().SetLifespan(0.2f);
		particleSystems.back().SetGravityOn(false);
		particleSystems.back().SetLayer(LAYER::layer_FRONT);
		particleSystems.back().SetEmitRate(10.0f);

		particleSystems.push_back(ps);
		particleSystems.back().Create(6, 5, "thrust3"); //left
		particleSystems.back().SetParticleColor({ 0,0,255 });
		particleSystems.back().SetSpawnRadius(0.0f, 0.0f);
		particleSystems.back().SetParams(160, 200, 20.0f);
		particleSystems.back().SetLifespan(0.2f);
		particleSystems.back().SetGravityOn(false);
		particleSystems.back().SetLayer(LAYER::layer_FRONT);
		particleSystems.back().SetEmitRate(10.0f);

		particleSystems.push_back(ps);
		particleSystems.back().Create((float)g_pixelWidth / 2, 20.0f, "Stars");
		particleSystems.back().SetParticleColor({ 180,180,180 });
		particleSystems.back().SetSpawnRadius(0.0f, 300.0f);
		particleSystems.back().SetParams(0, 360, 0.0f);
		particleSystems.back().SetLifespan(-1.0f);
		particleSystems.back().SetGravityOn(false);
		particleSystems.back().SetLayer(LAYER::layer_BACK);
		particleSystems.back().SetEmitRate(100.0f);
		particleSystems.back().SetEmitDurationSec(10.0f);
		particleSystems.back().SetActive(true);

		particleSystems.push_back(ps);
		particleSystems.back().Create(0, 0, "explosion");
		particleSystems.back().SetParticleColor(LANDERCOLOR);
		particleSystems.back().SetSpawnRadius(0.0f, 5.0f);
		particleSystems.back().SetParams(0, 360, 40.0f);
		particleSystems.back().SetLifespan(3.0f);
		particleSystems.back().SetGravityOn(false);
		particleSystems.back().SetLayer(LAYER::layer_FRONT);
		particleSystems.back().SetEmitRate(400.0f);
		particleSystems.back().SetEmitDurationSec(0.5f);
		particleSystems.back().SetActive(false);


		//Set Particle System Parents
		index = GetSpriteIndex("lander");
		psIndex = GetParticleSystemIndex("thrust");
		particleSystems[psIndex].SetParent(&sprites[index]);
		psIndex = GetParticleSystemIndex("thrust2");
		particleSystems[psIndex].SetParent(&sprites[index]);
		psIndex = GetParticleSystemIndex("thrust3");
		particleSystems[psIndex].SetParent(&sprites[index]);
	}
	void Load2_Terrain(MCGraphics* pGFX)
	{
		TBSprite s;
		
		//skylimit 
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 305, g_pixelWidth, g_pixelHeight / 3, SkyBoxColor);
		sprites.back().SetName("Out");
		sprites.back().SetWrap(true);
		sprites.back().SetLayer(LAYER::layer_NEAR);
		sprites.back().SetHasAnimation(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.back().setPhysics(false);

		//Lava
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 30, g_pixelWidth + 30, 50, NearGroundColor);
		sprites.back().SetName("lava");
		sprites.back().SetLayer(LAYER::layer_FAR);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 30, g_pixelWidth + 30, 50, NearGroundColor);
		sprites.back().SetName("lava");
		sprites.back().SetLayer(LAYER::layer_FAR);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		//Lava island
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 2 - 6, g_pixelHeight - 86, g_pixelWidth / 15, 80, CANYONWALLCOLOR);
		sprites.back().SetName("lavaisland1");
		sprites.back().SetLayer(LAYER::layer_FAR);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 2 - 11, g_pixelHeight - 11, g_pixelWidth / 15 + 10, 5, CANYONWALLCOLOR);
		sprites.back().SetName("lavaisland2");
		sprites.back().SetLayer(LAYER::layer_FAR);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 2 - 8, g_pixelHeight - 16, g_pixelWidth / 15 + 4, 5, CANYONWALLCOLOR);
		sprites.back().SetName("lavaisland3");
		sprites.back().SetLayer(LAYER::layer_FAR);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 2 - 9, g_pixelHeight - 40, 4, 4, CANYONWALLCOLOR);
		sprites.back().SetName("lavaislandbump1");
		sprites.back().SetLayer(LAYER::layer_FAR);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 2 - 9, g_pixelHeight - 60, 4, 4, CANYONWALLCOLOR);
		sprites.back().SetName("lavaislandbump2");
		sprites.back().SetLayer(LAYER::layer_FAR);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 2 - 9, g_pixelHeight - 30, 4, 4, CANYONWALLCOLOR);
		sprites.back().SetName("lavaislandbump3");
		sprites.back().SetLayer(LAYER::layer_FAR);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 2 + 12, g_pixelHeight - 23, 4, 4, CANYONWALLCOLOR);
		sprites.back().SetName("lavaislandbump4");
		sprites.back().SetLayer(LAYER::layer_FAR);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 2 + 12, g_pixelHeight - 30, 4, 4, CANYONWALLCOLOR);
		sprites.back().SetName("lavaislandbump5");
		sprites.back().SetLayer(LAYER::layer_FAR);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 2 + 12, g_pixelHeight - 80, 4, 4, CANYONWALLCOLOR);
		sprites.back().SetName("lavaislandbump6");
		sprites.back().SetLayer(LAYER::layer_FAR);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth / 2 + 12, g_pixelHeight - 45, 4, 4, CANYONWALLCOLOR);
		sprites.back().SetName("lavaislandbump7");
		sprites.back().SetLayer(LAYER::layer_FAR);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		//Canyon Wall left Sprites
		sprites.push_back(s);
		sprites.back().Create(0, 10, 10, 300, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.back().SetTexture(&textures[1]);
		sprites.back().SetFlipX(false);
		sprites.back().SetFlipY(false);

		sprites.push_back(s);
		sprites.back().Create(0, 40, 40, 300, CANYONWALLCOLOR);
		sprites.back().SetName("wallcolliderl");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetIsCollider(true);
		sprites.back().SetCollide(CollideType::Lose);
		
		
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 20, 30, 20, 21, LANDERCOLOR);
		sprites.back().SetName("rwall2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
	//	sprites.back().SetCollide(CollideType::Lose);
		sprites.back().SetCollide(CollideType::HitObject);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 20, 60, 20, 200, CANYONWALLCOLOR);
		sprites.back().SetName("rwall2.1");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 25, 90, 5, 200, CANYONWALLCOLOR);
		sprites.back().Create(g_pixelWidth - 25, 70, 5, 200, CANYONWALLCOLOR);
		sprites.back().SetName("rwall3");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 30, 94, 10, 200, CANYONWALLCOLOR);
		sprites.back().SetName("rwall4");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 39, 120, 9, 200, CANYONWALLCOLOR);
		sprites.back().SetName("rwall5");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
	}


	void SetSpriteVisible(string name, bool show)
	{
		//TODO
		//Eventually implement GetAncestor();
		for (int i = 0; i < (int)sprites.size(); i++)
		{
			if (sprites[i].GetName() == name)
			{
				sprites[i].SetVisible(show);
			}
			if (sprites[i].GetParent() != nullptr)
			{
				if (sprites[i].GetParent()->GetName() == name)
				{
					sprites[i].SetVisible(show);
				}
			}
		}
	}
	void SetSpritePhysics(string name, bool on)
	{
		for (int i = 0; i < (int)sprites.size(); i++)
		{
			if (sprites[i].GetName() == name)
			{
				sprites[i].setPhysics(on);
			}
			if (sprites[i].GetParent() != nullptr)
			{
				if (sprites[i].GetParent()->GetName() == name)
				{
					sprites[i].setPhysics(on);
				}
			}
		}
	}
	void SetParticleSystemActive(string name, bool on)
	{
		int index = GetParticleSystemIndex(name);
		if (index >= 0)
		{
			TBSprite* pParent = particleSystems[index].GetParent();
			if (pParent != nullptr && pParent->GetVisible())
			{
				particleSystems[index].SetActive(on);
			}
			else if (pParent != nullptr && !pParent->GetVisible())
			{
				g_Notify.Notify({ NOTIFYTYPE::OnStart, OBJECTTYPE::PS, this->name});
				particleSystems[index].SetActive(false);
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
	void SetCollisionsPtr(deque<CollisionInfo>* pC)
	{
		pCollisions = pC;
	}
	void OnSpriteCollision(string a, string b)
	{
		if (pCollisions != nullptr)
		{
			CollisionInfo info(a, b, true);
			pCollisions->push_back(info);
		}
		
	}
	void ClearWinElements()
	{
		for (int i = 0; i < particleSystems.size(); i++)
		{
			if (particleSystems[i].GetDeleteOnWin())
			{
				particleSystems[i].SetActive(false);
			}
		}
	}
	void TestCollision()
	{
		int id = GetSpriteIndex("lander");
		if (id > -1)
		{
			string hit = sprites[id].TestCollision(sprites);
			OnSpriteCollision(sprites[id].GetName(), hit);
		}
	}
	void HandleBullet()
	{
		TBSprite* pS = GetSprite("bullet");
		if (pS != nullptr)
		{
			if (pS->GetVisible())
			{ //Delete bullet if offscreen

				float x = pS->GetX();
				OutputDebugStringA((to_string(x) + "\n").c_str());
				if (x < 0.0f || x >(float)g_pixelWidth)
				{
					pS->SetVisible(false);
					pS->SetHasAnimation(false);
				}
			}

			if (!pS->GetVisible() && GetShootKeyDown())
			{
				//shoot bullet
				TBSprite* pL = GetSprite("lander");
				bool faceleft = pL->GetFlipX();
				float x = pL->GetCenterX();
				float y = pL->GetCenterY();
				
				pS->Create((int)x, (int)y + 1, 3 /*<-original 4*/, 1, { 255, 213, 0 });
				pS->SetName("bullet");
				pS->SetVisible(true);
				//mess with first  V  value for bullet speed. original 200.0f
				pS->SetAnimationX(220.039f * (faceleft ? 1.0f : -1.0f));
				//pS->SetCollide(CollideType::E);
				pS->SetHasAnimation(true);
			}

		}
	}
	void HandleBulletCollision()
	{
		TBSprite* bl = GetSprite("bullet");
		TBSprite* la = GetSprite("lander");

		TBSprite TBs;

		for (int i = 0; i < sprites.size(); i++)
		{ 
			if (sprites.back().GetCollide() == CollideType::HitObject)
			{

				TBs.SetVisible(false);
				TBs.SetCollide(CollideType::None);
				bl->SetVisible(false);

				SetParticlesParent("explosion", la->GetName());
				SetParticleSystemActive("explosion", true);

				TBSprite* bt = GetSprite(TBs.GetName());
				SetSpritePhysics(bt->GetName(), false);
				SetSpriteVisible(bt->GetName(), false);
			}
		}

		
		

	}
	void Process(double elapsedTimeSec)
	{
		
		for (int i = 0; i < (int)sprites.size(); i++)
		{
			sprites[i].Process(elapsedTimeSec);
		}

		if (tempSprites.size())
		{
			for (int i = (int)tempSprites.size() - 1; i >= 0; i--)
			{
				tempSprites[i].Process(elapsedTimeSec);

				if (tempSprites[i].IsExpired())
				{
					tempSprites.erase(tempSprites.begin() + i);
				}
			}
		}

		HandleBullet();

		for (int i = 0; i < (int)particleSystems.size(); i++)
		{
			particleSystems[i].Process(elapsedTimeSec);
		}

		if (!g_TargetShowing && GetElapsedSeconds() >= TargetTime)
		{
			SetSpriteVisible("target", true);
			g_TargetShowing = true;
		}
	}
	TBSprite* AddTempSprite(int x, int y, const string& caption, bool floating)
	{
		TBSprite tempSp;
		tempSp.Create(x - 3, y - 5, 20, 20, { 0, 255, 255 });
		tempSp.SetIsTextSprite(true);
		tempSp.SetSpriteText(caption);
		tempSp.SetLifeTime(2.5f);
		if (floating)
		{
			tempSp.SetAnimationY(-12.0f);
			tempSp.SetAnimationX(GetRandRange(-10.0f, 10.0f));
			tempSp.SetHasAnimation(true);
		}
		tempSp.SetTextAlign(TEXT_ALIGN::LEFT);
		tempSp.SetVisible(true);
		tempSp.SetLayer(LAYER::layer_HUD);
		tempSp.SetScreen(true);
		tempSprites.push_back(tempSp);
		return &tempSprites.back();
	}
	void DisableChildParticles(TBSprite* tb)
	{
		for (int i = 0; i < (int)particleSystems.size(); i++)
		{
			if (particleSystems[i].GetParent() == tb)
			{
				particleSystems[i].SetActive(false);
			}
		}
	}

	//Draw Function
	void Draw(MCGraphics* pGFX)
	{
		pGFX->Clear();

		for (int layer = 0; layer < 6; layer++)
		{
			for (int i = 0; i < (int)particleSystems.size(); i++)
			{
				if (particleSystems[i].GetLayer() == (LAYER)layer)
				{
					particleSystems[i].Draw(pGFX);
				} 
			}
			for (int i = 0; i < (int)sprites.size(); i++)
			{
				if (sprites[i].GetLayer() == (LAYER)layer)
				{
					sprites[i].Draw(pGFX);
				}
			}
			for (int i = 0; i < (int)tempSprites.size(); i++)
			{
				if (tempSprites[i].GetLayer() == (LAYER)layer)
				{
					tempSprites[i].Draw(pGFX);
				}
			}
		}
	}
	

};