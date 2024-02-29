// ImageView.cpp : implementation file
//

#include "pch.h"
#include "ImageView.h"

// CImageView

IMPLEMENT_DYNAMIC(CImageView, CWnd)

CImageView::CImageView()
{
	m_dwColor = COLOR_BLACK;
	m_hBitmap = NULL;
	m_LPRCount = 0;
}

CImageView::~CImageView()
{
}


BEGIN_MESSAGE_MAP(CImageView, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CImageView message handlers




void CImageView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: Add your message handler code here
					   // Do not call CWnd::OnPaint() for painting messages
	dc.BitBlt(0, 0, m_rcView.Width(), m_rcView.Height(), &m_dcView, 0, 0, SRCCOPY);
}

void CImageView::InitView(COLORREF dwColor)
{
	m_dwColor = dwColor;
	UpdateView();
}

BOOL CImageView::UpdateView()
{
	CDC* pDC = GetDC();
	DrawBackground(pDC);
	if (m_hBitmap != NULL) {
		DrawImage(pDC);
		DrawRectangle(&m_dcView);
	}
	ReleaseDC(pDC);
	return RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_UPDATENOW);
}

void CImageView::SetImage(HBITMAP hBitmap)
{
	if (m_hBitmap != NULL)
		DeleteObject(m_hBitmap);
	m_hBitmap = hBitmap;
	GetObject(hBitmap, sizeof(BITMAP), &m_bInfo);
	UpdateView();
}

//void CImageView::SetImage(HBITMAP hBitmap, LPRResultData lprData, int lprCount)
//{
//	if (m_hBitmap != NULL)
//		DeleteObject(m_hBitmap);
//	m_hBitmap = hBitmap;
//	GetObject(hBitmap, sizeof(BITMAP), &m_bInfo);
//	m_LPRCount = lprCount;
//	memset(&m_LPRData, 0, sizeof(LPRResultData));
//	memcpy(&m_LPRData, &lprData, sizeof(LPRResultData));
//	UpdateView();
//}

void CImageView::DrawBackground(CDC * pDC)
{
	m_dcView.DeleteDC();
	if (m_bmView.GetSafeHandle() != NULL)
		m_bmView.DeleteObject();

	GetClientRect(&m_rcView);
	m_dcView.CreateCompatibleDC(pDC);
	m_bmView.CreateCompatibleBitmap(pDC, m_rcView.Width(), m_rcView.Height());
	m_dcView.SelectObject(m_bmView);
	m_dcView.FillSolidRect(m_rcView, m_dwColor);
	m_dcView.SelectStockObject(NULL_BRUSH);
}

void CImageView::DrawImage(CDC * pDC)
{
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(m_hBitmap);
	m_fScale = min(m_rcView.Width() / (float)m_bInfo.bmWidth, m_rcView.Height() / (float)m_bInfo.bmHeight);
	m_nScaleW = int(m_bInfo.bmWidth * m_fScale);
	m_nScaleH = int(m_bInfo.bmHeight * m_fScale);
	m_nLeft = (m_rcView.Width() - m_nScaleW) / 2;
	m_nTop = (m_rcView.Height() - m_nScaleH) / 2;
	m_dcView.SetStretchBltMode(HALFTONE);
	m_dcView.StretchBlt(m_nLeft, m_nTop, m_nScaleW, m_nScaleH, &dc, 0, 0, m_bInfo.bmWidth, m_bInfo.bmHeight, SRCCOPY);
}

void CImageView::DrawRectangle(CDC * pDC)
{
	//if (m_LPRCount <= 0)
	//	return;
	//CPen penRegion(PS_SOLID, 2, RGB(0, 0, 255));
	//CPen Selpen(PS_SOLID, 3, RGB(255, 0, 0));
	//pDC->SelectStockObject(NULL_BRUSH);
	//pDC->SelectObject(&Selpen);
	//for (int i = 0; i < m_LPRCount; i++) {
	//	int left = m_nLeft + (m_LPRData.PlateData[i].lprRect.left - 10) * m_fScale;
	//	int right = m_nLeft + (m_LPRData.PlateData[i].lprRect.right + 10) * m_fScale;
	//	int top = m_nTop + (m_LPRData.PlateData[i].lprRect.top - 10) * m_fScale;
	//	int bottom = m_nTop + (m_LPRData.PlateData[i].lprRect.bottom + 10) * m_fScale;
	//	CRect rt = CRect(left, top, right, bottom);
	//	pDC->Rectangle(rt);

	//	CFont font, *pOldFont;
	//	int hei = 20;
	//	VERIFY
	//	(
	//		font.CreateFont(
	//			hei,						// nHeight
	//			0,							// nWidth
	//			0,							// nEscapement
	//			0,							// nOrientation
	//			700,						// nWeight
	//			FALSE,						// bItalic
	//			FALSE,						// bUnderline
	//			0,							// cStrikeOut
	//			DEFAULT_CHARSET,			// nCharSet,//<cch>
	//			OUT_DEFAULT_PRECIS,			// nOutPrecision
	//			CLIP_DEFAULT_PRECIS,	    // nClipPrecision
	//			PROOF_QUALITY,				// nQuality
	//			VARIABLE_PITCH,				// nPitchAndFamily
	//			_T("Times New Roman")		// lpszFacename
	//		)
	//	);
	//	pOldFont = pDC->SelectObject(&font);
	//	CString strObjTemp = CString(m_LPRData.PlateData[i].lprStr, strlen(m_LPRData.PlateData[i].lprStr));
	//	CString temp;
	//	temp.Format(_T("-[conf: %.2f]"), m_LPRData.PlateData[i].conf);
	//	strObjTemp += temp + _T("%");
	//	pDC->SetTextColor(RGB(20, 20, 200));
	//	pDC->SetBkColor(RGB(200, 200, 20));
	//	pDC->TextOut(left, bottom, strObjTemp);
	//}
}


void CImageView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	UpdateView();
}
