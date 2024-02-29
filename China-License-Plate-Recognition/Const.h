
#ifndef _CONST_H_INCLUDED
#define _CONST_H_INCLUDED

#define WM_SELECT_PAGE	WM_USER + 0x30


#define HEADER_HEIGHT	40
#define FOOTER_HEIGHT	30
#define MENU_HEIGHT		40
#define TITLE	_T("China License Plate Recognition")

#define COLOR_BG_BLACK	RGB(0, 0, 0)
#define COLOR_TIMER		RGB(30, 200, 20)

#define COLOR_FT_WHITE	RGB(255, 255, 255)

#define COLOR_DOT		RGB(255, 255, 0)
void Init();

extern CFont the_font_20NC, the_font_16NC, the_font_14NC, the_font_12NC;

#endif