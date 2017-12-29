#include <Adafruit_NeoPixel.h>

#define PIN5 5
#define PIN6 6
#define PIN9 9
#define PIN10 10
#define PIN11 11

#define LED_BR 5



#define NUMPIXELS 13

//선언 시작했다

int now_mode;
String now_color;
float dust_value;
int now_weather;
float temperature;


//선언 끝났다

Adafruit_NeoPixel pixels[5] = {Adafruit_NeoPixel(NUMPIXELS, PIN5, NEO_RGBW + NEO_KHZ800),Adafruit_NeoPixel(NUMPIXELS, PIN6, NEO_RGBW + NEO_KHZ800),Adafruit_NeoPixel(NUMPIXELS, PIN9, NEO_RGBW + NEO_KHZ800),Adafruit_NeoPixel(NUMPIXELS, PIN10, NEO_RGBW + NEO_KHZ800),Adafruit_NeoPixel(NUMPIXELS, PIN11, NEO_RGBW + NEO_KHZ800)};

// initialize the library with the numbers of the interface pins


void serial_in();
void rain();
void thunder();
void rain_thunder();
void snow();
void snow_thunder();
void sunny();
void hot();
void cold();
void cloudy();


int delayval;
bool flag[5];
int cnt[5];
int rain_drop_pbt=50;
int thunder_pbt=10;
int snow_drop_pbt=25;
int snow_drop_pbtp=1000;
int dust_drop_pbt=100;
int cnt_dust=-4;
int fire[7][11][5];

uint8_t r =0; 
uint8_t g = 0; 
uint8_t b = 0;
int tmp;


//@@@@@@@@@@@@@@@@@@@@@@@@ 설정 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void setup() 
{
  Serial.begin(9600);

  for (int i=0;i<5;i++)
  {
    pixels[i].begin();
    pixels[i].setBrightness(LED_BR);
  }

  fire[0][2][2]=1;
  fire[0][2][3]=1;
  fire[0][3][2]=1;
  fire[0][4][2]=1;
  fire[0][4][3]=1;
  fire[0][5][1]=1;
  fire[0][5][2]=2;
  fire[0][5][3]=1;
  fire[0][6][1]=1;
  fire[0][6][2]=2;
  fire[0][6][3]=2;
  fire[0][6][4]=1;
  fire[0][7][0]=1;
  fire[0][7][1]=2;
  fire[0][7][2]=3;
  fire[0][7][3]=2;
  fire[0][7][4]=1;
  fire[0][8][0]=1;
  fire[0][8][1]=2;
  fire[0][8][2]=3;
  fire[0][8][3]=2;
  fire[0][8][4]=1;

  fire[1][3][2]=1;
  fire[1][4][2]=1;
  fire[1][5][1]=1;
  fire[1][5][2]=1;
  fire[1][6][1]=1;
  fire[1][6][2]=2;
  fire[1][6][3]=1;
  fire[1][7][0]=1;
  fire[1][7][1]=2;
  fire[1][7][2]=3;
  fire[1][7][3]=2;
  fire[1][7][4]=1;
  fire[1][8][0]=1;
  fire[1][8][1]=2;
  fire[1][8][2]=3;
  fire[1][8][3]=1;

  fire[2][3][2]=1;
  fire[2][4][2]=1;
  fire[2][5][1]=1;
  fire[2][5][2]=2;
  fire[2][6][1]=1;
  fire[2][6][2]=3;
  fire[2][6][3]=1;
  fire[2][7][0]=1;
  fire[2][7][1]=2;
  fire[2][7][2]=3;
  fire[2][7][3]=2;
  fire[2][7][4]=1;
  fire[2][8][1]=2;
  fire[2][8][2]=3;
  fire[2][8][3]=2;
  fire[2][8][4]=1;

  fire[3][2][3]=1;
  fire[3][3][2]=1;
  fire[3][3][3]=1;
  fire[3][4][2]=1;
  fire[3][5][2]=1;
  fire[3][5][3]=1;
  fire[3][6][1]=1;
  fire[3][6][2]=2;
  fire[3][6][3]=1;
  fire[3][7][0]=1;
  fire[3][7][1]=2;
  fire[3][7][2]=3;
  fire[3][7][3]=2;
  fire[3][7][4]=1;
  fire[3][8][1]=1;
  fire[3][8][2]=3;
  fire[3][8][3]=2;
  fire[3][8][4]=1;


  fire[4][2][2]=1;
  fire[4][3][1]=1;
  fire[4][3][2]=1;
  fire[4][4][2]=1;
  fire[4][5][1]=1;
  fire[4][5][2]=1;
  fire[4][6][1]=1;
  fire[4][6][2]=2;
  fire[4][6][3]=1;
  fire[4][7][0]=1;
  fire[4][7][1]=2;
  fire[4][7][2]=2;
  fire[4][7][3]=2;
  fire[4][7][4]=1;
  fire[4][8][0]=1;
  fire[4][8][1]=2;
  fire[4][8][2]=3;
  fire[4][8][3]=1;


  fire[5][3][1]=1;
  fire[5][4][2]=1;
  fire[5][5][1]=1;
  fire[5][5][2]=1;
  fire[5][6][2]=2;
  fire[5][6][3]=1;
  fire[5][7][0]=1;
  fire[5][7][1]=2;
  fire[5][7][2]=3;
  fire[5][7][3]=1;
  fire[5][8][0]=1;
  fire[5][8][1]=2;
  fire[5][8][2]=3;
  fire[5][8][3]=2;
  fire[5][8][4]=1;


  fire[6][2][3]=1;
  fire[6][3][2]=1;
  fire[6][3][3]=1;
  fire[6][4][2]=1;
  fire[6][5][1]=1;
  fire[6][5][2]=2;
  fire[6][6][1]=1;
  fire[6][6][2]=3;
  fire[6][6][3]=1;
  fire[6][7][1]=1;
  fire[6][7][2]=3;
  fire[6][7][3]=2;
  fire[6][7][4]=1;
  fire[6][8][0]=1;
  fire[6][8][1]=2;
  fire[6][8][2]=3;
  fire[6][8][3]=2;
  fire[6][8][4]=1;
  
  
  
  
  randomSeed(analogRead(0)); 
}

