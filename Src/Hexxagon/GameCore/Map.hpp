#pragma once

#include <vector>

namespace Hexxagon
{
    const unsigned int MaxMapLength = 100;
    class MapItem
    {
        enum ItemType
        {
            EMPTY,
            PLayer,
            INVALID,
        };
        ItemType m_Type;
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

        const MapItem& GetMapStatus(int x, int y) const;

        const int MapWidth();

        const int MapHeigth();
    private:
        MapItem MapStatus[MaxMapLength][MaxMapLength];
    };
}