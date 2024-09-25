#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "MCGraphics.cpp"
using namespace std;

static wstring g_GameTitle = L"TanLander";

static  int g_pixelWidth = 288;
static int g_pixelHeight = 224;

static float g_fPI = 3.14159265358979323846264338327950f;
static double g_PI = 3.14159265358979323846264338327950;

//Force of Gravity
static float g = 0.01f;

static RGBTRIPLE DarkenColor(const RGBTRIPLE& s, int percent)
{
	float pc = (float)percent / 100.0f;
	RGBTRIPLE result = { (BYTE)((float)s.rgbtBlue * pc),(BYTE)((float)s.rgbtGreen * pc), (BYTE)((float)s.rgbtRed * pc) };
	return result;
}

static RGBQUAD RGBQ(byte r, byte g, byte b, byte a)
{
    RGBQUAD color;
    color.rgbRed = r;
    color.rgbGreen = g;
    color.rgbBlue = b;
    color.rgbReserved = a;
    return color;
}

static void GetRandCircle(float radius, float* px, float* py)
{
    double theta = ((double)rand() / (double)RAND_MAX) * 2.0 * g_PI;
    *px = radius * (float)cos(theta);
    *py = radius * (float)sin(theta);
}

static int GetRandomH()
{
    return (int)((((float)rand() / (float)RAND_MAX) * (float)g_pixelWidth));
}

static int GetRandomV()
{
    return (int)((((float)rand() / (float)RAND_MAX) * (float)g_pixelHeight));
}
static float GetRandNorm()
{
    return (((float)rand() / (float)RAND_MAX) * 2.0f) - 1.0f;
}

static int g_CurrentScore = 0;

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
