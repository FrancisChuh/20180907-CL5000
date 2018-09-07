#include "temper.h"

const u16 EVA_temper_array[26]={//蒸发器温度
  0xE4D,//-40℃
  0xDC0,//-35℃
  0xD01,//-30℃
  0xC36,//-25℃
  0xB52,//-20℃
  0xA5A,//-15℃
  0x956,//-10℃
  0x84F,//-5℃	
  0x74D,// 0℃	
  0x658,// 5℃	
  0x576,//10℃
  0x4AA,//15℃
  0x3F6,//20℃
  0x359,//25℃
  0x2D2,//30℃
  0x260,//35℃
  0x1FF,//40℃
  0x1AE,//45℃
  0x16A,//50℃
  0x136,//55℃
  0x101,//60℃
  0xDD ,//65℃
  0xB9 ,//70℃
  0xA0 ,//75℃
  0x86 ,//80℃
  0x74  //85℃
};

const u16 Sun_Photo_array[11]={//阳光，0-10,11个照度数值，反推温度
  0xFFF,  //0W/m2
  0xE68,  //100W/m2
  0xCD2,  //200W/m2
  0xB3C,  //300W/m2
  0x9A6,  //400W/m2
  0x80F,  //500W/m2
  0x679,  //600W/m2
  0x4E3,  //700W/m2
  0x34D,  //800W/m2
  0x1B6,  //900W/m2
  0x20   //1000W/m2
};

const u16 OUT_temper_array[24]={//外温传感器数值
  0xDB2,//-30℃
  0xD1D,//-25℃
  0xC71,//-20℃
  0xBB2,//-15℃
  0xAE2,//-10℃
  0xA06,//-5℃	
  0x925,// 0℃	
  0x844,// 5℃	
  0x767,//10℃
  0x695,//15℃
  0x5CF,//20℃
  0x519,//25℃
  0x475,//30℃
  0x3E2,//35℃
  0x360,//40℃
  0x2EF,//45℃
  0x28C,//50℃
  0x234,//55℃
  0x1EC,//60℃
  0x1AA,//65℃
  0x172,//70℃
  0x142,//75℃
  0x11A,//80℃
  0xF5  //85℃
};

const u16 IN_temper_array[24]={//内温传感器数值
  0xDB2,//-30℃
  0xD1D,//-25℃
  0xC71,//-20℃
  0xBB2,//-15℃
  0xAE2,//-10℃
  0xA06,//-5℃	
  0x925,// 0℃	
  0x844,// 5℃	
  0x767,//10℃
  0x695,//15℃
  0x5CF,//20℃
  0x519,//25℃
  0x475,//30℃
  0x3E2,//35℃
  0x360,//40℃
  0x2EF,//45℃
  0x28C,//50℃
  0x234,//55℃
  0x1EC,//60℃
  0x1AA,//65℃
  0x172,//70℃
  0x142,//75℃
  0x11A,//80℃
  0xF5  //85℃
};

const u16 PIPE_temper_array[19]={//管路温度
  0xF85,  //-40℃
  0xF1D,  //-30℃
  0xE77,  //-20℃
  0xD80,  //-10℃
  0xC31,  //0℃
  0xA98,  //10℃
  0x8D7,  //20℃
  0x716,  //30℃
  0x57F,  //40℃
  0x42B,  //50℃
  0x320,  //60℃
  0x255,  //70℃
  0x1BE,  //80℃
  0x14F,  //90℃
  0xFE ,  //100℃
  0xC2 ,  //110℃
  0x96 ,  //120℃
  0x75 ,  //130℃
  0x5A    //140℃
};

const u16 WIND_temper_array[29]={//风道温度传感器数值
  0xE34,//-40
  0xDB1,//-35
  0xD16,//-30
  0xC64,//-25
  0xB9E,//-20
  0xAC7,//-15
  0x9E5,//-10
  0x8FD,//-5
  0x817,//0
  0x738,//5
  0x662,//10
  0x59D,//15
  0x4E9,//20
  0x446,//25
  0x3B7,//30
  0x337,//35
  0x2C9,//40
  0x269,//45
  0x217,//50
  0x1CF,//55
  0x192,//60
  0x15D,//65
  0x130,//70
  0x109,//75
  0x0E8,//80
  0x0CC,//85
  0x0B4,//90
  0x09E,//95
  0x08C //100
};


