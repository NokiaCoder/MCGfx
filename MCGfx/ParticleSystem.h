#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "MCGraphics.cpp"
#include "TBGlobals.h"

class Particle
{
private:
	bool alive = true;
	float x = 0.0f;
	float y = 0.0f;
	float vx = 0.0f;
	float vy = 0.0f;
	RGBQUAD color;
	double lifetimeSec;
	double age;


public:
	void Create(float velx, float vely, double life, RGBQUAD c)
	{
		alive = true;
		x = 0.0f;
		y = 0.0f;
		vx = velx;
		vy = vely;
		lifetimeSec = life * (GetRandNorm() + 0.5f);
		age = 0.0;
		color = c;
	}
	void Process(double elapsedTimeSec)
	{
		if (alive)
		{
			age += elapsedTimeSec;
			if (age <= lifetimeSec)
			{
				x +=(float)( vx * elapsedTimeSec);
				y +=(float)( vy * elapsedTimeSec);
			}
			else
			{
				alive = false;
			}
		}
	}

	void Draw(MCGraphics* pGFX, float ex, float ey)
	{
		if (alive)
		{
			pGFX->SetPixel((int)(ex + x), (int)(ey + y), { color.rgbRed, color.rgbGreen, color.rgbBlue });
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
	string name = "";
	float emitterX = 0.0f;
	float emitterY = 0.0f;
	float rate = 40.0f;

	vector<Particle> particles;
	void Spawn()
	{
		Particle s;

		particles.push_back(s);
		float x;
		float y;
		GetRandCircle(GetRandNorm() + 10.0f, &x, &y);
		particles.back().Create(x, y, 3.0f, RGBQ(105, 100, 75, 255));
	}

public:
	ParticleSystem() = default;

	ParticleSystem(const ParticleSystem& copy)
	{
		gravityActive = copy.gravityActive;
		name = copy.name;


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

	void Create(float  x, float y, const string& name)
	{
		emitterX = x;
		emitterY = y;
		this->name = name;
	}

	void Process(double elapsedTimeSec)
	{
		for (int i = 0; i < (int)particles.size(); i++)
		{
			particles[i].Process(elapsedTimeSec);
		}
		for (int i = (int)particles.size() - 1; i >= 0; i--)
		{
			if (!particles[i].IsAlive())
			{
				particles.erase(particles.begin() + i);
			}
		}
		int num =(int)( rate * elapsedTimeSec);
		num = num == 0 ? 1 : num;
		for (int i = 0; i < num; i++)
		{
			Spawn();
		}
	}

	void Draw(MCGraphics* pGFX)
	{
		pGFX->SetPixel((int)emitterX, (int)emitterY, { 0, 0, 255 });
		
		for (int i = 0; i < (int)particles.size(); i++)
		{
			particles[i].Draw(pGFX, emitterX, emitterY);
		}
	}
};

