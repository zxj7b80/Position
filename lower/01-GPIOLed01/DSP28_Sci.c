
/****************************************************************************
*
*文件名：DSP28_Sci.c
*
*功  能：对SCI串口通信模块进行初始化
*
*作  者: likyo from hellodsp
*
*版  本：V1.0
*
****************************************************************************/

#include "DSP28_Device.h"

/****************************************************************************
*
*名    称：InitSci()
*
*功    能：本实验中使用的是SciA模块，因此需要对其进行初始化，通信数据格式为波
*          特率为19200，数据位8位，无极性校验，停止位1位。
*
*入口参数：无
*
*出口参数：无
*
****************************************************************************/

void InitSci(void)
{   //A------------------------------------------------
	SciaRegs.SCICCR.bit.STOPBITS=0;        //1位停止位
	SciaRegs.SCICCR.bit.PARITYENA=0;       //禁止极性功能
	SciaRegs.SCICCR.bit.LOOPBKENA=0;       //禁止回送测试模式功能
	SciaRegs.SCICCR.bit.ADDRIDLE_MODE=0;   //空闲线模式
	SciaRegs.SCICCR.bit.SCICHAR=7;         //8位数据位
	
	SciaRegs.SCICTL1.bit.TXENA=1;          //SCIA模块的发送使能
	SciaRegs.SCICTL1.bit.RXENA=1;          //SCIA模块的接收使能
	
	SciaRegs.SCIHBAUD=0;
	SciaRegs.SCILBAUD=0xF3;                //波特率为19200	
	
	SciaRegs.SCICTL1.bit.SWRESET=1;        //重启SCI
    //B-------------------------------------------------
	ScibRegs.SCICCR.bit.STOPBITS=0;        //1位停止位
	ScibRegs.SCICCR.bit.PARITYENA=0;       //禁止极性功能
	ScibRegs.SCICCR.bit.LOOPBKENA=0;       //禁止回送测试模式功能
	ScibRegs.SCICCR.bit.ADDRIDLE_MODE=0;   //空闲线模式
	ScibRegs.SCICCR.bit.SCICHAR=7;         //8位数据位
	
	ScibRegs.SCICTL1.bit.TXENA=1;          //SCIB模块的发送使能
	ScibRegs.SCICTL1.bit.RXENA=1;          //SCIB模块的接收使能
	
	ScibRegs.SCIHBAUD=0;
	ScibRegs.SCILBAUD=0xF3;                //波特率为19200	
	
	ScibRegs.SCICTL1.bit.SWRESET=1;        //重启SCI
}

/****************************************************************************
*
*名    称：SciaTx_Ready()
*
*功    能：查询SCICTL2寄存器的TXRDY标志位，来确认发送准备是否就绪
*
*入口参数：无
*
*出口参数：i，即TXRDY的状态
*          1：发送准备已经就绪
*          0：发送准备尚未就绪
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
*名    称：SciaRx_Ready()
*
*功    能：查询SCIRXST寄存器的RXRDY标志位，来确认接收准备是否就绪
*
*入口参数：无
*
*出口参数：i，即RXRDY的状态
*          1：接收准备已经就绪
*          0：接收准备尚未就绪
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
