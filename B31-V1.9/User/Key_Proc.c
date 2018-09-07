#include "Key_Proc.h"

#include "hw_test.h"


void change_fan_slowly(u8 level)
{
    static u8 purpose=0;
    if(level==0xff)
    {
        if(s_Heat_Cap.Set_Fan>purpose)
        {
            s_Heat_Cap.Set_Fan-=10;
            if(s_Heat_Cap.Set_Fan<10)//风扇全关
            {
                s_Heat_Cap.AC_IN_STATUS=0;//关闭压缩机
                s_Heat_Cap.Tem_Purpose=0;//关闭温度显示
                s_Heat_Cap.Tem_Slave_Purpose=0;
            }
        }
        else if(s_Heat_Cap.Set_Fan<purpose)
        {
            s_Heat_Cap.Set_Fan+=10;
        }
    }
    else if(level==0xfe)
    {
        purpose=s_Heat_Cap.Set_Fan;
    }
    else
    {
        purpose=level;
    }
}

void set_fun(u8 level)
{
    s_Heat_Cap.Set_Fan=level;
    change_fan_slowly(0xfe);
}

void save_tem(void)
{
    s_FDEF_Last.Tem_Purpose=s_Heat_Cap.Tem_Purpose;//关闭温度显示
    s_FDEF_Last.Tem_Slave_Purpose=s_Heat_Cap.Tem_Slave_Purpose;
}

void tem_on(void)
{
    if(s_FDEF_Last.Tem_Purpose==0 && s_FDEF_Last.Tem_Slave_Purpose==0)
    {
        s_Heat_Cap.Tem_Purpose=250;
        s_Heat_Cap.Tem_Slave_Purpose=250;
        save_tem();
    }
    else
    {
        s_Heat_Cap.Tem_Purpose=s_FDEF_Last.Tem_Purpose;
        s_Heat_Cap.Tem_Slave_Purpose=s_FDEF_Last.Tem_Slave_Purpose;
    }
}

void ac_on(void)
{
    s_Heat_Cap.AC_IN_STATUS=1;
    s_FDEF_Last.AC_IN_Status_Last=s_Heat_Cap.AC_IN_STATUS;
}


