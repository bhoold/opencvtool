// CpicViewer.cpp: 实现文件
//

#include "stdafx.h"
#include "opencvtool.h"
#include "CpicViewer.h"


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
	LPCWSTR className = _T("CPicWindow");
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


BOOL CpicViewer::update(CString file)
{
	m_pic_path = file;
	InvalidateRect(NULL, TRUE);
	return 0;
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
		CWnd::OnPaint();
	}
	else {
		int nWidth = rect.Width();
		int nHeight = rect.Height();

		CImage image;
		image.Load(m_pic_path);
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
