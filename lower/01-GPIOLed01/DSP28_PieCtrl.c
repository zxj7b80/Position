
/****************************************************************************
*
*�ļ�����DSP28_PieCtrl.c
*
*��  �ܣ���PIE�жϵĿ��ƼĴ������г�ʼ��
*
*��  ��: lft @��RenAll
*
****************************************************************************/

#include "DSP28_Device.h"

/****************************************************************************
*
*��    �ƣ�InitPieCtrl()
*
*��    �ܣ�PIE�жϿ�������ʼ������        
*
*��ڲ�������
*
*���ڲ�������
*
****************************************************************************/

void InitPieCtrl(void)
{
	// ��ֹPIEģ��
	PieCtrl.PIECRTL.bit.ENPIE = 0;

	// ��ֹPIE�����ж�
	PieCtrl.PIEIER1.all = 0;
	PieCtrl.PIEIER2.all = 0;
	PieCtrl.PIEIER3.all = 0;	
	PieCtrl.PIEIER4.all = 0;
	PieCtrl.PIEIER5.all = 0;
	PieCtrl.PIEIER6.all = 0;
	PieCtrl.PIEIER7.all = 0;
	PieCtrl.PIEIER8.all = 0;
	PieCtrl.PIEIER9.all = 0;
	PieCtrl.PIEIER10.all = 0;
	PieCtrl.PIEIER11.all = 0;
	PieCtrl.PIEIER12.all = 0;

	// �������PIEIFR���жϱ�־λ
	PieCtrl.PIEIFR1.all = 0;
	PieCtrl.PIEIFR2.all = 0;
	PieCtrl.PIEIFR3.all = 0;	
	PieCtrl.PIEIFR4.all = 0;
	PieCtrl.PIEIFR5.all = 0;
	PieCtrl.PIEIFR6.all = 0;
	PieCtrl.PIEIFR7.all = 0;
	PieCtrl.PIEIFR8.all = 0;
	PieCtrl.PIEIFR9.all = 0;
	PieCtrl.PIEIFR10.all = 0;
	PieCtrl.PIEIFR11.all = 0;
	PieCtrl.PIEIFR12.all = 0;

	// ʹ��PIEģ��
	PieCtrl.PIECRTL.bit.ENPIE = 1;
	PieCtrl.PIEACK.all = 0xFFFF;
}	

//===========================================================================
// No more.
//===========================================================================
