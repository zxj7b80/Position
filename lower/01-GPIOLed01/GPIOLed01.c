

/****************************************************************************
*
*文件名：Sci01.c
*
*功  能：使用SCIA模块和PC机进行串口通信，等待PC机上的串口调试软件向DSP发送数据，
*        DSP接收到上位机发送的数据之后，将这些数据发回PC机，显示在串口调试软件
*        中。
*
*说  明：本实验中SCIA模块的发送和接收采用查询方式实现，空闲线模式波特率为19200，
*        通信数据格式为1位停止位，8位数据位，无校验位
*
*作  者: zhang ling fei
*
*版  本: V1.0
*
****************************************************************************/
#include "DSP28_Device.h"
#include "string.h"

#define uchar unsigned char
#define uint  unsigned int


unsigned int Sci_VarRx[100];  //用于存放接收到的数据
unsigned int i;              
unsigned int Send_Flag;       //发送标志位。1:有数据需要发送 0:无数据需要发送

//以下是开机后发送到手机的内容，发送的号码在程序中修改。
unsigned char jingwei[] = "118.7324630,32.2121540\r\n";
unsigned char JW[50]={"my"};

unsigned char sms_text1[] = "abc123\r\n";

unsigned char sms_text2[] = "AT\r\n";

unsigned char sms_text3[] = "AT+CSCS=\"GSM\"\r\n";
unsigned char sms_text4[] = "AT+CMGF=1\r\n";
unsigned char sms_text5[] = "AT+CMGS=\"18751976179\"\r\n";


unsigned char sms_text6[] = "AT+CIPMUX=0\r\n";
unsigned char sms_text7[] = "AT+CIPRXGET=1\r\n";
unsigned char sms_text8[] = "AT+CIPQRCLOSE=1\r\n";
unsigned char sms_text9[] = "AT+CIPMODE=0\r\n";
unsigned char sms_text10[] = "AT+CIPSTART=\"TCP\",\"zxj7b80.xicp.net\",37240\r\n";
unsigned char sms_text11[] = "AT+CIPSEND\r\n";
unsigned char sms_text12[] = "AT+CIPCLOSE=1\r\n";
unsigned char sms_text13[] = "AT+CIPSHUT\r\n";

unsigned char res1[]="AT";
unsigned char res2[]="OK";
unsigned char res3[]="CONNECT OK";
unsigned char res4[]="SEND OK";

unsigned char sms_text14[] = "\r\n";

unsigned char flag_rec=0;
unsigned char num_rec=0;
   
//unsigned char code kaijihuamian[]="HLJU-505";
//unsigned char code receiving[]="Receiving!";
//unsigned char code nodata[]="No GPS data!";
//         char code TIME_AREA= 8;		//时区
unsigned char flag_data;	//数据标志位

//GPS数据存储数组
unsigned char tmp;
//正常读数据时J11,W10。
unsigned char JD[12];//="118.732463";		//经度  定义时要比所需长度多几位，为了有‘\0’
unsigned char JD_a;		//经度方向
unsigned char WD[11];//="32.212154";		//纬度
unsigned char WD_a;		//纬度方向
unsigned char date[6];		//日期
unsigned char time[6];		//时间
unsigned char time1[6];		//时间
unsigned char speed[5]={'0','0','0','0','0'};		//速度
unsigned char high[6];		//高度
unsigned char angle[5];		//方位角
unsigned char use_sat[2];	//使用的卫星数
unsigned char total_sat[2];	//天空中总卫星数
unsigned char lock;			//定位状态

//串口中断需要的变量
unsigned char seg_count;	//逗号计数器
unsigned char dot_count;	//小数点计数器
unsigned char byte_count;	//位数计数器
unsigned char cmd_number;	//命令类型
unsigned char mode;			//0：结束模式，1：命令模式，2：数据模式
unsigned char buf_full;		//1：整句接收完成，相应数据有效。0：缓存数据无效。
unsigned char cmd[5];		//命令类型存储数组

