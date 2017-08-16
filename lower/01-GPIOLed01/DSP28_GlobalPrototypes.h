
/****************************************************************************
*
*�ļ�����DSP28_GlobalPrototypes.h
*
*��  �ܣ�2812ȫ�ֺ��������ļ�
*
*��  ��: lft @��RenAll
*
****************************************************************************/


#ifndef EXAMPLE_H
#define EXAMPLE_H

/*---- ȫ�ֺ������� -----------------------------------*/
extern void InitAdc(void);
extern void InitDevEmu(void);
extern void InitDevice(void);
extern void InitECana(void);
extern void InitEv(void);
extern void InitGpio(void);
extern void InitMcbsp(void);
extern void InitPieCtrl(void);
extern void InitPieVectTable(void);
extern void InitPeripherals(void);
extern void InitSci(void);
extern int  SciaTx_Ready(void);
extern int  SciaRx_Ready(void);
extern void InitSpi(void);
extern void InitSysCtrl(void);
extern void InitXintf(void);
extern void InitXIntrupt(void);

extern void KickDog(void);

#endif   

//===========================================================================
// No more.
//===========================================================================

