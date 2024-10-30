#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "MCGraphics.cpp"
#include "TBGlobals.h"

using namespace std;

//collide behavior enum
enum class CollideType
{
	None = 0,
	Win,
	Lose,
	Explode,
	Restart,
	Push,
	Random,
	PowerUp,
};

class TBSprite
{
private:
	//PRIVATE MEMBERS
	float x = 0.0f; //left most
	float y = 0.0f; //upper most
	int w = 0; //width
	int h = 0; //height
	RGBTRIPLE color;
	string name;
	bool hasPhysics = false;
	float vx = 0.0f;
	float vy = 0.0f;
	float fx = 0.0f;
	float fy = 0.0f;
	float ground = 202.0f; //Value for ground (change value to change height of ground
	bool stayAboveGround = false;
	bool gravityActive = false;
	TBSprite* pParent = nullptr;
	TBSprite* pShowOnCollide = nullptr;
	bool visible = true;
	bool wrap = false;
	bool hasAnimation = false;
	CollideType collideType = CollideType::None;
	bool isTextSprite = false;
	TEXT_ALIGN textAlign = TEXT_ALIGN::LEFT;
	string spriteText = "";
	bool hitTarget = false;
	float animationX = 0.0f;
	float animationY = 0.0f;
	float lifeTime = -1.0f;
	float age = 0.0f;
	LAYER layer = LAYER::layer_NONE;


public:
	//ACCESSORS
	void ShowOnCollide()
	{
		if (pShowOnCollide != nullptr)
		{
			pShowOnCollide->SetVisible(true);
		}
	}
	void SetShowOnCollide(TBSprite* pS)
	{
		pShowOnCollide = pS;
	}
	
	//lifetime setter/getter
	float GetLifeTime()
	{
		return lifeTime;
	}
	void SetLifeTime(float lT)
	{
		lifeTime = lT;
	}
	
	//text sprite
	bool GetIsTextSprite()
	{
		return isTextSprite;
	}
	void SetIsTextSprite(bool tS)
	{
		isTextSprite = tS;
	}

	//sprite text
	string GetSpriteText()
	{
		return spriteText;
	}
	void SetSpriteText(string s)
	{
		spriteText = s;
	}

	void SetTextAlign(TEXT_ALIGN align)
	{
		textAlign = align;
	}
	TEXT_ALIGN GetTextAlign()
	{
		return textAlign;
	}

	// accessors
	string GetName()
	{
		return name;
	}
	void SetName(string n)
	{
		name = n;
	}

	//hit target accessors
	bool GetHitTarget()
	{
		return hitTarget;
	}
	void SetHitTarget(bool hTarget)
	{
		hitTarget = hTarget;
	}
	
	//Collision Accessors
	CollideType GetCollide()
	{
		return collideType;
	}
	void SetCollide(CollideType c)
	{
		collideType = c;
	}

	//Gravity accessors
	bool GetGravityOn()
	{
		return gravityActive;
	}
	void SetGravityOn(bool gravityOn)
	{
		gravityActive = gravityOn;
		if (gravityActive)
		{
			vy += 0.1f;
		}
		else
		{
			vy -= 0.1f;
		}
	}

	TBSprite* GetParent()
	{
		return pParent;
	}
	void SetParent(TBSprite* pP)
	{
		pParent = pP;
	}

	float GetX()
	{
		if (pParent != nullptr)
		{
			return x + pParent->GetX();
		}
		return x;
	}
	float GetY()
	{
		if (pParent != nullptr)
		{
			return y + pParent->GetY();
		}
		return y;
	}

	void SetVx(float v)
	{
		vx = v;
	}
	void SetVy(float v)
	{
		vy = v;
	}

	bool GetVisible()
	{
		return visible;
	}
	void SetVisible(bool v)
	{
		visible = v;
		if (v)
		{
			age = 0.0f;
		}
	}

	void SetFx(float f)
	{
		fx += f;
	}
	void SetFy(float f)
	{
		fy += f;
	}

	void SetHasAnimation(bool hA)
	{
		hasAnimation = hA;
	}
	bool GetHasAnimation()
	{
		return hasAnimation;
	}

	float GetAnimationX()
	{
		return animationX;
	}
	float GetAnimationY()
	{
		return animationY;
	}

	void SetAnimationX(float ax)
	{
		animationX = ax;
	}
	void SetAnimationY(float ay)
	{
		animationY = ay;
	}

	void setPhysics(bool ph)
	{
		hasPhysics = ph;
	}
	bool getPhysics()
	{
		return hasPhysics;
	}

	void SetLayer(LAYER l)
		{
			layer = l;
		}
	LAYER GetLayer()
		{
			return layer;
		}

	void SetStayAboveGround(bool sa) //ground accessor
		{
			stayAboveGround = sa;
		}

	void SetWrap(bool wrapOn) //Wrap accessor
		{
			wrap = wrapOn;
		} 

	//constructors / destructors
	TBSprite()
		{
			name = "";
			x = 0.0f;
			y = 0.0f;
			w = 0;
			h = 0;

			color = { 255, 255, 255 };
		}