unsigned char R_close=0;
unsigned char T_close=0;

unsigned char jd_last_flag=0,wd_last_flag=0;

unsigned char samp='1';
unsigned char tmp_B=0;

//以下用于保存单片机收到模块发来的AT指令，通过这些指令单片机可以判断模块的状态
uchar GsmRcv[50]="OK";
uchar GsmRcvAt[50]="OK"; 
uchar GsmRcvCnt = 0;
uchar GsmAtFlag = 0;


void Uart1Send(unsigned char c);
void Uart1Sends(unsigned char *str);
void Uart2Send(unsigned char c1);
void Uart2Sends(unsigned char *str1);
void DelaySec(int sec);
void DataParse(void);
 int ScibRx_Ready(void);
 int ScibTx_Ready(void);
void wait4(void);
void Receive(uchar * RES);
/****************************************************************************
*
*名    称：main()
*
*功    能：完成初始化工作，并采用查询方式实现SCIA的发送和接收功能
*
*入口参数：无
*
*出口参数：无
*
****************************************************************************/
void main(void)
{
    InitSysCtrl();  //初始化系统函数

	DINT;
	IER = 0x0000;   //禁止CPU中断
	IFR = 0x0000;   //清除CPU中断标志
	
	InitPieCtrl();  //初始化PIE控制寄存器

	InitPieVectTable();  //初始化PIE中断向量表	 
	
	InitGpio();  //初始化Gpio口
	
	InitPeripherals(); //初始化SCIA
       
       
    GpioDataRegs.GPASET.bit.GPIOA0=1;    //点亮D1
    DelaySec(150);
    GpioDataRegs.GPACLEAR.bit.GPIOA0=1;  //熄灭D1
	DelaySec(50);


    
	GpioDataRegs.GPASET.bit.GPIOA0=1;    //点亮D1
    DelaySec(150);

	//GPRS通信
    Uart1Sends(sms_text2);
	Receive(res2);
	Uart1Sends(sms_text2);
	Receive(res2);
    Uart1Sends(sms_text6);
    Receive(res2);
	Uart1Sends(sms_text7);
    Receive(res2);
	Uart1Sends(sms_text8);
    Receive(res2);
	Uart1Sends(sms_text9);
    Receive(res2);
	GpioDataRegs.GPACLEAR.bit.GPIOA0=1;  //熄灭D1
    DelaySec(150);
    GpioDataRegs.GPASET.bit.GPIOA0=1;    //点亮D1
    Uart1Sends(sms_text10);          
	Receive(res3);
	GpioDataRegs.GPACLEAR.bit.GPIOA0=1;  //熄灭D1
    DelaySec(150);
	for(;;)
	{   
        GpioDataRegs.GPASET.bit.GPIOA0=1;    //点亮D1
	    //发送数据命令
		Uart1Sends(sms_text11);
        wait4();
		DelaySec(50);
        GpioDataRegs.GPACLEAR.bit.GPIOA0=1;  //熄灭D1

        //GPS数据解析------------------------------------------------------------------
        //ScibRegs.SCICTL1.bit.RXENA=1;
        while(1)
		{
		  if(ScibRx_Ready()==1)
		  {
		    tmp_B=ScibRegs.SCIRXBUF.all;
			if(tmp_B=='*')  break;
		  }
		}

		while(1) 
		{
          DataParse();
		  if(tmp=='*'&&lock==1)
		  {
		    lock=0;
		    //ScibRegs.SCICTL1.bit.RXENA=0;
			break;
		  } 
		}
		//---------------------------------------------------------------------------------*/
		

        Uart1Sends(JD);
        Uart1Send(',');
        Uart1Sends(WD);
        Uart1Send('\n');
        Uart1Send(0x1a);
        Receive(res4);

		DelaySec(50);
        /*
        //断开连接
        Uart2Sends(sms_text12);
        DelaySec(900);
		Uart2Sends(sms_text13);
        DelaySec(9000);
        */ 
	}
} 





