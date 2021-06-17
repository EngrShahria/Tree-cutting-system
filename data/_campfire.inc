
//==============================================================================
stock GetCFID()
{
	new FreeID;
	for(new i; i < MAX_FIRE; i++)
	{
		if(CampFireInfo[i][CFCreated] == 0) 
		{ 
			FreeID = i;
			break;
		}
	}
	return FreeID;
}

stock GetCampFire(playerid)
{
	new _cfID;
	for(new i; i < MAX_TREE; i++) 
		if( CampFireInfo[i][CFCreated] == 1)
		{
			if(IsPlayerInRangeOfPoint(playerid, 5.0, CampFireInfo[i][CFPosX], CampFireInfo[i][CFPosY], CampFireInfo[i][CFPosZ]) )
			{ 
				_cfID = i;
				break;
			}
		}	 
	return _cfID;
}


stock CreateCampFireLog(playerid, cID) 
{
	new Float:pX, Float:pY, Float:pZ, Float:pA;
	GetPlayerFrontPos(playerid, pX, pY, pZ, pA, 1);

	CampFireInfo[cID][CFPosX] = pX;
	CampFireInfo[cID][CFPosY] = pY;
	CampFireInfo[cID][CFPosZ] = pZ;
	CampFireInfo[cID][CFPosA] = pA;

	CampFireObject[cID][0] = CreateObject(841, pX, pY, pZ-1, 0.000, 0.000, pA);
	CampFireObject[cID][1] = CreateObject(841, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000);
	CampFireObject[cID][2] = CreateObject(841, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000);

    AttachObjectToObject(CampFireObject[cID][1], CampFireObject[cID][0], 0, -0.5, 0, 0, 0, 0, 1);
    AttachObjectToObject(CampFireObject[cID][2], CampFireObject[cID][0], 0, -0.5, 0, 0, 0, 90, 1);
    CampFireInfo[cID][CFCreated] = 1;
    CampFireInfo[cID][CFFired] = 0;
    format(campstr, sizeof campstr, "Camp Fire (%d)\n /lightfire", cID);
    CampFireInfo[cID][CFText] = CreateDynamic3DTextLabel(campstr, 0xFFFFFF, pX, pY, pZ -1.5, 3);

}

stock AddFires(cID)
{
	CampFireObject[cID][3] = CreateObject(18688, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000);
	CampFireObject[cID][4] = CreateObject(18688, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000);
	CampFireObject[cID][5] = CreateObject(18688, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000);
	AttachObjectToObject(CampFireObject[cID][3], CampFireObject[cID][0], 0.5, -0.5, -2, 0, 0, 0, 1);
    AttachObjectToObject(CampFireObject[cID][4], CampFireObject[cID][0], -0.5, -0.5, -2, 0, 0, 0, 1);
    AttachObjectToObject(CampFireObject[cID][5], CampFireObject[cID][0], 0, -0.5, -2, 0, 0, 0, 1);
    CampFireInfo[cID][CFFired] = 1;
    CampFireInfo[cID][CFHealth] = 100;

    format(campstr, sizeof campstr, "Camp Fire (%d)\n Camp Fire Health: %d", cID, CampFireInfo[cID][CFHealth]);
    UpdateDynamic3DTextLabelText(CampFireInfo[cID][CFText], -1, campstr);

    CampFireInfo[cID][CFTimer] =  SetTimerEx("CampFireTimer", 5000, 1, "i", cID);

}


stock DestroyCampFire(cID)
{
 	if(CampFireInfo[cID][CFFired] == 1)
 	{
		DestroyObject(CampFireObject[cID][0]);
		DestroyObject(CampFireObject[cID][1]);
		DestroyObject(CampFireObject[cID][2]);
		DestroyObject(CampFireObject[cID][3]);
		DestroyObject(CampFireObject[cID][4]);
		DestroyObject(CampFireObject[cID][5]);
	}
	else 
	{
		DestroyObject(CampFireObject[cID][0]);
		DestroyObject(CampFireObject[cID][1]);
		DestroyObject(CampFireObject[cID][2]);
	}
	CampFireInfo[cID][CFCreated] = 0;
	CampFireInfo[cID][CFHealth] = 0;
	KillTimer(CampFireInfo[cID][CFTimer]);
	DestroyDynamic3DTextLabel(CampFireInfo[cID][CFText]);

}

public CampFireTimer(cfID)
{	

	if(CampFireInfo[cfID][CFCreated] == 1)
	{
		CampFireInfo[cfID][CFHealth] -= random(5);
		if(CampFireInfo[cfID][CFHealth] < 1)
		{
			DestroyCampFire(cfID);
		}
		format(campstr, sizeof campstr, "Camp Fire (%d)\n Camp Fire Health: %d", cfID, CampFireInfo[cfID][CFHealth]);
    	UpdateDynamic3DTextLabelText(CampFireInfo[cfID][CFText], -1, campstr);
	}
	return 1;
}
