#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "MCGraphics.cpp"
#include "TBGlobals.h"

using namespace std;
//Enum class Layers near to far
enum class LAYER
{
	layer_BACK = 0,
	layer_FAR,
	Layer_MID,
	layer_NEAR,
	layer_FRONT,
	layer_NONE,
};

//collide behavior enum
enum class Collide
{
	Win = 0,
	Loss,
	Explode,
	Restart,
	Push,
	Random,
};

class TBSprite
{
private:
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
	bool visible = true;
	bool wrap = false;
	bool hasAnimation = false;
	bool canCollide = false;
	bool isTextSprite = false;
	string spriteText = "";
	bool hitTarget = false;
	float animationX = 0.0f;
	float animationY = 0.0f;
	LAYER layer = LAYER::layer_NONE;


public:
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

	// accessors
	string GetName()
	{
		return name;
	}
	void SetName(string n)
	{
		name = n;
	}

	//hittarget accessors
	bool GetHitTarget()
	{
		return hitTarget;
	}
	void SetHitTarget(bool hTarget)
	{
		hitTarget = hTarget;
	}
	
	//Collision Accessors
	bool GetCollide()
	{
		return canCollide;
	}
	void SetCollide(bool active)
	{
		canCollide = active;
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
		// constructors / destructors
	TBSprite()
		{
			name = "";
			x = 0.0f;
			y = 0.0f;
			w = 0;
			h = 0;

			color = { 255, 255, 255 };
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

	void TestCollision(vector<TBSprite>& sprites)
	{
		if (GetCollide() && getPhysics())
		{
			for (int i = 0; i < (int)sprites.size(); i++)
			{
				if (name != sprites[i].name)
				{
					if (sprites[i].GetCollide())
					{
						if (TestIntersection(x, y, (float)w, (float)h, sprites[i].x, sprites[i].y, (float)sprites[i].w, (float)sprites[i].h))
						{
							setPhysics(false);
							x = floor(x);
							y = floor(y);
						}
					}
				}
			}
		}
	}

	void Process(double elapsedTimeSec)
		{
			
			if (hasPhysics == true)
			{
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
		//code for wrapping function
	void Draw(MCGraphics* pGFX)
		{
			if (visible)
			{
				if (GetIsTextSprite())
				{
					pGFX->DrawTextString(spriteText, GetX(), GetY(), GetX() + w, GetY() + h);
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