//延时函数大概是1s钟，不过延时大的话不准...
void DelaySec(int sec)
{
	unsigned int i , j= 0;

	for(i=0; i<sec; i++)
	{
		for(j=0; j<65535; j++)
		{	
		}
	}
}

void Uart1Send(unsigned char c)
{
	SciaRegs.SCITXBUF=c;
	while(SciaTx_Ready()==0);
    //DelaySec(30);

}


void Uart1Sends(unsigned char *str)
{
	while(*str!='\0')
	{
		SciaRegs.SCITXBUF=*str;
		while(SciaTx_Ready()==0);
		str++;
		//DelaySec(30);
	}
}

void Uart2Send(unsigned char c1)
{
	ScibRegs.SCITXBUF=c1;
	while(ScibTx_Ready()==0);//等待发送完成信号（TI=1）出现
	//TI=0;	
	//DelaySec(30);//延时3秒
}

//串行口连续发送char型数组，遇到终止号/0将停止
void Uart2Sends(unsigned char *str1)
{
	while(*str1!='\0')
	{
		ScibRegs.SCITXBUF=*str1;
		while(ScibTx_Ready()==0);//等待发送完成信号（TI=1）出现
		//TI=0;
		str1++;
		//DelaySec(30);//延时3秒
	}
}

void wait4(void)
{
  unsigned char temple=0; 
  //SciaRegs.SCICTL1.bit.RXENA=1;

  while(1)
  {   
	if(SciaRx_Ready() == 1)
	{
	  temple=SciaRegs.SCIRXBUF.all;
      if(temple=='>')
	  {
	    //SciaRegs.SCICTL1.bit.RXENA=0;
	    break;
	  }
	}
  }
}

