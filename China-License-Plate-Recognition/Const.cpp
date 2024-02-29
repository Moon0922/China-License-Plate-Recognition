
#include "pch.h"

CFont the_font_20NC, the_font_16NC, the_font_14NC, the_font_12NC;

void Init()
{
	the_font_20NC.CreateFont(20, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("Times New Roman"));
	the_font_16NC.CreateFont(16, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("Times New Roman"));
	the_font_14NC.CreateFont(14, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("Times New Roman"));
	the_font_12NC.CreateFont(12, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, _T("Times New Roman"));
}

CString GetTextLimit(CString strText)
{
	return strText;
}

