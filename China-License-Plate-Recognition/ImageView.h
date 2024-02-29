#pragma once
#define		COLOR_BLACK		RGB(0, 0, 0)
#define		COLOR_RED		RGB(255, 0, 0)
#define		COLOR_GREEN		RGB(0, 255, 0)
#define		COLOR_BLUE		RGB(0, 0, 255)
#define		COLOR_YELLOW	RGB(255, 255, 0)
#define		COLOR_MAGENTA	RGB(255, 0, 255)
#define		COLOR_CYAN		RGB(0, 255, 255)
#define		COLOR_WHITE		RGB(255, 255, 255)
#define		COLOR_GRAY		RGB(122, 122, 122)
// CImageView
//#include "CRLPREngineExport.h"
class CImageView : public CWnd
{
	DECLARE_DYNAMIC(CImageView)

public:
	CImageView();
	virtual ~CImageView();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	void	InitView(COLORREF dwColor = COLOR_BLACK);
	BOOL	UpdateView();
	void	SetImage(HBITMAP hBitmap);
	//void	SetImage(HBITMAP hBitmap, LPRResultData lprData, int lprCount);
	void	DrawBackground(CDC* pDC);
	void	DrawImage(CDC* pDC);
	void	DrawRectangle(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	CRect	m_rcView;
	CDC		m_dcView;
	CBitmap	m_bmView;
	COLORREF m_dwColor;
	HBITMAP	m_hBitmap;
	BITMAP	m_bInfo;
	//LPRResultData m_LPRData;
	int		m_LPRCount;
	float	m_fScale;
	int     m_nScaleW;
	int     m_nScaleH;
	int		m_nLeft;
	int		m_nTop;
};


