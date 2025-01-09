#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include "MCGraphics.cpp"
#include "TBGlobals.h"
//#include "TBNotifyMgr.h"

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

static string CollideType2Str(CollideType c)
{
	switch (c)
	{
	case CollideType::None:
		return "None";
	case CollideType::Win:
		return "Win";
	case CollideType::Lose:
		return "Lose";
	case CollideType::Explode:
		return "Explode";
	case CollideType::Restart:
		return "Restart";
	case CollideType::Push:
		return "Push";
	case CollideType::Random:
		return "Random";
	case CollideType::PowerUp:
		return "PowerUp";
	}
	return "None";
}
static CollideType Str2CollideType(string s)
{
	if (s == "None")
	{
		return CollideType::None;
	}
	if (s == "Win")
	{
		return CollideType::Win;
	}
	if (s == "Lose")
	{
		return CollideType::Lose;
	}
	if (s == "Explode")
	{
		return CollideType::Explode;
	}
	if (s == "Restart")
	{
		return CollideType::Restart;
	}
	if (s == "Push")
	{
		return CollideType::Push;
	}
	if (s == "Random")
	{
		return CollideType::Random;
	}
	if (s == "PowerUp")
	{
		return CollideType::PowerUp;
	}

	return CollideType::None;
}

static string TextAlign2Str(TEXT_ALIGN ta)
{
	switch (ta)
	{
	case TEXT_ALIGN::CENTER:
		return "CENTER";
	case TEXT_ALIGN::LEFT:
		return "LEFT";
	case TEXT_ALIGN::RIGHT:
		return "RIGHT";
	}
	return "CENTER";
}
static TEXT_ALIGN Str2TextAlign(string s)
{
	if (s == "CENTER")
	{
		return TEXT_ALIGN::CENTER;
	}
	if (s == "LEFT")
	{
		return TEXT_ALIGN::LEFT;
	}
	if (s == "RIGHT")
	{
		return TEXT_ALIGN::RIGHT;
	}

	return TEXT_ALIGN::CENTER;
}

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
	string parentName = "";
	string showOnCollideName = "";
	TBSprite* pParent = nullptr;
	TBSprite* pShowOnCollide = nullptr;
	bool visible = true;
	bool wrap = false;
	bool hasAnimation = false;
	CollideType collideType = CollideType::None;
	bool isTextSprite = false;
	bool isScreen = false;
	bool explodeOnCollideLose = false;
	TEXT_ALIGN textAlign = TEXT_ALIGN::LEFT;
	string spriteText = "";
	bool hitTarget = false;
	float animationX = 0.0f;
	float animationY = 0.0f;
	float lifeTime = -1.0f;
	float age = 0.0f;
	LAYER layer = LAYER::layer_NONE;


