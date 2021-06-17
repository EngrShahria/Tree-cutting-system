_LoadTreeObjects()
{

	Tree_Object[0] = CreateDynamicObject(769, 749.0507, -309.8623, 8.2555, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[1] = CreateDynamicObject(769, 754.5626, -320.1347, 8.8076, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[2] = CreateDynamicObject(769, 751.5040, -313.4539, 8.4760, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[3] = CreateDynamicObject(769, 753.7249, -299.7298, 8.5131, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[4] = CreateDynamicObject(769, 764.5994, -292.4833, 8.6544, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[5] = CreateDynamicObject(769, 517.6510, -657.9473, 18.3113, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[6] = CreateDynamicObject(769, 520.8775, -663.3848, 17.5134, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[7] = CreateDynamicObject(769, 526.5047, -652.1000, 17.4292, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[8] = CreateDynamicObject(769, 0.3487, -168.5241, -1.9909, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[9] = CreateDynamicObject(769, 2.9475, -174.9255, -1.4499, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[10] = CreateDynamicObject(769, -8.0193, -138.9526, -1.0119, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[11] = CreateDynamicObject(769, -826.1135, 125.0716, 8.1408, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[12] = CreateDynamicObject(769, -819.7636, 120.6839, 8.3701, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[13] = CreateDynamicObject(769, -820.6732, 126.2552, 7.6831, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[14] = CreateDynamicObject(769, 357.1928, -224.7408, 4.7428, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[15] = CreateDynamicObject(769, 358.9705, -232.0836, 4.7016, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[16] = CreateDynamicObject(769, 842.0261, -13.3898, 62.4825, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[17] = CreateDynamicObject(769, 1114.4134, 470.5184, 26.7210, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[18] = CreateDynamicObject(769, 1112.5270, 473.2625, 26.2458, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[19] = CreateDynamicObject(769, 1337.5961, 97.8343, 21.1602, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[20] = CreateDynamicObject(769, 1346.1047, 99.0287, 21.9588, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[21] = CreateDynamicObject(769, 1330.1448, 99.4325, 20.5465, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[22] = CreateDynamicObject(769, 1336.2589, 107.7016, 20.9921, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[23] = CreateDynamicObject(769, 1925.9532, 87.1464, 28.8044, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[24] = CreateDynamicObject(769, 1919.0743, 86.1691, 28.3676, 0.0000, 0.0000, 0.0000); //Locust_hi
	Tree_Object[25] = CreateDynamicObject(769, 1920.8483, 96.3210, 29.4844, 0.0000, 0.0000, 0.0000); //Locust_hi

	for(new i; i < sizeof(Tree_Object); i++)
	{
		if(IsValidDynamicObject(Tree_Object[i]))
		{
			TreeInfo[i][TCreated] = 1;
			GetDynamicObjectPos(Tree_Object[i], TreeInfo[i][TPosX], TreeInfo[i][TPosY], TreeInfo[i][TPosZ]);
			TreeInfo[i][TLogs] = 0;
			format(treestr, sizeof treestr, "The tree has total %d logs.", TreeInfo[i][TLogs]);
			TreeInfo[i][TreeText] = CreateDynamic3DTextLabel(treestr, -1, TreeInfo[i][TPosX], TreeInfo[i][TPosY], TreeInfo[i][TPosZ]+2, 5, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, 0, 0);
			TotalTrees++;
			TreeInfo[i][TreeTimer] = SetTimerEx("TreeLogTimer", 5000, 1, "i", i);
		}
	}
	return 1;
}
_DestroyTreeObjects()
{
	for(new i; i < sizeof(Tree_Object); i++)
	{
		if(IsValidDynamicObject(Tree_Object[i]))
		{
			DestroyDynamicObject(Tree_Object[i]);
			DestroyDynamic3DTextLabel(TreeInfo[i][TreeText]);
			TreeInfo[i][TCreated] = 0;
			TotalTrees = 0;
			KillTimer(TreeInfo[i][TreeTimer] );
		}
	}
}


stock DestroyTreeObject(id)
{
	if(IsValidDynamicObject(Tree_Object[id]))
	{
		DestroyDynamicObject(Tree_Object[id]);
		DestroyDynamic3DTextLabel(TreeInfo[id][TreeText]);
		TreeInfo[id][TCreated] = 0;
		TotalTrees--;
		KillTimer(TreeInfo[id][TreeTimer] );

	}

	return 1;
}


stock IsNearTree(playerid)
{
	for(new i; i < MAX_TREE; i++) 
		if( TreeInfo[i][TCreated] == 1)
		{
			if(IsPlayerInRangeOfPoint(playerid, 5.0, TreeInfo[i][TPosX], TreeInfo[i][TPosY], TreeInfo[i][TPosZ]) )
				return 1;
		}	 
	return 0;
}

stock GetTreeID(playerid)
{
	new _tID;
	for(new i; i < MAX_TREE; i++) 
		if( TreeInfo[i][TCreated] == 1)
		{
			if(IsPlayerInRangeOfPoint(playerid, 5.0, TreeInfo[i][TPosX], TreeInfo[i][TPosY], TreeInfo[i][TPosZ]) )
			{ 
				_tID = i;
				break;
			}
		}	 
	return _tID;
}


public TreeLogTimer(tID)
{
	new ranlog = random(3);
	if(TreeInfo[tID][TCreated] == 1)
	{
		TreeInfo[tID][TLogs] += ranlog;
		if(TreeInfo[tID][TLogs] >= MAX_LOG)
		{
			TreeInfo[tID][TLogs] = MAX_LOG;
		}
		format(treestr, sizeof treestr, "The tree has total %d logs.", TreeInfo[tID][TLogs]);
		UpdateDynamic3DTextLabelText(TreeInfo[tID][TreeText], -1, treestr);
	}
	return 1;
}


