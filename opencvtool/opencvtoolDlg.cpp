
// opencv toolDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "opencvtool.h"
#include "opencvtoolDlg.h"
#include "afxdialogex.h"

#include "Copencv.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CopencvtoolDlg 对话框



CopencvtoolDlg::CopencvtoolDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPENCVTOOL_DIALOG, pParent)
	, m_sel_pic(_T(""))
	, m_threshold_maxval_val(0)
	, m_threshold_thresh_val(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_sel_pic_path = _T("");
	m_sel_pic_name = _T("");
	m_sel_pic_ext = _T("");

}

void CopencvtoolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEL_PIC, m_sel_pic);
	DDX_Control(pDX, IDC_CUSTOM_PIC, m_pic_viewer);
	DDX_Control(pDX, IDC_CHECK_INVERTED, m_btnCheck_inverted);
	DDX_Control(pDX, IDC_LIST_THRESHOLD_TYPE, m_listbox_threshold_type);
	DDX_Control(pDX, IDC_CHECK_THRESHOLD, m_btnCheck_threshold);
	DDX_Control(pDX, IDC_SLIDER_THRESHOLD_MAXVAL, m_slider_threshold_maxval);
	DDX_Control(pDX, IDC_SLIDER_THRESHOLD_THRESH, m_slider_threshold_thresh);
	DDX_Text(pDX, IDC_STATIC_THRESHOLD_MAXVAL_VAL, m_threshold_maxval_val);
	DDX_Text(pDX, IDC_STATIC_THRESHOLD_THRESH_VAL, m_threshold_thresh_val);
	DDX_Control(pDX, IDC_LIST_CVTCOLOR_TYPE, m_listbox_cvtcolor_type);
	DDX_Control(pDX, IDC_CHECK_CVTCOLOR, m_btnCheck_cvtcolor);
}

BEGIN_MESSAGE_MAP(CopencvtoolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEL_PIC, &CopencvtoolDlg::OnBnClickedBtnSelPic)
	ON_BN_CLICKED(IDC_BTN_EMPTY_PIC, &CopencvtoolDlg::OnBnClickedBtnEmptyPic)
	ON_BN_CLICKED(IDC_CHECK_INVERTED, &CopencvtoolDlg::OnBnClickedCheckInverted)
	ON_BN_CLICKED(IDC_CHECK_THRESHOLD, &CopencvtoolDlg::OnBnClickedCheckThreshold)
	ON_WM_HSCROLL()
	ON_LBN_SELCHANGE(IDC_LIST_THRESHOLD_TYPE, &CopencvtoolDlg::OnLbnSelchangeListThresholdType)
	ON_BN_CLICKED(IDC_CHECK_CVTCOLOR, &CopencvtoolDlg::OnBnClickedCheckCvtcolor)
	ON_LBN_SELCHANGE(IDC_LIST_CVTCOLOR_TYPE, &CopencvtoolDlg::OnLbnSelchangeListCvtcolorType)
END_MESSAGE_MAP()


// CopencvtoolDlg 消息处理程序

BOOL CopencvtoolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_slider_threshold_thresh.SetRange(0, 255);
	m_slider_threshold_thresh.SetPos(0);
	m_threshold_thresh_val = 0;

	m_slider_threshold_maxval.SetRange(0, 255);
	m_slider_threshold_maxval.SetPos(255);
	m_threshold_maxval_val = 255;

	m_listbox_threshold_type.AddString(_T("THRESH_BINARY"));
	m_listbox_threshold_type.AddString(_T("THRESH_BINARY_INV"));
	m_listbox_threshold_type.AddString(_T("THRESH_TRUNC"));
	m_listbox_threshold_type.AddString(_T("THRESH_TOZERO"));
	m_listbox_threshold_type.AddString(_T("THRESH_TOZERO_INV"));
	m_listbox_threshold_type.SetCurSel(0);

	m_listbox_cvtcolor_type.AddString(_T("COLOR_BGR2BGRA/COLOR_RGB2RGBA"));
	m_listbox_cvtcolor_type.AddString(_T("COLOR_BGRA2BGR/COLOR_RGBA2RGB"));
	m_listbox_cvtcolor_type.AddString(_T("COLOR_BGR2RGBA/COLOR_RGB2BGRA"));
	m_listbox_cvtcolor_type.AddString(_T("COLOR_RGBA2BGR/COLOR_BGRA2RGB"));
	m_listbox_cvtcolor_type.AddString(_T("COLOR_BGR2RGB/COLOR_RGB2BGR"));
	m_listbox_cvtcolor_type.AddString(_T("COLOR_BGRA2RGBA/COLOR_RGBA2BGRA"));
	m_listbox_cvtcolor_type.SetCurSel(0);

	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CopencvtoolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CopencvtoolDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CopencvtoolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CopencvtoolDlg::OnBnClickedBtnSelPic()
{

	BOOL open_state = TRUE;		    //记录对话框打开状态，True为打开，False为保存
	CString default_dir = _T("");	//默认目录名
	CString defalut_path = _T("");	//默认路径名
	CString filter = _T("文件 (*.bmp;*.jpeg;*.jpg;*.png;*.tiff)|"
		"*.bmp;*.jpeg;*.jpg;*.png;*.tiff||");

	// 单选
	CFileDialog dlg(open_state, default_dir, defalut_path, OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, filter, this);
	dlg.m_ofn.lpstrTitle = _T("选择图片");

	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		m_sel_pic_path = dlg.GetPathName();					//路径名
		m_sel_pic_name = dlg.GetFileName();					//文件名
		m_sel_pic_ext = dlg.GetFileExt();					//扩展名
		m_sel_pic = m_sel_pic_path;

		UpdateData(FALSE);

		m_pic_viewer.update();

	}


	/*
	// 多选
	CFileDialog dlg(TRUE, _T("*.jpg"), NULL, OFN_ALLOWMULTISELECT | OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, _T("All Files(*.*)|*.*|"), this);
	dlg.m_ofn.lpstrTitle = _T("选择图片");
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		POSITION fileNamesPosition = dlg.GetStartPosition();
		while (fileNamesPosition != NULL)
		{
			filename = dlg.GetNextPathName(fileNamesPosition);
			//all_sel_files.push_back(filename);
		}
	}
	*/
}


