
/****************************************************************************
*
*�ļ�����DSP28_PieVect.c
*
*��  �ܣ���2812�ж���������г�ʼ������
*
*��  ��: lft @��RenAll
*
****************************************************************************/

#include "DSP28_Device.h"

const struct PIE_VECT_TABLE PieVectTableInit = {

      PIE_RESERVED,  // �����Ŀռ�
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   
      PIE_RESERVED,   


      // �������ж�����
      INT13_ISR,     // XINT13����CPU��ʱ��1�ж�
      INT14_ISR,     // CPU��ʱ��2�ж�
      DATALOG_ISR,   // CPU���ݼ�¼�ж�
      RTOSINT_ISR,   // CPUʵʱOS�ж�
      EMUINT_ISR,    // CPU�����ж�
      NMI_ISR,       // �ⲿ�������ж�
      ILLEGAL_ISR,   // �Ƿ�����
      USER0_ISR,     // �û��������ж�0
      USER1_ISR,     // �û��������ж�1
      USER2_ISR,     // �û��������ж�2
      USER3_ISR,     // �û��������ж�3
      USER4_ISR,     // �û��������ж�4
      USER5_ISR,     // �û��������ж�5
      USER6_ISR,     // �û��������ж�6
      USER7_ISR,     // �û��������ж�7
      USER8_ISR,     // �û��������ж�8
      USER9_ISR,     // �û��������ж�9
      USER10_ISR,    // �û��������ж�10
      USER11_ISR,    // �û��������ж�11

      // PIE ��1����
      PDPINTA_ISR,   // EV-A�Ĺ������������ж�
      PDPINTB_ISR,   // EV-B�Ĺ������������ж�
      rsvd_ISR,      // ����
      XINT1_ISR,     // �ⲿ�ӿڣ�XINT1���ж�   
      XINT2_ISR,     // �ⲿ�ӿڣ�XINT2���ж�
      ADCINT_ISR,    // ADC�ж�
      TINT0_ISR,     // CPU��ʱ��0�ж�
      WAKEINT_ISR,   // WD�ж�

      // PIE ��2����
      CMP1INT_ISR,   // �Ƚϵ�Ԫ1�Ƚ��ж�
      CMP2INT_ISR,   // �Ƚϵ�Ԫ2�Ƚ��ж�
      CMP3INT_ISR,   // �Ƚϵ�Ԫ3�Ƚ��ж�
      T1PINT_ISR,    // ͨ�ö�ʱ��1�����ж�
      T1CINT_ISR,    // ͨ�ö�ʱ��1�Ƚ��ж�
      T1UFINT_ISR,   // ͨ�ö�ʱ��1�����ж�
      T1OFINT_ISR,   // ͨ�ö�ʱ��1�����ж�
      rsvd_ISR,      // ����
      
      // PIE ��3����
      T2PINT_ISR,    // ͨ�ö�ʱ��2�����ж�
      T2CINT_ISR,    // ͨ�ö�ʱ��2�Ƚ��ж�
      T2UFINT_ISR,   // ͨ�ö�ʱ��2�����ж�
      T2OFINT_ISR,   // ͨ�ö�ʱ��2�����ж�
      CAPINT1_ISR,   // ����Ԫ1�����ж�
      CAPINT2_ISR,   // ����Ԫ2�����ж�
      CAPINT3_ISR,   // ����Ԫ3�����ж�
      rsvd_ISR,
      
      // PIE ��4����
      CMP4INT_ISR,   // �Ƚϵ�Ԫ4�Ƚ��ж�
      CMP5INT_ISR,   // �Ƚϵ�Ԫ5�Ƚ��ж�
      CMP6INT_ISR,   // �Ƚϵ�Ԫ6�Ƚ��ж�
      T3PINT_ISR,    // ͨ�ö�ʱ��3�����ж�
      T3CINT_ISR,    // ͨ�ö�ʱ��3�Ƚ��ж�
      T3UFINT_ISR,   // ͨ�ö�ʱ��3�����ж�
      T3OFINT_ISR,   // ͨ�ö�ʱ��3�����ж�
      rsvd_ISR,      // ����
     
      // PIE ��5����
      T4PINT_ISR,    // ͨ�ö�ʱ��4�����ж�
      T4CINT_ISR,    // ͨ�ö�ʱ��4�Ƚ��ж�
      T4UFINT_ISR,   // ͨ�ö�ʱ��4�����ж�
      T4OFINT_ISR,   // ͨ�ö�ʱ��4�����ж�
      CAPINT4_ISR,   // ����Ԫ4�����ж�
      CAPINT5_ISR,   // ����Ԫ5�����ж�
      CAPINT6_ISR,   // ����Ԫ6�����ж�
      rsvd_ISR,      // ����  

      // PIE ��6����
      SPIRXINTA_ISR, // SPI-A�����ж�
      SPITXINTA_ISR, // SPI-A�����ж�
      rsvd_ISR,      // ����
      rsvd_ISR,
      MRINTA_ISR,    // McBSP-A�����ж�
      MXINTA_ISR,    // McBSP-A�����ж�
      rsvd_ISR,      //����
      rsvd_ISR,
      
      // PIE ��7����
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   

      // PIE ��8����
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      
      // PIE ��9����    
      SCIRXINTA_ISR, // SCI-A�����ж�
      SCITXINTA_ISR, // SCI-A�����ж�
      SCIRXINTB_ISR, // SCI-B�����ж�
      SCITXINTB_ISR, // SCI-B�����ж�
      ECAN0INTA_ISR, // eCAN0�ж�
      ECAN1INTA_ISR, // eCAN1�ж�
      rsvd_ISR,   
      rsvd_ISR,   
      
      // PIE ��10����
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
            
      // PIE ��11����
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   

      // PIE ��12����
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
      rsvd_ISR,   
};


/****************************************************************************
*
*��    �ƣ�InitPieVectTable()
*
*��    �ܣ��ú�����PIE�ж���������г�ʼ�������ϵ�������ִ��
*
*��ڲ�������
*
*���ڲ�������
*
****************************************************************************/

void InitPieVectTable(void)
{
	int16	i;
	Uint32 *Source = (void *) &PieVectTableInit;
	Uint32 *Dest = (void *) &PieVectTable;
		
	EALLOW;	
	for(i=0; i < 128; i++)
		*Dest++ = *Source++;	
	EDIS;

	// ʹ��PIE������
	PieCtrl.PIECRTL.bit.ENPIE = 1;	
			
}

//===========================================================================
// No more.
//===========================================================================
