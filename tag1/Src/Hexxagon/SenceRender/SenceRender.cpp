#include "stdafx.h"
#include "../../Hexxagon/resource.h"

#include "SenceRender.hpp"
#include <assert.h>
#include <afxmt.h>

const double gdCos30 = 0.86602540378443864676372317075294;
const double HexgaonSize = 20;
const double HexgaonSizeB = HexgaonSize * gdCos30;

Render Render::m_Render;

Render::Render()
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
    ::strncpy_s(font.lfFaceName, _T("΢���ź�"), 31);

    m_PlayerInfoFont.CreateFontIndirect(&font);
}

void Render::Init()
{
    /*Calc The Start Point*/
    using namespace Hexxagon;
    m_iMapWidth = Game::HexxagonGame().CurMatch()->GetMap().MapWidth();
    m_iMapHeight = Game::HexxagonGame().CurMatch()->GetMap().MapHeigth();
    //ԭ���ʽΪ 200 + (16-iMapWidth)/2*36;
    m_iStartX = 468 -18*m_iMapWidth; 
    //ԭ���ʽΪ (600 - iMapHeight*30 - (iMapWidth-1)*15)/2 + (iMapWidth-1)*15;
    m_iStartY = 285 + (15-30*m_iMapHeight+15*m_iMapWidth)/2; 
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

CPoint Render::GetPosInPixel(int x, int y)
{
    return CPoint(m_iStartX + x*36, m_iStartY - x*15 + y*30);
}

void Render::RenderSence()
{
    using namespace Hexxagon;
    //CurMatchΪ�գ�����Ϸδ������ʼ��
    if(!Game::HexxagonGame().CurMatch())
    {
        return;
    }
    /*Draw Game Information*/
    DrawGameInfo();

    /*Draw Map*/
    CPoint posItem;
    for (int i =0; i < m_iMapWidth; ++i)
    {
        for (int j = 0; j < m_iMapHeight; ++j)
        {
            MapItem curItem = Game::HexxagonGame().CurMatch()->GetMap().GetMapStatus(i, j);
            posItem = GetPosInPixel(i,j);
            switch (curItem.m_Type)
            {
            case MapItem::INVALID:
                break;
            case MapItem::EMPTY:
                DrawHexagon(posItem.x, posItem.y, IDB_BITMAP1, IDB_BITMAP2, curItem.m_Type);
                break;
            case MapItem::PLayer1://���1ʹ����ɫʯ��
                DrawHexagon(posItem.x, posItem.y, IDB_BITMAP3, IDB_BITMAP2, curItem.m_Type);
                break;
            case MapItem::PLayer2://���2ʹ�ú�ɫʯ��
                DrawHexagon(posItem.x, posItem.y, IDB_BITMAP4, IDB_BITMAP2, curItem.m_Type);
                break;
            default:
                break;
            }
        }
    }

}

//�ú���ֻ�Դ�����������λͼ��������Ȼ����ͼ�����һ������Ŀǰû������
void Render::DrawHexagon(int cx, int cy, unsigned bitmapID1, unsigned bitmapID2, Hexxagon::MapItem::ItemType iType /*= Hexxagon::MapItem::ItemType::EMPTY*/)
{
    using namespace Hexxagon;
    CBitmap hole1,hole2;

    if (iType == MapItem::INVALID)
        assert(false);//���ڲ��ɷ���ʯ�ӵط��������л���

    if (!(hole1.LoadBitmap(bitmapID1)&&hole2.LoadBitmap(bitmapID2)))
    {
        if (MessageBox(NULL,"�޷��ҵ���Ҫ���ص�λͼ","����λͼʧ��",MB_OK) == IDOK)
        {
            return;
        }
    }

    CMutex g_Mutex;
    g_Mutex.Lock();
    CDC cdctemp;
    cdctemp.CreateCompatibleDC(NULL);
    cdctemp.SelectObject(&hole2);
    m_pDC->BitBlt(cx, cy, 50, 30, &cdctemp, 0, 0, SRCPAINT);//��Դλͼ��Ŀ��λͼ����������

    cdctemp.SelectObject(&hole1);
    m_pDC->BitBlt(cx, cy, 50, 30, &cdctemp, 0, 0, SRCAND);//��Դλͼ��Ŀ��λͼ�����롱����
    cdctemp.DeleteDC();
    g_Mutex.Unlock();
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

    //����ߵľ��ο�
    m_pDC->MoveTo(0 + 2, 0 + 2);
    m_pDC->LineTo(Xborder - 2,0 + 2);
    m_pDC->LineTo(Xborder - 2, m_Height - 2);
    m_pDC->LineTo(0 + 2, m_Height - 2);
    m_pDC->LineTo(0 + 2, 0 + 2);

    //���ұߵľ��ο�
    CPen GreenPen(PS_SOLID, 5, gColorGreen);
    m_pDC->SelectObject(&GreenPen);
    m_pDC->MoveTo(Xborder + 3, 0 +2);
    m_pDC->LineTo(m_Width - 2, 0 + 2);
    m_pDC->LineTo(m_Width - 2, m_Height - 2);
    m_pDC->LineTo(Xborder + 3, m_Height - 2);
    m_pDC->LineTo(Xborder + 3, 0 + 2);

    m_pDC->SetTextColor(RGB(200, 200, 200));
    //���һ��Ϣ
    DrawHexagon(Xoffset, YPos, IDB_BITMAP5, IDB_BITMAP7, MapItem::PLayer1);
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

    //��Ҷ���Ϣ
    DrawHexagon(Xoffset, YPos, IDB_BITMAP6, IDB_BITMAP7, MapItem::PLayer2);
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

    //��д������Ϣ
    YPos += 60;
    m_pDC->TextOut(Xoffset, YPos, _T("For More Help"));
    YPos += 30;
    m_pDC->TextOut(Xoffset, YPos, _T("Press F2"));

    m_pDC->SelectObject(pOldFont);
    m_pDC->SelectObject(pOldPen);
}