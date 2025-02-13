#pragma once
#include "TBSprite.cpp"
#include "TBGlobals.h"

enum class Move_Direction
{
	None = 0,
	Up,
	Down,
	Left,
	Right,
	UpLeft,
	DownLeft,
	UpRight,
	DownRight,
	
};

enum class TARGET_TYPE
{
	None = 0,
	Dropper,
	SliderLR,
	SliderRL,
	Lifter,
	Still,

};

static bool MoveHasX(Move_Direction md)
{
	return (int)md >= 3;
}
static bool MoveHasY(Move_Direction md)
{
	return (int)md > 0 && ((int)md < 3 || (int)md > 4);
}

class TBHitTarget : public TBSprite
{
private:

protected:

	Move_Direction move = Move_Direction::None;
	TARGET_TYPE targetType = TARGET_TYPE::None;

public:

	string GetType() override;

	

	TBSprite* GetBase()
	{
		return (TBSprite*)this;
	}

	Move_Direction GetMoveDirection()
	{
		return move;
	}
	void SetMoveDirection(Move_Direction md)
	{
		move = md;
		GetBase()->SetHasAnimation(move != Move_Direction::None);
		GetBase()->SetAnimationX(MoveHasX(move) ? 1.0f : 0.0f);
		GetBase()->SetAnimationY(MoveHasY(move) ? 1.0f : 0.0f);
	}

	TARGET_TYPE GetTargetType()
	{
		return targetType;
	}
	void SetTargetType(TARGET_TYPE tt)
	{
		targetType = tt;
		switch (targetType)
		{
		case TARGET_TYPE::Dropper:
		{
			Create((int)GetRandRange(0, (float)g_pixelWidth), 0, 5, 5, ASTEROIDCOLOR);
			SetMoveDirection(Move_Direction::Down);
			GetBase()->SetHasAnimation(true);
			GetBase()->SetAnimationY(GetRandRange(5.0f, 10.0f) * 10.0f);
			GetBase()->SetLayer(LAYER::layer_FRONT);
			SetCollide(CollideType::Lose);
			break;
		}
		case TARGET_TYPE::Lifter:
		{
			Create((int)GetRandRange(0, (float)g_pixelWidth), 0, 5, 5, ASTEROIDCOLOR);
			SetMoveDirection(Move_Direction::Up);
			GetBase()->SetHasAnimation(true);
			GetBase()->SetAnimationY(GetRandRange(5.0f, 10.0f) * 10.0f);
			GetBase()->SetLayer(LAYER::layer_FRONT);
			SetCollide(CollideType::Lose);
			break;
		}
		case TARGET_TYPE::SliderLR:
		{
			Create(0, (int)GetRandRange(0, (float)g_pixelWidth), 5, 5, SLIDERLRCOLOR);
			GetBase()->SetHasAnimation(true);
			GetBase()->SetAnimationX(GetRandRange(5.0f, 10.0f) * 10.0f);
			GetBase()->SetLayer(LAYER::layer_FRONT);
			SetCollide(CollideType::Lose);
			break;
		}
		case TARGET_TYPE::SliderRL:
		{
			Create(g_pixelWidth, (int)GetRandRange(0, (float)g_pixelWidth), 5, 5, SLIDERRLCOLOR);
			GetBase()->SetHasAnimation(true);
			GetBase()->SetAnimationX(-GetRandRange(5.0f, 10.0f) * 10.0f);
			GetBase()->SetLayer(LAYER::layer_FRONT);
			SetCollide(CollideType::PowerUp);
			break;
		}
		case TARGET_TYPE::Still:
		{
			Create(0, 0, 5, 10, PAYLOADCOLOR);
			GetBase()->SetLayer(LAYER::layer_FRONT);
			SetCollide(CollideType::PowerUp);
			break;
		}

		}
	}

	void Process(double elapsedTimeSec) override;
};


