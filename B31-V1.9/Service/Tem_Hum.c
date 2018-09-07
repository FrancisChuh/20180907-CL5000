#include "Tem_Hum.h"

AUTO_FDEF_TypeDef s_DEW_Point={250,0,0};

void Get_Tem_Hum(void)
{
//  s_DEW_Point.FDEF_HUM=1250*s_AD_Val.AD_PRESSHI/0xFFF-125;
//  s_DEW_Point.FDEF_TEM=2187.5*s_AD_Val.AD_PRESSLOW/0xFFF-668.75;
//  s_DEW_Point.DEW_TEM=Tem_Dew(&s_DEW_Point);
}

int16_t Tem_Dew(AUTO_FDEF_TypeDef* s_AUTO_FDEF_TypeDef)
{
  AUTO_FDEF_TypeDef s_AUTO_FDEF=*s_AUTO_FDEF_TypeDef;
  int16_t Temp_Dew_Point;
  double a,b;
  
  if(s_AUTO_FDEF.FDEF_TEM>0)
  {
    a=log((double)s_AUTO_FDEF.FDEF_HUM/1000)+(17.62*s_AUTO_FDEF.FDEF_TEM/10)/(243.12+s_AUTO_FDEF.FDEF_TEM/10);
    b=17.62-log((double)s_AUTO_FDEF.FDEF_HUM/1000)-(17.62*s_AUTO_FDEF.FDEF_TEM/10)/(243.12+s_AUTO_FDEF.FDEF_TEM/10);
    Temp_Dew_Point=2431.2*a/b;
  }
  else
  {
    a=log((double)s_AUTO_FDEF.FDEF_HUM/1000)+(22.46*s_AUTO_FDEF.FDEF_TEM/10)/(272.62+s_AUTO_FDEF.FDEF_TEM/10);
    b=22.46-log((double)s_AUTO_FDEF.FDEF_HUM/1000)-(22.46*s_AUTO_FDEF.FDEF_TEM/10)/(272.62+s_AUTO_FDEF.FDEF_TEM/10);
    Temp_Dew_Point=2726.2*a/b;
  }
  return Temp_Dew_Point;
}
//end
