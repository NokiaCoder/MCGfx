#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "MCGraphics.cpp"
using namespace std;



static  int g_pixelWidth = 288;
static int g_pixelHeight = 224;

static RGBTRIPLE DarkenColor(const RGBTRIPLE& s, int percent)
{
	float pc = (float)percent / 100.0f;
	RGBTRIPLE result = { (BYTE)((float)s.rgbtBlue * pc),(BYTE)((float)s.rgbtGreen * pc), (BYTE)((float)s.rgbtRed * pc) };
	return result;
}