//@@@@@@@@@@@@@@@@@@@@@@@@ 루프 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void loop()
{
  serial_in();
  
  if (now_mode==0)
    default_light();
  else if (now_mode==1)
    weather_light();
  else if (now_mode==2)
    temperature_light();
  else if (now_mode==3)
    dust_light();
  else if (now_mode==4)
    light_off();
  else if (now_mode==5)
    emotion();
    
}

//@@@@@@@@@@@@@@@@@@@@@@@@ 감정 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void emotion()
{
  serial_in();
  
  if (now_mode!=5)
    return;

  if (now_weather==20)
    hell_fire();
  else if (now_weather==21)
    long_rain();
  else if (now_weather==22)
    short_rain();
  else if (now_weather==23)
    e_cloudy();
  else if (now_weather==24)
    Maerong();
  else if (now_weather==25)
    joy();
  else if (now_weather==26)
    little_cloudy();
}

//@@@@@@@@@@@@@@@@@@@@@@@@ 불 끔 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void light_off()
{
  while(1)
  {
    serial_in();
  
    if (now_mode!=4)
      return;
  
    r=0;
    g=0;
    b=0;

    for (int i=0;i<NUMPIXELS;i++)
    {
      for (int j=0;j<5;j++)
      {
        pixels[j].setPixelColor(i,pixels[j].Color(g,r,b));
      }
    }

    for (int i=0;i<5;i++)
    {
      pixels[i].show();
    }
  }
}

//@@@@@@@@@@@@@@@@@@@@@@@@ 기본 무드등 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void default_light()
{
  while(1)
  {
    serial_in();
    
    if (now_mode!=0)
      return;
    
    r=0;
    g=0;
    b=0;
  
    if('0'<=now_color[3] && now_color[3]<='9')
      r+=int(now_color[3]-'0')*16;
    else if ('a'<=now_color[3] && now_color[3]<='f')
      r+=int(now_color[3]-'a'+10)*16;
    if('0'<=now_color[4] && now_color[4]<='9')
      r+=int(now_color[4]-'0');
    else if ('a'<=now_color[4] && now_color[4]<='f')
      r+=int(now_color[4]-'a'+10);
    
    if('0'<=now_color[5] && now_color[5]<='9')
      g+=int(now_color[5]-'0')*16;
    else if ('a'<=now_color[5] && now_color[5]<='f')
      g+=int(now_color[5]-'a'+10)*16;
    if('0'<=now_color[6] && now_color[6]<='9')
      g+=int(now_color[6]-'0');
    else if ('a'<=now_color[6] && now_color[6]<='f')
      g+=int(now_color[6]-'a'+10);

    if('0'<=now_color[7] && now_color[7]<='9')
      b+=int(now_color[7]-'0')*16;
    else if ('a'<=now_color[7] && now_color[7]<='f')
      b+=int(now_color[7]-'a'+10)*16;
    if('0'<=now_color[8] && now_color[8]<='9')
      b+=int(now_color[8]-'0');
    else if ('a'<=now_color[8] && now_color[8]<='f')
      b+=int(now_color[8]-'a'+10);

    for (int i=0;i<NUMPIXELS;i++)
    {
      for (int j=0;j<5;j++)
      {
        pixels[j].setPixelColor(i,pixels[j].Color(g,r,b));
      }
    }

    for (int i=0;i<5;i++)
    {
      pixels[i].show();
    }
    
  }
}

//@@@@@@@@@@@@@@@@@@@@@@@@ 날씨 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void weather_light()
{
  serial_in();
  
  if (now_mode!=1)
    return;

  if (now_weather==0)
    rain_thunder();
  else if (now_weather==1)
    rain();
  else if (now_weather==2)
    snow_thunder();
  else if (now_weather==3)
    snow();
  else if (now_weather==4)
    thunder();
  else if (now_weather==5)
    hot();
  else if (now_weather==6)
    cold();
  else if (now_weather==7)
    cloudy();
  else if (now_weather==8)
    sunny();

  for (int i=0;i<5;i++)
    pixels[i].clear();
}

