#include "MOTOR_DRIVE.h"
#include "TB9102.h"

extern TB9102 tb9102_list[4];


/*          模式电机驱动          */
#define ModeACTFDEF_DRV     tb9102_list[0]
#define ModeACTFDEF_PIN     TB9102_OC1
#define ModeACTVENT_PIN     TB9102_OC2
void MODE_ACW(void){
    TB9102_OUTPUT_H(&ModeACTFDEF_DRV,ModeACTFDEF_PIN);
    TB9102_OUTPUT_L(&ModeACTFDEF_DRV,ModeACTVENT_PIN);
}
void MODE_CW(void){
    TB9102_OUTPUT_L(&ModeACTFDEF_DRV,ModeACTFDEF_PIN);
    TB9102_OUTPUT_H(&ModeACTFDEF_DRV,ModeACTVENT_PIN);
}
void Stop_Mode_Motor(void){
    TB9102_OUTPUT_L(&ModeACTFDEF_DRV,ModeACTFDEF_PIN);
    TB9102_OUTPUT_L(&ModeACTFDEF_DRV,ModeACTVENT_PIN);
}    
                            
/*          内外循环电机驱动    */
#define IntakeACTFRE_DRV    tb9102_list[0]
#define IntakeACTFRE_PIN    TB9102_OB1
#define IntakeACTREC_PIN    TB9102_OB2
void REC_ACW(void){
    TB9102_OUTPUT_H(&ModeACTFDEF_DRV,IntakeACTFRE_PIN);
    TB9102_OUTPUT_L(&ModeACTFDEF_DRV,IntakeACTREC_PIN);
}
void REC_CW(void){
    TB9102_OUTPUT_L(&ModeACTFDEF_DRV,IntakeACTFRE_PIN);
    TB9102_OUTPUT_H(&ModeACTFDEF_DRV,IntakeACTREC_PIN);
}
void Stop_REC_Motor(void){
    TB9102_OUTPUT_L(&ModeACTFDEF_DRV,IntakeACTFRE_PIN);
    TB9102_OUTPUT_L(&ModeACTFDEF_DRV,IntakeACTREC_PIN);
}

/*          后内外循环电机驱动       */
#define DesACT_DRV          tb9102_list[2]
#define DesACT_PIN          TB9102_OB1
#define DesACTR_PIN         TB9102_OB2
void DesACT_ACW(void){
    TB9102_OUTPUT_H(&DesACT_DRV,DesACT_PIN);
    TB9102_OUTPUT_L(&DesACT_DRV,DesACTR_PIN);
};

void DesACT_CW(void){
    TB9102_OUTPUT_L(&DesACT_DRV,DesACT_PIN);
    TB9102_OUTPUT_H(&DesACT_DRV,DesACTR_PIN);
};

void Stop_DesACT_Motor(void){
    TB9102_OUTPUT_H(&DesACT_DRV,DesACT_PIN);
    TB9102_OUTPUT_L(&DesACT_DRV,DesACTR_PIN);
};
                    
/*          左温度电机驱动     */
#define TempACTWARM_CO_DRV  tb9102_list[1]
#define TempACTWARM_CO_PIN  TB9102_OA1
#define TempACTCOOL_CO_PIN  TB9102_OA2
void TempCO_ACW(void){
    TB9102_OUTPUT_H(&TempACTWARM_CO_DRV,TempACTWARM_CO_PIN);
    TB9102_OUTPUT_L(&TempACTWARM_CO_DRV,TempACTCOOL_CO_PIN);
}
void TempCO_CW(void){
    TB9102_OUTPUT_L(&TempACTWARM_CO_DRV,TempACTWARM_CO_PIN);
    TB9102_OUTPUT_H(&TempACTWARM_CO_DRV,TempACTCOOL_CO_PIN);
}
void Stop_TempCO_Motor(void){
    TB9102_OUTPUT_L(&TempACTWARM_CO_DRV,TempACTWARM_CO_PIN);
    TB9102_OUTPUT_L(&TempACTWARM_CO_DRV,TempACTCOOL_CO_PIN);
}    


/*          */
#define F_FANCLOSE_DRV      tb9102_list[1]
#define F_FANCLOSE_PIN      TB9102_OB1
#define R_FANCLOSE_PIN      TB9102_OB2

/*          右温度电机驱动     */
#define TempACTWARM_PA_DRV  tb9102_list[1]
#define TempACTWARM_PA_PIN  TB9102_OC1
#define TempACTCOOL_PA_PIN  TB9102_OC2
void TempPA_ACW(void){
    TB9102_OUTPUT_H(&TempACTWARM_PA_DRV,TempACTWARM_PA_PIN);
    TB9102_OUTPUT_L(&TempACTWARM_PA_DRV,TempACTCOOL_PA_PIN);
}
void TempPA_CW(void){
    TB9102_OUTPUT_L(&TempACTWARM_PA_DRV,TempACTWARM_PA_PIN);
    TB9102_OUTPUT_H(&TempACTWARM_PA_DRV,TempACTCOOL_PA_PIN);
}
void Stop_TempPA_Motor(void){
    TB9102_OUTPUT_L(&TempACTWARM_PA_DRV,TempACTWARM_PA_PIN);
    TB9102_OUTPUT_L(&TempACTWARM_PA_DRV,TempACTCOOL_PA_PIN);
}

void TEMP_ACW(void){};
void TEMP_CW(void){};

void Stop_TEMP_Motor(void){};
void Stop_Mode_Motor_P(void){};
void Stop_TEMP_Motor_P(void){};
void Stop_REC_Motor_P(void){};

void Moter_Ctrl(void)//执行器驱动
{
    uint8_t i;
    for(i=0;i<4;i++)
    {
        tb9102_update(&tb9102_list[i]);
    }
}
//end
