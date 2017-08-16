
// mapDlg.h : header file
//

#pragma once
#include "ServerSocket.h"
#include "webmap.h"
class CServerSocket;                  //一定要加上

// CmapDlg dialog
class CmapDlg : public CDialogEx
{
// Construction
public:
	CmapDlg(CWnd* pParent = NULL);	// standard constructor
	CServerSocket* listenSocket;     // 用于打开服务器
	CPtrList m_clientList;                 // 链表用于存储用户
	bool m_connect;                       // 用于标记服务器状态,布尔值，未初始化时为true
	void AddClient();                       // 增加用户，响应用户请求
	void RemoveClient(CServerSocket* pSocket);          // 移除下线的用户
	void RecvData(CServerSocket* pSocket);                 // 获取数据
	void UpdateEvent(CString str);  // 更新事件日志
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
