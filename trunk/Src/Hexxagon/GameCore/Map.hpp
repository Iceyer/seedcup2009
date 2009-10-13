#pragma once

#include <vector>

namespace Hexxagon
{
    const unsigned int MaxMapLength = 100;
    class MapItem
    {
    public:
        enum ItemType
        {
            EMPTY,
            PLayer,
            INVALID,
        };
        int      m_Type;
        unsigned int X;
        unsigned int Y;
    private:
        void * m_pOwener;
    };

    class MapMgr
    {
        typedef std::vector<MapItem>    MapItemList;
    public:
        MapMgr();

        ~MapMgr();

        bool LoadMap(std::string strMapFileName);

        bool SaveMap(std::string strMapFileName);

        const MapItem& GetMapStatus(const int x, const int y) const;

        int MapWidth();

        int MapHeigth();
    private:
        MapItem MapStatus[MaxMapLength][MaxMapLength];
        int     m_iMapWidth;
        int     m_iMapHeight;
    };
}