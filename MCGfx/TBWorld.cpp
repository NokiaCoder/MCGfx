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
		//sprites.push_back(s);
		//sprites.back().Create(0, g_pixelHeight - 305, g_pixelWidth, g_pixelHeight / 3, SkyBoxColor);
		//sprites.back().SetName("skybox");
		//sprites.back().SetWrap(true);
		//sprites.back().SetLayer(LAYER::layer_NEAR);
		//sprites.back().SetHasAnimation(false);
		//sprites.back().SetCollide(CollideType::Lose);
		//sprites.back().setPhysics(false);

		//sprites.push_back(s);
		//sprites.back().Create(g_pixelWidth / 4 + 10, g_pixelHeight / 2 - 35, 50, g_pixelHeight / 2, FarColor);
		//sprites.back().SetName("mtAFar");
		//sprites.back().SetWrap(true);
		//sprites.back().SetLayer(LAYER::layer_FAR);
		//sprites.back().SetHasAnimation(true);
		//sprites.back().SetAnimationX(mountMidSpeed * scrollSpeed);
		//sprites.back().setPhysics(false);

		//		//Enemies/comets
		//for (int i = 0; i < enemyCount; i++)
		//{
		//	sprites.push_back(s);
		//	sprites.back().Create(0, static_cast<int>(GetRandRange(20.0f, 160.0f)), 2, 2, MeteorCOLOR);
		//	sprites.back().SetName("meteor" + to_string(i));
		//	sprites.back().SetWrap(true);
		//	sprites.back().SetLayer(LAYER::layer_NEAR);
		//	sprites.back().SetHasAnimation(true);
		//	sprites.back().SetAnimationX(GetRandRange(-10.0f, 10.0f) * 10.0f);
		//	sprites.back().setPhysics(false);
		//	sprites.back().SetCollide(CollideType::Lose);
		//	sprites.back().SetGravityOn(false);
		//}

		////powerup
		//for (int i = 0; i < enemyCount; i++)
		//{
		//	sprites.push_back(s);
		//	sprites.back().Create(0, static_cast<int>(GetRandRange(20.0f, 160.0f)), 2, 2, PowerUpCOLOR);
		//	sprites.back().SetName("powerup" + to_string(i));
		//	sprites.back().SetWrap(true);
		//	sprites.back().SetLayer(LAYER::layer_NEAR);
		//	sprites.back().SetHasAnimation(true);
		//	sprites.back().SetAnimationX(GetRandRange(-10.0f, 10.0f) * 10.0f);
		//	sprites.back().setPhysics(false);
		//	sprites.back().SetCollide(CollideType::PowerUp);
		//	sprites.back().SetGravityOn(false);
		//}

		////Near Ground
		//sprites.push_back(s);
		//sprites.back().Create(0, g_pixelHeight - 30, g_pixelWidth + 30, 50, NearGroundColor); //for each change color with 3 last values in {}. { blue, green, red}
		//sprites.back().SetName("ground");
		//sprites.back().SetLayer(LAYER::layer_NEAR);
		//sprites.back().SetHasAnimation(false);
		//sprites.back().setPhysics(false);
		//sprites.back().SetCollide(CollideType::Lose);

		//sprites.push_back(s);
		//sprites.back().Create(GetRandomH(), g_pixelHeight - 35, 8, 8, TargetCOLOR); //for each change color with 3 last values in {}. { blue, green, red}
		//sprites.back().SetName("target");
		//sprites.back().SetLayer(LAYER::layer_FRONT);
		//sprites.back().SetHasAnimation(false);
		//sprites.back().setPhysics(false);
		//sprites.back().SetCollide(CollideType::Win);

		//Lander and attachments
		//sprites.push_back(s);
		//sprites.back().Create(140, 0, 4, 4, LANDERCOLOR);
		//sprites.back().SetName("lander");
		//sprites.back().SetGravityOn(true);
		//sprites.back().SetVx(landerSpeed);
		//sprites.back().SetWrap(true);
		//sprites.back().SetLayer(LAYER::layer_FRONT);
		//sprites.back().SetStayAboveGround(true);
		//sprites.back().setPhysics(true);
		//sprites.back().SetCollide(CollideType::Win);
		//sprites.back().SetExplodeOnCollide(true);

		//sprites.push_back(s);
		//sprites.back().Create(1, -4, 2, 3, LANDERCOLOR);
		//sprites.back().SetName("landerHead");
		//sprites.back().SetParent(GetSprite("lander"));
		//sprites.back().SetVisible(true);
		//sprites.back().SetLayer(LAYER::layer_FRONT);
		//sprites.back().setPhysics(false);
		//sprites.back().SetWrap(true);

		////FOUND ERROR if sprite is in x = -1,-2,-3,etc it will do the corner error
		////broken one
		//sprites.push_back(s);
		//sprites.back().Create(-1, 2, 2, 2, LANDERCOLOR);
		//sprites.back().SetName("Left lander wing1");
		//sprites.back().SetParent(GetSprite("lander"));
		//sprites.back().SetVisible(true);
		//sprites.back().SetLayer(LAYER::layer_FRONT);
		//sprites.back().setPhysics(false);
		//sprites.back().SetWrap(true);



		sprites.clear();
		particleSystems.clear();

		pGFX->SetColorText({ 0, 255, 255 });

		//pre allocate to avoid stale pointers
		int index = -1;
		int psIndex = -1;

		int enemyCount = 2 * g_LevelOn;

		pGFX->SetBackgroundColor(DarkenColor({ 80, 120, 180 },50));

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

		//Speed settings
		float mountMidSpeed = -0.01f;
		float mountNearSpeed = -0.03f;
		float landerSpeed = GetRandRange(-1.0f, 1.0f);
		float scrollSpeed = -0.0f;

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
		sprites.back().Create(g_pixelWidth/2, g_pixelHeight - 35, 8, 8, TargetCOLOR); //for each change color with 3 last values in {}. { blue, green, red}
		sprites.back().SetName("target");
		sprites.back().SetLayer(LAYER::layer_FRONT);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Win);

		//Canyon Wall left Sprites
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight-1, 43, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l1");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 2, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 3, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l3");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 4, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l4");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 5, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l5");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 6, 37, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l6");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 7, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l7");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 8, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l8");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 9, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l9");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 10, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l10");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 11, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l11");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 12, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l12");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 13, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l13");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 14, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l14");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 15, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l15");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 16, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l16");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 17, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l17");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 18, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l18");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 19, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l19");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 20, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l20");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 21, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l21");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 22, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l22");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 23, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l23");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 24, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l24");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 25, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l25");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 26, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l26");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 27, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l27");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 28, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l28");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 29, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l29");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 30, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l30");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 31, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l31");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 32, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l32");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 33, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l33");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 34, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l34");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 35, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l35");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 36, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l36");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 37, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l37");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 38, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l38");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 39, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l39");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 40, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l40");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 41, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l41");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 42, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l42");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 43, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l43");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 44, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l44");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 45, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l45");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 46, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l46");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 47, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l47");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 48, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l48");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 49, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l49");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 50, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l50");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 51, 43, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l51");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 52, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l52");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 53, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l53");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 54, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l54");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 55, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l55");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 56, 37, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l56");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 57, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l57");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 58, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l58");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 59, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l59");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 60, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l60");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 61, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l61");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 62, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l62");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 63, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l63");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 64, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l64");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 65, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l65");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 66, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l66");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 67, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l67");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 68, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l68");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 69, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l69");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 70, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l70");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 71, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l71");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 72, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l72");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 73, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l73");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 74, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l74");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 75, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l75");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 76, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l76");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 77, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l77");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 78, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l78");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 79, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l79");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 80, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l80");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 81, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l81");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 82, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l82");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 83, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l83");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 84, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l84");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 85, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l85");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 86, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l86");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 87, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l87");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 88, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l88");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 89, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l89");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 90, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l90");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 91, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l91");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 92, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l92");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 93, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l93");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 94, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l94");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 95, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l95");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 96, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l96");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 97, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l97");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 98, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l98");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 99, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l99");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 100, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l100");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);



		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 101, 43, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l101");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 102, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l102");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 103, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l103");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 104, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 105, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 106, 37, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 107, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 108, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 109, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 110, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 111, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 112, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 113, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 114, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 115, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 116, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 117, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 118, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 119, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 120, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 121, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 122, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 123, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 124, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 125, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 126, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 127, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 128, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 129, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 130, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 131, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 132, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 133, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 134, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 135, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 136, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 137, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 138, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 139, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 140, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 141, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 142, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 143, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 144, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 145, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 146, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 147, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 148, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 149, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 150, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 151, 43, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l1");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 152, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 153, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 154, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 155, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 156, 37, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 157, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 158, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 159, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 160, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 161, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 162, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 163, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 164, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 165, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 166, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 167, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 168, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 169, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 170, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 171, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 172, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 173, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 174, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 175, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 176, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 177, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 178, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 179, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 180, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 181, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 182, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 183, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 184, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 185, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 186, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 187, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 188, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 189, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 190, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 191, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 192, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 193, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 194, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 195, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 196, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 197, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 198, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 199, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 200, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);




		//Canyon Wall Right Sprites
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth-43 , g_pixelHeight - 1, 43, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l1");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 2, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 3, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 4, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 5, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 37, g_pixelHeight - 6, 37, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 7, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 8, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 9, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 10, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 11, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 12, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 13, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 14, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 15, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 16, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 17, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 18, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 19, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 20, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 21, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 22, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 23, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 24, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 25, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 26, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 27, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(0, g_pixelHeight - 28, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 29, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 30, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 31, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 32, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 33, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 34, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 35, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 36, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 37, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 38, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 39, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 40, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 41, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 42, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 43, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 44, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 45, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 46, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 47, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 48, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 49, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 50, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 43, g_pixelHeight - 51, 43, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l1");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 52, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 53, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 54, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 55, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 56, 37, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 57, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 58, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 59, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 60, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 61, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 62, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 63, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 64, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 65, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 66, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 67, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 68, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 69, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 70, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 71, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 72, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 73, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 74, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 75, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 76, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 77, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 78, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 79, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 80, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 81, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 82, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 83, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 84, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 85, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 86, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 87, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 88, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 89, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 90, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 91, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 92, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 93, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 94, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 95, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 96, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 97, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 98, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 99, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 100, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 43, g_pixelHeight - 101, 43, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l1");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 102, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 103, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 104, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 105, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 37, g_pixelHeight - 106, 37, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 107, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 108, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 109, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 110, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 111, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 112, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 113, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 114, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 115, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 116, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 117, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 118, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 119, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 120, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 121, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 122, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 123, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 124, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 125, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 126, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 127, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 128, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 129, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 130, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 131, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 132, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 133, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 134, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 135, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 136, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 137, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 138, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 139, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 140, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 141, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 142, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 143, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 144, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 145, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 146, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 147, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 148, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 149, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 150, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 43, g_pixelHeight - 151, 43, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l1");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 152, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 153, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 154, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 155, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 37, g_pixelHeight - 156, 37, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 157, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 158, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);

		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 159, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 160, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 161, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 162, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 163, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 164, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 165, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 166, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 167, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 168, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 169, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 170, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 171, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 172, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 173, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 174, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 175, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 176, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 177, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 178, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 179, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 180, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 181, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 182, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 183, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 184, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 185, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 186, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 187, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 188, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 189, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 190, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 191, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 192, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 193, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 194, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 195, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 196, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 197, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 198, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 199, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);
		sprites.push_back(s);
		sprites.back().Create(g_pixelWidth - 38, g_pixelHeight - 200, 38, 1, CANYONWALLCOLOR);
		sprites.back().SetName("wall1l2");
		sprites.back().SetLayer(LAYER::layer_MID);
		sprites.back().SetHasAnimation(false);
		sprites.back().setPhysics(false);
		sprites.back().SetCollide(CollideType::Lose);



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
		particleSystems.back().Create(0, 0, "smoke1");
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
		particleSystems.back().Create(0, 0, "smoke2");
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

		for (int i = 0; i < (int)particleSystems.size(); i++)
		{
			particleSystems[i].Process(elapsedTimeSec);
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