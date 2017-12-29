#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>


char ssid[] = "AndroidHotspot1407";     //  연결하실 와이파이 이름
char pass[] = "wonjunjang";  // 네트워크 보안키
char hostname[] = "52.79.41.31";
String currentLine = "";
String server_currentLine = "";
int port = 3000;
IPAddress hostIp;
WiFiClient client;
WiFiClient receive_server;
WiFiServer server(80);
int status = WL_IDLE_STATUS;
const unsigned long requestInterval = 60000;  // 요구 시간 딜레이(1 min)
uint8_t ret;
unsigned long lastAttemptTime = 0;            // 마지막으로 서버에서 데이터를 전송받은 시간
boolean readingWeather = false;
boolean readingTemperature = false;
boolean readingnow_mode = false;

String weatherString = "";   
String weatherTemperature = "";   
String weather_string_now_mode = "";

boolean readingnow_color = false;
String weather_string_now_color = "";   
String now_color = "";

boolean readingnow_real_wea = false;
String weather_string_real_wea = "";   
int now_weather = 0;

boolean reading_dust_value = false;
String weather_string_dust_value = "";   
float dust_value = 0;

int sky_cnt=0;
int sky[8] = {8,8,8,8,8,8,8,8};
float temperature[8] = {0,0,0,0,0,0,0};
int now_mode = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  while(!Serial){
    
  }
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // 와이파이 실드가 아닐 경우
    while(true);
  } 
   // 와이파이에 연결 시도
  while ( status != WL_CONNECTED) { // 연결이 될 때 까지 반복
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // WPA/WAP2 네트워크에 연결
    status = WiFi.begin(ssid, pass);

    delay(10000);
  }
     Serial.print("You're connected to the network");
  printCurrentNet();
  printWifiData();
  server.begin();
  connectToServer();
}

void loop() {
  delay(100);
  connectToServer();
//  Serial.print("LED 온");
}

void printWifiData() {
  // WI-FI 실드의 IP를 출력한다.
  IPAddress ip = WiFi.localIP();
//    Serial.print("IP Address: ");
//  Serial.println(ip);
//  Serial.println(ip);
  
  // MAC어드레스를 출력한다.
  byte mac[6];  
  WiFi.macAddress(mac);
//  Serial.print("MAC address: ");
//  Serial.print(mac[5],HEX);
//  Serial.print(":");
//  Serial.print(mac[4],HEX);
//  Serial.print(":");
//  Serial.print(mac[3],HEX);
//  Serial.print(":");
//  Serial.print(mac[2],HEX);
//  Serial.print(":");
//  Serial.print(mac[1],HEX);
//  Serial.print(":");
//  Serial.println(mac[0],HEX);
 ret = WiFi.hostByName("52.79.41.31", hostIp);
//  Serial.print("ret: ");
//  Serial.println(ret);
//
//  Serial.print("Host IP: ");
//  Serial.println(hostIp);
//  Serial.println("");
}
void printCurrentNet() {
  // 접속하려는 네트워크의 SSID를 출력한다.
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // 접속하려는 router의 MAC 주소를 출력한다.
  byte bssid[6];
  WiFi.BSSID(bssid);    
//  Serial.print("BSSID: ");
//  Serial.print(bssid[5],HEX);
//  Serial.print(":");
//  Serial.print(bssid[4],HEX);
//  Serial.print(":");
//  Serial.print(bssid[3],HEX);
//  Serial.print(":");
//  Serial.print(bssid[2],HEX);
//  Serial.print(":");
//  Serial.print(bssid[1],HEX);
//  Serial.print(":");
//  Serial.println(bssid[0],HEX);

  // 수신 신호 강도를 출력한다.
  long rssi = WiFi.RSSI();
//  Serial.print("signal strength (RSSI):");
//  Serial.println(rssi);

  // 암호화 타입을 출력한다.
  byte encryption = WiFi.encryptionType();
//  Serial.print("Encryption Type:");
//  Serial.println(encryption,HEX);
//  Serial.println();
}

