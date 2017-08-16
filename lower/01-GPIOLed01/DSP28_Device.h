
/****************************************************************************
*
*�ļ�����DSP28_Device.h
*
*��  �ܣ�2812�豸����ض���
*
*��  ��: lft @��RenAll
*
****************************************************************************/

#ifndef DSP28_DEVICE_H
#define DSP28_DEVICE_H

#define	TARGET	1
//---------------------------------------------------------------------------
// ������ѡ��Ŀ��оƬ:

#define	F2812   TARGET
#define	F2810   0

//---------------------------------------------------------------------------
// ͨ�õ�CPU����:

extern cregister volatile unsigned int IFR;
extern cregister volatile unsigned int IER;
#define  EINT   asm(" clrc INTM")
#define  DINT   asm(" setc INTM")
#define  ERTM   asm(" clrc DBGM")
#define  DRTM   asm(" setc DBGM")
#define	 EALLOW	asm(" EALLOW")
#define	 EDIS	asm(" EDIS")
#define  ESTOP0 asm(" ESTOP0")
#define  NOP asm(" NOP")

#define	M_INT1		0x0001
#define	M_INT2		0x0002
#define	M_INT3		0x0004
#define	M_INT4		0x0008
#define	M_INT5		0x0010
#define	M_INT6		0x0020
#define	M_INT7		0x0040
#define	M_INT8		0x0080
#define	M_INT9		0x0100
#define	M_INT10		0x0200
#define	M_INT11		0x0400
#define	M_INT12		0x0800
#define	M_INT13		0x1000
#define	M_INT14		0x2000
#define	M_DLOG		0x4000
#define	M_RTOS		0x8000

#define	BIT0		0x0001
#define	BIT1		0x0002
#define	BIT2		0x0004
#define	BIT3		0x0008
#define	BIT4		0x0010
#define	BIT5		0x0020
#define	BIT6		0x0040
#define	BIT7		0x0080
#define	BIT8		0x0100
#define	BIT9		0x0200
#define	BIT10		0x0400
#define	BIT11		0x0800
#define	BIT12		0x1000
#define	BIT13		0x2000
#define	BIT14		0x4000
#define	BIT15		0x8000

//---------------------------------------------------------------------------
// Ϊ�˾��и��õĿ���ֲ�ԣ��������������ʱʹ���������������
// 16λ��32λ���з��ź��޷����������͵Ķ�������:
//

typedef int  		int16;
typedef long 		int32;
typedef unsigned int  	Uint16;
typedef unsigned long 	Uint32;

//---------------------------------------------------------------------------
// �������е�ͷ�ļ�:
//

#include "DSP28_GlobalPrototypes.h"   // Դ�ļ���ȫ�ֺ�����ԭ��

#include "DSP28_SysCtrl.h"         // ϵͳ����
#include "DSP28_DevEmu.h"          // ����Ĵ���
#include "DSP28_Xintf.h"           // �ⲿ�ӿڼĴ���
#include "DSP28_CpuTimers.h"       // 32λCPU��ʱ��
#include "DSP28_PieCtrl.h"         // PIE���ƼĴ���
#include "DSP28_PieVect.h"         // PIE������
#include "DSP28_DefaultIsr.h"      // PIE�жϺ���
#include "DSP28_Spi.h"             // SPI �Ĵ���
#include "DSP28_Sci.h"             // SCI �Ĵ���
#include "DSP28_Mcbsp.h"           // McBSP �Ĵ���
#include "DSP28_ECan.h"            // ��ǿ�� eCAN �Ĵ���
#include "DSP28_Gpio.h"            // ͨ��I/Oģ��Ĵ���
#include "DSP28_Ev.h"              // �¼��������Ĵ���
#include "DSP28_Adc.h"             // ADC �Ĵ���
#include "DSP28_XIntrupt.h"        // �ⲿ�ж�
#include "DSP28_Globalvariable.h"  // ȫ�ֱ���

#endif  


//===========================================================================
// No more.
//===========================================================================
