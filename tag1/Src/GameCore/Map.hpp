#pragma once

#include "..\Player\PlayerAction.hpp"
#include <vector>
//#include <list>

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

        int MapWidth() const;

        int MapHeigth() const;

    private:
        MapItem *m_pData;
        int     m_iMapWidth;
        int     m_iMapHeight;
    };

    class MapMgr
    {
    public:
        typedef std::vector<Map*>           MapList;
        typedef MapList::iterator           MapItor;
        typedef MapList::const_iterator     MapConstItor;

        MapMgr();

        ~MapMgr();

        MapItor Begin();

        MapItor End();

        Map* AddMap(std::string strMapFileName);
    private:
        MapList       m_MapList;
    };

}