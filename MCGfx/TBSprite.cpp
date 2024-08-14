#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "MCGraphics.cpp"

using namespace std;

class TBSprite
{
	private:
		float x = 0.0f; //left most
		float y = 0.0f; //upper most
		int w = 0; //width
		int h = 0; //height
		RGBTRIPLE color;
		string name;
		float vx = 0.0f;
		float vy = 0.1f;
		float fx = 0.0f;
		float fy = 0.0f;
		float g = 0.001f;
		float ground = 500.0f;
		bool gravityActive = false;
		TBSprite* pParent = nullptr;
		bool visible = true;
		bool wrap = false;

		

public:
		// accessors
		string GetName()
		{
			return name;
		}
		void SetName(string n)
		{
			name = n;
		}

		bool GetGravityOn()
		{
			return gravityActive;
		}
		void SetGravityOn(bool gravityOn)
		{
			gravityActive = gravityOn;
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
			fx = f;
		}
		void SetFy(float f)
		{
			fy = f;
		}

		void SetWrap(bool wrapOn)
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
		}

		void Process()
		{
			if (gravityActive)
			{
				// setup forces
				float fx = this->fx;
				float fy = g + this->fy; //fy is set to gravity

				//calculate velocities
				vx += fx;
				vy += fy;

				//calculate positions
				x += vx;
				y += vy;

				//check y against ground
				if (y > ground)
				{
					y = ground;
					vx = 0.0f;
					vy = 0.0f;
				}
			}
		}

		void Draw(MCGraphics* pGFX)
		{
			if (visible)
			{
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
					if (x >= 800)
					{
						x -= 800.0f;
					}
					else if (x < (float)-w)
					{
						x += 800.0f;
					}
				}
			}
		}
	
		



};