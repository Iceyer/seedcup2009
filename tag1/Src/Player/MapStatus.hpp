#pragma once

#include "PlayerDLLAPI.hpp"
#include "..\GameCore\Map.hpp"

PLAYER_DLL_API void SetMap(Hexxagon::Map* pMap);

typedef void (*pSetMap) (Hexxagon::Map*);

const std::string strSetMapFunc = "SetMap";

int GetMapWidth();

int GetMapHeight();

int GetMapStatus(const int x, const int y);
