#ifndef __S32K_ADC_H__
#define __S32K_ADC_H__ 

typedef enum ADCn  //ADC�˿�
{
	SADC0,
	SADC1
}ADCn;

//ADCͨ��
typedef enum ADC_Ch
{
    AD0 = 0, //	            ADC0_SE0   -- PTA0		                    ADC1_SE0   -- PTA2
    AD1 = 1, //	            ADC0_SE1   -- PTA1			            ADC1_SE1   -- PTA3
    AD2 = 2, //	            ADC0_SE2   -- PTA6			            ADC1_SE2   -- PTD2
    AD3 = 3, //	            ADC0_SE3   -- PTA7		                    ADC1_SE3   -- PTD3
    AD4 = 4, //	            ADC0_SE4   -- PTB0				    ADC1_SE4   -- PTC6
    AD5 = 5, //	            ADC0_SE5   -- PTB1				    ADC1_SE5   -- PTC7
    AD6 = 6, //	            ADC0_SE6   -- PTB2			            ADC1_SE6   -- PTD4
    AD7 = 7, //	            ADC0_SE7   -- PTB3				    ADC1_SE7   -- PTB12
    AD8 = 8,  //	    ADC0_SE8  	-- PTC0			            ADC1_SE8    -- PTB13
    AD9 = 9,  //	    ADC0_SE9  	-- PTC1			            ADC1_SE9    -- PTB14
    AD10 = 10, //	    ADC0_SE10 	-- PTC2		                    ADC1_SE10   -- PTE2
    AD11 = 11, //	    ADC0_SE11 	-- PTC3			            ADC1_SE11   -- PTE6
    AD12 = 12, //	    ADC0_SE12 	-- PTC14		            ADC1_SE12   -- PTA15
    AD13 = 13, //	    ADC0_SE13 	-- PTC15			    ADC1_SE13   -- PTA16
    AD14 = 14, //	    ADC0_SE14 	-- PTC16			    ADC1_SE14   -- PTB15
    AD15 = 15, //	    ADC0_SE15 	-- PTC17			    ADC1_SE15   -- PTB16
    AD16 = 16, //	    ����				            ADC1_SE16
    AD17 = 17, //	    ����		                            ����
    AD18 = 18, //	    ����		                            ����
    AD19 = 19, //	    ADC0_DM0				             ADC1_DM0
    AD20 = 20, //	    ADC0_DM1				             ADC1_DM1
    AD21 = 21, //				        	                   
    AD22 = 22, //
    AD23 = 23, //	    DAC0_OUT(12-bit) -- DAC0_OUT		    DAC1_OUT(12-bit)
    AD24 = 24, //	    ����					    ����
    AD25 = 25, //	    ����					    ����
    AD26 = 26, //	    Temperature Sensor (S.E)		            Temperature Sensor (S.E)
    AD27 = 27, //	    Bandgap (S.E)				    Bandgap (S.E)
    AD28 = 28, //	    ����					    ����
    AD29 = 29, //	    VREFH (S.E)				            VREFH (S.E)
    AD30 = 30, //	    VREFL					    VREFL
    AD31 = 31 //	    ����ADC0				            ����ADC1
} ADC_Ch;

//����λ��
typedef enum ADC_nbit
{
    ADC_8bit   = 0x00,
    ADC_10bit  = 0x02,
    ADC_12bit  = 0x01,
    ADC_16bit  = 0x03
} ADC_nbit;


typedef enum
{
    ADC_AVERAGE_4 = 0x00U,  /*!< Hardware average of 4 samples. */
    ADC_AVERAGE_8 = 0x01U,  /*!< Hardware average of 8 samples. */
    ADC_AVERAGE_16 = 0x02U, /*!< Hardware average of 16 samples. */
    ADC_AVERAGE_32 = 0x03U  /*!< Hardware average of 32 samples. */
} adc_average_t;

typedef enum
{
    ADC_TRIGGER_SOFTWARE       = 0x00U,   /*!< Software trigger. */
    ADC_TRIGGER_HARDWARE       = 0x01U    /*!< Hardware trigger. */
} adc_trigger_t;

// Clock divisor
//ʱ�ӷ�Ƶ
#define ADIV_1            0x00
#define ADIV_2            0x01
#define ADIV_4            0x02
#define ADIV_8            0x03

//ADC����ʱ��Դѡ�� ���ߣ�����/2����altclk������ADC�����첽ʱ���Լ�������
#define ADICLK_BUS        0x00
#define ADICLK_BUS_2      0x01
#define ADICLK_ALTCLK     0x02
#define ADICLK_ADACK      0x03

// ������ʱ��ѡ��20,12,6����2�������ʱ�Ӷ��ڳ�����ʱ��
#define ADLSTS_20          0x00
#define ADLSTS_12          0x01
#define ADLSTS_6           0x02
#define ADLSTS_2           0x03

// ֻ��״̬λ,ת��״̬
#define ADACT_ACTIVE       ADC_SC2_ADACT_MASK
#define ADACT_INACTIVE     0x00

// ������ʼת��:Ӳ���������������
#define ADTRG_HW           ADC_SC2_ADTRG_MASK
#define ADTRG_SW           0x00

//ADC�ȽϹ���ʹ�ܣ���ֹ����ʹ��
#define ACFE_DISABLED      0x00
#define ACFE_ENABLED       ADC_SC2_ACFE_MASK

// �ȽϹ��ܴ��ڱȽ�ʹ�ܣ����ڻ���С��
#define ACFGT_GREATER      ADC_SC2_ACFGT_MASK
#define ACFGT_LESS         0x00

// �ȽϹ��ܷ�Χʹ�ܣ�ʹ�ܻ��߽�ֹ
#define ACREN_ENABLED      ADC_SC2_ACREN_MASK
#define ACREN_DISABLED     0x00

// DMAʹ�ܣ�ʹ�ܻ��߽�ֹ
#define DMAEN_ENABLED      ADC_SC2_DMAEN_MASK
#define DMAEN_DISABLED     0x00

//ADCת���ĵ�ѹ�ο�ѡ��
#define REFSEL_EXT         0x00
#define REFSEL_ALT         0x01
#define REFSEL_RES         0x02     /* reserved */
#define REFSEL_RES_EXT     0x03     /* reserved but defaults to Vref */

////ADCSC3
// У׼��ʼ���߹ر�
#define CAL_BEGIN          ADC_SC3_CAL_MASK
#define CAL_OFF            0x00

// ָʾУ׼ʧ�ܳɹ���״̬
#define CALF_FAIL          ADC_SC3_CALF_MASK
#define CALF_NORMAL        0x00

// ADC����ת������һ��ת��
#define ADCO_CONTINUOUS    ADC_SC3_ADCO_MASK
#define ADCO_SINGLE        0x00

// ƽ������ʹ�ܻ��߽�ֹ
#define AVGE_ENABLED       ADC_SC3_AVGE_MASK
#define AVGE_DISABLED      0x00


//�ⲿ�����ӿ�����
void Adc_Init(ADCn adcn, ADC_Ch ch);              //AD��ʼ��
void adc_start(ADCn adcn, ADC_Ch ch);
void ADC_AutoCalibration(ADCn adcn);

#endif /* __ADC16_H__ */
