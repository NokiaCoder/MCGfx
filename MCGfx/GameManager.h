#pragma once
#include <string>
#include <vector>
#include "MCGraphics.cpp"
#include "TBWorld.cpp"
#include "TBGlobals.h"
#include "MCSound.h"
#include <thread>
#include <deque>
#include <ostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;


class GameManager
{
private:
	MCGraphics* pGfx = nullptr;
	TBWorld world;
	bool lButtonDown = false;
	bool rButtonDown = false;
	bool lButtonClick = false;
	bool rButtonClick = false;
	int mouseX = 0;
	int mouseY = 0;   
	bool leftKeyDown = false;
	bool rightKeyDown = false;
	bool thrustKeyDown = false;
	bool upKeyDown = false;
	bool restart = false;
	bool startShown = false;
	float mainThrust = -2.0f;
	float sideThrust = 2.0f;
	int losingScore = -400;
	bool gameLost = false;
	AudioPlayer audioPlayer;
	int fanfareSndId = -1;
	int explosionSndId = -1;
	int powerupSndId = -1;
	int thrustSndId = -1;
	bool thrustRunning = false;
	string startupScreenText = "Startup Screen Text";
	
	
	int getNextLine(const std::string & content, std::string & line, int startIndex)
	{
		//Check if we're already past the end of the string
		if (startIndex >= content.size())
		{
			line = ""; // Set line to empty if there's no more content
			return -1; // Return -1 to indicate no more lines
		}

		// Find the end of the current line
		size_t endIdx = content.find('\n', startIndex);

		// If there's no newline, read to the end of the string
		if (endIdx == std::string::npos)
		{
			endIdx = content.size();
		}

		// Extract the line
		line = content.substr(startIndex, endIdx - startIndex);

		// Return the starting index for the next line
		return (int)endIdx + 1; // Move past the newline character
	}
	
	void setFileValue(const string& header, const string& value)
	{
		if (header == "TITLE")
		{
			g_GameTitle = value;
		}
		else if(header == "STARTSCREENTEXT")
		{
			startupScreenText = value;
			//Replace every ^ with \n
			std::replace(startupScreenText.begin(), startupScreenText.end(), '^', '\n');
		}
	}

	void LoadGame(const string& fileName)
	{
		string contents;
		ifstream file(fileName);
		if (file)
		{
			std::stringstream buffer;
			buffer << file.rdbuf();
			contents = buffer.str();
			file.close();
		}


		vector<string> lines;
		int index = 0;
		while (index >= 0)
		{
			string line = "";
			index = getNextLine(contents, line, index);
			lines.push_back(line);
		}

		string header = "";
		for (int i = 0; i < (int)lines.size(); i++)
		{
			if (lines[i].length())
			{
				if (lines[i][0] == '$')
				{
					continue;
				}
				if (lines[i][0] == '#')
				{
					header = lines[i].substr(1);
					continue;
				}
				//we know we have a value
				setFileValue(header, lines[i]);
				header = "";
			}
		}

	}

	void MakeGameFile(const string& fileName)
	{
		ofstream outfile(fileName);

		if (outfile)
		{
			outfile << "$TBG game file" << endl;
			//Write game title
			outfile << "#TITLE" << endl;
			outfile << "TANLANDER" << endl;

			//write startup screen text
			outfile << "#STARTSCREENTEXT" << endl;
			outfile << "TANLANDER^written by^Tanner Boudreau^2024" << endl;
			

			//close file
			outfile.close();
		}
	}

public:

	deque<CollisionInfo> Collisions; 

	GameManager()
	{
		world.SetCollisionsPtr(&Collisions);
	}

	void SetupSound()
	{
		if (!audioPlayer.IsActive())
		{
			audioPlayer.Initialize(pGfx->GetHWND());
		}

		string path;
		path = GetContentFolder() + "\\fanfare.wav";
		fanfareSndId = audioPlayer.Preload(path);

		path = GetContentFolder() + "\\explosion.wav";
		explosionSndId = audioPlayer.Preload(path);

		path = GetContentFolder() + "\\powerup.wav";
		powerupSndId = audioPlayer.Preload(path);

		path = GetContentFolder() + "\\thrust.wav";
		thrustSndId = audioPlayer.Preload(path);
	}

	void Restart()
	{
		//MakeGameFile(GetCWD() + "\\TanLander.tbg"); 
		LoadGame(GetCWD() + "\\TanLander.tbg");
		if (gameLost == true)
		{
			return;
		}
		ShowCursor(FALSE);
		g_fuel = 1000;
		world.Load();
		SetupSound();
		StartTimer();
		if (!startShown)
		{
			audioPlayer.Play(fanfareSndId, false);
		}
	}

	void ShowStartScreen()
	{
		TBSprite start;
		start.Create(0, g_pixelHeight / 3 ,g_pixelWidth, g_pixelHeight, { 255, 255, 255 });
		start.SetName("startText");
		start.SetSpriteText(startupScreenText);
		start.SetTextAlign(TEXT_ALIGN::CENTER);
		start.SetIsTextSprite(true);
		start.SetVisible(true);
		start.SetLayer(LAYER::layer_FRONT);
		start.SetHasAnimation(false);
		start.setPhysics(false);
		start.Process(0.0f);
		start.Draw(pGfx);

	}

