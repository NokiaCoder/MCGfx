#pragma once


#include "TBWorld.cpp"
#include "TBGlobals.h"

class TBElementGen
{
private:
	double lastTime = 0;

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

		if (eTime - lastTime >= 5.0)
		{
			lastTime = eTime;

			TBSprite powerUp;
			powerUp.SetName("p");
			powerUp.Create((int)GetRandRange(10, 200), (int)GetRandRange(20, 100), 8, 8, { 255, 0, 0 });
			powerUp.SetWrap(true);
			powerUp.SetLayer(LAYER::layer_NEAR);
			powerUp.SetHasAnimation(true);
			powerUp.SetAnimationX(GetRandRange(-10.0f, 10.0f) * 10.0f);
			powerUp.setPhysics(false);
			powerUp.SetCollide(CollideType::PowerUp);
			powerUp.SetGravityOn(false);
			pSprites->push_back(powerUp);


		}
	}
};


