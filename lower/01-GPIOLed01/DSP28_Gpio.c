
/****************************************************************************
*
*文件名: DSP28_Gpio.c
*
*功  能: 2812通用输入输出口GPIO的初始化函数
*
*作  者: likyo from hellodsp
*
*版  本: V1.0
*
****************************************************************************/

#include "DSP28_Device.h"

/****************************************************************************
*
*名    称：InitGpio()
*
*功    能：初始化Gpio，使得Gpio的引脚处于已知的状态，例如确定其功能是特定功能
*          还是通用I/O。如果是通用I/O，是输入还是输出，等等。
*
*入口参数：无
*
*出口参数：无
*
****************************************************************************/

void InitGpio(void)
{

     EALLOW;
     
     GpioMuxRegs.GPFMUX.bit.SCITXDA_GPIOF4=1;  //设置SCIA的发送引脚
     GpioMuxRegs.GPFMUX.bit.SCIRXDA_GPIOF5=1;  //设置SCIA的接收引脚

	 GpioMuxRegs.GPGMUX.bit.SCITXDB_GPIOG4=1;  //设置SCIA的发送引脚
     GpioMuxRegs.GPGMUX.bit.SCIRXDB_GPIOG5=1;  //设置SCIA的接收引脚
     
     GpioMuxRegs.GPAMUX.bit.PWM1_GPIOA0=0; //设定PWM1-PWM6引脚为I/O口
	 GpioMuxRegs.GPADIR.bit.GPIOA0=1;      //设定PWM1-PWM6引脚为输出引脚

     EDIS;

}	
	
//===========================================================================
// No more.
//===========================================================================