void connectToServer() {
 int  temperature_cnt = 0 ;
//  Serial.println("");
//  Serial.println("connecting to server...");
  String content = "";
  if (client.connect(hostIp, 3000)) {
//    Serial.println("Connected! Making HTTP request");
    client.println("GET /weather_get HTTP/1.1"); 
    client.print("HOST: 52.79.41.31\n");
    client.println("Connection: cl0ose");
    client.println();
    delay(3000);  
    if(client.connected()){
      while (client.available()){
       char inChar = client.read();     
       currentLine += inChar;
       if(inChar ==  '\n'){
        
              currentLine = ""; 
              if(readingWeather){
              sky[sky_cnt] = weatherString.toInt();          
              weatherString = "";
              readingWeather = false;
              sky_cnt++;
             }else if(readingTemperature){
//              Serial.print("temperature_cnt : ");
              
              temperature[temperature_cnt] = weatherTemperature.toFloat();
              currentLine = "";
              weatherTemperature = "";
              readingTemperature = false;
              temperature_cnt++;
              
//              if(temperature_cnt == 7){
//                temperature_cnt = 0;
//              }
             }else if(readingnow_mode){
              now_mode = weather_string_now_mode.toInt();
              currentLine = "";
              weather_string_now_mode = "";
              readingnow_mode = false;
             }else if(readingnow_color){
              now_color = weather_string_now_color;
              currentLine = "";
              weather_string_now_color =   "";
              readingnow_color = false;
             }
             else if(readingnow_real_wea){
              
              now_weather = weather_string_real_wea.toInt();
              currentLine = "";
              weather_string_real_wea = "";
              readingnow_real_wea = false;
             }
             else if(reading_dust_value){
              dust_value = weather_string_dust_value.toFloat();
              currentLine = "";
              weather_string_dust_value = "";
              reading_dust_value = false;
             }
       }
       //
//boolean readingnow_color = false;
//String weather_string_now_color = "";   
//int now_color = 0;
//
//boolean readingnow_real_wea = false;
//String weather_string_real_wea = "";   
//int now_weather = 0;
//
//boolean reading_dust_value = false;
//String weather_string_dust_value = "";   
//float dust_value = 0;
       if ( currentLine.endsWith("now_mode : ")) {
          // 현재 스트링이 "<pressure value="로 끝났다면 기압 데이터를 받을 준비를 한다.
          readingnow_mode = true; 
        }
//        if ( currentLine.endsWith("weather : ")) {
//          // 현재 스트링이 "<pressure value="로 끝났다면 기압 데이터를 받을 준비를 한다.
//          readingWeather = true; 
//        }
        if ( currentLine.endsWith("temperature : ")) {
          // 현재 스트링이 "<pressure value="로 끝났다면 기압 데이터를 받을 준비를 한다.
          readingTemperature = true; 
        }
        
        if ( currentLine.endsWith("mood_color : ")) {
          // 현재 스트링이 "<pressure value="로 끝났다면 기압 데이터를 받을 준비를 한다.
          readingnow_color = true; 
        }
        if ( currentLine.endsWith("now_real_wea : ")) {
          // 현재 스트링이 "<pressure value="로 끝났다면 기압 데이터를 받을 준비를 한다.
          readingnow_real_wea = true; 
        }if ( currentLine.endsWith("dust_value : ")) {
          // 현재 스트링이 "<pressure value="로 끝났다면 기압 데이터를 받을 준비를 한다.
          reading_dust_value = true; 
        }
        
//        if(readingWeather){
//         if(inChar !=  '\n'){
//          weatherString += inChar;
//         }
//        }
         if(readingTemperature){
           if(inChar !=  '\n'){
            weatherTemperature += inChar;
           }
        }
        if(readingnow_mode){
         if(inChar !=  '\n'){
          weather_string_now_mode += inChar;
         }
        }
        if(readingnow_color){
         if(inChar !=  '\n'){
          weather_string_now_color += inChar;
         }
        }
        if(readingnow_real_wea){
         if(inChar !=  '\n'){
          weather_string_real_wea += inChar;
         }
        }
        if(reading_dust_value){
         if(inChar !=  '\n'){
          weather_string_dust_value += inChar;
         }
        }
      }
      client.stop();
    }
//  Serial.println("===========================================================");
//  Serial.print("now_mode : ");
  Serial.println(now_mode);
//  Serial.print("now_color : ");
  Serial.println(now_color);
//  Serial.print("now_weather : ");
  Serial.println(now_weather);
//  Serial.print("dust_value : ");
  Serial.println(dust_value);
  Serial.println(temperature[0]);
//  for(int i=0; i<8; i++){
////    Serial.print("temperature : ");
//    Serial.println(temperature[i]);
//  } 
}
}
