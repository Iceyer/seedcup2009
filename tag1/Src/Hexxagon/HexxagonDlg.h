// HexxagonDlg.h : 头文件
//

#pragma once


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
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    // 实现
protected:
    HICON m_hIcon;
    CRITICAL_SECTION m_Critical;

    // 生成的消息映射函数
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

};