//@@@@@@@@@@@@@@@@@@@@@@@@ 기온 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void temperature_light()
{
  while(1)
  {
    serial_in();
    if (now_mode!=2)
      return;

    r=255;
    g=255;
    b=255;

    if (temperature>10)
    {
      g=g-(int(temperature)-10)*9;
      b=b-(int(temperature)-10)*9;
    }
    else
    {
      r-=(10-int(temperature))*7;
      g-=(10-int(temperature))*7;
    }
    
    if (temperature>38)
    {
      g=0;
      b=0;
    }
    else if (temperature<-26)
    {
      r=0;
      g=0;
    }

    if (r<0)
      r=0.0;
    if (g<0)
      g=0.0;
    if (b<0)
      b=0.0;
      
    if (r>255)
      r=255.0;
    if (g>255)
      g=255.0;
    if (b>255)
      b=255.0;
    
    for (int i=0;i<NUMPIXELS;i++)
    {
      for (int j=0;j<5;j++)
      {
        pixels[j].setPixelColor(i,pixels[j].Color(g,r,b));
      }
    }

    for (int i=0;i<5;i++)
    {
      pixels[i].show();
    }
    
  }
}

//@@@@@@@@@@@@@@@@@@@@@@@@ 미세먼지 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void dust_light()
{
  bool flag_tmp=false;
  
  int r_state,g_state,b_state;
  //좋음 0,0,255
  //보통 0,255,0
  //나쁨 255,100,0
  //매우나쁨 255,0,0

  //노랑 255 255 64
  //황갈 90 46 30
  //옅은노랑 250 254 164

  delayval=150;
  
  while(1)
  {
    serial_in();

    if (now_mode!=3)
      return;
      
    if (dust_value<=30)
    {
      r_state=0;
      g_state=0;
      b_state=255;
    }
    else if (dust_value<=80)
    {
      r_state=0;
      g_state=255;
      b_state=0;
    }
    else if (dust_value<=150)
    {
      r_state=255;
      g_state=60;
      b_state=0;
    }
    else if (dust_value>150)
    {
      r_state=255;
      g_state=0;
      b_state=0;
    }
    
    r=200;
    g=150;
    b=0;

    int r_tmp=150;
    int g_tmp=75;
    int b_tmp=0;

    int tmp;
    if (!flag_tmp)
    {
      flag_tmp=true;
      cnt_dust=-4;
    }
    
    
    for (int i=0;i<NUMPIXELS;i++)
    {
      for (int j=0;j<5;j++)
      {
        pixels[j].setPixelColor(i,pixels[j].Color(g,r,b));
      }
    }

    if (flag_tmp)
    {
      for (int i=0;i<5;i++)
      {
        for (int j=0;j<5;j++)
        {
          pixels[j].setPixelColor(7-(i+cnt_dust),pixels[j].Color(g+int((g_tmp-g)/4)*i,r+int((r_tmp-r)/4)*i,b+int((b_tmp-b)/4)*i));
        }
      }
    }
    

    if (cnt_dust>=NUMPIXELS-8)
      flag_tmp=false;


    for (int i=8;i<=10;i++)
    {
      for (int j=0;j<5;j++)
      {
        pixels[j].setPixelColor(i,pixels[j].Color(g_state,r_state,b_state));
      }
    }

    for (int i=0;i<5;i++)
    {
       pixels[i].show(); 
    }

    cnt_dust++;
    delay(delayval);    
  }
  
}

/*
 0 무드등
 1 날씨
 2 기온
 3 미세먼지
 
 */

//@@@@@@@@@@@@@@@@@@@@@@@@ 통신입력 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void serial_in()
{
  String string_now_mode = "";
  bool ready_now_mode = false;
  String string_now_color = "";
  bool ready_now_color = false;
  String string_dust_value = "";
  bool ready_dust_value = false;
  String string_temperature = "";
  bool ready_temperature = false;
  String string_current = "";
  int temperature_cnt = 0;
  int cnt_tmp = 0;

  int now_mode_tmp=now_mode;
  String now_color_tmp=now_color;
  int now_weather_tmp=now_weather;
  float dust_value_tmp=dust_value;
  float temperature_tmp=temperature;
  
  while (Serial.available())
  {
    
    char inChar = Serial.read();
    string_current += inChar;
    
    if(inChar == '\n'){
      Serial.println(string_current);
      if(cnt_tmp == 0){
        now_mode_tmp = string_current.toInt();
      }else if(cnt_tmp == 1){
        now_color_tmp = string_current;
      }else if(cnt_tmp == 2){
        now_weather_tmp = string_current.toInt();
      }else if(cnt_tmp == 3){
        dust_value_tmp = string_current.toFloat();
      }else if(cnt_tmp == 4){
        temperature_tmp = string_current.toFloat();
        cnt_tmp = -2000;
      }else if(cnt_tmp < 0){
        string_current = "";
        break;
      }
      cnt_tmp++;
      string_current = "";
    }
    
    
  }
  cnt_tmp = 0;

    Serial.print("now_mode : ");
    Serial.println(now_mode_tmp);
    Serial.print("now_color : ");
    Serial.println(now_color_tmp);
    Serial.print("dust_value : ");
    Serial.println(dust_value_tmp);
    Serial.print("now_weather : ");
    Serial.println(now_weather_tmp);
    Serial.print("temperature : ");
    Serial.println(temperature_tmp);
    Serial.print("==============");

  if (now_mode_tmp<0 || now_mode_tmp>6)
    return;
  if (now_color_tmp[1]=='.' || now_color_tmp[2]=='.' || now_color_tmp[3]=='.' || now_color_tmp.length()!=11)
    return;
  if (now_weather_tmp<0 || (now_weather_tmp>8 && now_weather_tmp<20) || now_weather_tmp>27)
    return;
  if (dust_value_tmp<0)
    return;
  if (temperature>'a')
    return;

  now_mode=now_mode_tmp;
  now_color=now_color_tmp;
  now_weather=now_weather_tmp;
  dust_value=dust_value_tmp;
  temperature=temperature_tmp;
  
}
//@@@@@@@@@@@@@@@@@@@@@@@@ 흐림 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void cloudy()
{
  for (int i=0;i<5;i++)
    pixels[i].clear();
  
  r=50;
  g=50;
  b=80;


  for (int i=0;i<NUMPIXELS;i++)
  {
    for (int j=0;j<5;j++)
    {
      pixels[j].setPixelColor(i,pixels[j].Color(g,r,b));
    }
  }
  while(1)
  {
    serial_in();
    if (now_weather!=7 || now_mode!=1)
      return;

    for (int i=0;i<5;i++)
      pixels[i].show();
  }
  
}

