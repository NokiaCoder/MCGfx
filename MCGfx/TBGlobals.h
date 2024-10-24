#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "MCGraphics.cpp"
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

struct CollisionInfo
{
    string a;
    string b;
    bool isSprite;
    
    CollisionInfo(string aId, string bId, bool s)
    {
        a = aId;
        b = bId;
        isSprite = s;
    }

    CollisionInfo(const CollisionInfo& copy)
    {
        a = copy.a;
        b = copy.b;
        isSprite = copy.isSprite;
    }
};


static wstring g_GameTitle = L"TanLander";

static  int g_pixelWidth = 288;
static int g_pixelHeight = 224;
static int g_LevelOn = 1;

static float g_fPI = 3.14159265358979323846264338327950f;
static double g_PI = 3.14159265358979323846264338327950;
static double g_DEG2RAD = g_PI / 180.0;

//Force of Gravity
static float g = 0.01f;

static RGBTRIPLE DarkenColor(const RGBTRIPLE& s, int percent)
{
	float pc = (float)percent / 100.0f;
	RGBTRIPLE result = { (BYTE)((float)s.rgbtBlue * pc),(BYTE)((float)s.rgbtGreen * pc), (BYTE)((float)s.rgbtRed * pc) };
	return result;
}

static RGBTRIPLE BlendColor(const RGBTRIPLE& a, const RGBTRIPLE& b, int percent)
{
    float w = (float)percent / 100.0f;

    RGBTRIPLE c;
    c.rgbtBlue = (BYTE)(((float)a.rgbtBlue * w) + ((float)b.rgbtBlue * (1.0f - w)));
    c.rgbtGreen = (BYTE)(((float)a.rgbtGreen * w) + ((float)b.rgbtGreen * (1.0f - w)));
    c.rgbtRed = (BYTE)(((float)a.rgbtRed * w) + ((float)b.rgbtRed * (1.0f - w)));
    return c;
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

//Math Library

static float GetRandNorm()
{
    return (((float)rand() / (float)RAND_MAX) + 1.0f) * 0.5f;
}

static float GetRandF()
{
    return (float)rand() / (float)RAND_MAX;
}

static float GetMag(float x, float y)
{
    return sqrt(x * x + y * y);
}

static void Normalize(float& x, float& y)
{
    float mag = GetMag(x, y);
    if (mag == 0.0f)
    {
        x = 0.0f;
        y = 0.0f;
    }
    else
    {
        x /= mag;
        y /= mag;
    }
}

static void Scale(float& x, float& y, const float& scalar)
{
    x *= scalar;
    y *= scalar;
}

static float GetRandRange(float from, float to)
{
    return from + GetRandF() * (to - from);
}

static void GetRandCircle(float radius, float* px, float* py)
{
    double theta = ((double)rand() / (double)RAND_MAX) * 2.0 * g_PI;
    *px = radius * (float)cos(theta);
    *py = radius * (float)sin(theta);
}

static void GetRandCircle(float radiusMin, float radiusMax, float startDeg, float endDeg, float speed, float* vx,float* vy, float* px, float* py)
{
    float rad = GetRandRange(radiusMin, radiusMax);
    double theta = GetRandRange(startDeg, endDeg) * g_DEG2RAD;
    float velx = (float)cos(theta);
    float vely = (float)sin(theta);
    
    *px = rad * velx;
    *py = rad * vely;

    Normalize(velx, vely);
    Scale(velx, vely, speed * GetRandNorm());
    
    *vx = velx;
    *vy = vely;
}

static int GetRandomH()
{
    return (int)((((float)rand() / (float)RAND_MAX) * (float)g_pixelWidth));
}

static int GetRandomV()
{
    return (int)((((float)rand() / (float)RAND_MAX) * (float)g_pixelHeight));
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

static double GetElapsedMilliSecondsSinceFrame()
{
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);
    return 1000.0 * static_cast<double>(currentTime.QuadPart - g_lastFrameTime.QuadPart) / g_frequency.QuadPart;
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
