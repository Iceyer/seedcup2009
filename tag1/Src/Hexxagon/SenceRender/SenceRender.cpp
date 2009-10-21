#include "stdafx.h"
#include "../../Hexxagon/resource.h"

#include "SenceRender.hpp"

const double gdCos30 = 0.86602540378443864676372317075294;
const double HexgaonSize = 20;
const double HexgaonSizeB = HexgaonSize * gdCos30;

Render Render::m_Render;

Render::Render()
{
    LOGFONT                              font;

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

void Render::RenderSence()
{
    using namespace Hexxagon;

    //CurMatch为空，则游戏未正常初始化
    if(!Game::HexxagonGame().CurMatch())
    {
        return;
    }
    /*Draw Game Information*/
    DrawGameInfo();

    /*Draw Map*/
    /*Calc The Start Point*/
    const int     iMapWidth = Game::HexxagonGame().CurMatch()->GetMap().MapWidth();
    const int     iMapHeight = Game::HexxagonGame().CurMatch()->GetMap().MapHeigth();
    const int     iStartX = 468 -18*iMapWidth; //原表达式为 200 + (16-iMapWidth)/2*36;
    const int     iStartY = 285 + (15-30*iMapHeight+15*iMapWidth)/2; //原表达式为 (600 - iMapHeight*30 - (iMapWidth-1)*15)/2 + (iMapWidth-1)*15;

    int     iItemX;
    int     iItemY;
    for (int i =0; i < iMapWidth; ++i)
    {
        for (int j = 0; j < iMapHeight; ++j)
        {
            MapItem curItem = Game::HexxagonGame().CurMatch()->GetMap().GetMapStatus(i, j);
            iItemX  = iStartX + i*36;
            iItemY  = iStartY - i*15 + j*30;
            switch (curItem.m_Type)
            {
            case MapItem::INVALID:
                break;
            case MapItem::EMPTY:
                DrawHexagon(iItemX,iItemY,curItem.m_Type);
                break;
            case MapItem::PLayer1:
                DrawHexagon(iItemX,iItemY,curItem.m_Type);
                break;
            case MapItem::PLayer2:
                DrawHexagon(iItemX,iItemY,curItem.m_Type);
                break;
            default:
                break;
            }
        }
    }

}

void Render::DrawHexagon(int cx, int cy, Hexxagon::MapItem::ItemType iType)
{
    using namespace Hexxagon;
    CBitmap hole1,hole2;
    bool loadImageTag;
    switch (iType)
    {
    case MapItem::EMPTY:
        loadImageTag = hole1.LoadBitmap(IDB_BITMAP1)&&hole2.LoadBitmap(IDB_BITMAP2);
        break;
    case MapItem::PLayer1:
        loadImageTag = hole1.LoadBitmap(IDB_BITMAP3)&&hole2.LoadBitmap(IDB_BITMAP2);
        break;
    case MapItem::PLayer2:
        loadImageTag = hole1.LoadBitmap(IDB_BITMAP4)&&hole2.LoadBitmap(IDB_BITMAP2);
        break;
    default:
        break;
    }
    if (!loadImageTag)
    {
        if (MessageBox(NULL,"无法找到需要加载的位图","加载位图失败",MB_OK) == IDOK)
        {
            return;
        }
    }

    CDC cdctemp;
    cdctemp.CreateCompatibleDC(NULL);
    cdctemp.SelectObject(&hole2);
    m_pDC->BitBlt(cx,cy,50,30,&cdctemp,0,0,SRCPAINT);//与源位图与目标位图做“或”运算

    cdctemp.SelectObject(&hole1);
    m_pDC->BitBlt(cx,cy,50,30,&cdctemp,0,0,SRCAND);//与源位图与目标位图做“与”运算
    cdctemp.DeleteDC();
}

void Render::DrawPlayer1(int cx, int cy, int edgelength)
{
    /*CBrush  Brush(gColorBlue);
    CBrush* pOldBrush = m_pDC->SelectObject(&Brush);
    m_pDC->Ellipse(cx - edgelength, cy - edgelength, cx + edgelength, cy + edgelength); */
}

void Render::DrawPlayer2(int cx, int cy, int edgelength)
{
    /*CBrush  Brush(gColorWhite);
    CBrush* pOldBrush = m_pDC->SelectObject(&Brush);
    m_pDC->Ellipse(cx - edgelength, cy - edgelength, cx + edgelength, cy + edgelength); */
}

void Render::DrawGameInfo()
{
    using namespace Hexxagon;
    int         Xoffset = 20;
    int         Yoffset = 60;
    int         Xborder = 200;
    int         YDiv = 30;
    int         YPos = Yoffset;
    CFont*      pOldFont = m_pDC->SelectObject(&m_PlayerInfoFont);
    CPen RedPen(PS_SOLID, 5, gColorBlue);
    CPen* pOldPen = m_pDC->SelectObject(&RedPen);
    CString     strInfo;

    m_pDC->MoveTo(0 + 2, 0 + 2);
    m_pDC->LineTo(Xborder - 2,0 + 2);
    m_pDC->LineTo(Xborder - 2, m_Height - 2);
    m_pDC->LineTo(0 + 2, m_Height - 2);
    m_pDC->LineTo(0 + 2, 0 + 2);

    CPen GreenPen(PS_SOLID, 5, gColorGreen);
    m_pDC->SelectObject(&GreenPen);
    m_pDC->MoveTo(Xborder + 3, 0 +2);
    m_pDC->LineTo(m_Width - 2, 0 + 2);
    m_pDC->LineTo(m_Width - 2, m_Height - 2);
    m_pDC->LineTo(Xborder + 3, m_Height - 2);
    m_pDC->LineTo(Xborder + 3, 0 + 2);

    m_pDC->SetTextColor(RGB(200, 200, 200));
    //玩家一
    DrawHexagon(Xoffset, YPos, MapItem::PLayer2);
    m_pDC->TextOut(Xoffset + 60, YPos, _T("Player1"));
    YPos += 30;
    m_pDC->TextOut(Xoffset, YPos, _T("Name:"));
    YPos += 30;
    m_pDC->TextOut(Xoffset, YPos, Game::HexxagonGame().CurMatch()->GetPlayer(MapItem::PLayer1).GetName().c_str());
    YPos += 30;
    m_pDC->TextOut(Xoffset, YPos, _T("Score:"));
    strInfo.Format(_T("%d"), Game::HexxagonGame().CurMatch()->GetJudge().GetScore(MapItem::PLayer1));
    YPos += 30;
    m_pDC->TextOut(Xoffset, YPos, strInfo);
    //
    YPos += 60;

    //玩家二
    DrawHexagon(Xoffset, YPos, MapItem::PLayer1);
    m_pDC->TextOut(Xoffset + 60, YPos, _T("Player2"));
    YPos += 30;
    m_pDC->TextOut(Xoffset, YPos, _T("Name:"));
    YPos += 30;
    m_pDC->TextOut(Xoffset, YPos, Game::HexxagonGame().CurMatch()->GetPlayer(MapItem::PLayer2).GetName().c_str());
    YPos += 30;
    m_pDC->TextOut(Xoffset, YPos, _T("Score:"));
    strInfo.Format(_T("%d"), Game::HexxagonGame().CurMatch()->GetJudge().GetScore(MapItem::PLayer2));
    YPos += 30;
    m_pDC->TextOut(Xoffset, YPos, strInfo);

    YPos += 60;
    m_pDC->TextOut(Xoffset, YPos, _T("For More Help"));
    YPos += 30;
    m_pDC->TextOut(Xoffset, YPos, _T("Press F2"));

    m_pDC->SelectObject(pOldFont);
    m_pDC->SelectObject(pOldPen);
}