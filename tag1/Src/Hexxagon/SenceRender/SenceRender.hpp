//Header file for render sence
#pragma once

#include "../../GameCore/Map.hpp"
#include "../GameCore/Game.hpp"

const COLORREF gColorRed    = RGB(255, 0, 0);
const COLORREF gColorGreen  = RGB(0, 255, 0);
const COLORREF gColorBlue   = RGB(0, 0, 255);
const COLORREF gColorYellow = RGB(255, 255, 0);
const COLORREF gColorWhite  = RGB(255, 255, 255);
const COLORREF gColorBlack  = RGB(0, 0, 0);

const COLORREF gBackGroundColor = gColorBlack;

class CDC;

class Render
{
public:
    ~Render();

public:
    static Render& SRender()
    {
        return m_Render;
    }

    void SetDC(CDC *pdc);

    void Render::SetSenceSize(int x, int y);

    void DrawPreScreen();

    void RenderSence();

    void RenderMoveAction(const Action& curAction);

    void EnableMoveAction();

    bool IsMoveActionEnd();

    //���ĳһ��ͼ�����Ͻǵ���������
    inline CPoint LogicPos2PixelPos(int x, int y);

    //��ʼ����Ա����
    void Init();

    void DrawGameInfo();

    void DrawHexagon(int cx, int cy, unsigned BitmapID, unsigned BkBitmapID, Hexxagon::MapItem::ItemType iType = Hexxagon::MapItem::EMPTY);

    void Render::DrawPlayer1(int cx, int cy);
    
    void Render::DrawPlayer2(int cx, int cy);


private:
    Render();

    static Render m_Render;

    CDC     *m_pDC;
    int     m_Width;
    int     m_Height;
    int     m_iStartX;          //��¼������ͼ�����Ͻ�x����
    int     m_iStartY;          //��¼������ͼ�����Ͻ�y����
    int     m_iMapWidth;        //��¼�����ж��ٸ�hole
    int     m_iMapHeight;       //��¼�����ж��ٸ�hole

    CFont   m_PlayerInfoFont;
    CFont   m_PreInfoFont;

    CPoint  m_PosStart;
    CPoint  m_PosEnd;
    CPoint  m_CurPos;

public:
    bool    m_bMoveAction;
    bool    m_bMoving;
};