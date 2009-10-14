#pragma once

#include "PlayerDLLAPI.hpp"
#include "..\GameCore\Map.hpp"

PLAYER_DLL_API void SetMapMgr(Hexxagon::MapMgr* pMapMgr);

PLAYER_DLL_API int GetMapWidth();

PLAYER_DLL_API int GetMapHeight();

PLAYER_DLL_API int GetMapStatus(const int x, const int y);
