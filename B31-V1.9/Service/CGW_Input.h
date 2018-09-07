#ifndef __CGW_INPUT_H
#define __CGW_INPUT_H

#include <stdint.h>


typedef struct VCU_Status
{
    uint8_t ChillerSwchSts;
    uint8_t PrmtClimMasPwr;
    uint8_t PwrLmtReason;
    uint8_t CoolgFanDutyRat;
    uint8_t CoolgFanFtSts;
    uint8_t BattCoolgPmgFltSts;
    uint8_t MotCoolgPmpFltSts;
    uint8_t WPTCReq;
    uint8_t MotCoolgPmpDutyRat;
    uint8_t BattCoolgPmpDutyRat;
    uint8_t BattInputCooltTarTmp;
    uint8_t VhlCtrlSts;
    uint8_t IGNPosn;
    
    
    uint8_t SunlightInten;
    uint8_t ClassTHSnsrTmp;
    uint8_t AtmTHSnsrHum;
    uint8_t ESP_VhclS;
    uint8_t ESP_VhclSpdValid;
    uint8_t BCM_PwrStsFb;
    
}VCU_Status;




#endif
