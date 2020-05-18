
// opencv toolDlg.h: 头文件
//

#pragma once
#include "CpicViewer.h"

// CopencvtoolDlg 对话框
class CopencvtoolDlg : public CDialogEx
{
// 构造
public:
	CopencvtoolDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENCVTOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSelPic();
	CString m_sel_pic;
	CString m_sel_pic_path;
	CString m_sel_pic_name;
	CString m_sel_pic_ext;
//	CStatic m_pictl_pic;
	CpicViewer m_pic_viewer;
	afx_msg void OnBnClickedBtnEmptyPic();
};
