#pragma once

typedef struct tagRect
{
	long    left;
	long    top;
	long    right;
	long    bottom;
} Rect;


typedef struct tagPoint
{
	int x;
	int y;
} Point;

typedef struct tagSize
{
	int cx;
	int cy;
} Size;

struct InitSet
{
	Rect RoiRect;
	int nLetterHeightMin;
	int nLetterHeightMax;
	int skewAng;
	int mode;
};

#define MULTIRESULT			10

typedef struct tagLICENSE
{
	int	nLetNum;
	char szLicense[20];
	float pfDist;
	int	nTrust;
	Rect rtPlate;
	Rect blob[20];
	unsigned char	Type;
	unsigned char	bBkColor;
	unsigned char	bCarColor;
	unsigned char	bCarColDp;
} LICENSE, * LPLICENSE;

typedef struct tagCARPLATE
{
	int		nPlate;
	LICENSE	pPlate[MULTIRESULT];
	int		nProcTime;
}CARPLATE_DATA;

#ifdef __cplusplus
extern "C" {
#endif

	void* CNLPR_EngineHandleCreate();

	int	  CNLPR_EngineProcess(void* hEngineHandle, unsigned char* pRGB, int w, int h, InitSet* iniSet, CARPLATE_DATA* rscarData);

	void  CNLPR_EngineHandleDestroy(void* hEngineHandle);

#ifdef __cplusplus
}
#endif