
#include <WiFi.h>
#include "SoundData.h"
#include "XT_DAC_Audio.h"
#include <HTTPClient.h>
//XT_Wav_//Class ForceWithYou(wats/on);    
                                      
#include<string.h>
XT_Wav_Class Person(person);                       
XT_DAC_Audio_Class DacAudio(25,0);  
                                      

uint32_t DemoCounter=0;            
const char* ssid = "ARCHE_INDUSTRIES";
const char* password = "123456789";
const char* url = "http://192.168.1.5:5000/state";

const int trig = 4;
const int echo = 2;
long duration;
int distance;

void setup() 
{
  Serial.begin(115200);    
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(15,OUTPUT);
  delay(1000);                       
  WiFi.begin(ssid,password);                          
  while(WiFi.status()!=WL_CONNECTED){
  delay(1000);
  Serial.println("connecting to the wifi");
}
Serial.println("Connected");

}
String rept;
String match="1";
int counter=0;
void loop() 
{ digitalWrite(15,LOW);
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance= duration*0.017;

  if ((WiFi.status() == WL_CONNECTED)) { 
    
    HTTPClient http;

    http.begin(url); 
    int httpCode = http.GET();                                        

    if (httpCode > 0) { 

      String payload = http.getString();
      
      Serial.println(httpCode);  // response code
      Serial.println(payload);   // response data
      rept = payload;
      int len = rept.length()+1;
      char char_array[len];
      rept.toCharArray(char_array,len);
      Serial.print("dataaa :");
      Serial.println(char_array[1]);
       if(distance<100){
        digitalWrite(15,HIGH);
      }

//      Serial.print(match);
 //     Serial.print("\n");
      if(char_array[1]=='1'){
  //      Serial.println("in if");
        while(counter<2000 ){
        //  Serial.println("in while");
          DacAudio.FillBuffer();
             if(Person.Playing==false)
               DacAudio.Play(&Person);
            counter++;
         // Serial.println(counter);
         }
         }
         else{
          Serial.println("match not");
         }

         counter=0;
    }

    else {
      Serial.println("Error !!!");
    }

    http.end(); 
  }
  delay(1000);
}
