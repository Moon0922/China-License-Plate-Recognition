#include "pch.h"
#include "CVideoProcessor.h"

#include "China-License-Plate-Recognition.h"
#include "China-License-Plate-RecognitionDlg.h"

CVideoProcessor::CVideoProcessor(void)
{
	m_nVideoState = VIDEO_STATE_NONE;
	m_hVideoThread = 0;
	m_nVideoFramePerSecond = 0;
	m_nVideoFrameCount = 0;
	m_dblVideoTotalTime = 0;
	m_dblVideoCurrentTime = 0;
	//m_hEngineHandle = LPR_EngineCreate();
	InitializeCriticalSection(&m_CS);
}

CVideoProcessor::~CVideoProcessor(void)
{
	StopThread();
	//LPR_EngineDestroy(m_hEngineHandle);
	DeleteCriticalSection(&m_CS);
}

CString GetStringTime(int nTotalTime)
{
	CString strTime;

	int second = nTotalTime % 60;
	CString strSecond;
	if (second >= 10)
		strSecond.Format(_T("%d"), second);
	else
		strSecond.Format(_T("0%d"), second);

	int minute = (nTotalTime / 60) % 60;
	CString strMinute;
	if (minute >= 10)
		strMinute.Format(_T("%d"), minute);
	else
		strMinute.Format(_T("0%d"), minute);

	int hour = (nTotalTime / 60) / 60;
	CString strHour;
	if (hour >= 10)
		strHour.Format(_T("%d"), hour);
	else
		strHour.Format(_T("0%d"), hour);

	strTime = strHour + _T(":") + strMinute + _T(":") + strSecond;

	return strTime;
}

void CVideoProcessor::VideoOpen(CString strVideoPath)
{
	VideoStop();

	char pszVideoPath[1000] = { 0 };
	WideCharToMultiByte(CP_ACP, 0, strVideoPath.GetBuffer(), strVideoPath.GetLength(), pszVideoPath, 1000, NULL, NULL);

	cap.open(pszVideoPath);

	if (!cap.isOpened())
	{
		AfxMessageBox(_T("Can't open video"));
		return;
	}

	cap >> frame;
	if (frame.empty())
	{
		m_nVideoFramePerSecond = 0;
		m_nVideoFrameCount = 0;
		m_dblVideoTotalTime = 0;
		m_dblVideoCurrentTime = 0;
		return;
	}

	SetVideoBuffer(frame);
	m_nVideoFramePerSecond = cap.get(CAP_PROP_FPS);
	m_nVideoFrameCount = cap.get(CAP_PROP_FRAME_COUNT);
	m_dblVideoTotalTime = m_nVideoFrameCount / (double)m_nVideoFramePerSecond;
	m_dblVideoCurrentTime = 0;

	m_nVideoState = VIDEO_STATE_NONE;
}

void CVideoProcessor::VideoPlay()
{
	m_nVideoState = VIDEO_STATE_PLAY;
	if (m_hVideoThread)
		return;

	m_hVideoThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)VideoProcess, this, 0, 0);
}

void CVideoProcessor::VideoPause()
{
	m_nVideoState = VIDEO_STATE_PAUSE;
}

void CVideoProcessor::VideoStop()
{
	if (m_hVideoThread)
	{
		m_nVideoState = VIDEO_STATE_STOP;
		WaitForSingleObject(m_hVideoThread, INFINITE);
		CloseHandle(m_hVideoThread);
		m_hVideoThread = 0;
	}
}

CString CVideoProcessor::GetVideoTotalTime()
{
	return GetStringTime((int)m_dblVideoTotalTime);
}

CString CVideoProcessor::GetVideoCurrentTime()
{
	return GetStringTime((int)m_dblVideoCurrentTime);
}

CString CVideoProcessor::GetVideoTime()
{
	return GetVideoCurrentTime() + _T("/") + GetVideoTotalTime();
}

int CVideoProcessor::GetPos()
{
	double dblPos = cap.get(CAP_PROP_POS_FRAMES) / (double)cap.get(CAP_PROP_FRAME_COUNT) * PROGRESS_RANGE + 0.5;
	return min(int(dblPos), PROGRESS_RANGE);
}

