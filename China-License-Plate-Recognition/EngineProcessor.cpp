#include "pch.h"
#include "EngineProcessor.h"
//#include "CostaRicaLPR.h"
#include "ImageView.h"
#include "opencv2/opencv.hpp"
#include <time.h>

using namespace cv;
CEngineProcessor::CEngineProcessor()
{
	m_hLPRThread = 0;
	m_nProcStatus = PROC_NONE;
	m_curFileIndex = -1;
	//m_hEngineHandle = LPR_EngineCreate();
	InitializeCriticalSection(&m_CS);
}

CEngineProcessor::~CEngineProcessor()
{
	Stop();
	//LPR_EngineDestroy(m_hEngineHandle);
	DeleteCriticalSection(&m_CS);
}

static CString FindExtension(const CString& name)
{
	int len = name.GetLength();
	int i;
	for (i = len - 1; i >= 0; i--) {
		if (name[i] == '.') {
			return name.Mid(i + 1);
		}
	}
	return CString(_T(""));
}

static CString FindOnlyName(const CString& name)
{
	int len = name.GetLength();
	int i;
	CString strTmp;
	for (i = len - 1; i >= 0; i--) {
		if (name[i] == '\\') {
			strTmp = name.Mid(i + 1);
			break;
		}
	}

	len = strTmp.GetLength();
	for (i = 0; i < len; i++) {
		if (strTmp[i] == '.') {
			return strTmp.Left(i);
		}
	}

	return CString(_T(""));
}

static int FindType(const CString& ext)
{
	int type = 0;
	if (ext == _T("bmp"))						type = CXIMAGE_FORMAT_BMP;
#if CXIMAGE_SUPPORT_JPG
	else if (ext == _T("jpg") || ext == _T("jpeg"))	type = CXIMAGE_FORMAT_JPG;
#endif
#if CXIMAGE_SUPPORT_GIF
	else if (ext == _T("gif"))					type = CXIMAGE_FORMAT_GIF;
#endif
#if CXIMAGE_SUPPORT_PNG
	else if (ext == _T("png"))					type = CXIMAGE_FORMAT_PNG;
#endif
#if CXIMAGE_SUPPORT_MNG
	else if (ext == _T("mng") || ext == _T("jng"))	type = CXIMAGE_FORMAT_MNG;
#endif
#if CXIMAGE_SUPPORT_ICO
	else if (ext == _T("ico"))					type = CXIMAGE_FORMAT_ICO;
#endif
#if CXIMAGE_SUPPORT_TIF
	else if (ext == _T("tiff") || ext == _T("tif"))	type = CXIMAGE_FORMAT_TIF;
#endif
#if CXIMAGE_SUPPORT_TGA
	else if (ext == _T("tga"))					type = CXIMAGE_FORMAT_TGA;
#endif
#if CXIMAGE_SUPPORT_PCX
	else if (ext == _T("pcx"))					type = CXIMAGE_FORMAT_PCX;
#endif
#if CXIMAGE_SUPPORT_WBMP
	else if (ext == _T("wbmp"))					type = CXIMAGE_FORMAT_WBMP;
#endif
#if CXIMAGE_SUPPORT_WMF
	else if (ext == _T("wmf") || ext == _T("emf"))	type = CXIMAGE_FORMAT_WMF;
#endif
#if CXIMAGE_SUPPORT_J2K
	else if (ext == _T("j2k") || ext == _T("jp2"))	type = CXIMAGE_FORMAT_J2K;
#endif
#if CXIMAGE_SUPPORT_JBG
	else if (ext == _T("jbg"))					type = CXIMAGE_FORMAT_JBG;
#endif
#if CXIMAGE_SUPPORT_JP2
	else if (ext == _T("jp2") || ext == _T("j2k"))	type = CXIMAGE_FORMAT_JP2;
#endif
#if CXIMAGE_SUPPORT_JPC
	else if (ext == _T("jpc") || ext == _T("j2c"))	type = CXIMAGE_FORMAT_JPC;
#endif
#if CXIMAGE_SUPPORT_PGX
	else if (ext == _T("pgx"))					type = CXIMAGE_FORMAT_PGX;
#endif
#if CXIMAGE_SUPPORT_RAS
	else if (ext == _T("ras"))					type = CXIMAGE_FORMAT_RAS;
#endif
#if CXIMAGE_SUPPORT_PNM
	else if (ext == _T("pnm") || ext == _T("pgm") || ext == _T("ppm")) type = CXIMAGE_FORMAT_PNM;
#endif
	else type = CXIMAGE_FORMAT_UNKNOWN;
	return type;
}

