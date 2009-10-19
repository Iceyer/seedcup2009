#include "PlayerAction.hpp"
#include "MapStatus.hpp"

const   std::string strTeamName = "简单电脑";

PLAYER_DLL_API std::string GetPlayerName()
{
    return strTeamName;
}

// 取得某一位置的状态为：
//          0   表示不可填充状态（invalid)
//          1   表示为可填充状态（empty)
//          2   表示被player1占领状态（player1)
//          3   表示被player2占领状态（player2)
PLAYER_DLL_API Action GetPlayerAction(int playerNum)
{
    Action actionTest;
    int mapWidth = GetMapWidth();
    int mapHeight = GetMapHeight();
    int state;

    actionTest.DesPosX = 0;
    actionTest.DesPosY = 0;
    actionTest.PiecePosX = 0;
    actionTest.PiecePosY = 0;
    for (int i = 0; i != mapWidth; i++)
    {
        for (int j = 0; j != mapHeight; j++)
        {
            state = GetMapStatus(i,j);
            if (state == playerNum)
            {
                //inline
                if (i+1<mapWidth && GetMapStatus(i+1, j) == 1)
                {
                    actionTest.PiecePosX = i;
                    actionTest.PiecePosY = j;
                    actionTest.DesPosX = i+1;
                    actionTest.DesPosY = j;
                    goto TheEnd;
                }
                if (i+1<mapWidth && j+1<mapHeight && GetMapStatus(i+1, j+1) == 1)
                {
                    actionTest.PiecePosX = i;
                    actionTest.PiecePosY = j;
                    actionTest.DesPosX = i+1;
                    actionTest.DesPosY = j+1;
                    goto TheEnd;
                }
                if (j+1<mapHeight && GetMapStatus(i, j+1) == 1)
                {
                    actionTest.PiecePosX = i;
                    actionTest.PiecePosY = j;
                    actionTest.DesPosX = i;
                    actionTest.DesPosY = j+1;
                    goto TheEnd;
                }
                if (i-1>=0 && GetMapStatus(i-1, j) == 1)
                {
                    actionTest.PiecePosX = i;
                    actionTest.PiecePosY = j;
                    actionTest.DesPosX = i-1;
                    actionTest.DesPosY = j;
                    goto TheEnd;
                }
                if (i-1>=0 && j-1>=0 && GetMapStatus(i-1, j-1) == 1)
                {
                    actionTest.PiecePosX = i;
                    actionTest.PiecePosY = j;
                    actionTest.DesPosX = i-1;
                    actionTest.DesPosY = j-1;
                    goto TheEnd;
                }
                if (j-1>=0 && GetMapStatus(i, j-1) == 1)
                {
                    actionTest.PiecePosX = i;
                    actionTest.PiecePosY = j;
                    actionTest.DesPosX = i;
                    actionTest.DesPosY = j-1;
                    goto TheEnd;
                }
                //outline
                if (i+2<mapWidth && GetMapStatus(i+2, j) == 1)
                {
                    actionTest.PiecePosX = i;
                    actionTest.PiecePosY = j;
                    actionTest.DesPosX = i+2;
                    actionTest.DesPosY = j;
                    goto TheEnd;
                }
                if (i+2<mapWidth && j+1<mapHeight && GetMapStatus(i+2, j+1) == 1)
                {
                    actionTest.PiecePosX = i;
                    actionTest.PiecePosY = j;
                    actionTest.DesPosX = i+2;
                    actionTest.DesPosY = j+1;
                    goto TheEnd;
                }
                if (i+2<mapWidth && j+2<mapHeight && GetMapStatus(i+2, j+2) == 1)
                {
                    actionTest.PiecePosX = i;
                    actionTest.PiecePosY = j;
                    actionTest.DesPosX = i+2;
                    actionTest.DesPosY = j+2;
                    goto TheEnd;
                }
                if (i+1<mapWidth && j+2<mapHeight && GetMapStatus(i+1, j+2) == 1)
                {
                    actionTest.PiecePosX = i;
                    actionTest.PiecePosY = j;
                    actionTest.DesPosX = i+1;
                    actionTest.DesPosY = j+2;
                    goto TheEnd;
                }
                if (j+2<mapHeight && GetMapStatus(i, j+2) == 1)
                {
                    actionTest.PiecePosX = i;
                    actionTest.PiecePosY = j;
                    actionTest.DesPosX = i;
                    actionTest.DesPosY = j+2;
                    goto TheEnd;
                }
                if (i-2>=0 && GetMapStatus(i-2, j) == 1)
                {
                    actionTest.PiecePosX = i;
                    actionTest.PiecePosY = j;
                    actionTest.DesPosX = i-2;
                    actionTest.DesPosY = j;
                    goto TheEnd;
                }
                if (i-2>=0 && j-1>=0 && GetMapStatus(i-2, j-1) == 1)
                {
                    actionTest.PiecePosX = i;
                    actionTest.PiecePosY = j;
                    actionTest.DesPosX = i-2;
                    actionTest.DesPosY = j-1;
                    goto TheEnd;
                }
                if (i-2>=0 && j-2>=0 && GetMapStatus(i-2, j-2) == 1)
                {
                    actionTest.PiecePosX = i;
                    actionTest.PiecePosY = j;
                    actionTest.DesPosX = i-2;
                    actionTest.DesPosY = j-2;
                    goto TheEnd;
                }
                if (i-1>=0 && j-2>=0 && GetMapStatus(i-1, j-2) == 1)
                {
                    actionTest.PiecePosX = i;
                    actionTest.PiecePosY = j;
                    actionTest.DesPosX = i-1;
                    actionTest.DesPosY = j-2;
                    goto TheEnd;
                }
                if (j-2>=0 && GetMapStatus(i, j-2) == 1)
                {
                    actionTest.PiecePosX = i;
                    actionTest.PiecePosY = j;
                    actionTest.DesPosX = i;
                    actionTest.DesPosY = j-2;
                    goto TheEnd;
                }
            }
        }
    }

TheEnd:
    return  actionTest;
}