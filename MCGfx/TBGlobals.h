#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "MCGraphics.cpp"
using namespace std;

static wstring g_GameTitle = L"TanLander";

static  int g_pixelWidth = 288;
static int g_pixelHeight = 224;

//Force of Gravity
static float g = 0.01f;

static RGBTRIPLE DarkenColor(const RGBTRIPLE& s, int percent)
{
	float pc = (float)percent / 100.0f;
	RGBTRIPLE result = { (BYTE)((float)s.rgbtBlue * pc),(BYTE)((float)s.rgbtGreen * pc), (BYTE)((float)s.rgbtRed * pc) };
	return result;
}

//Game Timer
static LARGE_INTEGER    g_frequency;
static LARGE_INTEGER    g_startTime;
static LARGE_INTEGER    g_lastFrameTime;

static void StartTimer()
{
    QueryPerformanceFrequency(&g_frequency);
    QueryPerformanceCounter(&g_startTime);
    g_lastFrameTime = g_startTime;
}
static double GetElapsedSeconds()
{
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);
    return static_cast<double>(currentTime.QuadPart - g_startTime.QuadPart) / g_frequency.QuadPart;
}

static double GetElapsedFrameSeconds()
{
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);
    LARGE_INTEGER last = g_lastFrameTime;
    g_lastFrameTime = currentTime;
    return static_cast<double>(currentTime.QuadPart - last.QuadPart) / g_frequency.QuadPart;
}

static double GetElapsedMilliseconds()
{
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);
    return 1000.0 * static_cast<double>(currentTime.QuadPart - g_startTime.QuadPart) / g_frequency.QuadPart;
}

static bool TestIntersection(float ax, float ay, float aw, float ah, float bx, float by, float bw, float bh)
{
    if (ax + aw < bx || ax > bx + bw || ay + ah < by || ay > by + bh)
    {
        return false;
    }
    return true;
}
