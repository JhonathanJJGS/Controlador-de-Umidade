#include <DHT.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

#define DHTPIN 2 
#define DHTTYPE DHT11
#define fanPin 8
unsigned int leitura = 0;


DHT sensorUmidade(DHTPIN, DHTTYPE);
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);




//FUNÇÕES::


float getUmidade(){
 float umidade = sensorUmidade.readHumidity(); 
 return umidade; 
}

float getTemperatura(){
 float temperatura = sensorUmidade.readTemperature();
 return temperatura; 
}

void controle_Fan(){
  if(getUmidade() >= 60){
    digitalWrite(fanPin, HIGH);
    }else{
      digitalWrite(fanPin, LOW);
      }
  }

  void printData(){

     if(digitalRead(fanPin) == 0){
      Serial.print(getUmidade());
      Serial.print(",");
      Serial.print(getTemperatura());
      Serial.print(",");
      Serial.print("[FANOFF]");
      delay(1500);
      }else{
            Serial.print(getUmidade());
            Serial.print(",");
            Serial.print(getTemperatura());
            Serial.print(",");
            Serial.print("[FANON]");
            delay(1500);
        }
    
    
    
    }

  void leituraSerial(){
  
  if(Serial.available()>0){
      leitura = Serial.read();
      if(leitura == 1){

          digitalWrite(fanPin, HIGH);
          printData();
          delay(1500);
          digitalWrite(fanPin, LOW);
          
        }
      }
}
    
 
//-------------------------------------------------------------------
void setup(void) {
  u8g2.begin();
  Serial.begin(9600);
  sensorUmidade.begin();
  pinMode(fanPin, OUTPUT);
}

void loop(void) {
  leituraSerial();
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_t0_18_mr);
    //FRAME UMI
    u8g2.drawFrame(3,3,120,30);
    u8g2.drawStr(8,23,"UMID: ");
    u8g2.setCursor(59, 23);
    u8g2.print(getUmidade());
    u8g2.drawStr(104,23,"%");
    //FRAME TEMP
    u8g2.drawFrame(3,34,120,30);
    u8g2.drawStr(8,55,"TEMP: ");
    u8g2.setCursor(59, 55);
    u8g2.print(getTemperatura());
    u8g2.drawCircle(115, 42, 2, U8G2_DRAW_ALL);
    u8g2.drawStr( 104, 55, "C");
    controle_Fan();
    printData();
    leituraSerial();
    delay(500);
    
  } while ( u8g2.nextPage() );
  delay(1000);
}
