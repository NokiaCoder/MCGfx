#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "MCGraphics.cpp"
#include "TBGlobals.h"
#include "TBSprite.cpp"
#include "TBNotifyMgr.h"

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
	string name;


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
				g_Notify.Notify({ NOTIFYTYPE::OnEnd, OBJECTTYPE::PS, this->name});
			}
		}
	}

	float GetX()
	{
		return x;
	}
	void SetX(float xx)
	{
		x = xx;
	}

	float GetY()
	{
		return y;
	}
	void SetY(float yy)
	{
		y = yy;
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
	bool deleteOnWin = false;
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
	string parentSpriteName = "";
	vector<Particle> particles;
	TBSprite* pParent = nullptr;

	void Spawn(float wx, float wy)
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

		//After Spawning particles should be local cords

		particles.back().SetX(particles.back().GetX() + wx);
		particles.back().SetY(particles.back().GetY() + wy);
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


	float GetEmitterX() 
	{
		return emitterX;
	}
	float GetEmitterY()
	{
		return emitterY;
	}

	void SetPosParticleSystem(float eX, float eY)
	{
		emitterX += eX;
		emitterY += eY;
	}

	bool GetDeleteOnWin()
	{
		return deleteOnWin;
	}

	void SetDeleteOnWin(bool bo)
	{
		deleteOnWin = bo;
	}

	string GetParentSpriteName()
	{
		return parentSpriteName;
	}
	void SetParentSpriteName(string ps)
	{
		parentSpriteName = ps;
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
			float wx = emitterX;
			float wy = emitterY;
			if (GetParent() != nullptr)
			{
				wx += GetParent()->GetX();
				wy += GetParent()->GetY();
			}
			int num = (int)(emitRate * elapsedTimeSec);
			num = num == 0 ? 1 : num;
			for (int i = 0; i < num; i++)
			{
				Spawn(wx, wy);
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
		
		for (int i = 0; i < (int)particles.size(); i++)
		{
			//particles[i].Draw(pGFX, parentX, parentY);
			particles[i].Draw(pGFX, 0, 0);
		}
	}

	void MoveParticleS(int mx, int my)
	{
		emitterX += mx;
		emitterY += my;
	}

	string Serialize()
	{
		string str = "\nPARTICLESYSTEM\n";

		str += "gravityActive," + string(gravityActive ? "TRUE\n" : "FALSE\n");
		str += "fadeOut," + string(fadeOut ? "TRUE\n" : "FALSE\n");
		str += "active," + string(active ? "TRUE\n" : "FALSE\n");
		str += "deleteOnWin," + string(deleteOnWin ? "TRUE\n" : "FALSE\n");

		str += "name," + name + "\n";


		str += "emitterX," + to_string(emitterX) + "\n";
		str += "emitterY," + to_string(emitterY) + "\n";
		str += "emitRate," + to_string(emitRate) + "\n";
		str += "emitDurationSec," + to_string(emitDurationSec) + "\n";
		str += "startDeg," + to_string(startDeg) + "\n";
		str += "endDeg," + to_string(endDeg) + "\n";
		str += "startSpeed," + to_string(startSpeed) + "\n";
		str += "lifespanSec," + to_string(lifespanSec) + "\n";
		str += "runDurationSec," + to_string(runDurationSec) + "\n";

		str += "frameOn," + to_string(frameOn) + "\n";

		str += "spawnRadiusMin," + to_string(spawnRadiusMin) + "\n";
		str += "spawnRadiusMax," + to_string(spawnRadiusMax) + "\n";

		str += "staticParticles," + string(staticParticles ? "TRUE\n" : "FALSE\n");

		str += "particleColor," + to_string(particleColor.rgbtRed) + "|" + to_string(particleColor.rgbtGreen) + "|" + to_string(particleColor.rgbtBlue) + "\n";

		str += "layer," + Layer2Str(layer) + "\n";

		str += "parentSpriteName," + (pParent == nullptr ? "" : pParent->GetName());
		str += "\n";

		return str;
	}

	int Deserialize(const vector<string>& lines, int startIndex)
	{
		int index = startIndex;
		if (lines[index] == "PARTICLESYSTEM")
		{
			index++;
		}

		while (lines[index] != "")
		{

			//Line has KVP(KEYVALUEPAIR)
			vector<string> chunks;
			GetChunks(lines[index], chunks);
			if (chunks[0] == "gravityActive")
			{
				gravityActive = Str2TF(chunks[1]);
			}
			else if (chunks[0] == "fadeOut")
			{
				fadeOut = Str2TF(chunks[1]);
			}
			else if (chunks[0] == "active")
			{
				active = Str2TF(chunks[1]);
			}
			else if (chunks[0] == "deleteOnWin")
			{
				deleteOnWin = Str2TF(chunks[1]);
			}
			else if (chunks[0] == "name")
			{
				name = chunks[1];
			}
			else if (chunks[0] == "emitterX")
			{
				emitterX = Str2F(chunks[1]);
			}
			else if (chunks[0] == "emitterY")
			{
				emitterY = Str2F(chunks[1]);
			}
			else if (chunks[0] == "emitRate")
			{
				emitRate = Str2F(chunks[1]);
			}
			else if (chunks[0] == "emitDurationSec")
			{
				emitDurationSec = Str2F(chunks[1]);
			}
			else if (chunks[0] == "startDeg")
			{
				startDeg = Str2F(chunks[1]);
			}
			else if (chunks[0] == "endDeg")
			{
				endDeg = Str2F(chunks[1]);
			}
			else if (chunks[0] == "startSpeed")
			{
				startSpeed = Str2F(chunks[1]);
			}
			else if (chunks[0] == "lifespanSec")
			{
				lifespanSec = Str2F(chunks[1]);
			}
			else if (chunks[0] == "runDurationSec")
			{
				runDurationSec = Str2F(chunks[1]);
			}
			else if (chunks[0] == "frameOn")
			{
				frameOn = Str2I(chunks[1]);
			}
			else if (chunks[0] == "spawnRadiusMin")
			{
				spawnRadiusMin = Str2F(chunks[1]);
			}
			else if (chunks[0] == "spawnRadiusMax")
			{
				spawnRadiusMax = Str2F(chunks[1]);
			}
			else if (chunks[0] == "staticParticles")
			{
				staticParticles = Str2TF(chunks[1]);
			}
			else if (chunks[0] == "particleColor")
			{
				particleColor = Str2RGB(chunks[1]);
			}
			else if (chunks[0] == "layer")
			{
				layer = Str2Layer(chunks[1]);
			}
			else if (chunks[0] == "parentSpriteName")
			{
				SetParentSpriteName(chunks[1]);
			}

			index++;

		}
		return index;
	}
};

