#pragma once

#ifdef PLAYER_DLL_API_
#define PLAYER_DLL_API __declspec(dllexport)
#else
#define PLAYER_DLL_API __declspec(dllimport)
#endif