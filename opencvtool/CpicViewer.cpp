// CpicViewer.cpp: 实现文件
//

#include "stdafx.h"
#include "opencvtool.h"
#include "CpicViewer.h"

#include "opencvtoolDlg.h"
#include "Copencv.h"

Copencv ocv;


// CpicViewer

IMPLEMENT_DYNAMIC(CpicViewer, CWnd)

CpicViewer::CpicViewer()
{
	RegisterWindowClass(AfxGetInstanceHandle());
}

CpicViewer::~CpicViewer()
{
}


BEGIN_MESSAGE_MAP(CpicViewer, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CpicViewer 消息处理程序


BOOL CpicViewer::RegisterWindowClass(HINSTANCE hInstance)
{
	LPCSTR className = _T("CPicWindow");
	WNDCLASS windowclass;
	if (hInstance)
		hInstance = AfxGetInstanceHandle();

	if (!(::GetClassInfo(hInstance, className, &windowclass)))
	{
		windowclass.style = CS_DBLCLKS;
		windowclass.lpfnWndProc = ::DefWindowProc;
		windowclass.cbClsExtra = windowclass.cbWndExtra = 0;
		windowclass.hInstance = hInstance;
		windowclass.hIcon = NULL;
		windowclass.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		windowclass.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
		windowclass.lpszMenuName = NULL;
		windowclass.lpszClassName = className;

		if (!AfxRegisterClass(&windowclass))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}
	return TRUE;
}


BOOL CpicViewer::update()
{
	CopencvtoolDlg *pParentDlg = (CopencvtoolDlg*)this->GetParent();
	m_pic_path = (*pParentDlg).m_sel_pic;
	InvalidateRect(NULL, TRUE);
	return TRUE;
}


void CpicViewer::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CWnd::OnPaint()
	
	CRect		rect;
	GetClientRect(&rect);

	if (m_pic_path.IsEmpty()) {
		//dc.MoveTo(0, 0);
		//dc.LineTo(rect.right, rect.bottom);
		ocv.empty();
		CWnd::OnPaint();
	}
	else {
		CopencvtoolDlg *pParentDlg = (CopencvtoolDlg*)this->GetParent();

		int nWidth = rect.Width();
		int nHeight = rect.Height();

		CImage image;
		CString oldFile;
		ocv.getFile(oldFile);
		if (oldFile == m_pic_path) {
			ocv.resetImg();
		}
		else {
			ocv.loadImg(m_pic_path);
		}

		
		if (BST_CHECKED == pParentDlg->m_btnCheck_cvtcolor.GetCheck()) {
			ColorConversionCodes cvtClrVal = (ColorConversionCodes)pParentDlg->m_listbox_cvtcolor_type.GetCurSel();
			//pParentDlg->m_listbox_cvtcolor_type.GetText(pParentDlg->m_listbox_cvtcolor_type.GetCurSel(), cvtColor);
			ocv.cvtcolor(cvtClrVal);
		}
		
		if (BST_CHECKED == pParentDlg->m_btnCheck_inverted.GetCheck()) {
			ocv.inverted();
		}

		if (BST_CHECKED == pParentDlg->m_btnCheck_threshold.GetCheck()) {
			int nThresh, nMaxval, nThreshType;
			CString threshType;
			nThresh = pParentDlg->m_slider_threshold_thresh.GetPos();
			nMaxval = pParentDlg->m_slider_threshold_maxval.GetPos();
			nThreshType = pParentDlg->m_listbox_threshold_type.GetCurSel() + 1;
			ocv.threshold(nThresh, nMaxval, nThreshType);
		}

		ocv.outImg(&image);

		int nImgWidth = image.GetWidth();
		int nImgHeight = image.GetHeight();

		double nRateW = nWidth / nImgWidth;
		double nRateH = nHeight / nImgHeight;


		if (nRateW < 0 || nRateH < 0) {
			if (nImgWidth > nImgHeight) {
				if (nRateW < 0) {

				}
				else {

				}
			}
			else {

			}
		}


		int x = rect.left + (rect.Width() - nImgWidth) / 2;//计算图片插入位置x
		int y = rect.top + (rect.Height() - nImgHeight) / 2;//计算图片插入位置y

		image.BitBlt(dc, 0, 0, rect.Width(), rect.Height(), 0, 0);
		image.Destroy();    //没有Destroy()会有内存泄漏。Detach();不行的。
	}

}