//GPS信息解析
void DataParse(void)
{
	if(ScibRx_Ready()==1)
	{
		tmp=ScibRegs.SCIRXBUF.all;
		switch(tmp)
		{
			case '$':
				cmd_number=0;		//命令类型清空
				mode=1;				//接收命令模式
				byte_count=0;		//接收位数清空
				flag_data=1;
				flag_rec=1;		    //数据标志位置一
				break;
			case ',':
				seg_count++;		//逗号计数加1
				byte_count=0;
				break;
			case '*':
				switch(cmd_number)
				{
					case 1:
						buf_full|=0x01;
						break;
					case 2:
						buf_full|=0x02;
						break;
					case 3:
						buf_full|=0x04;
						break;
				}
				mode=0;
				R_close=1;
				break;
			default:
				if(mode==1)	//命令种类判断
				{
					cmd[byte_count]=tmp;			//接收字符放入类型缓存
					if(byte_count>=4)
					{				//如果类型数据接收完毕，判断类型
						if(cmd[0]=='G')
						{
							if(cmd[1]=='P')
							{
								if(cmd[2]=='G')
								{
									if(cmd[3]=='G')
									{
										if(cmd[4]=='A')
										{
											cmd_number=1;      //data type
											mode=2;
											seg_count=0;
											byte_count=0;
										}
									}
									else if(cmd[3]=='S')
									{
										if(cmd[4]=='V')
										{
											cmd_number=2;
											mode=2;
											seg_count=0;
											byte_count=0;
										}
									}
								}
								else if(cmd[2]=='R')
								{
									if(cmd[3]=='M')
									{
										if(cmd[4]=='C')
										{
											cmd_number=3;
											mode=2;
											seg_count=0;
											byte_count=0;
										}
									}
								}
							}
						}
					}
				}
				else if(mode==2)
				{
					//接收数据处理
					switch (cmd_number)
					{
						case 1:				//类型1数据接收。GPGGA
							switch(seg_count)
							{
								case 2:		//纬度处理
									if(byte_count<9)
									{
										WD[byte_count]=tmp;
										//wd_flag=1;
									}
									break;
								case 3:		//纬度方向处理
									if(byte_count<1)
									{
										WD_a=tmp;
                                        //wd_flag=1;
									}
									break;
								case 4:		//经度处理
									if(byte_count<10)
									{
										JD[byte_count]=tmp;
										//jd_flag=1;
									}
									break;
								case 5:		//经度方向处理
									if(byte_count<1)
									{
										JD_a=tmp;
										//jd_flag=1;
									}
									break;
								case 6:		//定位判断
								
									break;
								case 7:		//定位使用的卫星数
									if(byte_count<2)
									{
										use_sat[byte_count]=tmp;
									}
									break;
								case 9:		//高度处理
									if(byte_count<6)
									{
										high[byte_count]=tmp;
									}
									break;
							}
							break;
						case 2:				//类型2数据接收。GPGSV
							switch(seg_count)
							{
								case 3:		//天空中的卫星总数
									if(byte_count<2)
									{
										total_sat[byte_count]=tmp;
									}
									break;
							}
							break;
						case 3:				//类型3数据接收。GPRMC
							switch(seg_count)
							{
								case 1:		//时间处理
									if(byte_count<6)
									{				
										time[byte_count]=tmp;	
									}
									break;
								case 2:		//定位判断						
									if(byte_count<1)
									{
									  if (tmp=='V') {lock=0;}
									  else
									  {
									    lock=1;
									   }
									}
									break;
								case 3:		//纬度处理						
									if(byte_count<9)
									{
										WD[byte_count]=tmp;
										if(byte_count==8) 
										{
										  WD[9]='0';
                                          WD[10]='\0';
										}
										//wd_flag=1;
									}
									break;
								case 4:		//纬度方向处理						
									if(byte_count<1)
									{
										WD_a=tmp;
										//wd_flag=1;
									}
									break;
								case 5:		//经度处理						
									if(byte_count<10)
									{
										JD[byte_count]=tmp;
										if(byte_count==9) 
										{
										  JD[10]='0';
                                          JD[11]='\0';
										}
										//jd_flag=1;
									}
									break;
								case 6:		//经度方向处理						
									if(byte_count<1)
									{
										JD_a=tmp;
										//jd_flag=1;
									}
									break;
								case 7:		//速度处理						
									if(byte_count<5)
									{
										speed[byte_count]=tmp;
									}
									break;
								case 8:		//方位角处理						
									if(byte_count<5)
									{
										angle[byte_count]=tmp;
									}
									break;
								case 9:		//方位角处理						
									if(byte_count<6)
									{
										date[byte_count]=tmp;
									}
									break;

							}
							break;
					}
				}
				byte_count++;		
				break;
		}
	}
}


/*串行通讯中断，收发完成将进入该中断*/
void Receive(uchar * RES)
{
	uchar i = 0;
    while(1)
	{
	  if(SciaRx_Ready()==1)	//收到信息
	  {	
		GsmRcv[GsmRcvCnt] = SciaRegs.SCIRXBUF.all;
		GsmRcvCnt++;
		//收到了完整的AT指令，完整的AT指令是以0x0d 0x0a结尾的。故作此判断，在接收的过程中是否收到0x0d 0x0a
		if(GsmRcv[GsmRcvCnt-2] == 0x0D && GsmRcv[GsmRcvCnt-1] == 0x0A && GsmRcvCnt >= 2)
		{
			//一旦收到0x0d 0x0a，就将数据保存起来。用户主函数的判断。			
			for(i=0; i<GsmRcvCnt; i++)
			{
				GsmRcvAt[i] = GsmRcv[i];
				GsmRcv[i] = 0;	
			}
			GsmRcvCnt = 0;
			//GsmAtFlag = 1;//收到了完整的at指令，通过这个标志位置1，这样主函数就知道去判断了。
			if(strstr((char *)GsmRcvAt, (char *)RES) )//GsmAtFlag == 1 && 
	        {
	          break;
	        }								
		}
		else if(GsmRcvCnt >= 50)//因为内存有限，收到了50个字符还是没有看到0x0a 0x0d的话，就重新开始接收吧。
		{
			GsmRcvCnt = 0;
		}
      }
	}
}
//===========================================================================
// No more.
//===========================================================================

