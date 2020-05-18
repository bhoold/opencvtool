#pragma once


// CpicViewer

class CpicViewer : public CWnd
{
	DECLARE_DYNAMIC(CpicViewer)

public:
	CpicViewer();
	virtual ~CpicViewer();

protected:
	DECLARE_MESSAGE_MAP()
public:
	BOOL update();
	BOOL RegisterWindowClass(HINSTANCE hInstance);
	afx_msg void OnPaint();
	CString m_pic_path;
};