public:

	string Serialize()
	{

		string str = "\nSPRITE\n";
		str += "x," + to_string(x) + "\n";
		str += "y," + to_string(y) + "\n";
		str += "w," + to_string(w) + "\n";
		str += "h," + to_string(h) + "\n";

		str += "color," + to_string(color.rgbtRed) + "|" + to_string(color.rgbtGreen) + "|" + to_string(color.rgbtBlue) + "\n";

		str += "name," + name + "\n";

		str += "hasPhysics," + string(hasPhysics ? "TRUE\n":"FALSE\n");

		str += "vx," + to_string(vx) + "\n";
		str += "vy," + to_string(vy) + "\n";
		str += "fx," + to_string(fx) + "\n";
		str += "fy," + to_string(fy) + "\n";

		str += "ground," + to_string(ground) + "\n";

		str += "stayAboveGround," + string(stayAboveGround ? "TRUE\n":"FALSE\n");
		str += "gravityActive," + string(gravityActive ? "TRUE\n" : "FALSE\n");

		str += "pParent," + string(pParent != nullptr ? pParent->GetName() + "\n" : "\n");
		str += "pShowOnCollide," + string(pShowOnCollide != nullptr ? pShowOnCollide->GetName() + "\n" : "\n");

		str += "visible," + string(visible ? "TRUE\n" : "FALSE\n");
		str += "wrap," + string(wrap ? "TRUE\n" : "FALSE\n");
		str += "hasAnimation," + string(hasAnimation ? "TRUE\n" : "FALSE\n");

		str += "collideType," + CollideType2Str(collideType) + "\n";

		str += "isTextSprite," + string(isTextSprite ? "TRUE\n" : "FALSE\n");
		str += "isScreen," + string(isScreen ? "TRUE\n" : "FALSE\n");
		str += "explodeOnCollideLose," + string(explodeOnCollideLose ? "TRUE\n" : "FALSE\n");

		str += "textAlign," + TextAlign2Str(textAlign) + "\n";

		str += "spriteText," + spriteText + "\n";

		str += "hitTarget," + string(hitTarget ? "TRUE\n" : "FALSE\n");

		str += "animationX," + to_string(animationX) + "\n";
		str += "animationY," + to_string(animationY) + "\n";
		str += "lifeTime," + to_string(lifeTime) + "\n";
		str += "age," + to_string(age) + "\n";

		str += "layer," + Layer2Str(layer) + "\n";


		return str;
	}

	int Deserialize(const vector<string>& lines, int startIndex)
	{
		int index = startIndex;
		if (lines[index] == "SPRITE")
		{
			index++;
		}
		


		while (lines[index] != "")
		{


			//Line has KVP(KEYVALUEPAIR)
			vector<string> chunks;
			GetChunks(lines[index], chunks);
			if (chunks[0] == "x")
			{
				x = Str2F(chunks[1]);
			}
			else if (chunks[0] == "y")
			{
				y = Str2F(chunks[1]);
			}
			else if (chunks[0] == "w")
			{
				w = Str2I(chunks[1]);
			}
			else if (chunks[0] == "h")
			{
				h = Str2I(chunks[1]);
			}
			else if (chunks[0] == "color")
			{
				color = Str2RGB(chunks[1]);
			}
			else if (chunks[0] == "name")
			{
				name = chunks[1];
			}
			else if (chunks[0] == "hasPhysics")
			{
				hasPhysics = Str2TF(chunks[1]);
			}
			else if (chunks[0] == "vx")
			{
				vx = Str2F(chunks[1]);
			}
			else if (chunks[0] == "vy")
			{
				vy = Str2F(chunks[1]);
			}
			else if (chunks[0] == "fx")
			{
				fx = Str2F(chunks[1]);
			}
			else if (chunks[0] == "fy")
			{
				fy = Str2F(chunks[1]);
			}
			else if (chunks[0] == "ground")
			{
				ground = Str2F(chunks[1]);
			}
			else if (chunks[0] == "stayAboveGround")
			{
				stayAboveGround = Str2TF(chunks[1]);
			}
			else if (chunks[0] == "gravityActive")
			{
				gravityActive = Str2TF(chunks[1]);
			}
			else if (chunks[0] == "pParent")
			{
				SetParentName(chunks[1]);
			}
			else if (chunks[0] == "pShowOnCollide")
			{
				SetShowOnCollideName(chunks[1]);
			}
			else if (chunks[0] == "visible")
			{
				visible = Str2TF(chunks[1]);
			}
			else if (chunks[0] == "wrap")
			{
				wrap = Str2TF(chunks[1]);
			}
			else if (chunks[0] == "hasAnimation")
			{
				hasAnimation = Str2TF(chunks[1]);
			}
			else if (chunks[0] == "collideType")
			{
				collideType = Str2CollideType(chunks[1]);
			}
			else if (chunks[0] == "isTextSprite")
			{
				isTextSprite = Str2TF(chunks[1]);
			}
			else if (chunks[0] == "isScreen")
			{
				isScreen = Str2TF(chunks[1]);
			}
			else if (chunks[0] == "explodeOnCollideLose")
			{
				explodeOnCollideLose = Str2TF(chunks[1]);
			}
			else if (chunks[0] == "textAlign")
			{
				textAlign = Str2TextAlign(chunks[1]);
			}
			else if (chunks[0] == "spriteText")
			{
				spriteText = (chunks[1]);
			}
			else if (chunks[0] == "hitTarget")
			{
				hitTarget = Str2TF(chunks[1]);
			}
			else if (chunks[0] == "animationX")
			{
				animationX = Str2F(chunks[1]);
			}
			else if (chunks[0] == "animationY")
			{
				animationY = Str2F(chunks[1]);
			}
			else if (chunks[0] == "lifeTime")
			{
				lifeTime = Str2F(chunks[1]);
			}
			else if (chunks[0] == "age")
			{
				age = Str2F(chunks[1]);
			}
			else if (chunks[0] == "layer")
			{
				layer = Str2Layer(chunks[1]);
			}

			index++;
		}

		return index;
	}

	//ACCESSORS

	//Screen
	void SetScreen(bool s)
	{
		isScreen = s;
	}
	bool GetScreen()
	{
		return isScreen;
	}

	//Explode om loss collide
	void SetExplodeOnCollide(bool eocl)
	{
		explodeOnCollideLose = eocl;
	}
	bool GetExplodeOnCollide()
	{
		return explodeOnCollideLose;
	}

	//collide
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


	//GETTERS AND SETTERS
	TBSprite* GetParent()
	{
		return pParent;
	}
	void SetParent(TBSprite* pP)
	{
		if (pP != nullptr)
		{
			int u = 0;
		}
		pParent = pP;
	}

	//ParentName Get and Set
	void SetParentName(string sp)
	{
		parentName = sp;
	}
	string GetParentName()
	{
		return parentName;
	}

	//ShowOnCollide Get and Set
	void SetShowOnCollideName(string sc)
	{
		showOnCollideName = sc;
	}
	string GetShowOnCollideName()
	{
		return showOnCollideName;
	}

	float GetX()
	{
		float worldX = x;
		if (pParent != nullptr)
		{
			worldX = x + pParent->GetX();
		}
		if (!isScreen)
		{
			return g_Camera.TransformX(worldX);
		}
		return worldX;
	}
	float GetY()
	{
		float worldY = y;
		if (pParent != nullptr)
		{
			worldY = y + pParent->GetY();
		}
		if (!isScreen)
		{
			return g_Camera.TransformY(worldY);
		}
		return worldY;
	}

	void SetVx(float v)
	{
		vx = v;
	}
	void SetVy(float v)
	{
		vy = v;
	}

	float GetVx()
	{
		return vx;
	}
	float GetVy()
	{
		return vy;
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
		isScreen = copy.isScreen;
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
		if (GetVisible() && GetCollide() != CollideType::None && getPhysics())
		{
			for (int i = 0; i < (int)sprites.size(); i++)
			{
				if (name != sprites[i].name) //Test that the test sprite is not the same as this sprite
				{
					if (sprites[i].GetVisible() && sprites[i].GetCollide() != CollideType::None)
					{
						if (TestIntersection(x, y, (float)w, (float)h, sprites[i].x, sprites[i].y, (float)sprites[i].w, (float)sprites[i].h))
						{
							//A collision has happened!
		/*					g_Notify.Notify({ NOTIFYTYPE::OnCollide, OBJECTTYPE::SPR, this->name });*/
							if (sprites[i].GetCollide() == CollideType::Lose)
							{
								g_Notify.Notify({ NOTIFYTYPE::OnExplode, OBJECTTYPE::SPR, this->name });
							}
							if (sprites[i].GetCollide() == CollideType::Win)
							{
								setPhysics(false);
								x = floor(x);
								y = floor(y);
								g_Notify.Notify({ NOTIFYTYPE::OnWin, OBJECTTYPE::SPR, this->name });
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
				string text = spriteText;

				//Now write text
				RECT rect = { (int)GetX(), (int)GetY(), (int)GetX() + w, (int)GetY() + h };
				pGFX->WriteText(rect, text, GetTextAlign());
				return;
			}

			//Not a sprite text
			pGFX->FillRectangle((int)GetX(), (int)GetY(), (int)GetX() + w, (int)GetY() + h, color);



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
				else if (g_pixelWidth - x < w)
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