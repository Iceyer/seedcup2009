#pragma once

#include "PlayerDLLAPI.hpp"
#include "..\GameCore\Map.hpp"
#include "..\GameCore\Player.hpp"

PLAYER_DLL_API void SetMap(Hexxagon::Map* pMap);

typedef void (*pSetMap) (Hexxagon::Map*);

const std::string strSetMapFunc = "SetMap";

PLAYER_DLL_API void SetPlayer(Hexxagon::Player* pPlayer);

typedef void (*pSetPlayer) (Hexxagon::Player*);

const std::string strSetPlayerFunc = "SetPlayer";

int GetMapWidth();

int GetMapHeight();

int GetMapStatus(const int x, const int y);