//@@@@@@@@@@@@@@@@@@@@@@@@ 맑음 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void sunny()
{
  for (int i=0;i<5;i++)
  {
    pixels[i].clear();
  }

  //100 255 0
  //100 100 255
  r=255;
  g=100;
  b=0;

  for (int i=0;i<5;i++)
    pixels[i].setPixelColor(0,pixels[i].Color(g,r,b));
  
  for (int i=1;i<11;i++)
  {
    for (int j=0;j<5;j++)
    {
      pixels[j].setPixelColor(i,pixels[j].Color(g+int((100-100)/9)*(i-1),r+int((100-255)/9)*(i-1),b+int((255-0)/9)*(i-1)));
    }
  }

  for (int i=NUMPIXELS;i<NUMPIXELS;i++)
  {
    for (int j=0;j<5;j++)
      pixels[j].setPixelColor(i,pixels[j].Color(100,100,255));
  }

  while(1)
  {
    serial_in();

    if (now_weather!=8 || now_mode!=1)
      return;
    for (int i=0;i<5;i++)
      pixels[i].show();
  }
    
}

//@@@@@@@@@@@@@@@@@@@@@@@@ 눈+번개 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void snow_thunder()
{
  bool pos[NUMPIXELS][5]={0,};
  delayval=450;

      
  while(1)
  {
    serial_in();
    if (now_weather!=2 || now_mode!=1)
      return;
      
    for (int i=NUMPIXELS-2;i>0;i--)
    {
      for (int j=0;j<5;j++)
      {
        pos[i][j]=pos[i-1][j];
      }
    }

    for (int i=0;i<5;i++)
    {
      if (pos[2][i])
        snow_drop_pbt+=snow_drop_pbtp;
      tmp=random(snow_drop_pbt);
      if (tmp<4)
        pos[1][i]=true;
      if (pos[2][i])
        snow_drop_pbt-=snow_drop_pbtp;
    }

    r=255;
    g=255;
    b=255;

    for (int i=0;i<5;i++)
      pixels[i].clear();
      
    for (int i=1;i<NUMPIXELS;i++)
    {
      for (int j=0;j<5;j++)
      {
        if (pos[i][j])
          pixels[j].setPixelColor(i,pixels[j].Color(g,r,b));
        else
          pixels[j].setPixelColor(i,pixels[j].Color(0,0,0));
      }
    }

    tmp=random(thunder_pbt);
    
    if (tmp<5)
    {
      for (int i=0;i<5;i++)
      {
        for (int j=1;j<=2;j++)
          pixels[i].setPixelColor(j,pixels[i].Color(0,45,255));
      }

      for (int i=0;i<5;i++)
        pixels[i].show();
      delay(40);
    }

    
    for (int i=1;i<NUMPIXELS;i++)
    {
        for (int j=0;j<5;j++)
        {
          if (pos[i][j])
          pixels[j].setPixelColor(i,pixels[j].Color(g,r,b));
          else
          pixels[j].setPixelColor(i,pixels[j].Color(0,0,0));  
        }
    }


    for (int i=0;i<5;i++)
    {
      pixels[i].setPixelColor(0,pixels[i].Color(187,62,255));
      pixels[i].show();
    }
    
    delay(delayval);
  }
}

