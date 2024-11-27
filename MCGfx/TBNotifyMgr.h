#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum NOTIFYTYPE
{
	OnCollide = 0,
	OnExplode,
	OnUpdate,
	OnVisibilityChange,
	OnLanded,
	OnMiss,
	OnLose,
	OnWin,
	OnRestart,
	OnStart,
	OnEnd,
	OnGmNewgame,
	OnGmEnd,
	OnGmLoad,
	OnGmStart,
	OnGmWin,
	OnGmLose,
	OnLivesplus,
	onLivesNeg,
	OnFuelLow,
	OnFuelPlus,
	OnFuelNeg,
	OnPointsplus,

};

enum OBJECTTYPE
{
	GAMEMGR = 0,
	WORLD,
	SPR,
	PS,
};

struct Notification
{
public:
	NOTIFYTYPE NotifyType;
	OBJECTTYPE ObjectType;
	string Name;

	Notification() = default;
	Notification(NOTIFYTYPE notifyType, OBJECTTYPE objectType, string name)
	{
		NotifyType = notifyType;
		ObjectType = objectType;
		Name = name;
	}
};



class TBNotifyMgr
{
public:
	TBNotifyMgr() = default;

	void Notify(const Notification& message)
	{
		
	}
};




