#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "MCGraphics.cpp"
#include "TBGlobals.h"
#include "TBSprite.cpp"

class Particle
{
private:
	bool alive = true;
	bool hasGravity = false;
	bool fadeOut = true;
	float x = 0.0f;
	float y = 0.0f;
	float vx = 0.0f;
	float vy = 0.0f;
	RGBQUAD color = RGBQ(0, 0, 0, 0);
	double lifetimeSec = 0.0;
	double age = 0.0;
	


public:
	void Create(float posx, float posy, float velx, float vely, double life, bool hasgrav, bool fade, RGBQUAD c)
	{
		alive = true;
		x = posx;
		y = posy;
		vx = velx;
		vy = vely;
		if (life < 0.0)
		{
			lifetimeSec = life;
		}
		else
		{
			lifetimeSec = life * (GetRandNorm() + 0.5f);
		}
		if (lifetimeSec < 0.0)
		{
			int u = 0;
		}
		age = 0.0;
		color = c;
		hasGravity = hasgrav;
		fadeOut = fade;
	}
	void Process(double elapsedTimeSec)
	{
		if (alive)
		{
			age += elapsedTimeSec;

			if (age <= lifetimeSec || lifetimeSec < 0.0)
			{
				if (hasGravity)
				{
					vy += g * 10.0f;
				}
				x +=(float)( vx * elapsedTimeSec);
				y +=(float)( vy * elapsedTimeSec);
			}
			else
			{
				alive = false;
			}
		}
	}

	void SetColor(const RGBTRIPLE& c)
	{
		color = RGBQ(c.rgbtRed, c.rgbtGreen, c.rgbtBlue, 255);
	}

	void Draw(MCGraphics* pGFX, float ex, float ey)
	{
		if (alive)
		{
			RGBTRIPLE finalColor = { color.rgbBlue, color.rgbGreen, color.rgbRed };
			if (fadeOut)
			{
				finalColor = BlendColor(finalColor, pGFX->GetPixel((int)(ex + x), (int)(ey + y)), 100 - (int)(age / lifetimeSec * 100.0f));
			}
			pGFX->SetPixel((int)(ex + x), (int)(ey + y), { finalColor.rgbtBlue, finalColor.rgbtGreen, finalColor.rgbtRed });
		}
	}

	bool IsAlive()
	{
		return alive;
	}
};


class ParticleSystem
{
private:
	bool gravityActive = false;
	bool fadeOut = true;
	bool active = true;
	string name = "";
	float emitterX = 0.0f;
	float emitterY = 0.0f;
	float emitRate = 10.0f;
	float emitDurationSec = -1.0f;
	float startDeg = 0.0f;
	float endDeg = 360.0f;
	float startSpeed = 0.0f;
	float lifespanSec = 0.0f;
	float runDurationSec = -1.0f;
	int frameOn = 0;
	float spawnRadiusMin = 0.0f;
	float spawnRadiusMax = 1.0f;
	bool staticParticles = false;
	RGBTRIPLE particleColor = { 255, 255, 255 };
	LAYER layer = LAYER::layer_BACK;


	vector<Particle> particles;
	TBSprite* pParent = nullptr;

	void Spawn()
	{
		Particle s;

		particles.push_back(s);
		float vx = 0.0f;
		float vy = 0.0f;
		float posx = 0.0f;
		float posy = 0.0f;
		GetRandCircle(spawnRadiusMin, spawnRadiusMax ,startDeg, endDeg, startSpeed, &vx, &vy, &posx, &posy);

		particles.back().Create(posx, posy, vx, vy, lifespanSec, gravityActive, fadeOut, RGBQ(255, 100, 100, 255));
		particles.back().SetColor(particleColor);
	}

public:
	ParticleSystem() = default;

	ParticleSystem(const ParticleSystem& copy)
	{
		gravityActive = copy.gravityActive;
		name = copy.name;
		fadeOut = copy.fadeOut;
		emitterX = copy.emitterX;
		emitterY = copy.emitterY;
		emitRate = copy.emitRate;
		frameOn = copy.frameOn;
		particleColor = copy.particleColor;
		startDeg = copy.startDeg;
		endDeg = copy.endDeg;
		startSpeed = copy.startSpeed;
		lifespanSec = copy.lifespanSec;
		active = copy.active;
		layer = copy.layer;
		particles = copy.particles;
		spawnRadiusMin = copy.spawnRadiusMin;
		spawnRadiusMax = copy.spawnRadiusMax;
		staticParticles = copy.staticParticles;
		emitDurationSec = copy.emitDurationSec;
		runDurationSec = copy.runDurationSec;
	}
	//Gravity accessors
	bool GetGravityOn()
	{
		return gravityActive;
	}
	void SetGravityOn(bool gravityOn)
	{
		gravityActive = gravityOn;
	}

	LAYER GetLayer()
	{
		return layer;
	}
	
	//implementation is in the cpp file..
	void SetLayer(LAYER l);

	void SetSpawnRadius(float rmin, float rmax)
	{
		spawnRadiusMin = rmin;
		spawnRadiusMax = rmax;
	}

	void SetEmitRate(float er)
	{
		emitRate = er;
	}
	
	void SetEmitDurationSec(float ed)
	{
		emitDurationSec = ed;
	}

	void SetStaticParticles(bool s)
	{
		staticParticles = s;
	}

	void SetParticleColor(const RGBTRIPLE& c)
	{
		particleColor = c;
	}
	void SetActive(bool a)
	{
		active = a;
		runDurationSec = 0;
	}
	bool GetActive()
	{
		return active;
	}

	string GetName()
	{
		return name;
	}

	void SetLifespan(float lS)
	{
		lifespanSec = lS;
	}

	void SetParams(float sDeg, float eDeg, float startspd)
	{
		startDeg = sDeg;
		endDeg = eDeg;
		startSpeed = startspd;
	}

	TBSprite* GetParent()
	{
		return pParent;
	}
	void SetParent(TBSprite* pP)
	{
		pParent = pP;
	}
	
	void Create(float  x, float y, const string& name)
	{
		emitterX = x;
		emitterY = y;
		this->name = name;
	}


	void Process(double elapsedTimeSec)
	{
		runDurationSec += static_cast<float>(elapsedTimeSec);

		//process each defined particle
		for (int i = 0; i < (int)particles.size(); i++)
		{
			particles[i].Process(elapsedTimeSec);
		}

		//kill expired particles
		for (int i = (int)particles.size() - 1; i >= 0; i--)
		{
			if (!particles[i].IsAlive())
			{
				particles.erase(particles.begin() + i);
			}
		}

		if (runDurationSec >= emitDurationSec && emitDurationSec > 0)
		{
			active = false;
		}
		//spawn new particles
		if (frameOn > 0 && active)
		{
			int num = (int)(emitRate * elapsedTimeSec);
			num = num == 0 ? 1 : num;
			for (int i = 0; i < num; i++)
			{
				Spawn();
			}
		}

		//increment frame count
		frameOn++;
	}

	void Draw(MCGraphics* pGFX)
	{
		float parentX = emitterX;
		float parentY = emitterY;
		if (GetParent() != nullptr)
		{
			parentX += GetParent()->GetX();
			parentY += GetParent()->GetY();
		}

		//pGFX->SetPixel((int)parentX, (int)parentY, { 0, 0, 255 });
		
		for (int i = 0; i < (int)particles.size(); i++)
		{
			particles[i].Draw(pGFX, parentX, parentY);
		}
	}
};