//@@@@@@@@@@@@@@@@@@@@@@@@ 눈 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void snow()
{
  bool pos[NUMPIXELS][5]={false,};
  delayval=450;
  while(1)
  {
    serial_in();
    
    if (now_weather!=3 || now_mode!=1)
      return;
    
    for (int i=NUMPIXELS-2;i>0;i--)
    {
      for (int j=0;j<5;j++)
        pos[i][j]=pos[i-1][j];
    }

    for (int i=0;i<5;i++)
    {
     if (pos[2][i])
        snow_drop_pbt+=snow_drop_pbtp;
     tmp=random(snow_drop_pbt);
     if (tmp<4)
       pos[1][i]=true;
     if (pos[2][i])
      snow_drop_pbt-=snow_drop_pbtp;
    }

    r=255;
    g=255;
    b=255;


    for (int i=0;i<5;i++)
      pixels[i].clear();
      
    for (int i=1;i<NUMPIXELS-2;i++)
    {
      for (int j=0;j<5;j++)
      {
        if (pos[i][j])
          pixels[j].setPixelColor(i,pixels[j].Color(g,r,b));
        else
          pixels[j].setPixelColor(i,pixels[j].Color(0,0,0));
      }
    }

    for (int i=0;i<5;i++)
    {
      pixels[i].setPixelColor(0,pixels[i].Color(187,62,255));
      pixels[i].show();
    } 
    
    delay(delayval);
  }
}
//@@@@@@@@@@@@@@@@@@@@@@@@ 번개 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void thunder()
{
  r=45;
  g=0;
  b=255;
  int r_tmp,g_tmp,b_tmp;
  
  while(1)
  {
    serial_in();
    if (now_weather!=4 || now_mode!=1)
      return;

    r_tmp=50;
    g_tmp=50;
    b_tmp=80;


    for (int i=0;i<NUMPIXELS;i++)
    {
      for (int j=0;j<5;j++)
      {
        pixels[j].setPixelColor(i,pixels[j].Color(g_tmp,r_tmp,b_tmp));
      }
    }
    tmp=random(20);
    if (tmp<5)
    {
      for (int i=0;i<5;i++)
      {
        for (int j=0;j<=4;j++)
        {
          pixels[i].setPixelColor(j,pixels[i].Color(g,r,b));
        }
      }

     for (int i=0;i<5;i++)
        pixels[i].show();
      delay(30);

      for (int i=0;i<5;i++)
      {
        for (int j=0;j<=4;j++)
        {
          pixels[i].setPixelColor(j,pixels[i].Color(g_tmp,r_tmp,b_tmp));
        }
      }

      for (int i=0;i<5;i++)
        pixels[i].show();
        
    }
    delay(10);
  }
}

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@ 비 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
void rain()
{
  delayval=70;
  
  while(1)
  {
    serial_in();
      
    if (now_mode!=1 || now_weather!=1)
      break;
     
    for (int i=0;i<5;i++)
    {
      if (!flag[i])
      {
        tmp=random(rain_drop_pbt);
        if (tmp<4)
          flag[i]=true;
      }
    }

    r=0;
    g=0;
    b=255;

    for (int i=0;i<5;i++)
    {
      if (flag[i])
      {
        if (cnt[i]>=NUMPIXELS+3)
        {cnt[i]=0;flag[i]=false;break;}
        pixels[i].clear();
        pixels[i].setPixelColor(cnt[i]+0, pixels[i].Color(g,r,b));
        pixels[i].setPixelColor(cnt[i]-1, pixels[i].Color(g,r,b));
        pixels[i].setPixelColor(cnt[i]-2, pixels[i].Color(g,r,b));
        pixels[i].show();
        cnt[i]++;
      }
    }
    delay(delayval);
  }
  
}


//@@@@@@@@@@@@@@@@@@@@@@@ 비+번개 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void rain_thunder()
{
  r=0;
  g=0;
  b=255;
  delayval=70;
  
  while(1)
  {
    serial_in();
    if (now_weather!=0 || now_mode!=1)
      return;

    for (int i=0;i<5;i++)
    {
      if (!flag[i])
      {
        tmp=random(rain_drop_pbt);
        if (tmp<4)
          flag[i]=true;
      }
    }

    tmp=random(thunder_pbt);

    for (int i=0;i<5;i++)
    {
      if (flag[i])
      {
        if (cnt[i]>=NUMPIXELS+3)
        {cnt[i]=0;flag[i]=false;break;}
        pixels[i].clear();
        pixels[i].setPixelColor(cnt[i]+0, pixels[i].Color(g,r,b));
        pixels[i].setPixelColor(cnt[i]-1, pixels[i].Color(g,r,b));
        pixels[i].setPixelColor(cnt[i]-2, pixels[i].Color(g,r,b));
        cnt[i]++;
      }
      else
      {
        pixels[i].setPixelColor(cnt[i]+0, pixels[i].Color(0,0,0));
        pixels[i].setPixelColor(cnt[i]-1, pixels[i].Color(0,0,0));
        pixels[i].setPixelColor(cnt[i]-2, pixels[i].Color(0,0,0));
      }
    }

    if (tmp<5)
    {
      for (int i=0;i<5;i++)
      {
        pixels[i].setPixelColor(0,pixels[i].Color(0,45,255));
        pixels[i].show();
      }
    }
    else
    {
      for (int i=0;i<5;i++)
      {
        pixels[i].setPixelColor(0,pixels[i].Color(0,0,0));
        pixels[i].show();
      }
    }
    delay(delayval);
  }  
}

//@@@@@@@@@@@@@@@@@@@@@@@ 폭염 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void hot()
{
  //0번 - 2번 led
  //1번 - 1번 led
  //2번 - 4번 led
  //3번 - 3번 led
  //4번 - 0번 led
  delayval=100;
  for (int i=0;i<5;i++)
  {
    pixels[i].clear();
  }

  int k_tmp;

  while(1)
  {
    for (int i=0;i<7;i++)
    {
      serial_in();

      if (now_mode!=1 || now_weather!=5)
        return;

      for (int j=0;j<5;j++)
        pixels[j].clear();

      
      for (int j=0;j<11;j++)
      {
        for (int k=0;k<5;k++)
        {
          if (k==0)
            k_tmp=4;
          else if (k==1)
            k_tmp=1;
          else if (k==2)
            k_tmp=0;
          else if (k==3)
            k_tmp=3;
          else if (k==4)
            k_tmp=2;

          
          if (fire[i][j][k]==1)
            pixels[k_tmp].setPixelColor(j+2,pixels[k_tmp].Color(0,255,0));
          else if (fire[i][j][k]==2)
            pixels[k_tmp].setPixelColor(j+2,pixels[k_tmp].Color(100,255,0));
          else if (fire[i][j][k]==3)
            pixels[k_tmp].setPixelColor(j+2,pixels[k_tmp].Color(200,200,50));
          else
            pixels[k_tmp].setPixelColor(j+2,0);
        }
      }

      for (int j=0;j<5;j++)
        pixels[j].show();

      delay(delayval);
    }
  }
}

