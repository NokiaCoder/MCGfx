#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "MCGraphics.cpp"
#include "TBCamera.h"
#include "TBNotifyMgr.h"

using namespace std;

//Enum class Layers near to far
enum class LAYER
{
    layer_BACK = 0,
    layer_FAR = 1, 
    layer_MID = 2,
    layer_NEAR = 3,
    layer_FRONT = 4,
    layer_HUD = 5,
    layer_NONE = 6,
};

static string Layer2Str(LAYER l)
{
    switch (l)
    {
    case LAYER::layer_BACK:
        return "layer_BACK";
    case LAYER::layer_FAR:
        return "layer_FAR";
    case LAYER::layer_MID:
        return "layer_MID";
    case LAYER::layer_NEAR:
        return "layer_NEAR";
    case LAYER::layer_FRONT:
        return "layer_FRONT";
    case LAYER::layer_HUD:
        return "layer_HUD";
    }
    return "layer_NONE";
}
static LAYER Str2Layer(string s)
{
    if (s == "layer_BACK")
    {
        return LAYER::layer_BACK;
    }
    if (s == "layer_FAR")
    {
        return LAYER::layer_FAR;
    }
    if (s == "layer_MID")
    {
        return LAYER::layer_MID;
    }
    if (s == "layer_NEAR")
    {
        return LAYER::layer_NEAR;
    }
    if (s == "layer_FRONT")
    {
        return LAYER::layer_FRONT;
    }
    if (s == "layer_HUD")
    {
        return LAYER::layer_HUD;
    }
    return LAYER::layer_NONE;
}


static float Str2F(const string& s)
{
    return (float)atof(s.c_str());
}
static int Str2I(const string& s)
{
    return (int)atoi(s.c_str());
}
static bool Str2TF(const string& s)
{
    return s == "true" || s == "TRUE" || s == "True";
}

static float g_LandVyMax = 0.1f;

inline std::string& ltrim(std::string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}
inline std::string& rtrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(),
        std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}
inline std::string& trim(std::string& s)
{
    return ltrim(rtrim(s));
}
static int GetChunks(string str, vector<string>& chunks)
{
    int commaIndex = 0;
    chunks.clear();

    str = trim(str);

    if (str.length() > 0)
    {
        string firstString = "";
        chunks.push_back(firstString);
    }
    for (int i = 0; i < (int)str.size(); ++i)
    {
        if (str[i] != ',' && str[i] != '\r' && str[i] != '\n' && str[i] != ' ')
        {
            chunks[commaIndex].push_back(str[i]);
        }
        else
        {
            string newString = "";
            chunks.push_back(newString);
            commaIndex++;
        }
    }

    return (int)chunks.size();
}

static int GetChunks(string str,char delimiter, vector<string>& chunks)
{
    int commaIndex = 0;
    chunks.clear();

    str = trim(str);

    if (str.length() > 0)
    {
        string firstString = "";
        chunks.push_back(firstString);
    }
    for (int i = 0; i < (int)str.size(); ++i)
    {
        if (str[i] != delimiter && str[i] != '\r' && str[i] != '\n')
        {
            chunks[commaIndex].push_back(str[i]);
        }
        else
        {
            string newString = "";
            chunks.push_back(newString);
            commaIndex++;
        }
    }

    return (int)chunks.size();
}

static RGBTRIPLE Str2RGB(const string& s)
{
    vector<string> chunks;
    GetChunks(s, '|', chunks);
    RGBTRIPLE rgb;
    rgb.rgbtBlue = (uint8_t)Str2I(chunks[2]);
    rgb.rgbtGreen = (uint8_t)Str2I(chunks[1]);
    rgb.rgbtRed = (uint8_t)Str2I(chunks[0]);

    return rgb;
}

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

static string g_GameTitle = "Game Title";

static TBCamera g_Camera;

static TBNotifyMgr g_Notify;


static  int g_pixelWidth = 288;
static int g_pixelHeight = 224;
static int g_LevelOn = 1;
static	int g_fuel;
static int powerUpFuel = 50;

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
static int g_Lives = 3;

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

static string GetCWD()
{
    char buffer[2048];
    GetCurrentDirectoryA(2048, buffer);
    return string(buffer);
}

static string GetContentFolder()
{
    return GetCWD() + "\\Content";
}