void Key_Process(void)
{
    if(g_Key_Value & KEYAC_Pressed_MASK)    // AC 按键    ：压缩机
    {
        g_Key_Value &=(~KEYAC_Pressed_MASK);

        if(s_Heat_Cap.AC_IN_STATUS)//读AC状态
        {
            s_Heat_Cap.AC_IN_STATUS=0;//不允许开启压缩机
        }
        else
        {
            s_Heat_Cap.AC_IN_STATUS=1;//允许开启压缩机
        }
        s_FDEF_Last.AC_IN_Status_Last=s_Heat_Cap.AC_IN_STATUS;//手动按AC，保存AC状态：退出前除霜使用
        if(s_Heat_Cap.Set_Fan<10)//压缩机开启时，保证有风
        {
            set_fun(10);
//          s_Heat_Cap.Set_Fan=10;
            tem_on();
        }
        g_AUTO_Flag &= ~AUTO_AC_MASK ;       //解除自动AC
    }
  
    if(g_Key_Value & KEYMODE_Pressed_MASK)  // MODE 按键 ：各个出风口
    {
        g_Key_Value &=(~KEYMODE_Pressed_MASK);
        if(s_Heat_Cap.Mode_PPS<MODEFEDE)
        {
            s_Heat_Cap.Mode_PPS++;
        }
        else
        {
            s_Heat_Cap.Mode_PPS=MODEFACE;
        }
        Stop_Mode_Motor_P();
        g_AUTO_Flag &=~AUTO_MODE_MASK; //解除自动模式
    }
    if(g_Key_Value & KEYFDEF_Pressed_MASK)  // FDEF 按键：前面除霜
    {
        g_Key_Value &=(~KEYFDEF_Pressed_MASK);
        if(s_Heat_Cap.Mode_PPS==MODEFDEF)//退出除霜
        {
            exit_FDEF=1;
            s_Heat_Cap.AC_IN_STATUS = s_FDEF_Last.AC_IN_Status_Last;//恢复除霜前AC状态
            s_Heat_Cap.TAKE = s_FDEF_Last.REC_Status_Last;
            s_Heat_Cap.Mode_PPS = s_FDEF_Last.Mode_PPS_Last;
            g_AUTO_Flag = s_FDEF_Last.AUTO_Flag_Last;
            
            change_fan_slowly(s_FDEF_Last.Set_Fan_Last);
            s_FDEF_Last.Tem_Purpose=s_Heat_Cap.Tem_Purpose;
            s_FDEF_Last.Tem_Slave_Purpose=s_FDEF_Last.Tem_Slave_Purpose;
        }
        else//进入除霜
        {
            Fan_manual=0;
            exit_FDEF=0;
            s_FDEF_Last.Mode_PPS_Last = s_Heat_Cap.Mode_PPS;//保存模式
            s_FDEF_Last.AC_IN_Status_Last = s_Heat_Cap.AC_IN_STATUS;//保存AC状态
            s_FDEF_Last.Set_Fan_Last = s_Heat_Cap.Set_Fan;//保存风量
//          if(s_Heat_Cap.Set_Fan<50)//如果小于5档，则变为5档，如果大于5档，则不变
//          {
//              s_Heat_Cap.Set_Fan=50;//强制为5档风
//          }
            if(s_Heat_Cap.Set_Fan<10)
            {
                set_fun(10);
            }
            change_fan_slowly(50);
            if(s_FDEF_Last.Tem_Purpose==0 && s_FDEF_Last.Tem_Slave_Purpose==0)
            {
                s_Heat_Cap.Tem_Purpose=250;
                s_Heat_Cap.Tem_Slave_Purpose=250;
                s_FDEF_Last.Tem_Purpose=s_Heat_Cap.Tem_Purpose;
                s_FDEF_Last.Tem_Slave_Purpose=s_FDEF_Last.Tem_Purpose;
            }
            else
            {
                s_Heat_Cap.Tem_Purpose=s_FDEF_Last.Tem_Purpose;
                s_Heat_Cap.Tem_Slave_Purpose=s_FDEF_Last.Tem_Slave_Purpose;
            }
            s_FDEF_Last.REC_Status_Last = s_Heat_Cap.TAKE;//保存内外循环模式
            s_FDEF_Last.AUTO_Flag_Last = g_AUTO_Flag;
            s_Heat_Cap.Mode_PPS = MODEFDEF;//模式除霜：前
            s_Heat_Cap.AC_IN_STATUS = 1;//开AC
            s_Heat_Cap.TAKE = REC_OUTTake;//外循环
            g_AUTO_Flag = AUTO_TEMP_MASK;//退出自动
        }
        Stop_REC_Motor_P();
        Stop_Mode_Motor_P();
        Stop_TEMP_Motor_P();
    }
    
    if(g_Key_Value & KEYREC_Pressed_MASK)// REC 按键：内外循环
    {
        g_Key_Value &=(~KEYREC_Pressed_MASK);
        if(s_Heat_Cap.TAKE)
        {
            s_Heat_Cap.TAKE=REC_INTake;
        }
        else
        {
            s_Heat_Cap.TAKE=REC_OUTTake;
        }
        s_FDEF_Last.REC_Status_Last=s_Heat_Cap.TAKE;//手动按REC，保存REC状态
        Stop_REC_Motor_P();
        g_AUTO_Flag &=~AUTO_TAKE_MASK;
    }

    if(g_Key_Value & KEYRDEF_Pressed_MASK)  // RDEF 按键：后面除霜
    {
        g_Key_Value &=(~KEYRDEF_Pressed_MASK);
        if(s_Heat_Cap.RDEF_STATUS)
        {
            s_Heat_Cap.RDEF_STATUS=0;
        }
        else 
        {
            s_Heat_Cap.RDEF_STATUS=1;
        }
    }
  
    if(g_Key_Value & KEYAUTO_Pressed_MASK)//AUTO按键
    {
        g_Key_Value &=(~KEYAUTO_Pressed_MASK);
        g_AUTO_Flag = AUTO_TAKE_MASK | AUTO_MODE_MASK | AUTO_FAN_MASK | AUTO_AC_MASK | AUTO_TEMP_MASK | AUTO_PTC_MASK;
        if(s_Heat_Cap.Set_Fan==0)//如果无风，强制开启3档风：马上会交给auto控制
        {
            set_fun(30);
//          s_Heat_Cap.Set_Fan=30;
        }
        if(s_Heat_Cap.Mode_PPS==MODEFDEF)//退出除霜：如果正在除霜
        {
            s_Heat_Cap.Mode_PPS=s_FDEF_Last.Mode_PPS_Last;//模式切换为之前保存的状态
        }
        exit_FDEF=0;

        Stop_Mode_Motor_P();
    }
  
    if(g_Key_Value & KEYOFF_Pressed_MASK)//OFF按键
    {
        g_Key_Value &=(~KEYOFF_Pressed_MASK);
        s_Heat_Cap.AC_IN_STATUS=0;//AC关闭
        set_fun(s_Heat_Cap.Set_Fan_Now=0);//风机关闭
        g_AUTO_Flag = AUTO_TEMP_MASK;//退出AUTO
        s_Heat_Cap.PTC_IN_STATUS=0;//PTC关闭
        s_Heat_Cap.PM25_STATUS=0;//PM2.5关闭
        
        /*保存之前的温度*/
        if(s_Heat_Cap.Tem_Purpose!=0 && s_Heat_Cap.Tem_Slave_Purpose!=0)
        {
            s_FDEF_Last.Tem_Purpose=s_Heat_Cap.Tem_Purpose;
            s_FDEF_Last.Tem_Slave_Purpose=s_Heat_Cap.Tem_Slave_Purpose;
        
            s_Heat_Cap.Tem_Purpose=0;
            s_Heat_Cap.Tem_Slave_Purpose=0;
        }
        
        if(s_Heat_Cap.Mode_PPS==MODEFDEF)//如果是前除霜，则切换为之前状态
        {
            s_Heat_Cap.Mode_PPS=s_FDEF_Last.Mode_PPS_Last;
            Fan_manual=1;
        }
        
        exit_FDEF=0;
//      s_Heat_Cap.TAKE=REC_OUTTake;//外循环
//      Stop_REC_Motor();
        Stop_Mode_Motor_P();
    }

    if(g_Key_Value & KEYFAN_H_Pressed_MASK)  // 风量加
    {
        g_Key_Value &=(~KEYFAN_H_Pressed_MASK);
    
        Fan_manual=1;//手动调节风量标志
        if(s_Heat_Cap.Set_Fan%10)//整数档位
        {
            s_Heat_Cap.Set_Fan=10*(s_Heat_Cap.Set_Fan/10);
        }
        set_fun(s_Heat_Cap.Set_Fan+10);
        if(s_Heat_Cap.Set_Fan>80)//最大7档风->最大8档风
        {
            set_fun(80);
//          s_Heat_Cap.Set_Fan=80;
        }
        s_FDEF_Last.Set_Fan_Last=s_Heat_Cap.Set_Fan;
        //ac_on();
        tem_on();
        g_AUTO_Flag &=~AUTO_FAN_MASK;
    }
    
    if(g_Key_Value & KEYFAN_L_Pressed_MASK)// 风量减
    {
        g_Key_Value &=(~KEYFAN_L_Pressed_MASK);

        Fan_manual=1;
        if(s_Heat_Cap.Set_Fan%10)//整数档位
        {
            set_fun(10*(s_Heat_Cap.Set_Fan/10));
//          s_Heat_Cap.Set_Fan=10*(s_Heat_Cap.Set_Fan/10);
        }
        if(s_Heat_Cap.Set_Fan>10)//最小1档风
        {
            set_fun(s_Heat_Cap.Set_Fan-10);
//          s_Heat_Cap.Set_Fan-=10;
        }
        
        s_FDEF_Last.Set_Fan_Last=s_Heat_Cap.Set_Fan;
        //ac_on();
        tem_on();
        g_AUTO_Flag &=~AUTO_FAN_MASK;
    }

    /*  温度表示:0.1℃/LSB   */
    if(g_Key_Value & KEYTEMP_H_Pressed_MASK)    // 主驾驶温度加
    {
        g_Key_Value &=(~KEYTEMP_H_Pressed_MASK);
        
        if(s_Heat_Cap.Tem_Purpose==0 && 
            s_Heat_Cap.Tem_Slave_Purpose==0)//如果是关闭状态，则恢复之前的状态
        {
//          s_Heat_Cap.Tem_Slave_Purpose=s_FDEF_Last.Tem_Slave_Purpose;
//          s_Heat_Cap.Tem_Purpose=s_FDEF_Last.Tem_Purpose;
            tem_on();
        }
        else
        {
            if(s_Heat_Cap.Tem_Purpose<MAX_TEMSET-5)//范围限定
            {
                s_Heat_Cap.Tem_Purpose+=5;
            }
            else
            {
                s_Heat_Cap.Tem_Purpose=MAX_TEMSET-5;
//                  s_Heat_Cap.Set_Fan=80;
            }
            if((s_Heat_Cap.Tem_Purpose-s_Heat_Cap.Tem_Slave_Purpose)>40)//主副驾驶之间的温度差不能太大
            {
                s_Heat_Cap.Tem_Slave_Purpose=s_Heat_Cap.Tem_Purpose-40;
            }
            if(s_Heat_Cap.Tem_Slave_Purpose==(MIN_TEMSET+5))//必须同时处在Lo或者Hi状态
            {
                s_Heat_Cap.Tem_Slave_Purpose+=5;
            }
            if(s_Heat_Cap.Tem_Purpose==MAX_TEMSET-5)
            {
                s_Heat_Cap.Tem_Slave_Purpose=MAX_TEMSET-5;
            }

            if(s_Heat_Cap.DUAL_STATUS) ///跟随模式
            {
                s_Heat_Cap.Tem_Slave_Purpose=s_Heat_Cap.Tem_Purpose;
            }
        }
        
        if(s_Heat_Cap.Set_Fan<10)
        {
            set_fun(10);
//          s_Heat_Cap.Set_Fan=10;
        }
        save_tem();
        Stop_TEMP_Motor_P();
    }

    if(g_Key_Value & KEYTEMP_L_Pressed_MASK){    //主驾驶温度减
        g_Key_Value &=(~KEYTEMP_L_Pressed_MASK);
        
        if(s_Heat_Cap.Tem_Purpose==0 && 
            s_Heat_Cap.Tem_Slave_Purpose==0)//如果是关闭状态，则恢复之前的状态
        {
//            s_Heat_Cap.Tem_Slave_Purpose=s_FDEF_Last.Tem_Slave_Purpose;
//            s_Heat_Cap.Tem_Purpose=s_FDEF_Last.Tem_Purpose;
            tem_on();
        }
        else
        {   if(s_Heat_Cap.Tem_Purpose>MIN_TEMSET+5)//范围限定
            {
                s_Heat_Cap.Tem_Purpose-=5;
            }
            else
            {
                s_Heat_Cap.Tem_Purpose=MIN_TEMSET+5;
//              s_Heat_Cap.Set_Fan=80;
            }

            if((s_Heat_Cap.Tem_Slave_Purpose-s_Heat_Cap.Tem_Purpose)>40)    //主副驾驶之间的温度差不能太大
            {
                s_Heat_Cap.Tem_Slave_Purpose=s_Heat_Cap.Tem_Purpose+40;
            }
            if(s_Heat_Cap.Tem_Slave_Purpose==(MAX_TEMSET-5))//必须同时处在Lo或者Hi状态
            {
                s_Heat_Cap.Tem_Slave_Purpose-=5;
            }
            if(s_Heat_Cap.Tem_Purpose==MIN_TEMSET+5)
            {
                s_Heat_Cap.Tem_Slave_Purpose=MIN_TEMSET+5;
            }

            if(s_Heat_Cap.DUAL_STATUS) ///跟随模式
            {
                s_Heat_Cap.Tem_Slave_Purpose=s_Heat_Cap.Tem_Purpose;
            }
        }
        
        if(s_Heat_Cap.Set_Fan<10)
        {
            set_fun(10);
//          s_Heat_Cap.Set_Fan=10;
        }
        save_tem();
        Stop_TEMP_Motor_P();
    }
    
    if(g_Key_Value & KEYTEMP_SLAVE_L_Pressed_MASK){//副驾驶温度降低
        g_Key_Value &=(~KEYTEMP_SLAVE_L_Pressed_MASK);
        
        if(s_Heat_Cap.Tem_Outside>0)
        {
            s_Heat_Cap.Tem_Outside-=10;
        }
        else
        {
            s_Heat_Cap.Tem_Outside=0;
        }
        
        if(s_Heat_Cap.Tem_Purpose==0 && 
            s_Heat_Cap.Tem_Slave_Purpose==0){//如果是关闭状态，则恢复之前的状态
//            s_Heat_Cap.Tem_Slave_Purpose=s_FDEF_Last.Tem_Slave_Purpose;
//            s_Heat_Cap.Tem_Purpose=s_FDEF_Last.Tem_Purpose;
            tem_on();
        }
        else{
            if(s_Heat_Cap.Tem_Slave_Purpose>MIN_TEMSET+5)//范围限定
            {
                s_Heat_Cap.Tem_Slave_Purpose-=5;
            }
            else
            {
                s_Heat_Cap.Tem_Slave_Purpose=MIN_TEMSET+5;
//              s_Heat_Cap.Set_Fan=80;
            }
            
            if((s_Heat_Cap.Tem_Purpose-s_Heat_Cap.Tem_Slave_Purpose)>40)    //主副驾驶之间的温度差不能太大
            {
                s_Heat_Cap.Tem_Purpose=s_Heat_Cap.Tem_Slave_Purpose+40;
            }
            if(s_Heat_Cap.Tem_Purpose==(MAX_TEMSET-5))//必须同时处在Lo或者Hi状态
            {
                s_Heat_Cap.Tem_Purpose-=5;
            }
            if(s_Heat_Cap.Tem_Slave_Purpose==MIN_TEMSET+5)
            {
                s_Heat_Cap.Tem_Purpose=MIN_TEMSET+5;
            }

            if(s_Heat_Cap.DUAL_STATUS) ///跟随模式
            {
                s_Heat_Cap.Tem_Purpose=s_Heat_Cap.Tem_Slave_Purpose;
            }
        }
        if(s_Heat_Cap.Set_Fan<10)
        {
            set_fun(10);
//          s_Heat_Cap.Set_Fan=10;
        }
        
        save_tem();

        Stop_TEMP_Motor_P();
    }
    
    if(g_Key_Value & KEYTEMP_SLAVE_H_Pressed_MASK)//副驾驶温度增加
    {
        g_Key_Value &=(~KEYTEMP_SLAVE_H_Pressed_MASK);
        
        if(s_Heat_Cap.Tem_Outside<1000)
        {
            s_Heat_Cap.Tem_Outside+=10;
        }
        else
        {
            s_Heat_Cap.Tem_Outside=1000;
        }
        
        if(s_Heat_Cap.Tem_Purpose==0 && 
            s_Heat_Cap.Tem_Slave_Purpose==0)//如果是关闭状态，则恢复之前的状态
        {
//            s_Heat_Cap.Tem_Slave_Purpose=s_FDEF_Last.Tem_Slave_Purpose;
//            s_Heat_Cap.Tem_Purpose=s_FDEF_Last.Tem_Purpose;
            tem_on();
        }
        else
        {
            if(s_Heat_Cap.Tem_Slave_Purpose<MAX_TEMSET-5)//范围限定
            {
                s_Heat_Cap.Tem_Slave_Purpose+=5;
            }
            else
            {
                s_Heat_Cap.Tem_Slave_Purpose=MAX_TEMSET-5;
//              s_Heat_Cap.Set_Fan=80;
            }
            
            if((s_Heat_Cap.Tem_Slave_Purpose-s_Heat_Cap.Tem_Purpose)>40)//主副驾驶之间的温度差不能太大
            {
                s_Heat_Cap.Tem_Purpose=s_Heat_Cap.Tem_Slave_Purpose-40;
            }
            if(s_Heat_Cap.Tem_Purpose==(MIN_TEMSET+5))//必须同时处在Lo或者Hi状态
            {
                s_Heat_Cap.Tem_Purpose+=5;
            }
            if(s_Heat_Cap.Tem_Slave_Purpose==MAX_TEMSET-5)
            {
                s_Heat_Cap.Tem_Purpose=MAX_TEMSET-5;
            }
            if(s_Heat_Cap.DUAL_STATUS) ///跟随模式
            {
                s_Heat_Cap.Tem_Purpose=s_Heat_Cap.Tem_Slave_Purpose;
            }
        }
        if(s_Heat_Cap.Set_Fan<10)
        {
            set_fun(10);
//          s_Heat_Cap.Set_Fan=10;
        }
        save_tem();
        Stop_TEMP_Motor_P();
    }

    if(g_Key_Value & KEYDULE_Pressed_MASK)//副驾驶跟随
    {
        g_Key_Value &=(~KEYDULE_Pressed_MASK);
        
        if(s_Heat_Cap.DUAL_STATUS==0)
        {
            s_Heat_Cap.DUAL_STATUS=1;
            s_Heat_Cap.Tem_Slave_Purpose=s_Heat_Cap.Tem_Purpose;
        }
        else
        {
            s_Heat_Cap.DUAL_STATUS=0;
        }
    }
    
    #if 0
    if(g_Key_Value & KEYFDEF2_Pressed_MASK) // 前挡加热
    {
        g_Key_Value &=(~KEYFDEF2_Pressed_MASK);
        if(s_Heat_Cap.FDEF2_STATUS)
        {
            s_Heat_Cap.FDEF2_STATUS=0;
        }
        else
        {
            s_Heat_Cap.FDEF2_STATUS=1;
        }
    }
    
    if(g_Key_Value & KEYSEATL_Pressed_MASK) // 左座椅加热
    {
        g_Key_Value &=(~KEYSEATL_Pressed_MASK);
        if(s_Heat_Cap.SEATL_STATUS)
        {
            s_Heat_Cap.SEATL_STATUS=0;
        }
        else
        {
            s_Heat_Cap.SEATL_STATUS=1;
        }
    }
    
    if(g_Key_Value & KEYSEATR_Pressed_MASK) //右座椅加热
    {
        g_Key_Value &=(~KEYSEATR_Pressed_MASK);
        if(s_Heat_Cap.SEATR_STATUS)
        {
            s_Heat_Cap.SEATR_STATUS=0;
        }
        else
        {
            s_Heat_Cap.SEATR_STATUS=1;
        }
    }
  if(g_Key_Value & KEYPM25_Pressed_MASK)
    {
        g_Key_Value &= (~KEYPM25_Pressed_MASK);
        if(s_Heat_Cap.PM25_STATUS)
        {
            s_Heat_Cap.PM25_STATUS=0;
        }
        else
        {
            s_Heat_Cap.PM25_STATUS=1;
            if(s_Heat_Cap.Set_Fan==0)
      {
        s_Heat_Cap.Set_Fan=10;
      }
        }
    }
    #endif
}

//end