//@@@@@@@@@@@@@@@@@@@@@@@ 한파 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void cold()
{
  //0번 - 2번 led
  //1번 - 1번 led
  //2번 - 4번 led
  //3번 - 3번 led
  //4번 - 0번 led
  
  delayval=900;
  int ice_range[11][5];
  int ice_range_tmp[11][5];
  int x,y;
  int dx[4],dy[4];
  int k_tmp;
  int tmp;
  
  while(1)
  {
    serial_in();

    if (now_mode!=1 || now_weather!=6)
      return;

    for (int i=0;i<11;i++)
    {
      for (int j=0;j<5;j++)
      {
        ice_range[i][j]=0;
        ice_range_tmp[i][j]=0;
      }
    }

    for (int i=0;i<5;i++)
    {
      pixels[i].clear();
      pixels[i].show();
    }

    x=int(random(2))+1;
    y=int(random(3))+4;

    ice_range[y][x]=true;
    
    for (int i=0;i<20;i++)
    {
      serial_in();

      if (now_mode!=1 || now_weather!=6)
        return;

      delay(delayval-15*i);

      for (int j=0;j<11;j++)
      {
        for (int k=0;k<5;k++)
        {
          if (k==0)
              k_tmp=4;
          else if (k==1)
              k_tmp=1;
          else if (k==2)
              k_tmp=0;
          else if (k==3)
              k_tmp=3;
          else if (k==4)
              k_tmp=2;
              
          if (ice_range[j][k]>0)
          {
            tmp=ice_range[j][k];
            pixels[k_tmp].setPixelColor(j,pixels[k_tmp].Color(157+(2-tmp)*15,72+(2-tmp)*30,255));
            
            dx[0]=k-1;
            dx[1]=k;
            dx[2]=k+1;
            dx[3]=k;
            dy[0]=j;
            dy[1]=j-1;
            dy[2]=j;
            dy[3]=j+1;

            for (int l=0;l<4;l++)
            {
              tmp=random(100);
              if (tmp<50)
              { 
                if (dx[l]>=0 && dx[l]<5 && dy[l]>=0 && dy[l]<11)
                  ice_range_tmp[dy[l]][dx[l]]++;

                if (ice_range_tmp[dy[l]][dx[l]]>2)
                  ice_range_tmp[dy[l]][dx[l]]=2;
              }
            }
            ice_range_tmp[j][k]++;
            if (ice_range_tmp[j][k]>2)
              ice_range_tmp[j][k]=2;
          }
          else
          {
            pixels[k_tmp].setPixelColor(j,0);
          }
        }
      }
      
      for (int j=0;j<11;j++)
      {
        for (int k=0;k<5;k++)
        {
          ice_range[j][k]=ice_range_tmp[j][k];
        }
      }

      for (int j=0;j<5;j++)
      {
        pixels[j].show();
      }
    }
  }
}

//@@@@@@@@@@@@@@@@@@@@@@@@ 크리스마스 에디션 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void X_mas()
{
  while(1)
  {
    serial_in();
    if (now_mode!=4)
      return;
 
    for (int i=0;i<5;i++)
    {
      for (int j=0;j<=10;j++)
      {
        r=0;
        g=255;
        b=0;
        /*
        tmp=random(100);
        if (tmp<=70)
        {
          r=0;
          g=255;
          b=0;
        }
        else if (tmp<=85)
        {
          r=255;
          g=0;
          b=0;
        }
        else
        {
          r=255;
          g=255;
          b=0;
        }
        */
        pixels[i].setPixelColor(j,pixels[i].Color(g,r,b));
     }
   }

   
   for (int i=0;i<5;i++)
      pixels[i].show();
        
    delay(500);
  }
}

