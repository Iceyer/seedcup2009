#include "stdafx.h"
#include "../../Hexxagon/resource.h"

#include "SenceRender.hpp"
#include <cmath>
#include <assert.h>
#include <afxmt.h>

const double gdCos30 = 0.86602540378443864676372317075294;
const double HoleSize = 26;
int          giN = 0;
int          giM = 0;
Render Render::m_Render;
using namespace Hexxagon;

Render::Render()
: m_bMoveAction(false)
, m_bMoving(false)
, m_showResult(true)
{
    LOGFONT                 font;
    font.lfHeight           = - 20;
    font.lfWidth            = 0;
    font.lfEscapement       = 0;
    font.lfOrientation      = 0;
    font.lfWeight           = FW_THIN;
    font.lfItalic           = FALSE;
    font.lfUnderline        = FALSE;
    font.lfStrikeOut        = FALSE;
    font.lfOutPrecision     = OUT_TT_PRECIS;
    font.lfClipPrecision    = CLIP_DEFAULT_PRECIS;
    font.lfQuality          = DEFAULT_QUALITY;
    font.lfPitchAndFamily   = DEFAULT_PITCH;
    font.lfOutPrecision     = OUT_TT_PRECIS;
    font.lfPitchAndFamily   = DEFAULT_PITCH | FF_DONTCARE;
    ::strncpy_s(font.lfFaceName, _T("微软雅黑"), 31);

    m_PlayerInfoFont.CreateFontIndirect(&font);

    font.lfHeight = -40;
    ::strncpy_s(font.lfFaceName, _T("Courier New"), 31);
    m_PreInfoFont.CreateFontIndirect(&font);
}

void Render::Init()
{
    m_iMapWidth = Game::HexxagonGame().CurMatch()->GetMap().MapWidth();
    m_iMapHeight = Game::HexxagonGame().CurMatch()->GetMap().MapHeigth();
    //原表达式为 200 + (16-iMapWidth)/2*36;
    m_iStartX = 500 -26 * m_iMapWidth * 3 / 4;
    //原表达式为 (600 - iMapHeight*30 - (iMapWidth-1)*15)/2 + (iMapWidth-1)*15;
    m_iStartY = 300 - HoleSize * gdCos30 * m_iMapHeight + gdCos30 * HoleSize * (m_iMapWidth - 1) / 2;
}

Render::~Render()
{
    m_PlayerInfoFont.DeleteObject();
}

void Render::SetDC(CDC *pdc)
{
    m_pDC = pdc;
}

void Render::SetSenceSize(int width, int height)
{
    m_Width = width;
    m_Height = height;
}

CPoint Render::LogicPos2PixelPos(int x, int y)
{
    return CPoint(m_iStartX + x * 36/*3 * HoleSize / 2*/, 
                  m_iStartY + y * 21.5/*gdCos30 * HoleSize*/ * 2 - x * 21.5/* gdCos30 *HoleSize*/);
}

void Render::RenderSence()
{
    //CurMatch为空，则游戏未正常初始化
    if(!Game::HexxagonGame().CurMatch())
    {
        DrawPreScreen();
        return;
    }
    /*Init Need Data*/
    Init();

    /*Draw Map*/
    CPoint posItem;
    for (int i =0; i < m_iMapWidth; ++i)
    {
        for (int j = 0; j < m_iMapHeight; ++j)
        {
            MapItem curItem = Game::HexxagonGame().CurMatch()->GetMap().GetMapStatus(i, j);
            posItem = LogicPos2PixelPos(i,j);
            switch (curItem.m_Type)
            {
            case MapItem::INVALID:
                break;
            case MapItem::EMPTY:
                DrawHexagon(posItem.x, posItem.y, IDB_EMPTY_HOLE, IDB_HOLE_BK, curItem.m_Type);
                break;
            case MapItem::PLayer1://玩家1使用蓝色石子
                DrawHexagon(posItem.x, posItem.y, IDB_EMPTY_HOLE, IDB_HOLE_BK, curItem.m_Type);
                DrawPlayer1(posItem.x, posItem.y);
                //DrawHexagon(posItem.x, posItem.y, IDB_BLUE_HOLE, IDB_HOLE_BK, curItem.m_Type);
                break;
            case MapItem::PLayer2://玩家2使用红色石子
                DrawHexagon(posItem.x, posItem.y, IDB_EMPTY_HOLE, IDB_HOLE_BK, curItem.m_Type);
                DrawPlayer2(posItem.x, posItem.y);
                //DrawHexagon(posItem.x, posItem.y, IDB_RED_HOLE, IDB_HOLE_BK, curItem.m_Type);
                break;
            default:
                break;
            }
        }
    }

    if (m_bMoveAction)
    {
        RenderMoveAction(Game::HexxagonGame().CurMatch()->GetCurAction());
    }

    if (Game::HexxagonGame().CurMatch()->IsMatchEnd() && m_showResult)
    {
        DrawMatchEndInfo();
    }

    /*Draw Game Information*/
    DrawGameInfo();
}

