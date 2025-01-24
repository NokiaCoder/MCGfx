#pragma once


#include "TBWorld.cpp"
#include "TBGlobals.h"
#include "TBHitTarget.h"
#include <vector>
#include <string>

class TBElementGen
{
private:
	double lastTime = 0;
	double lastTime1 = 0;
	double lastTime2 = 0;
	double lastTime3 = 0;
	double lastTime4 = 0;
	double lastTime5 = 0;

	int t = 0;

	RGBTRIPLE ASTEROIDCOLOR = { 81, 81, 85 };

	vector<TBSprite>* pSprites;
	vector<ParticleSystem>* pParticleSystems;

public:
	TBElementGen() = default;

	void SetElements(vector<TBSprite>* spr, vector<ParticleSystem>* ps)
	{
		pSprites = spr;
		pParticleSystems = ps;
	}

	void Process()
	{
		double eTime = GetElapsedSeconds();

		//placeholder collors for now green = fuel, blue = powerup
		if (eTime - lastTime >= (double)GetRandRange(1.0f, 5.0f))
		{
			lastTime = eTime;

			TBHitTarget asteroid;
			asteroid.SetTargetType(TARGET_TYPE::Dropper);
			pSprites->push_back(asteroid);
		}
		if (eTime - lastTime1 >= (double)GetRandRange(10.0f, 15.0f) && t ==0 )
		{
			lastTime1 = eTime;
			//

			//TBSprite powerUp1;
			//powerUp1.SetName("pfuel1");//make it so it can be landed on TODO
			//powerUp1.Create(49, 135, 9, 3, { 255, 0, 0 });
			//powerUp1.SetWrap(true);
			//powerUp1.SetLayer(LAYER::layer_NEAR);
			////	powerUp.SetHasAnimation(true);
			////	powerUp.SetAnimationX(GetRandRange(-10.0f, 10.0f) * 10.0f);
			//powerUp1.setPhysics(false);
			//powerUp1.SetCollide(CollideType::PowerUp);
			////powerUp.SetCollide(CollideType::Lose); //Testing purposes, it Works
			//powerUp1.SetGravityOn(false);

			//t++;
			//pSprites->push_back(powerUp1);
		}

	}
};