//@@@@@@@@@@@@@@@@@@@@@@@@ 메롱 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void Maerong()
{
  int p[5][5];
  int j_tmp;
  bool mod_flag=true;

  for (int i=0;i<5;i++)
  {
    for (int j=0;j<5;j++)
    {
      p[i][j]=0;
    }
  }
  for (int i=0;i<2;i++)
  {
    p[i][2]=1;
    p[2][4-i]=2;
    p[4-i][2]=3;
    p[2][i]=4;
  }

  p[1][1]=1;
  p[1][3]=2;
  p[3][3]=3;
  p[3][1]=4;
  
  for (int i=0;i<11;i++)
  {
    for (int j=0;j<5;j++)
    {
      pixels[j].setPixelColor(i,pixels[j].Color(187,62,255));
    }
  }
  
  while(1)
  {
    serial_in();
  
    if (now_mode!=5 || now_weather!=24)
      return;

    for (int i=0;i<5;i++)
    {
      for (int j=0;j<5;j++)
      {
        if (j==0)
            j_tmp=4;
        else if (j==1)
            j_tmp=1;
        else if (j==2)
            j_tmp=0;
        else if (j==3)
            j_tmp=3;
        else if (j==4)
            j_tmp=2;
            
        if (p[i][j]==0)
        {
          r=62;
          g=187;
          b=255;
        }
        else if (p[i][j]==1)
        {
          r=255;
          g=0;
          b=0;
        }
        else if (p[i][j]==2)
        {
          r=0;
          g=255;
          b=0;
        }
        else if (p[i][j]==3)
        {
          r=0;
          g=0;
          b=255;
        }
        else
        {
          r=255;
          g=255;
          b=0;
        }
        
        pixels[j_tmp].setPixelColor(i+2,pixels[i].Color(g,r,b));
      }
    }

    pixels[0].setPixelColor(4,0);
    
    for (int i=0;i<5;i++)
    {
      pixels[i].show();
    }
    
    if (mod_flag)
    {
      p[1][3]=p[1][2];
      p[1][2]=0;
      p[0][4]=p[0][2];
      p[0][2]=0;

      p[3][3]=p[2][3];
      p[2][3]=0;
      p[4][4]=p[2][4];
      p[2][4]=0;

      p[3][1]=p[3][2];
      p[3][2]=0;
      p[4][0]=p[4][2];
      p[4][2]=0;

      p[1][1]=p[2][1];
      p[2][1]=0;
      p[0][0]=p[2][0];
      p[2][0]=0;

      
      mod_flag=false;
    }
    else
    {
      p[2][3]=p[1][3];
      p[1][3]=0;
      p[2][4]=p[0][4];
      p[0][4]=0;

      p[3][2]=p[3][3];
      p[3][3]=0;
      p[4][2]=p[4][4];
      p[4][4]=0;

      p[2][1]=p[3][1];
      p[3][1]=0;
      p[2][0]=p[4][0];
      p[4][0]=0;

      p[1][2]=p[1][1];
      p[1][1]=0;
      p[0][2]=p[0][0];
      p[0][0]=0;
      mod_flag=true;
    }

    delay(100);
  }
}

//@@@@@@@@@@@@@@@@@@@@@@@ 지옥불 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void hell_fire()
{
  //0번 - 2번 led
  //1번 - 1번 led
  //2번 - 4번 led
  //3번 - 3번 led
  //4번 - 0번 led
  delayval=100;
  for (int i=0;i<5;i++)
  {
    pixels[i].clear();
  }

  int k_tmp;

  while(1)
  {
    for (int i=0;i<7;i++)
    {
      serial_in();

      if (now_mode!=5 || now_weather!=20)
        return;

      for (int j=0;j<5;j++)
        pixels[j].clear();

      
      for (int j=0;j<11;j++)
      {
        for (int k=0;k<5;k++)
        {
          if (k==0)
            k_tmp=4;
          else if (k==1)
            k_tmp=1;
          else if (k==2)
            k_tmp=0;
          else if (k==3)
            k_tmp=3;
          else if (k==4)
            k_tmp=2;

          
          if (fire[i][j][k]==1)
          {
            pixels[k_tmp].setPixelColor(j+2,pixels[k_tmp].Color(0,255,0));
          }
          else if (fire[i][j][k]==2)
          {
              pixels[k_tmp].setPixelColor(j+2,pixels[k_tmp].Color(100,255,0));
          }
          else if (fire[i][j][k]==3)
          {
            pixels[k_tmp].setPixelColor(j+2,pixels[k_tmp].Color(200,200,50));
          }
          else
            pixels[k_tmp].setPixelColor(j+2,pixels[k_tmp].Color(8,100,8));
        }
      }

      for (int i=0;i<2;i++)
      {
        for (int j=0;j<5;j++)
        {
          pixels[j].setPixelColor(i,pixels[j].Color(8,100,8)); 
        }
      }
      
      for (int j=0;j<5;j++)
        pixels[j].show();

      delay(delayval);
    }
  }
}

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@ 가랑비 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
void short_rain()
{
  delayval=70;

  for (int i=0;i<5;i++)
  {
    for (int j=0;j<11;j++)
    {
      pixels[i].setPixelColor(j,0);
    }
    pixels[i].show();
  }
  while(1)
  {
    serial_in();

    if (now_mode!=5 || now_weather!=22)
      break;
     
    for (int i=0;i<5;i++)
    {
      if (!flag[i])
      {
        tmp=random(rain_drop_pbt+100);
        if (tmp<4)
          flag[i]=true;
      }
    }

    r=0;
    g=0;
    b=255;

    for (int i=0;i<5;i++)
    {
      if (flag[i])
      {
        if (cnt[i]>=NUMPIXELS+3)
        {cnt[i]=0;flag[i]=false;break;}
        pixels[i].clear();
        pixels[i].setPixelColor(cnt[i]+0, pixels[i].Color(g,r,b));
        pixels[i].setPixelColor(cnt[i]-1, pixels[i].Color(g,r,b));
        pixels[i].show();
        cnt[i]++;
      }
    }
    delay(delayval);
  }
  
}

/*@@@@@@@@@@@@@@@@@@@@@@@@@@@ 장대비 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*/
void long_rain()
{
  delayval=40;

  for (int i=0;i<5;i++)
  {
    for (int j=0;j<11;j++)
    {
      pixels[i].setPixelColor(j,0);
    }
    pixels[i].show();
  }
  
  while(1)
  {
    serial_in();
      
    if (now_mode!=5 || now_weather!=21)
      break;
     
    for (int i=0;i<5;i++)
    {
      if (!flag[i])
      {
        tmp=random(rain_drop_pbt-20);
        if (tmp<4)
          flag[i]=true;
      }
    }

    r=0;
    g=0;
    b=255;

    for (int i=0;i<5;i++)
    {
      if (flag[i])
      {
        if (cnt[i]>=NUMPIXELS+1)
        {cnt[i]=0;flag[i]=false;break;}
        pixels[i].clear();
        pixels[i].setPixelColor(cnt[i]+0, pixels[i].Color(g,r,b));
        pixels[i].setPixelColor(cnt[i]-1, pixels[i].Color(g,r,b));
        pixels[i].setPixelColor(cnt[i]-2, pixels[i].Color(g,r,b));
        pixels[i].show();
        cnt[i]++;
      }
    }
    delay(delayval);
  }
}

