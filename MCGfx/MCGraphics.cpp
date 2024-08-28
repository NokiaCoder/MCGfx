#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include <vector>
#include "TBGlobals.h"

using namespace std;





class MCGraphics
{
private:
    // Private member variables
    int width = 0;
    int height = 0;
    bool isActive = false;
    bool stretchToFill = false;
    bool randomizeColors = false;
    RGBTRIPLE clearColor = { 0, 0, 0 };

    //info for blit
    BITMAPINFO bitmapInfo;

    //backBuffer array
    std::vector<RGBTRIPLE> backBuffer;

    // Private member functions
    void InitializeBitmapInfo()
    {
        ZeroMemory(&bitmapInfo, sizeof(bitmapInfo));
        bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bitmapInfo.bmiHeader.biWidth = width;
        bitmapInfo.bmiHeader.biHeight = -height; // Negative for top-down bitmap
        bitmapInfo.bmiHeader.biPlanes = 1;
        bitmapInfo.bmiHeader.biBitCount = 24; // 24 bits per pixel (RGB)
        bitmapInfo.bmiHeader.biCompression = BI_RGB;
    }

public:
    //Constructor & Destructor    
    MCGraphics()
    {
        isActive = false;
        width = 0;
        height = 0;
        ZeroMemory(&bitmapInfo, sizeof(bitmapInfo));
    }
    ~MCGraphics()
    {
	}   

    //Public Member Functions
    void Initialize(int widthPixels, int heightPixels)
	{
		width = widthPixels;
		height = heightPixels;
		backBuffer.resize(width * height);

        Clear();
		InitializeBitmapInfo();
        isActive = true;
	}

    //Public Getters & Setters
    bool GetRandomizeColor()
    {
        return randomizeColors;
    }
    void SetRandomizeColor(bool isActive)
	{
		randomizeColors = isActive;
	}
    bool GetStretchToFill()
	{
		return stretchToFill;
	}
    void SetStretchToFill(bool isActive)
    {
        stretchToFill = isActive;
	}
    void SetBackgroundColor(RGBTRIPLE color)
	{
		clearColor = color;
	}
    RGBTRIPLE GetBackgroundColor()
    {
        return clearColor;
	}

    //Public Backbuffer Drawing Functions
    void Clear()
    {
        std::fill(backBuffer.begin(), backBuffer.end(), clearColor);
    }
    void Clear(COLORREF color)
    {
        RGBTRIPLE rgb;
        rgb.rgbtRed = GetRValue(color);
        rgb.rgbtGreen = GetGValue(color);
        rgb.rgbtBlue = GetBValue(color);

        std::fill(backBuffer.begin(), backBuffer.end(), rgb);
    }
    void SetPixel(int x, int y, RGBTRIPLE color)
    {
        if (x >= 0 && x < width && y >= 0 && y < height)
        {
            backBuffer[y * width + x] = color;
        }
    }
    void DrawLine(int x0, int y0, int x1, int y1, RGBTRIPLE color)
	{
		int dx = abs(x1 - x0);
		int dy = abs(y1 - y0);
		int sx = x0 < x1 ? 1 : -1;
		int sy = y0 < y1 ? 1 : -1;
		int err = (dx > dy ? dx : -dy) / 2;
		int e2;

        if( randomizeColors )
		{
			color.rgbtRed = rand() % 256;
			color.rgbtGreen = rand() % 256;
			color.rgbtBlue = rand() % 256;
		}

		for (;;)
		{
			SetPixel(x0, y0, color);

            if (x0 == x1 && y0 == y1)
            {
                break;
            }

			e2 = err;
			if (e2 > -dx) 
            { 
                err -= dy; 
                x0 += sx; 
            }

			if (e2 < dy) 
            { 
                err += dx; 
                y0 += sy; 
            }
		}
	}
    void DrawRectangle(int x0, int y0, int x1, int y1, RGBTRIPLE color)
    {
        if (randomizeColors)
        {
            color.rgbtRed = rand() % 256;
            color.rgbtGreen = rand() % 256;
            color.rgbtBlue = rand() % 256;
        }

        int xMin = min(max(x0, 0), width);
        int xMax = min(max(x1, 0), width);
        int yMin = min(max(y0, 0), height);
        int yMax = min(max(y1, 0), height);

        for( int i = xMin; i <= xMax; i++)
		{
            backBuffer[yMin * width + i] = color;
            backBuffer[yMax * width + i] = color;
		}
        for( int i = yMin; i <= yMax; i++)  
        {
            backBuffer[i * width + xMin] = color;
            backBuffer[i * width + xMax] = color;
            SetPixel(xMin, i, color);
			SetPixel(xMax, i, color);
		}
    }
    void FillRectangle(int x0, int y0, int x1, int y1, RGBTRIPLE color)
	{
        if (randomizeColors)
        {
            color.rgbtRed = rand() % 256;
            color.rgbtGreen = rand() % 256;
            color.rgbtBlue = rand() % 256;
        }

        int xMin = min(max(x0, 0), width);
        int xMax = min(max(x1, 0), width);

		for (int y = y0; y <= y1; y++)
		{
            for( int x = xMin; x <= xMax; x++)
			{
				SetPixel(x, y, color);
			}
		}
	}

    //Present to Screen
    void Present(HWND hwnd)
    {
        if (isActive)
        {
            HDC hdc = GetDC(hwnd);
            RECT clientRect;
            GetClientRect(hwnd, &clientRect);

            int srcWidth = width;
            int srcHeight = height;
            int destWidth = clientRect.right - clientRect.left;
            int destHeight = clientRect.bottom - clientRect.top;

            StretchDIBits(
                            hdc,
                            0, 0, destWidth, destHeight,    // Destination rectangle
                            0, 0, srcWidth, srcHeight,      // Source rectangle
                            backBuffer.data(),
                            &bitmapInfo,
                            DIB_RGB_COLORS,
                            SRCCOPY
                        );

            ReleaseDC(hwnd, hdc);   
        }
    }
};
