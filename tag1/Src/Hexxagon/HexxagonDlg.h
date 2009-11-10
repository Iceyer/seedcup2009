// HexxagonDlg.h : 头文件
//

#pragma once

#include "resource.h"

// CHexxagonDlg 对话框
class CHexxagonDlg : public CDialog
{
    // 构造
public:
    CHexxagonDlg(CWnd* pParent = NULL);	// 标准构造函数

    ~CHexxagonDlg();

    // 对话框数据
    enum { IDD = IDD_HEXXAGON_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
    /// 生成的消息映射函数
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnDestroy();
    afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    DECLARE_MESSAGE_MAP()

public:
    static CHexxagonDlg *Myself();
    void StartGame();
    void NextMatch();
    void DisableUI();

    /// 实现
protected:
    HICON                       m_hIcon;
    static CHexxagonDlg*        m_pSelf;
};
