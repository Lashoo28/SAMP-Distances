// SA:MP Distance Functions (C) 2024 | Lashoo28
/*
    // Global
    GetDistancePoinFromPoint

    // Player
    GetDistancePlayerFromPlayer
    IsPlayerNearToPlayer
    GetClosestPlayerFromPlayer

    // Vehicles
    GetDistanceVehicleFromVehicle
    IsVehicleNearToVehicle

    // Player/Vehicle
    GetVehicleDistanceFromPlayer
    GetClosestVehicleFromPlayer
    IsPlayerNearToVehicle
*/

#if defined jdf_included
	#endinput
#endif
 
#define jdf_included

#tryinclude <a_samp>

#if !defined IsValidVehicle
    native IsValidVehicle(vehicleid);
#endif

stock GetDistancePoinFromPoint(Float:x,Float:y,Float:z,Float:x2,Float:y2,Float:z2)
{
    new Float:dist = floatsqroot(floatpower(floatabs(floatsub(x2,x)),2)+floatpower(floatabs(floatsub(y2,y)),2)+floatpower(floatabs(floatsub(z2,z)),2));
	return floatround(dist);
} 

// Player
stock GetDistancePlayerFromPlayer(player1, player2)
{
    if(!(0 <= player1 < MAX_PLAYERS) || !(0 <= player2 < MAX_PLAYERS)) {
        return false;
    }
    if(!IsPlayerConnected(player1) || !IsPlayerConnected(player2)) {
        return false;
    }
    new Float:px1, Float:py1, Float:pz1,
        Float:px2, Float:py2, Float:pz2;
    GetPlayerPos(player1, px1, py1, pz1);
    GetPlayerPos(player2, px2, py2, pz2);
    return GetDistancePoinFromPoint(px1, py1, pz1, px2, py2, pz2);
}
stock IsPlayerNearToPlayer(playerid, Float:range, targetid)
{
    if(!(0 <= playerid < MAX_PLAYERS) || !(0 <= targetid < MAX_PLAYERS)) {
        return false;
    }
    if(!IsPlayerConnected(playerid) || !IsPlayerConnected(targetid)) {
        return false;
    }
    if(range <= 0.0) {
        return false;
    }
    return (GetDistancePlayerFromPlayer(playerid, targetid) <= range);
}
stock GetClosestPlayerFromPlayer(playerid)
{
    if(!IsPlayerConnected(playerid) || !(0 <= playerid < MAX_PLAYERS)) {
        return false;
    }
    new gplayerid = INVALID_PLAYER_ID,
        Float:_lastDist = 0.0, Float:_getDist = 0.0;
    for(new i = 0, j = GetPlayerPoolSize(); i <= j; i ++)
    {
        if(!IsPlayerConnected(i)) continue;
        _getDist = GetDistancePlayerFromPlayer(playerid, i);
        if(_lastDist > _getDist)
        {
            _lastDist = _getDist;
            gplayerid = i;
        }
    }
    return gplayerid;
}

// Vehicles
stock GetDistanceVehicleFromVehicle(vehicle1, vehicle2)
{
    if(!(0 <= vehicle1 < MAX_VEHICLES) || !(0 <= vehicle2 < MAX_VEHICLES)) {
        return false;
    }
    if(!IsValidVehicle(vehicle1) || !IsValidVehicle(vehicle2)) {
        return false;
    }
    new Float:vx1, Float:vy1, Float:vz1,
        Float:vx2, Float:vy2, Float:vz2;
    GetVehiclePos(vehicle1, vx1, vy1, vz1);
    GetVehiclePos(vehicle2, vx2, vy2, vz2);
    return GetDistancePoinFromPoint(vx1, vy1, vz1, vx2, vy2, vz2);
}
stock IsVehicleNearToVehicle(vehicleid, Float:range, targetvehicle)
{
    if(!(0 <= vehicleid < MAX_VEHICLES) || !(0 <= targetvehicle < MAX_VEHICLES)) {
        return false;
    }
    if(!IsValidVehicle(vehicleid) || !IsValidVehicle(targetvehicle)) {
        return false;
    }
    if(range <= 0.0) {
        return false;
    }
    return (GetDistanceVehicleFromVehicle(vehicleid, targetvehicle) <= range);
}

// Player/Vehicles
stock GetVehicleDistanceFromPlayer(vehicleid, playerid)
{
    if((!(0 <= playerid < MAX_PLAYERS) || !(0 <= vehicleid < MAX_VEHICLES))) {
        return false;
    }
    if((!IsPlayerConnected(playerid)) || (IsValidVehicle(vehicleid))) {
        return false;
    }
    new Float:px, Float:py, Float:pz,
        Float:vx, Float:vy, Float:vz;
    GetPlayerPos(playerid, px, py, pz);
    GetVehiclePos(vehicleid, vx, vy, vz);
    return GetDistancePoinFromPoint(px, py, pz, vx, vy, vz);
}
stock GetClosestVehicleFromPlayer(playerid)
{
    if(!IsPlayerConnected(playerid) || !(0 <= playerid < MAX_PLAYERS)) {
        return false;
    }
    new gvehicleid = INVALID_VEHICLE_ID,
        Float:_lastDist = 0.0, Float:_getDist = 0.0;
    for(new i = 0, j = GetVehiclePoolSize(); i <= j; i ++)
    {
        if(!IsValidVehicle(i)) continue;
        _getDist = GetVehicleDistanceFromPlayer(i, playerid);
        if(_lastDist > _getDist)
        {
            _lastDist = _getDist;
            gvehicleid = i;
        }
    }
    return gvehicleid;
}
stock IsPlayerNearToVehicle(playerid, Float:range, vehicleid)
{
    if(!(0 <= playerid < MAX_PLAYERS) || !(0 <= targetid < MAX_PLAYERS)) {
        return false;
    }
    if(!IsPlayerConnected(playerid) || !IsPlayerConnected(targetid)) {
        return false;
    }
    if(!IsValidVehicle(vehicleid)) {
        return false;
    }
    if(range <= 0.0) {
        return false;
    }
    return (GetVehicleDistanceFromPlayer(vehicle, playerid) <= range);
}