void CEngineProcessor::CollectData(CString strDir)
{
	m_strImageDir = strDir;
	m_vecImagePath.clear();
	m_wndListCtrl->DeleteAllItems();
	CString strDefaultPath;
	strDefaultPath = m_strImageDir;

	CString	strIndexFind = strDefaultPath + _T("\\*.*");
	CFileFind	finder;
	BOOL bWorking = finder.FindFile(strIndexFind);

	CString strFilename;
	CString strOnlyname;
	CString strExtension;
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		strFilename = finder.GetFilePath();
		strExtension = FindExtension(strFilename);
		strOnlyname = FindOnlyName(strFilename);
		strExtension.MakeLower();
		if (strExtension != _T(""))
		{
			int type = FindType(strExtension);
			if (type != 0)
			{
				CString strImageFilename = finder.GetFileName();
				m_vecImagePath.push_back(strImageFilename);
				CString temp;
				int index = (int)m_vecImagePath.size();
				temp.Format(_T("%04d"), index);
				m_wndListCtrl->InsertItem(index - 1, temp);
				m_wndListCtrl->SetItemText(index - 1, 1, strImageFilename);
			}
		}
	}
	
}

void CEngineProcessor::Start()
{
	if (m_vecImagePath.size() == 0)
		return;
	m_nProcStatus = PROC_START;
	if (m_hLPRThread)
		return;
	m_hLPRThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)LPRProc, this, 0, 0);
}

void CEngineProcessor::Stop()
{
	m_nProcStatus = PROC_STOP;
}

void CEngineProcessor::LPRProc(LPARAM lParam)
{
	CEngineProcessor* pThis = (CEngineProcessor*)lParam;
	int nImages = pThis->m_vecImagePath.size();
	for (int i = 0; i < nImages; i++)
	{
		if (pThis->m_nProcStatus == PROC_STOP)
		{
			Sleep(10);
			break;
		}
		pThis->StillImage(i);
	}
	pThis->m_nProcStatus = PROC_STOP;
	pThis->m_hLPRThread = 0;
}

void CEngineProcessor::StillImage(int index)
{
	if (index < 0 || index > m_vecImagePath.size() - 1) return;
	m_curFileIndex = index;
	m_wndListCtrl->SetFocus();

	CxImage xImage;
	CString strImgName = m_strImageDir + _T("\\") + m_vecImagePath.at(index);
	char szImgPath[_MAX_PATH] = { 0 };
	WideCharToMultiByte(CP_ACP, 0, strImgName.GetBuffer(), strImgName.GetLength(), szImgPath, _MAX_PATH, NULL, NULL);
	Mat	mImage = imread(szImgPath);
	int w = mImage.cols;
	int h = mImage.rows;
	xImage.Create(w, h, 24);
	for (int y = 0; y < h; y++)
		memcpy(xImage.GetBits(y), mImage.data + (h - 1 - y) * 3 * mImage.cols, 3 * mImage.cols);
	Mat gray;
	cvtColor(mImage, gray, COLOR_BGR2GRAY);

	//LPRResultData m_ResultData;
	//int pTime = (int)clock();
	//int nPlateNum = LPR_Process(m_hEngineHandle, gray.data, gray.cols, gray.rows, &m_ResultData);
	//pTime = (int)clock() - pTime;
	//CString temp;
	//temp.Format(_T("%dms"), pTime);
	//m_wndListCtrl->SetItemText(index, 3, temp);
	//CString lprResult = _T("LPR_Failed"), strConf = _T("");
	//if (nPlateNum) {
	//	lprResult = _T("");
	//	for (int j = 0; j < nPlateNum; j++)
	//	{
	//		lprResult += CString(m_ResultData.PlateData[j].lprStr, strlen(m_ResultData.PlateData[j].lprStr));
	//		temp.Format(_T("%.2f"), m_ResultData.PlateData[j].conf);
	//		strConf += temp + _T("%");
	//		if (index < nPlateNum - 1)
	//		{
	//			strConf += _T("_");
	//			lprResult += _T("_");
	//		}
	//	}
	//}
	//m_wndListCtrl->SetItemText(index, 4, strConf);
	//m_wndListCtrl->SetItemText(index, 2, lprResult);
	//((CImageView*)m_pImageView)->SetImage(xImage.MakeBitmap(), m_ResultData, nPlateNum);
	((CImageView*)m_pImageView)->SetImage(xImage.MakeBitmap());
}
