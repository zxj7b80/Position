
/****************************************************************************
*
*�ļ�����DSP28_Sci.c
*
*��  �ܣ���SCI����ͨ��ģ����г�ʼ��
*
*��  ��: likyo from hellodsp
*
*��  ����V1.0
*
****************************************************************************/

#include "DSP28_Device.h"

/****************************************************************************
*
*��    �ƣ�InitSci()
*
*��    �ܣ���ʵ����ʹ�õ���SciAģ�飬�����Ҫ������г�ʼ����ͨ�����ݸ�ʽΪ��
*          ����Ϊ19200������λ8λ���޼���У�飬ֹͣλ1λ��
*
*��ڲ�������
*
*���ڲ�������
*
****************************************************************************/

void InitSci(void)
{   //A------------------------------------------------
	SciaRegs.SCICCR.bit.STOPBITS=0;        //1λֹͣλ
	SciaRegs.SCICCR.bit.PARITYENA=0;       //��ֹ���Թ���
	SciaRegs.SCICCR.bit.LOOPBKENA=0;       //��ֹ���Ͳ���ģʽ����
	SciaRegs.SCICCR.bit.ADDRIDLE_MODE=0;   //������ģʽ
	SciaRegs.SCICCR.bit.SCICHAR=7;         //8λ����λ
	
	SciaRegs.SCICTL1.bit.TXENA=1;          //SCIAģ��ķ���ʹ��
	SciaRegs.SCICTL1.bit.RXENA=1;          //SCIAģ��Ľ���ʹ��
	
	SciaRegs.SCIHBAUD=0;
	SciaRegs.SCILBAUD=0xF3;                //������Ϊ19200	
	
	SciaRegs.SCICTL1.bit.SWRESET=1;        //����SCI
    //B-------------------------------------------------
	ScibRegs.SCICCR.bit.STOPBITS=0;        //1λֹͣλ
	ScibRegs.SCICCR.bit.PARITYENA=0;       //��ֹ���Թ���
	ScibRegs.SCICCR.bit.LOOPBKENA=0;       //��ֹ���Ͳ���ģʽ����
	ScibRegs.SCICCR.bit.ADDRIDLE_MODE=0;   //������ģʽ
	ScibRegs.SCICCR.bit.SCICHAR=7;         //8λ����λ
	
	ScibRegs.SCICTL1.bit.TXENA=1;          //SCIBģ��ķ���ʹ��
	ScibRegs.SCICTL1.bit.RXENA=1;          //SCIBģ��Ľ���ʹ��
	
	ScibRegs.SCIHBAUD=0;
	ScibRegs.SCILBAUD=0xF3;                //������Ϊ19200	
	
	ScibRegs.SCICTL1.bit.SWRESET=1;        //����SCI
}

/****************************************************************************
*
*��    �ƣ�SciaTx_Ready()
*
*��    �ܣ���ѯSCICTL2�Ĵ�����TXRDY��־λ����ȷ�Ϸ���׼���Ƿ����
*
*��ڲ�������
*
*���ڲ�����i����TXRDY��״̬
*          1������׼���Ѿ�����
*          0������׼����δ����
*       
****************************************************************************/

int SciaTx_Ready(void)
{
	unsigned int i;
	if(SciaRegs.SCICTL2.bit.TXRDY == 1)
	{
		i = 1;
	}
	else
	{
		i = 0;
	}
	return(i);
}

int ScibTx_Ready(void)
{
	unsigned int i;
	if(ScibRegs.SCICTL2.bit.TXRDY == 1)
	{
		i = 1;
	}
	else
	{
		i = 0;
	}
	return(i);
}

/****************************************************************************
*
*��    �ƣ�SciaRx_Ready()
*
*��    �ܣ���ѯSCIRXST�Ĵ�����RXRDY��־λ����ȷ�Ͻ���׼���Ƿ����
*
*��ڲ�������
*
*���ڲ�����i����RXRDY��״̬
*          1������׼���Ѿ�����
*          0������׼����δ����
*       
****************************************************************************/

int SciaRx_Ready(void)
{
	unsigned int i;
	if(SciaRegs.SCIRXST.bit.RXRDY == 1)
	{
		i = 1;
	}
	else
	{
		i = 0;
	}
	return(i);
}
	

int ScibRx_Ready(void)
{
	unsigned int i;
	if(ScibRegs.SCIRXST.bit.RXRDY == 1)
	{
		i = 1;
	}
	else
	{
		i = 0;
	}
	return(i);
}

//===========================================================================
// No more.
//===========================================================================