void Render::EnableMoveAction()
{
    m_bMoveAction = true;
    m_bMoving = false;
}

bool Render::IsMoveActionEnd()
{
    return m_bMoveAction;
}

void Render::DrawPreScreen()
{
    CFont*      pOldFont = m_pDC->SelectObject(&m_PreInfoFont);
    m_pDC->SetTextColor(gColorBlue);
    m_pDC->SetTextAlign(TA_CENTER | TA_BASELINE);
    m_pDC->TextOut(m_Width / 2, m_Height / 2, _T("Press F5 to Start Game"));
    m_pDC->SelectObject(pOldFont);
}

void Render::ShowResultSwitch()
{
    m_showResult = !m_showResult;
}


void Render::DrawMatchEndInfo()
{
    CFont*      pOldFont = m_pDC->SelectObject(&m_PreInfoFont);
    CPen BluePen(PS_SOLID, 5, gColorBlue);
    CPen* pOldPen = m_pDC->SelectObject(&BluePen);
    CBrush GreenBrush(gColorRed);
    CBrush* pOldBrush = m_pDC->SelectObject(&GreenBrush);

    CRect rcWinInfo(CPoint(300, 260), CPoint(700, 350));
    m_pDC->FillRect(&rcWinInfo, &GreenBrush);
    m_pDC->MoveTo(300, 260);
    m_pDC->LineTo(700, 260);
    m_pDC->LineTo(700, 350);
    m_pDC->LineTo(300, 350);
    m_pDC->LineTo(300, 260);

    m_pDC->SetTextAlign(TA_CENTER);
    m_pDC->SetTextColor(gColorBlue);
    CString     strInfo;
    if (Hexxagon::Game::HexxagonGame().CurMatch()->Winner())
    {
        strInfo.Format(_T("%s WIN"), Hexxagon::Game::HexxagonGame().CurMatch()->Winner()->GetName().c_str());
    }
    else
    {
        strInfo = _T("Draw");
    }

    m_pDC->TextOut(500, 270, strInfo);

    m_pDC->SelectObject(&m_PlayerInfoFont);
    m_pDC->SetTextColor(gColorGrey200);
    if (Hexxagon::Game::HexxagonGame().gbGameOver)
    {
        m_pDC->TextOut(500, 320, _T("ALL MATCH OVER!PRESS ESC TO EXIT..."));
    } 
    else
    {
        m_pDC->TextOut(500, 320, _T("Press F4 For Next Match..."));
    }

    pOldPen = m_pDC->SelectObject(pOldPen);
    pOldBrush = m_pDC->SelectObject(pOldBrush);
}

void Render::RenderMoveAction(const Action& curAction)
{
    if(!m_bMoveAction)
    {
        return;
    }
    m_PosStart = Render::SRender().LogicPos2PixelPos(curAction.PiecePosX,curAction.PiecePosY);
    m_PosEnd = Render::SRender().LogicPos2PixelPos(curAction.DesPosX,curAction.DesPosY);
    float crossLength = (float)sqrt(double((m_PosEnd.x-m_PosStart.x)*(m_PosEnd.x-m_PosStart.x) 
        + (m_PosEnd.y-m_PosStart.y)*(m_PosEnd.y-m_PosStart.y)));
    float delta = 3;
    if (!m_bMoving)
    {
        m_CurPos = m_PosStart;
        m_bMoving = true;
        giM = crossLength / delta;
        giN = 0;
    }
    else
    {
        MapItem::ItemType   ID = (MapItem::ItemType)Game::HexxagonGame().CurMatch()->GetCurPlayer().GetPlayerID();
        if (Game::HexxagonGame().CurMatch()->GetActionType() == 2)
        {
            DrawHexagon(m_PosStart.x, m_PosStart.y, IDB_EMPTY_HOLE, IDB_HOLE_BK, ID);
        }
        switch (ID)
        {
        case MapItem::PLayer1://玩家1使用蓝色石子
            DrawPlayer1(m_CurPos.x,m_CurPos.y);
            break;
        case MapItem::PLayer2://玩家2使用红色石子
            DrawPlayer2(m_CurPos.x,m_CurPos.y);
            break;
        default:
            break;
        }

        float deltaX = ((m_PosEnd.x - m_PosStart.x)/double(giM));
        float deltaY = ((m_PosEnd.y - m_PosStart.y)/DOUBLE(giM));

        m_CurPos.x = m_PosStart.x + giN * deltaX;
        m_CurPos.y = m_PosStart.y + giN * deltaY;
        giN ++;
        if(giN == giM)
        {
            m_bMoveAction = false;
        }
    }
}

