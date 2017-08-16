
// mapDlg.cpp : implementation file
#include "stdafx.h"
#include "map.h"
#include "mapDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmapDlg dialog
CmapDlg::CmapDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmapDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_port = 0;
	m_usercount = 0;
	m_IP = _T("");
	m_lat = _T("");
	m_lng = _T("");
}

void CmapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PORT, m_port);
	DDX_Control(pDX, IDC_EventRecord, m_event);
	DDX_Text(pDX, IDC_UserCount, m_usercount);
	DDX_Text(pDX, IDC_IP, m_IP);
	DDX_Control(pDX, IDC_WEBMAP, m_webmap);
	DDX_Control(pDX, IDC_DataReceive, m_message);
	DDX_Text(pDX, IDC_LAT, m_lat);
	DDX_Text(pDX, IDC_LNG, m_lng);
}

BEGIN_MESSAGE_MAP(CmapDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_StartServer, &CmapDlg::OnBnClickedStartserver)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CmapDlg message handlers

BOOL CmapDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetTimer(1,1000,NULL);
//	SetTimer(2,1000,NULL);
	m_webmap.Navigate(_T("file:///C:/Users/Administrator/Desktop/GPStoBaidu.html"), NULL, NULL, NULL, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CmapDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CmapDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CmapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CmapDlg::OnBnClickedStartserver()
{
	// TODO: Add your control notification handler code here
	if (m_connect)
         {
          //       delete listenSocket;
                   listenSocket = NULL;
                   m_connect = false;
                   SetDlgItemText(IDC_StartServer, _T("打开服务器"));
                   UpdateEvent(_T("系统关闭服务器."));
                   return;
         }
         listenSocket = new CServerSocket();
         listenSocket->m_pDlg = this;
// 指定对话框为主对话框，不能少了这句
         UpdateData(true);
         if (!listenSocket->Create(m_port))                     
// 创建服务器的套接字，IP地址默认本机IP
         {
                   AfxMessageBox(_T("创建套接字错误！"));
                   listenSocket->Close();
                   return;
         }
         if (!listenSocket->Listen())
         {
                   AfxMessageBox(_T("监听失败！"));
                   listenSocket->Close();
                   return;
         }
         m_connect = true;
         SetDlgItemText(IDC_StartServer, _T("关闭服务器"));
         UpdateEvent(_T("系统打开服务器."));
}
void CmapDlg::AddClient()
{
         CServerSocket *pSocket = new CServerSocket;
         pSocket->m_pDlg = this;
         listenSocket->Accept(*pSocket);
         pSocket->AsyncSelect(FD_READ | FD_WRITE | FD_CLOSE);
         m_clientList.AddTail(pSocket);
         m_usercount = m_clientList.GetCount();
         UpdateData(false);
         UpdateEvent(_T("用户连接服务器."));
         //SendMSG(_T("Hello!"));
}
void CmapDlg::RemoveClient(CServerSocket* pSocket)
{
         POSITION nPos = m_clientList.GetHeadPosition();
         POSITION nTmpPos = nPos;
         while (nPos)
         {
                   CServerSocket* pSockItem = (CServerSocket*)m_clientList.GetNext(nPos);
                   if (pSockItem->m_hSocket == pSocket->m_hSocket)
                   {                          
                            pSockItem->Close();
                            delete pSockItem;
                            m_clientList.RemoveAt(nTmpPos);
                            m_usercount = m_clientList.GetCount();
                            UpdateData(false);
                            UpdateEvent(_T("用户离开."));
                            return;
                   }
                   nTmpPos = nPos;
         }
}

//====================================================================//
// 语法格式: static double Str_To_Double(char *buf)
// 实现功能： 把一个字符串转化成浮点数
// 参    数：字符串
// 返 回 值：转化后双精度值
//====================================================================//
double CmapDlg::Str_To_Double(char *buf)
{
	double rev = 0;
	double dat = 0;
	int integer = 1;
	char *str = buf;
	int i;
	int negative = 0;
	while (*str != '\0')
	{
		switch (*str)
		{
		case '0':
			dat = 0;
			break;
		case '1':
			dat = 1;
			break;
		case '2':
			dat = 2;
			break;
		case '3':
			dat = 3;
			break;
		case '4':
			dat = 4;
			break;
		case '5':
			dat = 5;
			break;
		case '6':
			dat = 6;
			break;
		case '7':
			dat = 7;
			break;
		case '8':
			dat = 8;
			break;
		case '9':
			dat = 9;
			break;
		case '.':
			dat = '.';
			break;
		case '-':
			negative = 1;
			break;
		default:
			break;

		}
		if (dat == '.')
		{
			integer = 0;
			i = 1;
			str++;
			continue;
		}
		if (integer == 1)
		{
			rev = rev * 10 + dat;
		}
		else
		{
			rev = rev + dat / (10 * i);
			i = i * 10;
		}
		str++;
	}
	if (negative == 1)
		rev = -rev;
	return rev;
}

void CmapDlg::RecvData(CServerSocket* pSocket)
{
	double df_latitude, df_longitude;
	int    du_latitude, du_longitude;
	double _latitude, _longitude;
	//char* Longitude;
	//char* Latitude;

         char* pData = NULL;
         pData = new char[1024];
         memset(pData, 0, sizeof(char)* 1024);
         UCHAR leng = 0;
		 leng = pSocket->Receive(pData, 1024, 0);
         str = pData;
// 在编辑框中显示接收到的数据
   //      ((CmapDlg*)theApp.GetMainWnd())->SetDlgItemTextW(IDC_DataReceive, str);
	//	 UpdateMessage(str);
		 CString strLongitude = str.Left(11);

		 CString strLatitude = str.Mid(12,21);

		 //---------------------------------------------------------------------------------------------
		 int Length1 = strLongitude.GetLength();
		int nBytes1 = WideCharToMultiByte(CP_ACP,0,strLongitude,Length1,NULL,0,NULL,NULL);
		char* Longitude = new char[ nBytes1 + 1];
		memset(Longitude,0,Length1 + 1);
		WideCharToMultiByte(CP_OEMCP, 0, strLongitude, Length1, Longitude, nBytes1, NULL, NULL); 
		Longitude[nBytes1] = 0;

		int Length2 = strLatitude.GetLength();
		int nBytes2 = WideCharToMultiByte(CP_ACP,0,strLatitude,Length2,NULL,0,NULL,NULL);
		char* Latitude = new char[ nBytes2 + 1];
		memset(Latitude,0,Length2 + 1);
		WideCharToMultiByte(CP_OEMCP, 0, strLatitude, Length2, Latitude, nBytes2, NULL, NULL); 
		Latitude[nBytes2] = 0;

		df_longitude=Str_To_Double(Longitude);
		df_latitude=Str_To_Double(Latitude);

		du_latitude = ((int)df_latitude) / 100;
		du_longitude = ((int)df_longitude) / 100;
		_latitude = du_latitude + (df_latitude - du_latitude*100) / 60.0;//+0.000025;//-0.000076;
		_longitude = du_longitude + (df_longitude - du_longitude*100) / 60.0;//+0.000028;

		m_lng.Format(_T("%f"), _longitude);
		m_lat.Format(_T("%f"), _latitude);
		//--------------------------------------------------------------------------------------------

		 GetDlgItem(IDC_LNG)->SetWindowText(m_lng);
		 GetDlgItem(IDC_LAT)->SetWindowText(m_lat);
		 
		 str1 = m_lng+","+m_lat;
		 GPSMarker();

         delete pData;
         pData = NULL;
   //      CSocket::RecvData(CServerSocket* pSocket)
  //       if (pSocket->Receive(pData, 1024, 0) != SOCKET_ERROR)
  //       {
  //                 str = pData;
           //        ControlPC(str);     // 依据指令控制电脑
           //        SendMSG(str);     // 转发数据给所有用户，包括发送数据的用户
  //       }
  //       delete pData;
  //       pData = NULL;
}
void CmapDlg::UpdateEvent(CString str)
{
         CString string;
         CTime time = CTime::GetCurrentTime();                  
// 获取系统当前时间
         str += _T("\r\n");                                                             
// 用于换行显示日志
         string = time.Format(_T("%Y/%m/%d %H:%M:%S  ")) + str;         
// 格式化当前时间
         int lastLine = m_event.LineIndex(m_event.GetLineCount() - 1);
//获取编辑框最后一行索引
         m_event.SetSel(lastLine+1,lastLine+2,0);                                     
//选择编辑框最后一行
         m_event.ReplaceSel(string);                                                             //替换所选那一行的内容
}
/*
void CmapDlg::UpdateMessage(CString str)
{
         int lastLine = m_event.LineIndex(m_event.GetLineCount() - 1);
//获取编辑框最后一行索引
         m_message.SetSel(lastLine+1,lastLine+2,0);                                     
//选择编辑框最后一行
         m_message.ReplaceSel(str);                                                             //替换所选那一行的内容
}*/
void CmapDlg::IPAddress()
{
		WORD wVersionRequested;
        WSADATA wsaData;
        char name[255];
    //    CString ip;
        PHOSTENT hostinfo;
        wVersionRequested = MAKEWORD( 2, 0 );
        if ( WSAStartup( wVersionRequested, &wsaData ) == 0 )
        {
              if( gethostname ( name, sizeof(name)) == 0)
              {
                    if((hostinfo = gethostbyname(name)) != NULL)
                    {
                          m_IP = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
                    }
              }
              
        } 
	GetDlgItem(IDC_IP)->SetWindowText(m_IP);
	WSACleanup();               //释放Winsock API
}

void CmapDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
    //CDialog::OnTimer(nIDEvent);
	if(nIDEvent == 1)
	{
		IPAddress();
	}
	
	CDialogEx::OnTimer(nIDEvent);
}
void CmapDlg::GPSMarker()
{
	char sRead[3000];

	int Length = str1.GetLength();
	int nBytes = WideCharToMultiByte(CP_ACP,0,str1,Length,NULL,0,NULL,NULL);
	char *new_pos = new char[ nBytes + 1];
	memset(new_pos,0,Length + 1);
	WideCharToMultiByte(CP_OEMCP, 0, str1, Length, new_pos, nBytes, NULL, NULL); 
	new_pos[nBytes] = 0;

	char s_search1='*';
	//读地图文件到缓冲区中
	CFile mfile(_T("C:/Users/Administrator/Desktop/GPStoBaidu.html"),CFile::modeRead);
	if (mfile.GetLength()<2)
	{
		return;
	}
    int f_size=mfile.GetLength();
	mfile.Read(sRead,f_size);
	mfile.Close();
    //修改缓冲区中的坐标数据
	for(int i=0;i<f_size;i++)
	{
		if (sRead[i]=='*')
		{
		//	m_length=i;
			for (int j=0;j<20;j++)
			{
				sRead[i+32+j]=new_pos[j];
			}
		}
	}
   
	//写地图文件
	CFile mfile1(_T("C:/Users/Administrator/Desktop/GPStoBaidu.html"),CFile::modeWrite);
	mfile1.Write(sRead,f_size);
	mfile1.Flush();
	mfile1.Close();
	//重新打开地图
	m_webmap.Navigate(_T("file:///C:/Users/Administrator/Desktop/GPStoBaidu.html"),NULL,NULL,NULL,NULL);
	UpdateData(FALSE);		               
}
