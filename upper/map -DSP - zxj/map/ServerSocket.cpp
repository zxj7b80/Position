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
	m_pDlg->AddClient();                                  //��������û�
	CSocket::OnAccept(nErrorCode);
}


void CServerSocket::OnClose(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
    m_pDlg->RemoveClient(this);                           //ɾ�������û�
	CSocket::OnClose(nErrorCode);
}


void CServerSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	m_pDlg->RecvData(this);                               // ��������
	CSocket::OnReceive(nErrorCode);
}
