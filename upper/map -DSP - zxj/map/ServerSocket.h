#pragma once

// CServerSocket command target
#include "mapDlg.h"                              // ���Ի���ͷ�ļ�
class CmapDlg;                                      //�����˼���
class CServerSocket : public CSocket
{
public:
	CmapDlg* m_pDlg;                       // ���Ի���ָ�����
	CServerSocket();
	virtual ~CServerSocket();
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


