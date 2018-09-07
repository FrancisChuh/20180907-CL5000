#ifndef _CAN_PROC_H__
#define _CAN_PROC_H__

#include "common.h"

#define break_count_times   300//秒，连续踩刹车超过5min*60=300s
#define break_tip_times		30//秒，休息30s
#define SpUp_count_times	60//秒，连续重踩油门超过1min*60=600s
#define SpUp_tip_times		30//秒，休息30s

#define MIN_RPM_TH						550//800rpm,判断发动机启动

#define SpeedRPM_TH						950//800rpm,判断刹车
#define VehicleSpeed_Break_TH 50//5km/h,判断刹车

void CAN_RX_Proc(void);
void CAN_TX_Proc(void);

#endif
