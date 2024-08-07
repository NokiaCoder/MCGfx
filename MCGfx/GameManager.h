#pragma once
#include <string>
#include <vector>
#include "MCGraphics.cpp"
using namespace std;


class GameManager
{
private:
	MCGraphics* pGfx = nullptr;
	bool lButtonDown = false;
	bool rButtonDown = false;
	bool lButtonClick = false;
	bool rButtonClick = false;
	int mouseX = 0;
	int mouseY = 0;



public:
void SetPointer(MCGraphics* ptr)
{
	pGfx = ptr;
}



void Update(bool lb, bool rb, int x, int y)
{
	//Handle left Button
	if (lButtonDown != lb)
	{
		lButtonClick = !lb;
	}
	else
	{
		lButtonClick = false;
	}
	lButtonDown = lb;

	//Handle Right Button
	if (rButtonDown != rb)
	{
		rButtonClick = !rb;
	}
	else
	{
		rButtonClick = false;
	}
	rButtonDown = rb;

	mouseX = x;
	mouseY = y;
}

void Render(HWND hwnd)
{
	pGfx->SetRandomizeColor(true);
	//pGfx->Clear();
	//pGfx->DrawLine(0, 0, mouseX , mouseY, { 255, 100, 0 });
	if (lButtonClick)
	{
		pGfx->FillRectangle(mouseX - 100, mouseY - 100, mouseX + 100, mouseY + 100, { 0, 0, 0 });
		lButtonClick = false;
	}
	pGfx->Present(hwnd);
	
}



};

