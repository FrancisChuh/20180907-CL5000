#ifndef __WPTC_H
#define __WPTC_H

#include <stdint.h>

#include "LIN.h"

typedef struct WPTC_CMD
{
    uint8_t enable;     //使能
    uint8_t TarTmp;     //目标温度
    uint8_t TarPwr;     //目标功率
    uint8_t HiVitRdy;   //高压电就绪：由can总线由汽车总控制器传过来
    uint8_t LoVitRdy;   //低压低就绪：由can总线由汽车总控制器传过来
}WPTC_CMD;

typedef struct WPTC_STATUS
{
    uint8_t InltTmp;//进水口温度
    uint8_t OutltTmp;//出水口温度
    uint8_t ActlHiVlt;//高压电压
    uint8_t ActlHiVltCur;//高压电流
    uint8_t ActlLoVlt;//低压电压
    uint8_t ActuPwr;//实际功率
    uint8_t Flags[2];//各个状态标志
//    uint8_t Sts;//wptc状态
//    uint8_t IGBTCircProtc;  //IGBT短路/断路
//    uint8_t LeakWtrProtc;//WPTC漏水保护
//    uint8_t PCBTmpSnsrProtc;//PCB温度传感器故障保护
//    uint8_t WPTCTmpSnsrProtc;//wptc温度传感器保护
//    uint8_t OvrCurtProtc;//wptc过流保护
//    uint8_t HiVltOvrVltProtc;//高压过呀保护
//    uint8_t HiVltUndrVltProtc;//高压欠压
//    uint8_t LoVltOvrVltProtc;//低压过呀保护
}WPTC_STATUS;

typedef struct WPTC
{
    WPTC_CMD            cmd;
    WPTC_STATUS         status;
    uint8_t             input_tmp[8];
}WPTC;


#endif
