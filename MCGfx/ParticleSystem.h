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
	RGBQUAD color;
	double lifetimeSec;
	double age;
	


public:
	void Create(float velx, float vely, double life, bool hasgrav, bool fade, RGBQUAD c)
	{
		alive = true;
		x = 0.0f;
		y = 0.0f;
		vx = velx;
		vy = vely;
		lifetimeSec = life * (GetRandNorm() + 0.5f);
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
			if (age <= lifetimeSec)
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
	float rate = 10.0f;
	float startDeg = 0.0f;
	float endDeg = 360.0f;
	float lifespanSec = 1.0f;
	float mag = 1.0f;
	int frameOn = 0;
	RGBTRIPLE particleColor = { 255, 255, 255 };


	vector<Particle> particles;
	TBSprite* pParent = nullptr;

	void Spawn()
	{
		Particle s;

		particles.push_back(s);
		float x;
		float y;
		GetRandCircle(GetRandNorm() + mag ,startDeg, endDeg, &x, &y);
		particles.back().Create(x, y, lifespanSec, gravityActive, fadeOut, RGBQ(255, 100, 100, 255));
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
		rate = copy.rate;
		frameOn = copy.frameOn;
		particleColor = copy.particleColor;
		startDeg = copy.startDeg;
		endDeg = copy.endDeg;
		lifespanSec = copy.lifespanSec;
		active = copy.active;
		mag = copy.mag;
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

	void SetMag(float mg)
	{
		mag = mg;
	}

	void SetParticleColor(const RGBTRIPLE& c)
	{
		particleColor = c;
	}
	void SetActive(bool a)
	{
		active = a;
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

	void SetRangeDeg(float sDeg, float eDeg)
	{
		startDeg = sDeg;
		endDeg = eDeg;
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


		//spawn new particles
		if (frameOn > 0 && active)
		{
			int num = (int)(rate * elapsedTimeSec);
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

