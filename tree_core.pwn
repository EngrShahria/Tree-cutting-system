#include <a_samp>
#include <streamer>
#include <ZCMD>

//knife > knife_part
//chainsaw ? WEAPON_csaw
#define MAX_FIRE 50
new CampFireObject[MAX_FIRE][8];

new treestr[128],
	campstr[128];

new PlayerTotalLogs[MAX_PLAYERS];


#define MAX_TREE 26
#define MAX_LOG 30

new Tree_Object[MAX_TREE],
	TotalTrees;

enum  _CampFireInfo
{
	
	CFCreated,
	CFFired, 
	CFHealth, 
	Float:CFPosX,
	Float:CFPosY,
	Float:CFPosZ,
	Float:CFPosA,
	Text3D:CFText,
	CFTimer
}

new CampFireInfo[sizeof(Tree_Object)][_CampFireInfo];

enum _TreeInfo
{
	TCreated, 
	Float:TPosX,
	Float:TPosY,
	Float:TPosZ,
	Text3D:TreeText,
	TLogs,
	TreeTimer
}
new TreeInfo[MAX_TREE][_TreeInfo];


forward TreeLogTimer(tID);
forward CampFireTimer(cfID);

new sTreeTimer;
forward ServerTreeCheck();
public ServerTreeCheck()
{
	if(TotalTrees == 0)
	{
		_LoadTreeObjects();
	}
	return 1;
}


public OnGameModeInit()
{
	_LoadTreeObjects();
	sTreeTimer = SetTimer("ServerTreeCheck", 10*60*1000 , 1);

	return 1;
}
public OnGameModeExit()
{
	_DestroyTreeObjects();
	KillTimer(sTreeTimer);
	return 1;
}
public OnPlayerConnect(playerid)
{	

	return 1;
}
public OnPlayerDisconnect(playerid, reason)
{

	return 1;
}


stock Float:GetAngleToXY(playerid, Float:X, Float:Y)
{	
	new  Float:Angle;
	new Float:CurrentX, Float:CurrentY, Float:CurrentZ;
	GetPlayerPos(playerid, CurrentX, CurrentY, CurrentZ);

 	Angle = atan2(Y-CurrentY, X-CurrentX);
  	Angle = floatsub(Angle, 90.0);
  	if(Angle < 0.0) Angle = floatadd(Angle, 360.0);
  	return Angle;
}

stock GetPlayerFrontPos(playerid, &Float:x, &Float:y, &Float:z, &Float:a, Float:dist)
{
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);

	x += (dist * floatsin(-a, degrees));
	y += (dist * floatcos(-a, degrees));
}



#include "data/_tree.inc"
#include "data/_campfire.inc"

#include "data/_commands.inc"
//#include "data/_admins.inc"

CMD:tp(playerid)
{
	return SetPlayerPos(playerid,759.9762, -309.5425, 11.3687);
}