void CVideoProcessor::StopThread()
{
	if (m_hVideoThread)
	{
		m_nVideoState = VIDEO_STATE_STOP;
		WaitForSingleObject(m_hVideoThread, INFINITE);
		CloseHandle(m_hVideoThread);
		m_hVideoThread = 0;
	}
}

void CVideoProcessor::LPRPerFrame(cv::Mat& frame)
{
	//Mat gray;
	//cvtColor(frame, gray, COLOR_BGR2GRAY);

	//LPRResultData m_ResultData;

	//int nPlateNum = LPR_Process(m_hEngineHandle, gray.data, gray.cols, gray.rows, &m_ResultData);

	//if (nPlateNum) {

	//	for (int j = 0; j < nPlateNum; j++)
	//	{
	//		int left = m_ResultData.PlateData[j].lprRect.left - 10;
	//		int top = m_ResultData.PlateData[j].lprRect.top - 10;
	//		int width = m_ResultData.PlateData[j].lprRect.right + 10 - left;
	//		int height = m_ResultData.PlateData[j].lprRect.bottom + 10 - top;
	//		rectangle(frame, Rect(left, top, width, height), Scalar(255, 0, 0));
	//		char szResult[100];
	//		sprintf(szResult, "%s-[conf: %.2f]\%", m_ResultData.PlateData[j].lprStr, m_ResultData.PlateData[j].conf);
	//		putText(frame, szResult, Point(left, top), FONT_HERSHEY_PLAIN, 1.0, Scalar(0, 255, 255));
	//	}
	//}
}

void CVideoProcessor::SetVideoBuffer(cv::Mat& mat)
{
	if (m_xVideoImage.GetWidth() != mat.cols || m_xVideoImage.GetHeight() != mat.rows)
		m_xVideoImage.Create(mat.cols, mat.rows, 24);

	for (int y = 0; y < mat.rows; y++)
		memcpy(m_xVideoImage.GetBits(y), mat.data + (mat.rows - 1 - y) * 3 * mat.cols, 3 * mat.cols);
}

void CVideoProcessor::VideoProcess(LPARAM lParam)
{
	CVideoProcessor* pProcess = (CVideoProcessor*)lParam;

	int64 nTime = 0;
	double dblTime = 0.0, totalTime = 0;
	while (true)
	{
		//video pause
		while (pProcess->m_nVideoState == VIDEO_STATE_PAUSE)
			Sleep(10);
		//video stop
		if (pProcess->m_nVideoState == VIDEO_STATE_STOP)
		{
			Sleep(10);
			break;
		}

		//******************** main process start ********************//
		for (int k = 0; k < 2; k++)
			pProcess->cap >> pProcess->frame;

		if (pProcess->frame.empty())
		{
			Sleep(10);
			break;
		}

		pProcess->m_dblVideoCurrentTime = pProcess->cap.get(CAP_PROP_POS_FRAMES) / (double)pProcess->m_nVideoFramePerSecond;
		nTime = getTickCount();

		pProcess->LPRPerFrame(pProcess->frame);

		nTime = getTickCount() - nTime;
		dblTime = nTime / getTickFrequency() * 1000.0;
#if 0
		char time[100] = { 0 };
		sprintf(time, "Time = %.2f ms", dblTime);
		rectangle(pProcess->frame, cv::Point(0, 0), cv::Point(600, 40), Scalar(0, 0, 255), -1);
		cv::putText(pProcess->frame, time, cv::Point(15, 35), CV_FONT_HERSHEY_PLAIN, 3, Scalar(0, 255, 255), 3);
#endif
		pProcess->SetVideoBuffer(pProcess->frame);

		//******************** main process end ********************//
		if (dblTime < 1000.0 / pProcess->m_nVideoFramePerSecond)
			Sleep(1000.0 / pProcess->m_nVideoFramePerSecond - dblTime);
	}
	pProcess->m_hVideoThread = 0;
}
