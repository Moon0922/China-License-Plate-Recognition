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

void CImageView::SetImage(HBITMAP hBitmap, CARPLATE_DATA carData)
{
	if (m_hBitmap != NULL)
		DeleteObject(m_hBitmap);
	m_hBitmap = hBitmap;
	GetObject(hBitmap, sizeof(BITMAP), &m_bInfo);
	memset(&m_carPlateData, 0, sizeof(CARPLATE_DATA));
	memcpy(&m_carPlateData, &carData, sizeof(CARPLATE_DATA));
	UpdateView();
}

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
	if (m_carPlateData.nPlate <= 0)
		return;
	CPen penRegion(PS_SOLID, 2, RGB(0, 0, 255));
	CPen Selpen(PS_SOLID, 3, RGB(255, 0, 0));
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->SelectObject(&Selpen);
	for (int i = 0; i < m_carPlateData.nPlate; i++) {
		int left = m_nLeft + (m_carPlateData.pPlate[i].rtPlate.left - 10) * m_fScale;
		int right = m_nLeft + (m_carPlateData.pPlate[i].rtPlate.right + 10) * m_fScale;
		int top = m_nTop + (m_carPlateData.pPlate[i].rtPlate.top - 10) * m_fScale;
		int bottom = m_nTop + (m_carPlateData.pPlate[i].rtPlate.bottom + 10) * m_fScale;
		CRect rt = CRect(left, top, right, bottom);
		pDC->Rectangle(rt);

		//for (int j = 0; j < m_carPlateData.pPlate[i].nLetNum; j++) 
		//{
		//	int left = m_nLeft + (m_carPlateData.pPlate[i].blob[j].left) * m_fScale;
		//	int right = m_nLeft + (m_carPlateData.pPlate[i].blob[j].right) * m_fScale;
		//	int top = m_nTop + (m_carPlateData.pPlate[i].blob[j].top) * m_fScale;
		//	int bottom = m_nTop + (m_carPlateData.pPlate[i].blob[j].bottom) * m_fScale;
		//	CRect rt = CRect(left, top, right, bottom);
		//	pDC->Rectangle(rt);
		//}

		CFont font, *pOldFont;
		int hei = 20;
		VERIFY
		(
			font.CreateFont(
				hei,						// nHeight
				0,							// nWidth
				0,							// nEscapement
				0,							// nOrientation
				700,						// nWeight
				FALSE,						// bItalic
				FALSE,						// bUnderline
				0,							// cStrikeOut
				DEFAULT_CHARSET,			// nCharSet,//<cch>
				OUT_DEFAULT_PRECIS,			// nOutPrecision
				CLIP_DEFAULT_PRECIS,	    // nClipPrecision
				PROOF_QUALITY,				// nQuality
				VARIABLE_PITCH,				// nPitchAndFamily
				_T("Times New Roman")		// lpszFacename
			)
		);
		pOldFont = pDC->SelectObject(&font);
		
		CString lprResult = CString(m_carPlateData.pPlate[i].szLicense, strlen(m_carPlateData.pPlate[i].szLicense) - 1);
		MultiByteToWideChar(CP_UTF8, 0, m_carPlateData.pPlate[i].szLicense, -1, lprResult.GetBuffer(), 20);
		CString temp;
		temp.Format(_T("-[conf: %d"), m_carPlateData.pPlate[i].nTrust);
		lprResult += temp + _T("%]");
		pDC->SetTextColor(RGB(20, 20, 200));
		pDC->SetBkColor(RGB(200, 200, 20));
		pDC->TextOut(left, bottom, lprResult);
	}
}


void CImageView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	UpdateView();
}
