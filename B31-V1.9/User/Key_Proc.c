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
            if(s_Heat_Cap.Set_Fan<10)//����ȫ��
            {
                s_Heat_Cap.AC_IN_STATUS=0;//�ر�ѹ����
                s_Heat_Cap.Tem_Purpose=0;//�ر��¶���ʾ
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
    s_FDEF_Last.Tem_Purpose=s_Heat_Cap.Tem_Purpose;//�ر��¶���ʾ
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
    if(g_Key_Value & KEYAC_Pressed_MASK)    // AC ����    ��ѹ����
    {
        g_Key_Value &=(~KEYAC_Pressed_MASK);

        if(s_Heat_Cap.AC_IN_STATUS)//��AC״̬
        {
            s_Heat_Cap.AC_IN_STATUS=0;//��������ѹ����
        }
        else
        {
            s_Heat_Cap.AC_IN_STATUS=1;//������ѹ����
        }
        s_FDEF_Last.AC_IN_Status_Last=s_Heat_Cap.AC_IN_STATUS;//�ֶ���AC������AC״̬���˳�ǰ��˪ʹ��
        if(s_Heat_Cap.Set_Fan<10)//ѹ��������ʱ����֤�з�
        {
            set_fun(10);
//          s_Heat_Cap.Set_Fan=10;
            tem_on();
        }
        g_AUTO_Flag &= ~AUTO_AC_MASK ;       //����Զ�AC
    }
  
    if(g_Key_Value & KEYMODE_Pressed_MASK)  // MODE ���� �����������
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
        g_AUTO_Flag &=~AUTO_MODE_MASK; //����Զ�ģʽ
    }
    if(g_Key_Value & KEYFDEF_Pressed_MASK)  // FDEF ������ǰ���˪
    {
        g_Key_Value &=(~KEYFDEF_Pressed_MASK);
        if(s_Heat_Cap.Mode_PPS==MODEFDEF)//�˳���˪
        {
            exit_FDEF=1;
            s_Heat_Cap.AC_IN_STATUS = s_FDEF_Last.AC_IN_Status_Last;//�ָ���˪ǰAC״̬
            s_Heat_Cap.TAKE = s_FDEF_Last.REC_Status_Last;
            s_Heat_Cap.Mode_PPS = s_FDEF_Last.Mode_PPS_Last;
            g_AUTO_Flag = s_FDEF_Last.AUTO_Flag_Last;
            
            change_fan_slowly(s_FDEF_Last.Set_Fan_Last);
            s_FDEF_Last.Tem_Purpose=s_Heat_Cap.Tem_Purpose;
            s_FDEF_Last.Tem_Slave_Purpose=s_FDEF_Last.Tem_Slave_Purpose;
        }
        else//�����˪
        {
            Fan_manual=0;
            exit_FDEF=0;
            s_FDEF_Last.Mode_PPS_Last = s_Heat_Cap.Mode_PPS;//����ģʽ
            s_FDEF_Last.AC_IN_Status_Last = s_Heat_Cap.AC_IN_STATUS;//����AC״̬
            s_FDEF_Last.Set_Fan_Last = s_Heat_Cap.Set_Fan;//�������
//          if(s_Heat_Cap.Set_Fan<50)//���С��5�������Ϊ5�����������5�����򲻱�
//          {
//              s_Heat_Cap.Set_Fan=50;//ǿ��Ϊ5����
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
            s_FDEF_Last.REC_Status_Last = s_Heat_Cap.TAKE;//��������ѭ��ģʽ
            s_FDEF_Last.AUTO_Flag_Last = g_AUTO_Flag;
            s_Heat_Cap.Mode_PPS = MODEFDEF;//ģʽ��˪��ǰ
            s_Heat_Cap.AC_IN_STATUS = 1;//��AC
            s_Heat_Cap.TAKE = REC_OUTTake;//��ѭ��
            g_AUTO_Flag = AUTO_TEMP_MASK;//�˳��Զ�
        }
        Stop_REC_Motor_P();
        Stop_Mode_Motor_P();
        Stop_TEMP_Motor_P();
    }
    
    if(g_Key_Value & KEYREC_Pressed_MASK)// REC ����������ѭ��
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
        s_FDEF_Last.REC_Status_Last=s_Heat_Cap.TAKE;//�ֶ���REC������REC״̬
        Stop_REC_Motor_P();
        g_AUTO_Flag &=~AUTO_TAKE_MASK;
    }

    if(g_Key_Value & KEYRDEF_Pressed_MASK)  // RDEF �����������˪
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
  
    if(g_Key_Value & KEYAUTO_Pressed_MASK)//AUTO����
    {
        g_Key_Value &=(~KEYAUTO_Pressed_MASK);
        g_AUTO_Flag = AUTO_TAKE_MASK | AUTO_MODE_MASK | AUTO_FAN_MASK | AUTO_AC_MASK | AUTO_TEMP_MASK | AUTO_PTC_MASK;
        if(s_Heat_Cap.Set_Fan==0)//����޷磬ǿ�ƿ���3���磺���ϻύ��auto����
        {
            set_fun(30);
//          s_Heat_Cap.Set_Fan=30;
        }
        if(s_Heat_Cap.Mode_PPS==MODEFDEF)//�˳���˪��������ڳ�˪
        {
            s_Heat_Cap.Mode_PPS=s_FDEF_Last.Mode_PPS_Last;//ģʽ�л�Ϊ֮ǰ�����״̬
        }
        exit_FDEF=0;

        Stop_Mode_Motor_P();
    }
  
    if(g_Key_Value & KEYOFF_Pressed_MASK)//OFF����
    {
        g_Key_Value &=(~KEYOFF_Pressed_MASK);
        s_Heat_Cap.AC_IN_STATUS=0;//AC�ر�
        set_fun(s_Heat_Cap.Set_Fan_Now=0);//����ر�
        g_AUTO_Flag = AUTO_TEMP_MASK;//�˳�AUTO
        s_Heat_Cap.PTC_IN_STATUS=0;//PTC�ر�
        s_Heat_Cap.PM25_STATUS=0;//PM2.5�ر�
        
        /*����֮ǰ���¶�*/
        if(s_Heat_Cap.Tem_Purpose!=0 && s_Heat_Cap.Tem_Slave_Purpose!=0)
        {
            s_FDEF_Last.Tem_Purpose=s_Heat_Cap.Tem_Purpose;
            s_FDEF_Last.Tem_Slave_Purpose=s_Heat_Cap.Tem_Slave_Purpose;
        
            s_Heat_Cap.Tem_Purpose=0;
            s_Heat_Cap.Tem_Slave_Purpose=0;
        }
        
        if(s_Heat_Cap.Mode_PPS==MODEFDEF)//�����ǰ��˪�����л�Ϊ֮ǰ״̬
        {
            s_Heat_Cap.Mode_PPS=s_FDEF_Last.Mode_PPS_Last;
            Fan_manual=1;
        }
        
        exit_FDEF=0;
//      s_Heat_Cap.TAKE=REC_OUTTake;//��ѭ��
//      Stop_REC_Motor();
        Stop_Mode_Motor_P();
    }

    if(g_Key_Value & KEYFAN_H_Pressed_MASK)  // ������
    {
        g_Key_Value &=(~KEYFAN_H_Pressed_MASK);
    
        Fan_manual=1;//�ֶ����ڷ�����־
        if(s_Heat_Cap.Set_Fan%10)//������λ
        {
            s_Heat_Cap.Set_Fan=10*(s_Heat_Cap.Set_Fan/10);
        }
        set_fun(s_Heat_Cap.Set_Fan+10);
        if(s_Heat_Cap.Set_Fan>80)//���7����->���8����
        {
            set_fun(80);
//          s_Heat_Cap.Set_Fan=80;
        }
        s_FDEF_Last.Set_Fan_Last=s_Heat_Cap.Set_Fan;
        //ac_on();
        tem_on();
        g_AUTO_Flag &=~AUTO_FAN_MASK;
    }
    
    if(g_Key_Value & KEYFAN_L_Pressed_MASK)// ������
    {
        g_Key_Value &=(~KEYFAN_L_Pressed_MASK);

        Fan_manual=1;
        if(s_Heat_Cap.Set_Fan%10)//������λ
        {
            set_fun(10*(s_Heat_Cap.Set_Fan/10));
//          s_Heat_Cap.Set_Fan=10*(s_Heat_Cap.Set_Fan/10);
        }
        if(s_Heat_Cap.Set_Fan>10)//��С1����
        {
            set_fun(s_Heat_Cap.Set_Fan-10);
//          s_Heat_Cap.Set_Fan-=10;
        }
        
        s_FDEF_Last.Set_Fan_Last=s_Heat_Cap.Set_Fan;
        //ac_on();
        tem_on();
        g_AUTO_Flag &=~AUTO_FAN_MASK;
    }

    /*  �¶ȱ�ʾ:0.1��/LSB   */
    if(g_Key_Value & KEYTEMP_H_Pressed_MASK)    // ����ʻ�¶ȼ�
    {
        g_Key_Value &=(~KEYTEMP_H_Pressed_MASK);
        
        if(s_Heat_Cap.Tem_Purpose==0 && 
            s_Heat_Cap.Tem_Slave_Purpose==0)//����ǹر�״̬����ָ�֮ǰ��״̬
        {
//          s_Heat_Cap.Tem_Slave_Purpose=s_FDEF_Last.Tem_Slave_Purpose;
//          s_Heat_Cap.Tem_Purpose=s_FDEF_Last.Tem_Purpose;
            tem_on();
        }
        else
        {
            if(s_Heat_Cap.Tem_Purpose<MAX_TEMSET-5)//��Χ�޶�
            {
                s_Heat_Cap.Tem_Purpose+=5;
            }
            else
            {
                s_Heat_Cap.Tem_Purpose=MAX_TEMSET-5;
//                  s_Heat_Cap.Set_Fan=80;
            }
            if((s_Heat_Cap.Tem_Purpose-s_Heat_Cap.Tem_Slave_Purpose)>40)//������ʻ֮����¶Ȳ��̫��
            {
                s_Heat_Cap.Tem_Slave_Purpose=s_Heat_Cap.Tem_Purpose-40;
            }
            if(s_Heat_Cap.Tem_Slave_Purpose==(MIN_TEMSET+5))//����ͬʱ����Lo����Hi״̬
            {
                s_Heat_Cap.Tem_Slave_Purpose+=5;
            }
            if(s_Heat_Cap.Tem_Purpose==MAX_TEMSET-5)
            {
                s_Heat_Cap.Tem_Slave_Purpose=MAX_TEMSET-5;
            }

            if(s_Heat_Cap.DUAL_STATUS) ///����ģʽ
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

    if(g_Key_Value & KEYTEMP_L_Pressed_MASK){    //����ʻ�¶ȼ�
        g_Key_Value &=(~KEYTEMP_L_Pressed_MASK);
        
        if(s_Heat_Cap.Tem_Purpose==0 && 
            s_Heat_Cap.Tem_Slave_Purpose==0)//����ǹر�״̬����ָ�֮ǰ��״̬
        {
//            s_Heat_Cap.Tem_Slave_Purpose=s_FDEF_Last.Tem_Slave_Purpose;
//            s_Heat_Cap.Tem_Purpose=s_FDEF_Last.Tem_Purpose;
            tem_on();
        }
        else
        {   if(s_Heat_Cap.Tem_Purpose>MIN_TEMSET+5)//��Χ�޶�
            {
                s_Heat_Cap.Tem_Purpose-=5;
            }
            else
            {
                s_Heat_Cap.Tem_Purpose=MIN_TEMSET+5;
//              s_Heat_Cap.Set_Fan=80;
            }

            if((s_Heat_Cap.Tem_Slave_Purpose-s_Heat_Cap.Tem_Purpose)>40)    //������ʻ֮����¶Ȳ��̫��
            {
                s_Heat_Cap.Tem_Slave_Purpose=s_Heat_Cap.Tem_Purpose+40;
            }
            if(s_Heat_Cap.Tem_Slave_Purpose==(MAX_TEMSET-5))//����ͬʱ����Lo����Hi״̬
            {
                s_Heat_Cap.Tem_Slave_Purpose-=5;
            }
            if(s_Heat_Cap.Tem_Purpose==MIN_TEMSET+5)
            {
                s_Heat_Cap.Tem_Slave_Purpose=MIN_TEMSET+5;
            }

            if(s_Heat_Cap.DUAL_STATUS) ///����ģʽ
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
    
    if(g_Key_Value & KEYTEMP_SLAVE_L_Pressed_MASK){//����ʻ�¶Ƚ���
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
            s_Heat_Cap.Tem_Slave_Purpose==0){//����ǹر�״̬����ָ�֮ǰ��״̬
//            s_Heat_Cap.Tem_Slave_Purpose=s_FDEF_Last.Tem_Slave_Purpose;
//            s_Heat_Cap.Tem_Purpose=s_FDEF_Last.Tem_Purpose;
            tem_on();
        }
        else{
            if(s_Heat_Cap.Tem_Slave_Purpose>MIN_TEMSET+5)//��Χ�޶�
            {
                s_Heat_Cap.Tem_Slave_Purpose-=5;
            }
            else
            {
                s_Heat_Cap.Tem_Slave_Purpose=MIN_TEMSET+5;
//              s_Heat_Cap.Set_Fan=80;
            }
            
            if((s_Heat_Cap.Tem_Purpose-s_Heat_Cap.Tem_Slave_Purpose)>40)    //������ʻ֮����¶Ȳ��̫��
            {
                s_Heat_Cap.Tem_Purpose=s_Heat_Cap.Tem_Slave_Purpose+40;
            }
            if(s_Heat_Cap.Tem_Purpose==(MAX_TEMSET-5))//����ͬʱ����Lo����Hi״̬
            {
                s_Heat_Cap.Tem_Purpose-=5;
            }
            if(s_Heat_Cap.Tem_Slave_Purpose==MIN_TEMSET+5)
            {
                s_Heat_Cap.Tem_Purpose=MIN_TEMSET+5;
            }

            if(s_Heat_Cap.DUAL_STATUS) ///����ģʽ
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
    
    if(g_Key_Value & KEYTEMP_SLAVE_H_Pressed_MASK)//����ʻ�¶�����
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
            s_Heat_Cap.Tem_Slave_Purpose==0)//����ǹر�״̬����ָ�֮ǰ��״̬
        {
//            s_Heat_Cap.Tem_Slave_Purpose=s_FDEF_Last.Tem_Slave_Purpose;
//            s_Heat_Cap.Tem_Purpose=s_FDEF_Last.Tem_Purpose;
            tem_on();
        }
        else
        {
            if(s_Heat_Cap.Tem_Slave_Purpose<MAX_TEMSET-5)//��Χ�޶�
            {
                s_Heat_Cap.Tem_Slave_Purpose+=5;
            }
            else
            {
                s_Heat_Cap.Tem_Slave_Purpose=MAX_TEMSET-5;
//              s_Heat_Cap.Set_Fan=80;
            }
            
            if((s_Heat_Cap.Tem_Slave_Purpose-s_Heat_Cap.Tem_Purpose)>40)//������ʻ֮����¶Ȳ��̫��
            {
                s_Heat_Cap.Tem_Purpose=s_Heat_Cap.Tem_Slave_Purpose-40;
            }
            if(s_Heat_Cap.Tem_Purpose==(MIN_TEMSET+5))//����ͬʱ����Lo����Hi״̬
            {
                s_Heat_Cap.Tem_Purpose+=5;
            }
            if(s_Heat_Cap.Tem_Slave_Purpose==MAX_TEMSET-5)
            {
                s_Heat_Cap.Tem_Purpose=MAX_TEMSET-5;
            }
            if(s_Heat_Cap.DUAL_STATUS) ///����ģʽ
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

    if(g_Key_Value & KEYDULE_Pressed_MASK)//����ʻ����
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
    if(g_Key_Value & KEYFDEF2_Pressed_MASK) // ǰ������
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
    
    if(g_Key_Value & KEYSEATL_Pressed_MASK) // �����μ���
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
    
    if(g_Key_Value & KEYSEATR_Pressed_MASK) //�����μ���
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