int16_t convert_temper_EVA(u16 temper_hex)//蒸发器温度十六进制电压值转10进制温度值
{
  u8 index;
  if(temper_hex>EVA_temper_array[0])
  {
    return -9999;
  }
  else if(temper_hex<EVA_temper_array[25])
  {
    return 9999;
  }
  index=1;//肯定不比[0]大
  while(temper_hex<EVA_temper_array[index])//算出位于哪个区间
  {
    index++;
  }
  return (-50)*(temper_hex-EVA_temper_array[index])/(EVA_temper_array[index-1]-EVA_temper_array[index])+(index*50-400);
}

u16 convert_PHOTO_SUN(u16 temper_hex)//阳关照度十六进制电压值转10进制温度值
{
  u8 index;
  if(temper_hex>Sun_Photo_array[0])
  {
    return 0;
  }
  else if(temper_hex<Sun_Photo_array[10])
  {
    return 1000;
  }
  index=1;//肯定不比[0]大
  while(temper_hex<Sun_Photo_array[index])//算出位于哪个区间
  {
    index++;
  }
  return (-100)*(temper_hex-Sun_Photo_array[index])/(Sun_Photo_array[index-1]-Sun_Photo_array[index])+(index*100);
}

int16_t convert_Temper_OUT(u16 temper_hex)//车外温度十六进制电压值转10进制温度值
{
  u8 index;
  if(temper_hex>OUT_temper_array[0])
  {
    return -9999;
  }
  else if(temper_hex<OUT_temper_array[23])
  {
    return 9999;
  }
  index=1;//肯定不比[0]大
  while(temper_hex<OUT_temper_array[index])//算出位于哪个区间
  {
    index++;
  }
  return (-50)*(temper_hex-OUT_temper_array[index])/(OUT_temper_array[index-1]-OUT_temper_array[index])+(index*50-300);
}

int16_t convert_Temper_IN(u16 temper_hex)//车内温度十六进制电压值转10进制温度值
{
  u8 index;
  if(temper_hex>IN_temper_array[0])
  {
    return -9999;
  }
  else if(temper_hex<IN_temper_array[23])
  {
    return 9999;
  }
  index=1;//肯定不比[0]大
  while(temper_hex<IN_temper_array[index])//算出位于哪个区间
  {
    index++;
  }
  return (-50)*(temper_hex-IN_temper_array[index])/(IN_temper_array[index-1]-IN_temper_array[index])+(index*50-300);
}

int16_t convert_Temper_Pipe(u16 temper_hex)//管路温度
{
  u8 index;
  if(temper_hex>PIPE_temper_array[0])
  {
    return -9999;
  }
  else if(temper_hex<PIPE_temper_array[18])
  {
    return 9999;
  }
  index=1;//肯定不比[0]大
  while(temper_hex<PIPE_temper_array[index])//算出位于哪个区间
  {
    index++;
  }
  return (-100)*(temper_hex-PIPE_temper_array[index])/(PIPE_temper_array[index-1]-PIPE_temper_array[index])+(index*100-400);
}

int16_t convert_Temper_wind(u16 temper_hex)//风道温度十六进制电压值转10进制温度值
{
  u8 index;
  if(temper_hex>WIND_temper_array[0])
  {
    return -9999;
  }
  else if(temper_hex<WIND_temper_array[28])
  {
    return 9999;
  }
  index=1;//肯定不比[0]大
  while(temper_hex<WIND_temper_array[index])//算出位于哪个区间
  {
    index++;
  }
  return (-50)*(temper_hex-WIND_temper_array[index])/(WIND_temper_array[index-1]-WIND_temper_array[index])+(index*50-400);
}
//end
