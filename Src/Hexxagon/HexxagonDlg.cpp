// HexxagonDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Hexxagon.h"
#include "HexxagonDlg.h"
#include ".\SenceRender\SenceRender.hpp"
#include ".\GameCore\Game.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

    // 对话框数据
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    // 实现
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CHexxagonDlg 对话框

CHexxagonDlg* CHexxagonDlg::m_pSelf;

CHexxagonDlg::CHexxagonDlg(CWnd* pParent /*=NULL*/)
: CDialog(CHexxagonDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    memset(&m_Critical, 0, sizeof(CRITICAL_SECTION));
    m_pSelf = this;
}

CHexxagonDlg::~CHexxagonDlg()
{
    ::DeleteCriticalSection(&m_Critical);
}

void CHexxagonDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHexxagonDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_WM_ERASEBKGND()
    ON_WM_DESTROY()
    ON_WM_KEYUP()
END_MESSAGE_MAP()


// CHexxagonDlg 消息处理程序

BOOL CHexxagonDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // 将“关于...”菜单项添加到系统菜单中。

    // IDM_ABOUTBOX 必须在系统命令范围内。
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    SetIcon(m_hIcon, TRUE);         // 设置大图标
    SetIcon(m_hIcon, FALSE);        // 设置小图标

    // TODO: 在此添加额外的初始化代码
    SetWindowPos(NULL, 0, 0, 800, 600, SWP_SHOWWINDOW);
    ::InitializeCriticalSection(&m_Critical);

    return  FALSE;
}

void CHexxagonDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHexxagonDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作区矩形中居中
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 绘制图标
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        //CDialog::OnPaint();
        //使用双缓冲绘图
        CPaintDC dc(this); // 用于绘制的设备上下文
        CRect lcrcClient;
        GetClientRect(&lcrcClient);

        CDC MemDC; //首先定义一个显示设备对象
        CBitmap MemBitmap;//定义一个位图对象
        MemDC.CreateCompatibleDC(NULL);
        MemBitmap.CreateCompatibleBitmap(&dc,lcrcClient.Width(),lcrcClient.Height());
        CBitmap *pOldBit=MemDC.SelectObject(&MemBitmap);

        MemDC.SetBkColor(gBackGroundColor);
        MemDC.SetBkMode(TRANSPARENT);

        CBrush lcBKBrush(gBackGroundColor);
        MemDC.FillRect(&lcrcClient, &lcBKBrush);

        //保存当前画笔
        CPen lcPen(PS_SOLID, 1, gColorGreen);
        CPen *lcpOldPen = MemDC.SelectObject(&lcPen);

        EnterCriticalSection(&m_Critical);
        Render::SRender().SetDC(&MemDC);
        Render::SRender().SetSenceSize(lcrcClient.Width(), lcrcClient.Height());

        Render::SRender().RenderSence();

        LeaveCriticalSection(&m_Critical);
        MemDC.SelectObject(lcpOldPen);

        dc.BitBlt(lcrcClient.left, lcrcClient.top, 
            lcrcClient.Width(), lcrcClient.Height(), 
            &MemDC, lcrcClient.left, lcrcClient.top, SRCCOPY);

        //绘图完成后的清理
        MemBitmap.DeleteObject();
        MemDC.DeleteDC();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHexxagonDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


BOOL CHexxagonDlg::OnEraseBkgnd(CDC* pDC)
{
    //return CDialog::OnEraseBkgnd(pDC);
    return TRUE;
}

CHexxagonDlg* CHexxagonDlg::Myself()
{
    return m_pSelf;
}
void CHexxagonDlg::OnDestroy()
{
    CDialog::OnDestroy();
    EnterCriticalSection(&m_Critical);
    Hexxagon::Game::HexxagonGame().gbStopMath = true;
    LeaveCriticalSection(&m_Critical);
    Hexxagon::Game::HexxagonGame().End();
}

void CHexxagonDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    switch (nChar)
    {
    case VK_F2:
        ShowHelpInfo();
        break;
    case VK_F3:
        DisableUI();
        break;
    case VK_F4:
        NextMatch();
        break;
    case VK_F5:
        StartGame();
        break;    
    case VK_F6:
        Render::SRender().ShowResultSwitch();
        Invalidate(TRUE);
        break;
    default:
        break;
    }
    CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CHexxagonDlg::StartGame()
{
    if (Hexxagon::Game::HexxagonGame().Prepare() && !Hexxagon::Game::HexxagonGame().gbGameStarted)
    {
        Hexxagon::Game::HexxagonGame().Start();
    }
}
void CHexxagonDlg::NextMatch()
{
    if (Hexxagon::Game::HexxagonGame().gbGameStarted && Hexxagon::Game::HexxagonGame().CurMatch()->IsMatchEnd())
    {
        Hexxagon::Game::HexxagonGame().NextMatch();
    }
    Invalidate(TRUE);
}
void CHexxagonDlg::DisableUI()
{
    EnterCriticalSection(&m_Critical);
    Hexxagon::Game::HexxagonGame().gbUIEnable = !Hexxagon::Game::HexxagonGame().gbUIEnable;
    //Render::SRender().m_bMoveAction = Hexxagon::Game::HexxagonGame().gbUIEnable;
    LeaveCriticalSection(&m_Critical);
}

void CHexxagonDlg::ShowHelpInfo()
{
    CString str;
    str = _T("F2 : Show Help Info\n");
    str += _T("F3 : Accelerate The Game\n");
    str += _T("F4 : Next Match\n");
    str += _T("F5 : Start The Game\n");
    str += _T("F6 : Show/Hide Result\n");
    MessageBox(str);
}
