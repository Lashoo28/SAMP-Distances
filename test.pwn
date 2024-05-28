#include <a_samp>
#include <distances>

main(){}

public OnPlayerSpawn(playerid)
{
	new string[64];
	format(string, sizeof(string), "Distance from you to player 1 (%.02f)",GetDistancePlayerFromPlayer(playerid, 1));
	SendClientMessage(playerid, -1, string);
	if(IsPlayerNearToPlayer(playerid, 5.0, 1))
	{
		format(string, sizeof(string), "Player 1 is near you");
	}
	else
	{
		format(string, sizeof(string), "Player 1 isn't near you");
	}
	SendClientMessage(playerid, -1, string);
	format(string, sizeof(string), "Closest player from you (%i)",GetClosestPlayerFromPlayer(playerid));
	SendClientMessage(playerid, -1, string);

	new Float:dist = 0.0;
	dist = GetDistanceVehicleFromVehicle(0, 1);
	if(IsVehicleNearToVehicle(0, 50.0, 1)) {}
	dist = GetVehicleDistanceFromPlayer(playerid, 0);
	new i = GetClosestVehicleFromPlayer(playerid);
	return 1;
}
