#pragma once
#include <string>
#include <vector>
#include "MCGraphics.cpp"
#include "TBWorld.cpp"
#include "TBGlobals.h"
#include "MCSound.h"
#include "TBSprite.cpp"
#include "TBNotifyMgr.h"
#include "TBElementGen.h"
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
	TBElementGen elementGen;
	ParticleSystem particleS;
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
	float sideThrust = 20.0f;
	int losingScore = -400;
	bool gameLost = false;
	AudioPlayer audioPlayer;
	int fanfareSndId = -1;
	int explosionSndId = -1;
	int powerupSndId = -1;
	int thrustSndId = -1;
	int sidefuelrate = 4;
	int fuelrate = 1;
	bool thrustRunning = false;
	string startupScreenText = "Startup Screen Text";
	const bool LOADFROMFILE = false;
	const bool WORLDLOAD2 = true;
	const bool SAVEFILE = false;
	
	TBSprite ts;
	
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

	void LoadGameFromFile(const string& fileName)
	{
		//try to load file
		string contents;
		ifstream file(fileName);
		
		//load file into string
		if (file)
		{
			std::stringstream buffer;
			buffer << file.rdbuf();
			contents = buffer.str();
			file.close();
		}

		//Break contents string into array of lines
		vector<string> lines;
		int index = 0;
		while (index >= 0)
		{
			string line = "";
			index = getNextLine(contents, line, index);
			lines.push_back(line);
		}

		//Now lines contains each line of the script
		world.PreLoad();
		
		//cycle through and parse each line
		string header = "";
		for (int i = 0; i < (int)lines.size(); i++)
		{
			if (lines[i].length())
			{
				if (lines[i][0] == '$')
				{
					continue;
				}
				if (lines[i] == "")
				{
					continue;
				}
				if (lines[i][0] == '#')
				{
					header = lines[i].substr(1);
					continue;
				}
				if (lines[i] == "SPRITE")
				{
					TBSprite* pS = world.AddSprite();
					i = pS->Deserialize(lines, i);
					pS->SetParent(world.GetSprite(pS->GetParentName()));
					pS->SetShowOnCollide(world.GetSprite(pS->GetShowOnCollideName()));
				}
				else if (lines[i] == "PARTICLESYSTEM")
				{
					ParticleSystem* pPS = world.AddParticleSystem();
					i = pPS->Deserialize(lines, i);
					string parentName = pPS->GetParentSpriteName();
					pPS->SetParent(world.GetSprite(parentName));

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
			
			//Save Out Content
			outfile << "\n\n#SPRITES\n";
			for (int i = 0; i < world.GetSpriteCount(); i++)
			{
				if (i == 35)
				{
					int u = 0;
				}
				string str = world.GetSpriteAtIndex(i)->Serialize();
				outfile << str;
			}
			outfile << "\n\n\n#PARTICLE SYSTEMS\n";
			for (int i = 0; i < world.GetParticleSystemCount(); i++)
			{
				string str = world.GetParticleSystemAtIndex(i)->Serialize();
				outfile << str;
			}
			
			//close file
			outfile.close();
		}
	}

	string name;

public:

	deque<CollisionInfo> Collisions; 

	GameManager()
	{
		world.SetCollisionsPtr(&Collisions);
		elementGen.SetElements(world.GetSprites(), world.GetTempSprites(), world.GetParticleSystems(), &world);
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

	void LoadSpriteImages()
	{

	}

	void StartGame()
	{
		

		if (gameLost == true)
		{
 			g_Notify.Notify({ NOTIFYTYPE::OnGmEnd, OBJECTTYPE::GAMEMGR, this->name });
			return;
		}
		ShowCursor(FALSE);
		g_fuel = 1000;

		if (LOADFROMFILE)
		{
			pGfx->SetColorText({ 255, 255, 0 });
			LoadGameFromFile(GetCWD() + "\\TanLander.tbg");
			
		}
		else if (!WORLDLOAD2)
		{
			//If LOADFROMFILE is false then load from world
			world.PreLoad();
			world.Load(pGfx);
			startupScreenText = "TAN LANDER\nwritten by\nTanner Boudreau\n2024";
		}
		else
		{
			//If LOADFROMFILE is false then load from world
			world.PreLoad();
			world.Load2(pGfx);
			startupScreenText = "CRASH LANDER\nwritten by\nTanner Boudreau\n2025";
		}

		if (SAVEFILE)
		{
			MakeGameFile(GetCWD() + "\\TanLander.tbg");
		}

		SetupSound();
		StartTimer();

		//
		// 
		// 
		// 
		// 
		// spawnPoints
		elementGen.ClearSpawnPt();
		elementGen.AddSpawnPt({ 40, 112 , 25, 25});
		elementGen.AddSpawnPt({ 40, 112 , 25, 25 });
		elementGen.AddSpawnPt({g_pixelWidth - 20, 50, 20, 20 });
		//elementGen.AddSpawnPt({ g_pixelWidth - 40, 108, 20, 20 });
		//elementGen.AddSpawnPt({ g_pixelWidth - 40, 108, 20, 20 });
		elementGen.Start();
		
		

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

	void UpdateHUD()
	{
		world.SetSpriteText("livestext", to_string(g_Lives) + " LS");
		world.SetSpriteText("scoretext", to_string(g_CurrentScore) + " SC");
		world.SetSpriteText("fueltext", "FL " + to_string(g_fuel));
	}

	//returns true if start screen is finished
	bool HandleStartScreen()
	{
		if (!startShown)
		{
			if (GetElapsedSeconds() <= 4.0f)
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
			StartGame();
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
			g_fuel -= keyDown ? fuelrate : 0;
		}
		else if (key == 'A') //Left
		{
			world.GetSprite("lander")->SetFlipX(true);
			leftKeyDown = keyDown;
			g_fuel -= keyDown ? sidefuelrate : 0;
		}
		else if (key == 'D') //Right
		{
			world.GetSprite("lander")->SetFlipX(false);
			rightKeyDown = keyDown;
			g_fuel -= keyDown ? sidefuelrate : 0;
		}
		else if (key == 'K') //Shoot
		{
			world.SetShootKeyDown(keyDown);
		}

		g_fuel = max(0, g_fuel);
		
	}


	void Process()
	{
		while (!g_Notify.qGM.empty())
		{
			Notification n = g_Notify.qGM.front();
			g_Notify.qGM.pop_front();



			switch (n.NotifyType)
			{
				case NOTIFYTYPE::OnExplode:
				{
					g_Lives -= 1;
					g_CurrentScore -= 100;
					if (g_CurrentScore > losingScore && g_Lives > 0)
					{
						world.SetSpriteVisible("losetext", true);
						TBSprite* pSprite = world.GetSprite(n.Name);
						world.DisableChildParticles(pSprite);
					}
					else //test for losing game condition
					{
						world.SetSpriteVisible("losegametext", true);
						gameLost = true;
						TBSprite* pSprite = world.GetSprite(n.Name);
						world.DisableChildParticles(pSprite);
					}

					TBSprite* pSprite = world.GetSprite(n.Name);
					world.SetSpritePhysics(pSprite->GetName(), false);
					world.SetParticlesParent("explosion", pSprite->GetName());
					world.SetParticleSystemActive("explosion", true);
					world.SetSpriteVisible(pSprite->GetName(), false);
					audioPlayer.Play(explosionSndId, false);
					break;
				}
				case NOTIFYTYPE::OnWin:
				{
					TBSprite* pSprite = world.GetSprite(n.Name);
					
					//test for safe landing
					if (pSprite->GetVy() > g_LandVyMax)
					{
						g_Notify.Notify({ NOTIFYTYPE::OnExplode, OBJECTTYPE::SPR, pSprite->GetName() });
						return;
					}

					g_LevelOn++;
					g_CurrentScore += 100;
					if (g_CurrentScore % 100 == 0)
					{
						g_Lives++;
					}
					world.SetSpriteVisible("wintext", true);
					world.SetSpriteVisible("wingametext", false);
					world.ClearWinElements();
				}
				break;
				case NOTIFYTYPE::OnFuelPlus:
				{
					TBSprite* ps = world.GetSprite(n.Name);
					g_CurrentScore += ps->GetRewardScore();
					audioPlayer.Play(powerupSndId);
					world.MoveSprite("lava", 0, 5);
					world.MoveSprite("target", 0, 5);
					world.MoveParticleSystem("volcano", 0, 5);
					world.MoveParticleSystem("volcano1", 0, 5);
				}
				break;
				case NOTIFYTYPE::OnGmWin:
				{
					world.SetSpriteVisible("wintext", false);
					world.SetSpriteVisible("wingametext", true);
				}
				break;
			}
		}

		while (Collisions.size() > 0)
		{
			CollisionInfo info = Collisions.front();
			TBSprite* ps = world.GetSprite(info.b);
		
			if (ps != nullptr)
			{
				if (ps->GetCollide() == CollideType::PowerUp)
				{
					ps->SetVisible(false);
					ps->SetCollide(CollideType::None);
					g_fuel += ps->GetFuelScore();
					audioPlayer.Play(powerupSndId);
					world.MoveSprite("lava", 0, -500);
				}
				else if (ps->GetCollide() == CollideType::Reward)
				{
					ps->SetVisible(false);
					ps->SetCollide(CollideType::None);
					g_CurrentScore += ps->GetRewardScore();
					audioPlayer.Play(powerupSndId);
					world.MoveSprite("lava", 0, -500);
				}
			}
			

			Collisions.pop_front();
		}

		elementGen.Process();
		UpdateHUD();		
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

