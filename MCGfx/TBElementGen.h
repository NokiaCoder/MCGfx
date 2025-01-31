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
	double lastTime6 = 0;
	double lastTime7 = 0;

	int t = 0;

	RGBTRIPLE ASTEROIDCOLOR = { 81, 81, 85 };

	vector<TBSprite>* pSprites = nullptr;
	vector<ParticleSystem>* pParticleSystems = nullptr;
	vector<TBSprite>* pTempSprites = nullptr;
	TBWorld* pWorld = nullptr;

	//vector<SCREENPT> spawnPoints;
	vector<SPAWNPOINT> spawnPoints;

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

	void SetElements(vector<TBSprite>* spr,vector<TBSprite>* pts, vector<ParticleSystem>* ps, TBWorld* pW)
	{
		pSprites = spr;
		pTempSprites = pts;
		pParticleSystems = ps;
		pWorld = pW;
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

		//Generate SlidersLR
		if (eTime - lastTime1 >= (double)GetRandRange(10.0f, 15.0f) && t ==0 )
		{
			lastTime1 = eTime;

			TBHitTarget ship;
			ship.SetTargetType(TARGET_TYPE::SliderLR);
			pSprites->push_back(ship);
		}

		//Generate slidersRL
		if (eTime - lastTime2 >= (double)GetRandRange(10.0f, 15.0f) && t == 0)
		{
			lastTime2 = eTime;

			TBHitTarget ship2;
			ship2.SetTargetType(TARGET_TYPE::SliderRL);
			pSprites->push_back(ship2);
		}

		//Spawn payload
		if (eTime - lastTime3 >= (double)GetRandRange(10.0f, 15.0f) && t == 0)
		{
			lastTime3 = eTime;

			TBHitTarget payload;
			SPAWNPOINT spt = GetSpawnPt();
			payload.SetTargetType(TARGET_TYPE::Still);
			payload.SetPos(static_cast<float>(spt.pos.x), static_cast<float>(spt.pos.y));
			pSprites->push_back(payload);

			//TODO move function to pay load collision
			pWorld->AddTempSprite(spt.pos.x, spt.pos.y, to_string(spt.fuel), true);

			
		}
	}

	void AddSpawnPt(const SPAWNPOINT& sPt)
	{
		spawnPoints.push_back(sPt);
	}
	void ClearSpawnPt()
	{
		spawnPoints.clear();
	}
	SPAWNPOINT GetSpawnPt()
	{
		if (spawnPoints.empty())
		{
			return {};
		}
		
		int index = static_cast<int>(GetRandRange(0.0f, static_cast<float>(spawnPoints.size())));
		return spawnPoints[index];
	}
};