	//returns true if start screen is finished
	bool HandleStartScreen()
	{
		if (!startShown)
		{
			if (GetElapsedSeconds() <= 3.0f)
			{
				ShowStartScreen();
				return false;
			}
		}
		return true;
	}

	void SetPointer(MCGraphics* ptr)
	{
		pGfx = ptr;
	}
	//Handles mouse click. Left and Right click
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

	void HandleKey(int key, bool keyDown)
	{
		//Restart requested
		if (key == VK_SPACE && !keyDown) //restart
		{
			Restart();
			return;
		}
		
		//out of fuel
		if (g_fuel <= 0)
		{
			world.SetSpriteVisible("thrust", false);
			world.SetSpriteVisible("thrust2", false);
			world.SetSpriteVisible("thrust3", false);
			return;
		}
		//handle key
		if (key == 'W') //Thrust
		{
			thrustKeyDown = keyDown;
			g_fuel -= keyDown ? 1 : 0;
		}
		else if (key == 'A') //Left
		{
			leftKeyDown = keyDown;
			g_fuel -= keyDown ? 1 : 0;
		}
		else if (key == 'D') //Right
		{
			rightKeyDown = keyDown;
			g_fuel -= keyDown ? 1 : 0;
		}

		g_fuel = max(0, g_fuel);
	}

	void Process()
	{
		while (Collisions.size() > 0)
		{
			CollisionInfo info = Collisions.front();
			TBSprite* ps = world.GetSprite(info.b);
		
			if (ps != nullptr)
			{
				//Player wins!
				if (ps->GetCollide() == CollideType::Win)
				{
					g_LevelOn++;
					g_CurrentScore += 100;
					world.SetSpriteVisible("wintext", true);
				}
				//Player loses :(
				else if (ps->GetCollide() == CollideType::Lose)
				{
					g_CurrentScore -= 100;
					if (g_CurrentScore > losingScore)
					{
						world.SetSpriteVisible("losetext", true);
					}
					world.SetParticlesParent("explosion", "lander");
					world.SetParticleSystemActive("explosion", true);
					world.SetSpriteVisible("lander", false);
					audioPlayer.Play(explosionSndId, false);
				}
				else if (ps->GetCollide() == CollideType::PowerUp)
				{
					ps->SetVisible(false);
					ps->SetCollide(CollideType::None);
					g_fuel += powerUpFuel;
					audioPlayer.Play(powerupSndId);
				}

				TBSprite* pScore = world.GetSprite("scoretext");
				if (pScore != nullptr)
				{
					//SCORE\n<score>
					world.SetSpriteText("scoretext", "SCORE\n" + to_string(g_CurrentScore));
				}
			}

			Collisions.pop_front();
		}
		
		//test for losing game condition
		if (g_CurrentScore <= losingScore)
		{
			world.SetSpriteVisible("losegametext", true);
			gameLost = true;
		}
	}

	void Render(HWND hwnd)
	{
		if (HandleStartScreen() == false)
		{
			pGfx->Present(hwnd);
			return;
		}
		startShown = true;
		//Get Master Timeslice
		double  elapsedTimeSec = GetElapsedFrameSeconds();

		//Test for collision
		world.TestCollision();
		float thrust = 0;
		float thrustLeft = 0;
		float thrustRight = 0;

		// sets amount of thrust for fire
		if (g_fuel <= 0)
		{
			world.SetSpriteVisible("thrust", false);
			world.SetSpriteVisible("thrust2", false);
			world.SetSpriteVisible("thrust3", false);
		}
		else
		{
			world.SetParticleSystemActive("thrust", thrustKeyDown);
			thrust = (mainThrust * (float)elapsedTimeSec);
			if (!thrustKeyDown)
			{
				thrust = 0;
			}
			world.SetParticleSystemActive("thrust2", rightKeyDown);
			thrustLeft = (-sideThrust * (float)elapsedTimeSec);
			if (!rightKeyDown)
			{
				thrustLeft = 0;
			}
			world.SetParticleSystemActive("thrust3", leftKeyDown);
			thrustRight = (sideThrust * (float)elapsedTimeSec);
			if (!leftKeyDown)
			{
				thrustRight = 0;
			}
		}

		// lander forces 
		world.SetSpriteForce("lander", thrust, false);
		world.SetSpriteForce("lander", thrustRight, true);
		world.SetSpriteForce("lander", thrustLeft, true);

		if (thrustKeyDown || rightKeyDown || leftKeyDown)
		{
			if (!thrustRunning)
			{
				thrustRunning = true;
				audioPlayer.Play(thrustSndId, true);
			}
		}
		else if (thrustRunning)
		{
			thrustRunning = false;
			audioPlayer.Stop(thrustSndId);
		}

		//process and draw world
		world.Process(elapsedTimeSec);
		world.Draw(pGfx);
		pGfx->Present(hwnd);
	}


};

