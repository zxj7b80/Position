// ServerSocket.cpp : implementation file
//

#include "stdafx.h"
#include "map.h"
#include "ServerSocket.h"


// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket member functions


void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	m_pDlg->AddClient();                                  //添加上线用户
	CSocket::OnAccept(nErrorCode);
}


void CServerSocket::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
    m_pDlg->RemoveClient(this);                           //删除下线用户
	CSocket::OnClose(nErrorCode);
}


void CServerSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	m_pDlg->RecvData(this);                               // 接收数据
	CSocket::OnReceive(nErrorCode);
}