	TBSprite(const TBSprite& copy)
	{
		x = copy.x;
		y = copy.y; 
		w = copy.w; 
		h = copy.h; 
		color = copy.color;
		name = copy.name;
		hasPhysics = copy.hasPhysics;
		vx = copy.vx;
		vy = copy.vy;
		fx = copy.fx;
		fy = copy.fy;
		ground = copy.ground; 
		stayAboveGround = copy.stayAboveGround;
		gravityActive = copy.gravityActive;
		pParent = copy.pParent;
		pShowOnCollide = copy.pShowOnCollide;
		visible = copy.visible;
		wrap = copy.wrap;
		hasAnimation = copy.hasAnimation;
		collideType = copy.collideType;
		isTextSprite = copy.isTextSprite;
		spriteText = copy.spriteText;
		hitTarget = copy.hitTarget;
		animationX = copy.animationX;
		animationY = copy.animationY;
		lifeTime = copy.lifeTime;
		age = copy.age;
		layer = copy.layer;
	}

	TBSprite(int left, int top, int width, int height, const RGBTRIPLE& rgbtriple)
		{
			Create(left, top, width, height, rgbtriple);
		}
	~TBSprite()
		{
		}

	//public functions
	void Create(int left, int top, int width, int height, const RGBTRIPLE& rgbtriple)
	{
		x = (float)left;
		y = (float)top;
		w = width;
		h = height;
		color = rgbtriple;
		name = "";
		gravityActive = false;
	}
	string TestCollision(vector<TBSprite>& sprites)
	{
		if (GetCollide() != CollideType::None && getPhysics())
		{
			for (int i = 0; i < (int)sprites.size(); i++)
			{
				if (name != sprites[i].name)
				{
					if (sprites[i].GetCollide() != CollideType::None)
					{
						if (TestIntersection(x, y, (float)w, (float)h, sprites[i].x, sprites[i].y, (float)sprites[i].w, (float)sprites[i].h))
						{
							//A collision has happened!
							if (sprites[i].GetCollide() == CollideType::Lose || sprites[i].GetCollide() == CollideType::Win)
							{
								setPhysics(false);
								x = floor(x);
								y = floor(y);
							}

							return sprites[i].name;
						}
					}
				}
			}
		}
		return "";
	}
	void Process(double elapsedTimeSec)
		{
			age += (float)elapsedTimeSec;
			if (lifeTime >= 0.0f && age >= lifeTime)
			{
				SetVisible(false);
			}
			if (hasPhysics == true)
			{
				if (name == "lander")
				{
					int u = 0;
				}
				//check y against ground
				if (y >= ground && this->stayAboveGround)
				{
					y = ground;
					vx = 0.0f;
					vy = 0.0f;
					x += vx;
					this->fx = this->fy = 0.0f;
					return;
				}

				// setup forces
				float fx = (this->fx * (float)elapsedTimeSec);
				float fy = (this->fy * (float)elapsedTimeSec);

				if (gravityActive)
				{
					fy += (g * (float)elapsedTimeSec);
				}

				//calculate velocities
				vx += fx;
				vy += fy;

				//calculate positions
				x += vx;
				y += vy;

				//zero out forces
				this->fx = this->fy = 0.0f;
			}
			if (hasAnimation == true)
			{
				x += (animationX * (float)elapsedTimeSec);
				y += (animationY * (float)elapsedTimeSec);
			}
		}
	void Draw(MCGraphics* pGFX)
		{
			if (visible)
			{
				if (GetIsTextSprite())
				{
					string text;
					int pos = (int)spriteText.find("<score>");
					if (pos != string::npos)
					{
						text = spriteText.substr(0, pos);
						text += to_string(g_CurrentScore);
					}
					else
					{
						int pos = (int)spriteText.find("<fuel>");
						if (pos != string::npos)
						{
							text = spriteText.substr(0, pos);
							text += to_string(g_fuel);
						}
					}
					//Now write text
					RECT rect = { (int)GetX(), (int)GetY(), (int)GetX() + w, (int)GetY() + h };
					pGFX->WriteText(rect, text, GetTextAlign());
					return;
				}
				if (pParent != nullptr)
				{
					pGFX->FillRectangle((int)GetX(), (int)GetY(), (int)GetX() + w, (int)GetY() + h, color);
				}
				else
				{
					pGFX->FillRectangle((int)x, (int)y, (int)x + w, (int)y + h, color);
				}

				if (wrap)
				{
					if (x >= g_pixelWidth) //sprite is past right of window
					{
						x -= (float)g_pixelWidth;
					}
					else if (x < (float)-w) //sprite is to the left of window
					{
						x += (float)g_pixelWidth;
					}
					else if (g_pixelWidth -x < w)
					{
						pGFX->FillRectangle((int)x, (int)y, (int)x + w, (int)y + h, color);
						int wrapX = (int)(x - (float)g_pixelWidth);
						pGFX->FillRectangle(wrapX, (int)y, wrapX + w, (int)y + h, color);
					}
					else if (x > -w && x < 0)
					{
						pGFX->FillRectangle((int)x, (int)y, (int)x + w, (int)y + h, color);
						int wrapX = (int)(x + (float)g_pixelWidth);
						pGFX->FillRectangle(wrapX, (int)y, wrapX + w, (int)y + h, color);
					}
				}
			}
		}
};