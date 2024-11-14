#pragma once
#include <string>
#include <vector>

using namespace std;

class TBCamera
{
public:
	float wtsX = 0.0f;
	float wtsY = 0.0f;

	float TransformX(float worldX)
	{
		return wtsX + worldX;
	}

	float TransformY(float worldY)
	{
		return wtsY + worldY;
	}

	void Transform(float* pWorldX, float* pWorldY)
	{
		*pWorldX = *pWorldX + wtsX;
		*pWorldY = *pWorldY + wtsY;
	}

	void Move(float x, float y)
	{
		wtsX += x;
		wtsY += y;
	}

	void MoveTo(float x, float y)
	{
		wtsX = x;
		wtsY = y;
	}
};

