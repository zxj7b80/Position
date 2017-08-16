#pragma once

// CServerSocket command target
#include "mapDlg.h"                              // 主对话框头文件
class CmapDlg;                                      //别忘了加上
class CServerSocket : public CSocket
{
public:
	CmapDlg* m_pDlg;                       // 主对话框指针对象
	CServerSocket();
	virtual ~CServerSocket();
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


