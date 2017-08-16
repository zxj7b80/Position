

/****************************************************************************
*
*�ļ�����Sci01.c
*
*��  �ܣ�ʹ��SCIAģ���PC�����д���ͨ�ţ��ȴ�PC���ϵĴ��ڵ��������DSP�������ݣ�
*        DSP���յ���λ�����͵�����֮�󣬽���Щ���ݷ���PC������ʾ�ڴ��ڵ������
*        �С�
*
*˵  ������ʵ����SCIAģ��ķ��ͺͽ��ղ��ò�ѯ��ʽʵ�֣�������ģʽ������Ϊ19200��
*        ͨ�����ݸ�ʽΪ1λֹͣλ��8λ����λ����У��λ
*
*��  ��: zhang ling fei
*
*��  ��: V1.0
*
****************************************************************************/
#include "DSP28_Device.h"
#include "string.h"

#define uchar unsigned char
#define uint  unsigned int


unsigned int Sci_VarRx[100];  //���ڴ�Ž��յ�������
unsigned int i;              
unsigned int Send_Flag;       //���ͱ�־λ��1:��������Ҫ���� 0:��������Ҫ����

//�����ǿ������͵��ֻ������ݣ����͵ĺ����ڳ������޸ġ�
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
//         char code TIME_AREA= 8;		//ʱ��
unsigned char flag_data;	//���ݱ�־λ

//GPS���ݴ洢����
unsigned char tmp;
//����������ʱJ11,W10��
unsigned char JD[12];//="118.732463";		//����  ����ʱҪ�����賤�ȶ༸λ��Ϊ���С�\0��
unsigned char JD_a;		//���ȷ���
unsigned char WD[11];//="32.212154";		//γ��
unsigned char WD_a;		//γ�ȷ���
unsigned char date[6];		//����
unsigned char time[6];		//ʱ��
unsigned char time1[6];		//ʱ��
unsigned char speed[5]={'0','0','0','0','0'};		//�ٶ�
unsigned char high[6];		//�߶�
unsigned char angle[5];		//��λ��
unsigned char use_sat[2];	//ʹ�õ�������
unsigned char total_sat[2];	//�������������
unsigned char lock;			//��λ״̬

//�����ж���Ҫ�ı���
unsigned char seg_count;	//���ż�����
unsigned char dot_count;	//С���������
unsigned char byte_count;	//λ��������
unsigned char cmd_number;	//��������
unsigned char mode;			//0������ģʽ��1������ģʽ��2������ģʽ
unsigned char buf_full;		//1�����������ɣ���Ӧ������Ч��0������������Ч��
unsigned char cmd[5];		//�������ʹ洢����

unsigned char R_close=0;
unsigned char T_close=0;

unsigned char jd_last_flag=0,wd_last_flag=0;

unsigned char samp='1';
unsigned char tmp_B=0;

//�������ڱ��浥Ƭ���յ�ģ�鷢����ATָ�ͨ����Щָ�Ƭ�������ж�ģ���״̬
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
*��    �ƣ�main()
*
*��    �ܣ���ɳ�ʼ�������������ò�ѯ��ʽʵ��SCIA�ķ��ͺͽ��չ���
*
*��ڲ�������
*
*���ڲ�������
*
****************************************************************************/
void main(void)
{
    InitSysCtrl();  //��ʼ��ϵͳ����

	DINT;
	IER = 0x0000;   //��ֹCPU�ж�
	IFR = 0x0000;   //���CPU�жϱ�־
	
	InitPieCtrl();  //��ʼ��PIE���ƼĴ���

	InitPieVectTable();  //��ʼ��PIE�ж�������	 
	
	InitGpio();  //��ʼ��Gpio��
	
	InitPeripherals(); //��ʼ��SCIA
       
       
    GpioDataRegs.GPASET.bit.GPIOA0=1;    //����D1
    DelaySec(150);
    GpioDataRegs.GPACLEAR.bit.GPIOA0=1;  //Ϩ��D1
	DelaySec(50);


    
	GpioDataRegs.GPASET.bit.GPIOA0=1;    //����D1
    DelaySec(150);

	//GPRSͨ��
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
	GpioDataRegs.GPACLEAR.bit.GPIOA0=1;  //Ϩ��D1
    DelaySec(150);
    GpioDataRegs.GPASET.bit.GPIOA0=1;    //����D1
    Uart1Sends(sms_text10);          
	Receive(res3);
	GpioDataRegs.GPACLEAR.bit.GPIOA0=1;  //Ϩ��D1
    DelaySec(150);
	for(;;)
	{   
        GpioDataRegs.GPASET.bit.GPIOA0=1;    //����D1
	    //������������
		Uart1Sends(sms_text11);
        wait4();
		DelaySec(50);
        GpioDataRegs.GPACLEAR.bit.GPIOA0=1;  //Ϩ��D1

        //GPS���ݽ���------------------------------------------------------------------
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
        //�Ͽ�����
        Uart2Sends(sms_text12);
        DelaySec(900);
		Uart2Sends(sms_text13);
        DelaySec(9000);
        */ 
	}
} 





//��ʱ���������1s�ӣ�������ʱ��Ļ���׼...
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
	while(ScibTx_Ready()==0);//�ȴ���������źţ�TI=1������
	//TI=0;	
	//DelaySec(30);//��ʱ3��
}

