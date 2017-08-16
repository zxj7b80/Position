
// mapDlg.h : header file
//

#pragma once
#include "ServerSocket.h"
#include "webmap.h"
class CServerSocket;                  //һ��Ҫ����

// CmapDlg dialog
class CmapDlg : public CDialogEx
{
// Construction
public:
	CmapDlg(CWnd* pParent = NULL);	// standard constructor
	CServerSocket* listenSocket;     // ���ڴ򿪷�����
	CPtrList m_clientList;                 // �������ڴ洢�û�
	bool m_connect;                       // ���ڱ�Ƿ�����״̬,����ֵ��δ��ʼ��ʱΪtrue
	void AddClient();                       // �����û�����Ӧ�û�����
	void RemoveClient(CServerSocket* pSocket);          // �Ƴ����ߵ��û�
	void RecvData(CServerSocket* pSocket);                 // ��ȡ����
	void UpdateEvent(CString str);  // �����¼���־
//	void UpdateMessage(CString str);  
	void IPAddress();
	void GPSMarker();
	double Str_To_Double(char *buf);
	BOOL WChar2MByte(LPCWSTR srcBuff, LPSTR destBuff, int nlen); 
// Dialog Data
	enum { IDD = IDD_MAP_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	UINT m_port;
	CEdit m_event;

	UINT m_usercount;
	afx_msg void OnBnClickedStartserver();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_IP;
	CWebmap m_webmap;
	CEdit m_message;

//	float Longitude;
//	float Latitude;
	CString str;
	CString m_lat;
	CString m_lng;
	CString str1;
};
