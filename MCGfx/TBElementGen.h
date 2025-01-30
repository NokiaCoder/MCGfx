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

	vector<TBSprite>* pSprites = nullptr;
	vector<ParticleSystem>* pParticleSystems = nullptr;

	vector<SCREENPT> spawnPoints;

public:
	TBElementGen() = default;

	void Start()
	{
		lastTime = GetElapsedSeconds();
		lastTime1 = lastTime;
		lastTime2 = lastTime;
		lastTime3 = lastTime;
		lastTime4 = lastTime;
		lastTime5 = lastTime;
	}

	void SetElements(vector<TBSprite>* spr, vector<ParticleSystem>* ps)
	{
		pSprites = spr;
		pParticleSystems = ps;
	}

	void Process()
	{
		double eTime = GetElapsedSeconds();

		//placeholder colors for now green = fuel, blue = powerup
		
		//Generate Droppers
		if (eTime - lastTime >= (double)GetRandRange(4.0f, 8.0f))
		{
			lastTime = eTime;

			TBHitTarget asteroid;
			asteroid.SetTargetType(TARGET_TYPE::Dropper);
			pSprites->push_back(asteroid);
		}

		//Generate Sliders
		if (eTime - lastTime1 >= (double)GetRandRange(10.0f, 15.0f) && t ==0 )
		{
			lastTime1 = eTime;

			TBHitTarget ship;
			ship.SetTargetType(TARGET_TYPE::SliderLR);
			pSprites->push_back(ship);
		}

		if (eTime - lastTime2 >= (double)GetRandRange(10.0f, 15.0f) && t == 0)
		{
			lastTime2 = eTime;

			TBHitTarget ship2;
			ship2.SetTargetType(TARGET_TYPE::SliderRL);
			pSprites->push_back(ship2);
		}

		//Spawn
		if (eTime - lastTime3 >= (double)GetRandRange(10.0f, 15.0f) && t == 0)
		{
			lastTime3 = eTime;

			TBHitTarget payload;
			SCREENPT origin = GetSpawnPt();
			payload.SetTargetType(TARGET_TYPE::Still);
			payload.SetPos(static_cast<float>(origin.x), static_cast<float>(origin.y));
			pSprites->push_back(payload);
		}
	}

	void AddSpawnPt(const SCREENPT& sPt)
	{
		spawnPoints.push_back(sPt);
	}
	void ClearSpawnPt()
	{
		spawnPoints.clear();
	}
	SCREENPT GetSpawnPt()
	{
		if (spawnPoints.empty())
		{
			return { -1, -1 };
		}
		
		int index = static_cast<int>(GetRandRange(0.0f, static_cast<float>(spawnPoints.size())));
		return spawnPoints[index];
	}
};