//@@@@@@@@@@@@@@@@@@@@@@@@ 기분흐림 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void e_cloudy()
{
  for (int i=0;i<5;i++)
    pixels[i].clear();
  
  r=50;
  g=50;
  b=80;


  for (int i=0;i<NUMPIXELS;i++)
  {
    for (int j=0;j<5;j++)
    {
      pixels[j].setPixelColor(i,pixels[j].Color(g,r,b));
    }
  }
  while(1)
  {
    serial_in();
    if (now_weather!=23 || now_mode!=5)
      return;

    for (int i=0;i<5;i++)
      pixels[i].show();
  }
  
}

//@@@@@@@@@@@@@@@@@@@@@@@@ 기쁨 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void joy()
{
    //0번 - 2번 led
  //1번 - 1번 led
  //2번 - 4번 led
  //3번 - 3번 led
  //4번 - 0번 led
  
  for (int i=0;i<5;i++)
    pixels[i].clear();
  
  r=62;
  g=187;
  b=255;


  for (int i=0;i<5;i++)
  {
    for (int j=0;j<5;j++)
    {
      pixels[j].setPixelColor(i,pixels[j].Color(200,200,50));
    }
  }

  for (int i=5;i<11;i++)
  {
    for (int j=0;j<5;j++)
    {
      pixels[j].setPixelColor(i,pixels[j].Color(g,r,b));
    }
  }

  pixels[4].setPixelColor(4,pixels[4].Color(g,r,b));

  pixels[1].setPixelColor(1,pixels[1].Color(255,255,0));
  pixels[1].setPixelColor(2,pixels[1].Color(255,255,0));

  pixels[0].setPixelColor(0,pixels[0].Color(255,255,0));
  pixels[3].setPixelColor(0,pixels[3].Color(255,255,0));

  pixels[0].setPixelColor(3,pixels[1].Color(255,255,0));
  pixels[3].setPixelColor(3,pixels[1].Color(255,255,0));

  pixels[2].setPixelColor(1,pixels[2].Color(255,255,0));
  pixels[2].setPixelColor(2,pixels[2].Color(255,255,0));

  pixels[0].setPixelColor(1,pixels[0].Color(100,255,0));
  pixels[0].setPixelColor(2,pixels[0].Color(100,255,0));
  pixels[3].setPixelColor(1,pixels[3].Color(100,255,0));
  pixels[3].setPixelColor(2,pixels[3].Color(100,255,0));
  
  while(1)
  {
    serial_in();
    if (now_weather!=25 || now_mode!=5)
      return;

    for (int i=0;i<5;i++)
      pixels[i].show();
  }
  
}

//@@@@@@@@@@@@@@@@@@@@@@@@ 약간기쁨 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
void little_cloudy()
{
  //0번 - 2번 led
  //1번 - 1번 led
  //2번 - 4번 led
  //3번 - 3번 led
  //4번 - 0번 led

  bool cloud_a[11][14]={0,};
  bool cloud_a_tmp[11][14];

  for (int i=0;i<2;i++)
  {
    for (int j=0;j<2;j++)
    {
      cloud_a[9+i][5+j]=true;
      cloud_a[4+i][3+j]=true;
      cloud_a[i][1+j]=true;
    }
  }

  cloud_a[10][4]=true;
  cloud_a[10][7]=true;
  cloud_a[5][2]=true;
  cloud_a[5][5]=true;
  cloud_a[1][0]=true;
  cloud_a[1][3]=true;
  
  for (int i=0;i<5;i++)
    pixels[i].clear();
  
  r=62;
  g=187;
  b=255;
  int j_tmp;
  while(1)
  {
    serial_in();
    if (now_weather!=26 || now_mode!=5)
      return;

    for (int i=0;i<11;i++)
    {
      for (int j=0;j<5;j++)
      {
        if (j==0)
            j_tmp=4;
          else if (j==1)
            j_tmp=1;
          else if (j==2)
            j_tmp=0;
          else if (j==3)
            j_tmp=3;
          else if (j==4)
            j_tmp=2;
         
        if (cloud_a[i][j+9])
          pixels[j_tmp].setPixelColor(i,pixels[j_tmp].Color(255,255,255));
        else
          pixels[j_tmp].setPixelColor(i,pixels[j_tmp].Color(g,r,b));
      }
    }
    
    for (int i=0;i<5;i++)
      pixels[i].show();

    for (int i=0;i<11;i++)
    {
      cloud_a_tmp[i][0]=cloud_a[i][13];
    }
    for (int i=0;i<11;i++)
    {
      for (int j=1;j<14;j++)
      {
        cloud_a_tmp[i][j]=cloud_a[i][j-1];
      }
    }
    for (int i=0;i<11;i++)
    {
      for (int j=0;j<14;j++)
      {
        cloud_a[i][j]=cloud_a_tmp[i][j];
      }
    }
    delay(600);
  }
  
}
