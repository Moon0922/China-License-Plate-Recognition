
#ifndef xMEMDC_H_INLCUDED
#define xMEMDC_H_INLCUDED
#pragma once

class CxMemDC : public CDC
{
public:
	CxMemDC(CDC* pDC, int nWidth, int nHeight);
	virtual ~CxMemDC();


	void	DrawTheText(CString strText, CRect crcArea, UINT nFormat, CFont* pFont, COLORREF crText);
	void	DrawTheRectangle(CRect crcArea, COLORREF crRect, COLORREF crEdge);
	void	DrawTheLine(int x1, int y1, int x2, int y2, COLORREF cr, int nWidth = 1);
	void	DrawTheDotRect(CRect crcData, COLORREF crText);
	void	DrawTheCirCle(int x, int y, int r, COLORREF crArea, COLORREF crEdge);
	void	DrawThePng(int nResId, CRect crcPng);
	int		DrawTheTextEx(int nY, CString strText, CRect crcText, CFont* pFont, COLORREF crText);

	void	DrawBlt(CDC* pDC, CRect crcBlt);

protected:

	CBitmap		m_cbmMem, *m_pcbmOld;
};

#endif