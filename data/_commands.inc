CMD:chainsaw(playerid)
{
	GivePlayerWeapon(playerid, 9, 1);
	return 1;
}
CMD:collectlogs(playerid)
{
	new TID = GetTreeID(playerid);
	new Float:A = GetAngleToXY(playerid, TreeInfo[TID][TPosX], TreeInfo[TID][TPosY]);
	
	if(GetPlayerWeapon(playerid) != 9) return SendClientMessage(playerid, -1, "You must have chainsaw to cut the tree");
	if(!IsNearTree(playerid)) return SendClientMessage(playerid, -1, "You must be near the tree");

	SetPlayerFacingAngle(playerid, A);

	PlayerTotalLogs[playerid] += TreeInfo[TID][TLogs];
	TreeInfo[TID][TLogs] = 0;

	ApplyAnimation(playerid, "chainsaw", "WEAPON_csaw", 4.0, 0, 0, 0, 0, 0);

	DestroyTreeObject(TID);

	return 1;
}

CMD:placelogs(playerid)
{
	new cfID = GetCFID();
	new Float:A = GetAngleToXY(playerid, CampFireInfo[cfID][CFPosX], CampFireInfo[cfID][CFPosY]);


	if( PlayerTotalLogs[playerid] < 8 ) return SendClientMessage(playerid, -1, "You do not have enough logs.");

	PlayerTotalLogs[playerid] -= 8;

	SetPlayerFacingAngle(playerid, A);

	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);

	CreateCampFireLog(playerid, cfID);

	return 1;
}

CMD:lightfire(playerid)
{
	new cfID = GetCampFire(playerid);
	new Float:A = GetAngleToXY(playerid, CampFireInfo[cfID][CFPosX], CampFireInfo[cfID][CFPosY]);

	if(CampFireInfo[cfID][CFFired] == 1)
		return SendClientMessage(playerid, -1, "The Fire already burning the logs");

	SetPlayerFacingAngle(playerid, A);
	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);
	
	AddFires(cfID);

	SendClientMessage(playerid, -1, "You have lighten up the Camp logs");
	return 1;
}

CMD:addlogs(playerid)
{
	new cfID = GetCampFire(playerid);
	new Float:A = GetAngleToXY(playerid, CampFireInfo[cfID][CFPosX], CampFireInfo[cfID][CFPosY]);

	if(CampFireInfo[cfID][CFFired] == 0)
		return SendClientMessage(playerid, -1, "You cannot add more logs");
	if(CampFireInfo[cfID][CFHealth] > 80)
		return SendClientMessage(playerid, -1, "You cannot add more logs");

	SetPlayerFacingAngle(playerid, A);
	ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);

	CampFireInfo[cfID][CFHealth] += 10;
	PlayerTotalLogs[playerid] -= 4;

	SendClientMessage(playerid, -1, "You have added more logs");
	return 1;
}


CMD:cleancamp(playerid)
{
	new cfID = GetCampFire(playerid);
	new Float:A = GetAngleToXY(playerid, CampFireInfo[cfID][CFPosX], CampFireInfo[cfID][CFPosY]);

	if(CampFireInfo[cfID][CFCreated] == 1)
	{
		SetPlayerFacingAngle(playerid, A);

		ApplyAnimation(playerid, "BOMBER", "BOM_Plant", 4.0, 0, 0, 0, 0, 0);
		DestroyCampFire(cfID);
	}
	SendClientMessage(playerid, -1, "You have cleared the Camp Fire");
	return 1;
}

CMD:inv(playerid)
{
	new string[128];
	format(string, sizeof string, "You have total %d logs", PlayerTotalLogs[playerid]);
	SendClientMessage(playerid, -1, string);
	return 1;
}