//���п���������char�����飬������ֹ��/0��ֹͣ
void Uart2Sends(unsigned char *str1)
{
	while(*str1!='\0')
	{
		ScibRegs.SCITXBUF=*str1;
		while(ScibTx_Ready()==0);//�ȴ���������źţ�TI=1������
		//TI=0;
		str1++;
		//DelaySec(30);//��ʱ3��
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

//GPS��Ϣ����
void DataParse(void)
{
	if(ScibRx_Ready()==1)
	{
		tmp=ScibRegs.SCIRXBUF.all;
		switch(tmp)
		{
			case '$':
				cmd_number=0;		//�����������
				mode=1;				//��������ģʽ
				byte_count=0;		//����λ�����
				flag_data=1;
				flag_rec=1;		    //���ݱ�־λ��һ
				break;
			case ',':
				seg_count++;		//���ż�����1
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
				if(mode==1)	//���������ж�
				{
					cmd[byte_count]=tmp;			//�����ַ��������ͻ���
					if(byte_count>=4)
					{				//����������ݽ�����ϣ��ж�����
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
					//�������ݴ���
					switch (cmd_number)
					{
						case 1:				//����1���ݽ��ա�GPGGA
							switch(seg_count)
							{
								case 2:		//γ�ȴ���
									if(byte_count<9)
									{
										WD[byte_count]=tmp;
										//wd_flag=1;
									}
									break;
								case 3:		//γ�ȷ�����
									if(byte_count<1)
									{
										WD_a=tmp;
                                        //wd_flag=1;
									}
									break;
								case 4:		//���ȴ���
									if(byte_count<10)
									{
										JD[byte_count]=tmp;
										//jd_flag=1;
									}
									break;
								case 5:		//���ȷ�����
									if(byte_count<1)
									{
										JD_a=tmp;
										//jd_flag=1;
									}
									break;
								case 6:		//��λ�ж�
								
									break;
								case 7:		//��λʹ�õ�������
									if(byte_count<2)
									{
										use_sat[byte_count]=tmp;
									}
									break;
								case 9:		//�߶ȴ���
									if(byte_count<6)
									{
										high[byte_count]=tmp;
									}
									break;
							}
							break;
						case 2:				//����2���ݽ��ա�GPGSV
							switch(seg_count)
							{
								case 3:		//����е���������
									if(byte_count<2)
									{
										total_sat[byte_count]=tmp;
									}
									break;
							}
							break;
						case 3:				//����3���ݽ��ա�GPRMC
							switch(seg_count)
							{
								case 1:		//ʱ�䴦��
									if(byte_count<6)
									{				
										time[byte_count]=tmp;	
									}
									break;
								case 2:		//��λ�ж�						
									if(byte_count<1)
									{
									  if (tmp=='V') {lock=0;}
									  else
									  {
									    lock=1;
									   }
									}
									break;
								case 3:		//γ�ȴ���						
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
								case 4:		//γ�ȷ�����						
									if(byte_count<1)
									{
										WD_a=tmp;
										//wd_flag=1;
									}
									break;
								case 5:		//���ȴ���						
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
								case 6:		//���ȷ�����						
									if(byte_count<1)
									{
										JD_a=tmp;
										//jd_flag=1;
									}
									break;
								case 7:		//�ٶȴ���						
									if(byte_count<5)
									{
										speed[byte_count]=tmp;
									}
									break;
								case 8:		//��λ�Ǵ���						
									if(byte_count<5)
									{
										angle[byte_count]=tmp;
									}
									break;
								case 9:		//��λ�Ǵ���						
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


/*����ͨѶ�жϣ��շ���ɽ�������ж�*/
void Receive(uchar * RES)
{
	uchar i = 0;
    while(1)
	{
	  if(SciaRx_Ready()==1)	//�յ���Ϣ
	  {	
		GsmRcv[GsmRcvCnt] = SciaRegs.SCIRXBUF.all;
		GsmRcvCnt++;
		//�յ���������ATָ�������ATָ������0x0d 0x0a��β�ġ��������жϣ��ڽ��յĹ������Ƿ��յ�0x0d 0x0a
		if(GsmRcv[GsmRcvCnt-2] == 0x0D && GsmRcv[GsmRcvCnt-1] == 0x0A && GsmRcvCnt >= 2)
		{
			//һ���յ�0x0d 0x0a���ͽ����ݱ����������û����������жϡ�			
			for(i=0; i<GsmRcvCnt; i++)
			{
				GsmRcvAt[i] = GsmRcv[i];
				GsmRcv[i] = 0;	
			}
			GsmRcvCnt = 0;
			//GsmAtFlag = 1;//�յ���������atָ�ͨ�������־λ��1��������������֪��ȥ�ж��ˡ�
			if(strstr((char *)GsmRcvAt, (char *)RES) )//GsmAtFlag == 1 && 
	        {
	          break;
	        }								
		}
		else if(GsmRcvCnt >= 50)//��Ϊ�ڴ����ޣ��յ���50���ַ�����û�п���0x0a 0x0d�Ļ��������¿�ʼ���հɡ�
		{
			GsmRcvCnt = 0;
		}
      }
	}
}
//===========================================================================
// No more.
//===========================================================================