//该函数只对传进来的两个位图进行运算然后贴图，最后一个参数目前没有作用
void Render::DrawHexagon(int cx, int cy, unsigned bitmapID1, unsigned bitmapID2, Hexxagon::MapItem::ItemType iType /*= Hexxagon::MapItem::ItemType::EMPTY*/)
{
    using namespace Hexxagon;
    CBitmap hole1,hole2;

    if (iType == MapItem::INVALID)
        assert(false);//对于不可放置石子地方，不进行绘制

    if (!(hole1.LoadBitmap(bitmapID1)&&hole2.LoadBitmap(bitmapID2)))
    {
        if (MessageBox(NULL, _T("无法找到需要加载的位图"), _T("加载位图失败"), MB_OK) == IDOK)
        {
            return;
        }
    }

    CDC cdctemp;
    cdctemp.CreateCompatibleDC(NULL);
    cdctemp.SelectObject(&hole2);
    m_pDC->BitBlt(cx, cy, 50, 43, &cdctemp, 0, 0, SRCPAINT);//与源位图与目标位图做“或”运算

    cdctemp.SelectObject(&hole1);
    m_pDC->BitBlt(cx, cy, 50, 43, &cdctemp, 0, 0, SRCAND);//与源位图与目标位图做“与”运算
    cdctemp.DeleteDC();
}

void Render::DrawPlayer1(int cx, int cy)
{
    DrawHexagon(cx, cy, IDB_BLUE_STONE, IDB_STONE_BK, Hexxagon::MapItem::PLayer1);
}

void Render::DrawPlayer2(int cx, int cy)
{
    DrawHexagon(cx, cy, IDB_RED_STONE, IDB_STONE_BK, Hexxagon::MapItem::PLayer2);
}

void Render::DrawGameInfo()
{
    using namespace Hexxagon;
    int         Xoffset = 20;
    int         Yoffset = 40;
    int         Xborder = 200;
    int         YDiv = 30;
    int         YPos = Yoffset;
    CFont*      pOldFont = m_pDC->SelectObject(&m_PlayerInfoFont);
    CPen RedPen(PS_SOLID, 5, gColorBlue);
    CPen* pOldPen = m_pDC->SelectObject(&RedPen);
    CString     strInfo;

    m_pDC->SetTextAlign(TA_LEFT | TA_TOP);
    //画左边的矩形框
    m_pDC->MoveTo(0 + 2, 0 + 2);
    m_pDC->LineTo(Xborder - 2,0 + 2);
    m_pDC->LineTo(Xborder - 2, m_Height - 2);
    m_pDC->LineTo(0 + 2, m_Height - 2);
    m_pDC->LineTo(0 + 2, 0 + 2);

    //画右边的矩形框
    CPen GreenPen(PS_SOLID, 5, gColorGreen);
    m_pDC->SelectObject(&GreenPen);
    m_pDC->MoveTo(Xborder + 3, 0 +2);
    m_pDC->LineTo(m_Width - 2, 0 + 2);
    m_pDC->LineTo(m_Width - 2, m_Height - 2);
    m_pDC->LineTo(Xborder + 3, m_Height - 2);
    m_pDC->LineTo(Xborder + 3, 0 + 2);

    m_pDC->SetTextColor(gColorGrey200);
    //玩家一信息
    DrawPlayer1(Xoffset, YPos - 10);
    m_pDC->TextOut(Xoffset + 60, YPos, _T("Player1"));
    YPos += 30;
    m_pDC->TextOut(Xoffset, YPos, _T("Name:"));
    YPos += 30;
    m_pDC->TextOut(Xoffset + 20, YPos, Game::HexxagonGame().CurMatch()->GetPlayer(MapItem::PLayer1).GetName().c_str());
    YPos += 30;
    m_pDC->TextOut(Xoffset, YPos, _T("Score:"));
    strInfo.Format(_T("%d"), Game::HexxagonGame().CurMatch()->GetJudge().GetScore(MapItem::PLayer1));
    YPos += 30;
    m_pDC->TextOut(Xoffset + 20, YPos, strInfo);
    YPos += 60;
    //玩家二信息
    DrawPlayer2(Xoffset, YPos - 10);
    m_pDC->TextOut(Xoffset + 60, YPos, _T("Player2"));
    YPos += 30;
    m_pDC->TextOut(Xoffset, YPos, _T("Name:"));
    YPos += 30;
    m_pDC->TextOut(Xoffset + 20, YPos, Game::HexxagonGame().CurMatch()->GetPlayer(MapItem::PLayer2).GetName().c_str());
    YPos += 30;
    m_pDC->TextOut(Xoffset, YPos, _T("Score:"));
    strInfo.Format(_T("%d"), Game::HexxagonGame().CurMatch()->GetJudge().GetScore(MapItem::PLayer2));
    YPos += 30;
    m_pDC->TextOut(Xoffset + 20, YPos, strInfo);
    //书写帮助信息
    YPos += 60;
    m_pDC->TextOut(Xoffset, YPos, _T("Press F2"));
    YPos += 30;
    m_pDC->TextOut(Xoffset, YPos, _T("For More Help"));
    YPos += 60;
    m_pDC->TextOut(Xoffset, YPos, _T("Press F3"));
    YPos += 30;
    m_pDC->TextOut(Xoffset, YPos, _T("To Accelerate"));
    m_pDC->SelectObject(pOldFont);
    m_pDC->SelectObject(pOldPen);
}