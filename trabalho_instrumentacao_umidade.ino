//Para conectar o display SDA vai na porta A4 e o SDK  vai na porta A5,
//O sensor é conectado da seguinte forma Primeiro pino no positivo, 
//segundo pino gnd 4 pino no A1.

#include <DHT.h>
#include <DHT_U.h>
#include <U8glib.h>
#define DHTPIN A1 
#define DHTTYPE DHT11  
#define pinCooler 4
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);  
DHT sensorUmidade(DHTPIN, DHTTYPE);



float getUmidade(){
 float umidade = sensorUmidade.readHumidity();  
 return umidade; 
}

float getTemperatura(){
 float temperatura = sensorUmidade.readTemperature();  
 return temperatura; 
}

void ligarCooler(){
 


}

void tela_umidade() 
{

  u8g.setFont(u8g_font_5x7); 
  u8g.drawStr( 22, 14, "Sensor de Umidade");
  u8g.setFont(u8g_font_fub30);
  u8g.setPrintPos( 10, 57);
  u8g.print(getUmidade());
  u8g.drawRFrame(0,18, 128, 46, 4);
}

void tela_temperatura() 
{

  u8g.setFont(u8g_font_5x7); 
  u8g.drawStr( 12, 14, "Sensor de Temperatura");
  u8g.setFont(u8g_font_fub30);
  u8g.setPrintPos( 10, 57);
  u8g.print(getTemperatura());
  u8g.setFont(u8g_font_8x13B);
  u8g.drawCircle(111, 24, 2); 
  u8g.drawStr( 115, 33, "C");
  u8g.setFont(u8g_font_5x7);
  u8g.drawRFrame(0,18, 128, 46, 4);
}
 
void setup(void) 
{
  Serial.begin(9600);
  pinMode(pinCooler, OUTPUT);
  sensorUmidade.begin();
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }
}
 
void loop(void) 
{
  u8g.firstPage();   
  do {
   tela_temperatura();
  }
  while( u8g.nextPage() );
  delay(1000);
  u8g.firstPage();   
  do {
   tela_umidade();
  }
  while( u8g.nextPage() );
}
