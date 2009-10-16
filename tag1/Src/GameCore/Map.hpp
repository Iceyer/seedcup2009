#pragma once

#include "..\Player\PlayerAction.hpp"
#include <vector>

namespace Hexxagon
{
    const unsigned int MaxMapLength = 15;
    class MapItem
    {
    public:
        enum ItemType
        {
            INVALID = 0,
            EMPTY   = 1,
            PLayer1 = 2,
            PLayer2 = 3,
        };
        ItemType     m_Type;
        //unsigned int X;
        //unsigned int Y;
    //private:
       // void * m_pOwener;
    };

    class Map
    {
    public:
        Map();

        ~Map();

        bool LoadMap(std::string strMapFileName);

        bool SaveMap(std::string strMapFileName);

        bool UpdateMap(const Action& action, int FailorInorOut);

        const MapItem& GetMapStatus(const int x, const int y) const;

        int MapWidth();

        int MapHeigth();

    private:
        MapItem *m_pData;
        int     m_iMapWidth;
        int     m_iMapHeight;
    };

    class MapMgr
    {
    public:
        MapMgr();

        ~MapMgr();

        Map* CurMap();

        void SetCurMap(Map* map);

        Map* AddMap(std::string strMapFileName);
    private:
        typedef std::vector<Map*>       MapList;
        Map*          m_pCurMap;
        MapList       m_MapList;
    };

}