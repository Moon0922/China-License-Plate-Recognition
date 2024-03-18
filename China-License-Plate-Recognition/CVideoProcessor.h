#pragma once

#define		VIDEO_STATE_NONE		0
#define		VIDEO_STATE_PLAY		1
#define		VIDEO_STATE_PAUSE		2
#define		VIDEO_STATE_STOP		3
#define		PROGRESS_RANGE			1000
#define		MESSAGE_DETECT_RESULT	WM_USER + 1601

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

class CVideoProcessor
{

public:
	CVideoProcessor(void);
	~CVideoProcessor(void);

public:
	void		VideoOpen(CString strVideoPath);
	void		VideoPlay();
	void		VideoPause();
	void		VideoStop();
	CString		GetVideoTotalTime();
	CString		GetVideoCurrentTime();
	CString		GetVideoTime();
	int			GetPos();
	void		StopThread();
	void		LPRPerFrame(cv::Mat& frame);
	void		SetVideoBuffer(cv::Mat& mat);
	static void VideoProcess(LPARAM lParam);

protected:
	void*  m_hEngineHandle;
	HANDLE m_hVideoThread;
public:
	cv::VideoCapture cap;
	cv::Mat		 frame;
	int			 m_nVideoState;
	CxImage		 m_xVideoImage;

	int			 m_nVideoFramePerSecond;
	int			 m_nVideoFrameCount;
	double		 m_dblVideoTotalTime;
	double		 m_dblVideoCurrentTime;
	CString		 m_strVideoTotalTime;
	CString		 m_strVideoCurrentTime;

	int					m_nThreshold;
	CRITICAL_SECTION	m_CS;

	void set_Threshold(int threshold)
	{
		m_nThreshold = threshold;
	}

	HANDLE get_thread_handle()
	{
		return m_hVideoThread;
	}
};

