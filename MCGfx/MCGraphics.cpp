#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include <vector>
#include "TBGlobals.h"

using namespace std;

struct TextBlock
{
    float x, y, w, h;
    string text;
    TextBlock() = default;
    TextBlock(float fx, float fy, float fw, float fh, const string& txt)
    {
        x = fx;
        y = fy;
        w = fw;
        h = fh;
        text = txt;
    }
    TextBlock(const TextBlock& copy)
    {
        x = copy.x;
        y = copy.y;
        w = copy.w;
        h = copy.h;
        text = copy.text;
    }
};

enum class TEXT_ALIGN
{
	LEFT,
	CENTER,
	RIGHT
};

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
    RGBTRIPLE textColor = { 255, 255, 255 };
    vector<TextBlock> textToRender;
    HFONT hFontSans = 0;

    //info for blit
    BITMAPINFO bitmapInfo;

	HWND hwnd = nullptr;
	HFONT hFontOCR = 0; //for rendering text

    //for rendering text
    HDC backbufferDC = 0;
    HBITMAP hBitmap_ = 0;
    RGBTRIPLE* pixelData_ = nullptr;
    //

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

    COLORREF RGBT2CR(const RGBTRIPLE& c)
    {
        return RGB(c.rgbtRed, c.rgbtGreen, c.rgbtBlue);
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
    void Initialize(HWND hwnd, int widthPixels, int heightPixels)
	{
		this->hwnd = hwnd;
		width = widthPixels;
		height = heightPixels;

        Clear();
		InitializeBitmapInfo();
        isActive = true;

        hFontSans = CreateFont(
            16,                        // Height (in points)
            0,                         // Width (0 means calculate automatically)
            0,                         // Escapement angle
            0,                         // Orientation angle
            FW_NORMAL,                  // Font weight
            FALSE,                      // Italic
            FALSE,                      // Underline
            FALSE,                      // Strikeout
            DEFAULT_CHARSET,            // Character set
            OUT_DEFAULT_PRECIS,         // Output precision
            CLIP_DEFAULT_PRECIS,        // Clipping precision
            CLEARTYPE_QUALITY,          // Quality (for ClearType)
            DEFAULT_PITCH | FF_SWISS,   // Font family
            TEXT("Courier"));           // Font fac

        //hFontSans = CreateFont(
        //    12,                        // Height of the font
        //    0,                         // Width of the font (0 = default)
        //    0,                         // Angle of escapement
        //    0,                         // Orientation angle
        //    FW_NORMAL,                 // Font weight (FW_BOLD for bold)
        //    FALSE,                     // Italic attribute
        //    FALSE,                     // Underline attribute
        //    FALSE,                     // Strikeout attribute
        //    DEFAULT_CHARSET,           // Character set
        //    OUT_DEFAULT_PRECIS,        // Output precision
        //    CLIP_DEFAULT_PRECIS,       // Clipping precision
        //    DEFAULT_QUALITY,           // Output quality
        //    DEFAULT_PITCH | FF_SWISS,  // Pitch and family
        //    L"Lucida Sans"                   // Font face name
        //);

        hFontOCR = CreateFont(
            10,                      // Height of font
            0,                       // Default width
            0,                       // Escapement angle
            0,                       // Orientation angle
            FW_BOLD,                 // Font weight (bold)
            FALSE,                   // Italic (false)
            FALSE,                   // Underline (false)
            FALSE,                   // StrikeOut (false)
            ANSI_CHARSET,            // Character set
            OUT_DEFAULT_PRECIS,      // Output precision
            CLIP_DEFAULT_PRECIS,     // Clipping precision
            DEFAULT_QUALITY,         // Output quality
            DEFAULT_PITCH | FF_SWISS,// Pitch and family
            L"OCR A");

        HDC screenDC = GetDC(NULL);
        backbufferDC = CreateCompatibleDC(screenDC);

        // Create DIB section and link pixelData_ to the RGB buffer
        hBitmap_ = CreateDIBSection(backbufferDC, &bitmapInfo, DIB_RGB_COLORS, (void**)&pixelData_, NULL, 0);
        if (hBitmap_ != 0)
        {
            SelectObject(backbufferDC, hBitmap_);
        }

        ReleaseDC(NULL, screenDC);
        
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
    void SetColorText(const RGBTRIPLE& color)
    {
        textColor = color;
    }
    RGBTRIPLE GetColorText()
    {
        return textColor;
    }
    HWND GetHWND()
    {
        return this->hwnd;
    }
    //Public Backbuffer Drawing Functions
    void Clear()
    {
        if (pixelData_ != nullptr)
        {
            for (int i = 0; i < width * height; i++)
            {
                pixelData_[i] = clearColor;
            }
        }
    }
    void Clear(COLORREF color)
    {
        RGBTRIPLE rgb;
        rgb.rgbtRed = GetRValue(color);
        rgb.rgbtGreen = GetGValue(color);
        rgb.rgbtBlue = GetBValue(color);

        for (int i = 0; i < width * height; i++)
        {
            pixelData_[i] = rgb;
        }
    }
    void SetPixel(int x, int y, RGBTRIPLE color)
    {
        if (x >= 0 && x < width && y >= 0 && y < height)
        {
            pixelData_[y * width + x] = color;
        }
    }
    void WriteText(RECT& rect, const string& str, TEXT_ALIGN align)
    {
        SetBkMode(backbufferDC, TRANSPARENT);
        COLORREF cr = RGBT2CR(textColor);
        COLORREF old_ = SetTextColor(backbufferDC, cr);
        SelectObject(backbufferDC, hFontSans);
        DWORD dwFlags = align == TEXT_ALIGN::LEFT ? DT_LEFT : align == TEXT_ALIGN::CENTER ? DT_CENTER : DT_RIGHT;
        DrawTextA(backbufferDC, str.c_str(), static_cast<int>(str.length()), &rect, dwFlags);
        SetTextColor(backbufferDC, old_);
    }
    RGBTRIPLE GetPixel(int x, int y)
    {
        if (x >= 0 && x < width && y >= 0 && y < height)
        {
            return pixelData_[y * width + x];
        }
        return { 0, 0, 0 };
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
            pixelData_[yMin * width + i] = color;
            pixelData_[yMax * width + i] = color;
		}
        for( int i = yMin; i <= yMax; i++)  
        {
            pixelData_[i * width + xMin] = color;
            pixelData_[i * width + xMax] = color;
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
    void DrawTextString(const string& text, float x, float y, float w, float h)
    {
        TextBlock tb(x, y, w, h, text);
        textToRender.push_back(tb);
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
                            pixelData_,
                            &bitmapInfo,
                            DIB_RGB_COLORS,
                            SRCCOPY
                        );
            HFONT oldFont = (HFONT)SelectObject(hdc, hFontSans);

            SetTextColor(hdc, RGB(255, 255, 255)); // White text
            SetBkMode(hdc, TRANSPARENT);           // Transparent background
            for (int i = 0; i < (int)textToRender.size(); i++)
            {
                RECT textRect = { (int)(textToRender[i].x),
                                    (int)(textToRender[i].y),
                                    (int)((textToRender[i].x + textToRender[i].w)),
                                    (int)((float)(textToRender[i].y + textToRender[i].h)) };

                DrawTextA(hdc, textToRender[i].text.c_str(), -1, &textRect, DT_LEFT | DT_TOP | DT_WORDBREAK);
            }
            textToRender.clear();

            ReleaseDC(hwnd, hdc);  
           
        }
    }
};