void CopencvtoolDlg::OnBnClickedBtnEmptyPic()
{
	m_sel_pic_path = _T("");
	m_sel_pic_name = _T("");
	m_sel_pic_ext = _T("");
	m_sel_pic = _T("");

	UpdateData(FALSE);

	m_pic_viewer.update();
}


void CopencvtoolDlg::OnBnClickedCheckInverted()
{
	m_pic_viewer.update();
}


void CopencvtoolDlg::OnBnClickedCheckThreshold()
{
	m_pic_viewer.update();
}


void CopencvtoolDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	int nMin = 0, nMax = 0, nOldPos = nPos, nTempPos = 0;
	int nCtrlId = pScrollBar->GetDlgCtrlID();
	CSliderCtrl *pSlider = NULL;
	if (m_slider_threshold_thresh.GetDlgCtrlID() == nCtrlId) {
		pSlider = (CSliderCtrl *)pScrollBar;
	}
	else if (m_slider_threshold_maxval.GetDlgCtrlID() == nCtrlId) {
		pSlider = (CSliderCtrl *)pScrollBar;
	}

	if (pSlider) {
		pSlider->GetRange(nMin, nMax);
		nTempPos = pSlider->GetPos();
	}

	if (m_slider_threshold_thresh.GetDlgCtrlID() == nCtrlId) {
		m_threshold_thresh_val = nTempPos;
		if (m_threshold_thresh_val > m_threshold_maxval_val) {
			m_slider_threshold_maxval.SetPos(m_threshold_thresh_val);
			m_threshold_maxval_val = m_threshold_thresh_val;
		}
	}
	else if (m_slider_threshold_maxval.GetDlgCtrlID() == nCtrlId) {
		m_threshold_maxval_val = nTempPos;
		if (m_threshold_maxval_val < m_threshold_thresh_val) {
			m_slider_threshold_thresh.SetPos(m_threshold_maxval_val);
			m_threshold_thresh_val = m_threshold_maxval_val;
		}
	}

	if (pSlider) {
		UpdateData(FALSE);
		if (BST_CHECKED == m_btnCheck_threshold.GetCheck()) {
			m_pic_viewer.update();
		}
	}



	/*
	int nOldPos = nPos;
	int nTempPos = pScrollBar->GetScrollPos();
	int nCurPos = 0;
	int nMin = 0, nMax = 0;
	pScrollBar->GetScrollRange(&nMin, &nMax);
	switch (nSBCode)
	{
	case SB_THUMBTRACK://拖动滑块
		if (nOldPos < nTempPos && nOldPos >= nMin)
		{
			pScrollBar->SetScrollPos(nOldPos, TRUE);
			pSlider->SetPos(nOldPos);
		}
		else if (nOldPos > nTempPos && nOldPos <= nMax)
		{
			pScrollBar->SetScrollPos(nOldPos, TRUE);

		}
		nCurPos = pScrollBar->GetScrollPos();
		break;
		//case SB_THUMBPOSITION://拖动完滑块
		//	pScrollBar->SetScrollPos(iPos, FALSE);
		//	
		//	break;
	case SB_LINEUP://点击上边的箭头
		if (nTempPos > nMin)
		{
			pScrollBar->SetScrollPos(nTempPos - 1, TRUE);

		}
		break;
	case SB_LINEDOWN://点击下边的箭头
		if (nTempPos < nMax)
		{
			pScrollBar->SetScrollPos(nTempPos + 1, TRUE);

		}
		break;
	case SB_PAGEUP://点击滚动条上方空白
		if (nTempPos > nMin)
		{
			pScrollBar->SetScrollPos(nTempPos - 1, TRUE);

		}
		break;
	case SB_PAGEDOWN://点击滚动条下方空白
		if (nTempPos < nMax)
		{
			pScrollBar->SetScrollPos(nTempPos + 1, TRUE);

		}
		break;
	case SB_ENDSCROLL://事件响应完
		nCurPos = pScrollBar->GetScrollPos();
		break;
	default:
		break;
	}
	*/
	
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CopencvtoolDlg::OnLbnSelchangeListThresholdType()
{
	if (BST_CHECKED == m_btnCheck_threshold.GetCheck()) {
		m_pic_viewer.update();
	}
}



void CopencvtoolDlg::OnBnClickedCheckCvtcolor()
{
	m_pic_viewer.update();
}


void CopencvtoolDlg::OnLbnSelchangeListCvtcolorType()
{
	if (BST_CHECKED == m_btnCheck_cvtcolor.GetCheck()) {
		m_pic_viewer.update();
	}
}
