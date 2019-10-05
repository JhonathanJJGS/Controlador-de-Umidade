#include <DHT.h>
#include <DHT_U.h>
#include <U8glib.h>

#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11



 
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);  // Display which does not send AC
DHT dht(DHTPIN, DHTTYPE);
 
void tela_umidade(float umidade) 
{
  //Comandos graficos para o display devem ser colocados aqui
  //Linha superior - temperatura
  u8g.setFont(u8g_font_5x7); 
  u8g.drawStr( 22, 14, "Sensor de Umidade");
  //Hora
  u8g.setFont(u8g_font_fub30);
  u8g.setPrintPos( 10, 57);
  u8g.print(umidade);
  //Texto - AM
  u8g.setFont(u8g_font_5x7);
  //moldura relogio
  u8g.drawRFrame(0,18, 128, 46, 4);
}

void tela_temperatura(float temperatura) 
{
  //Comandos graficos para o display devem ser colocados aqui
  //Linha superior - temperatura
  u8g.setFont(u8g_font_5x7); 
  u8g.drawStr( 15, 14, "Sensor de Temperatura");
  //Hora
  u8g.setFont(u8g_font_fub30);
  u8g.setPrintPos( 10, 57);
  u8g.print(temperatura);
  //Texto - AM
  u8g.setFont(u8g_font_5x7);
  //moldura relogio
  u8g.drawRFrame(0,18, 128, 46, 4);
}
 
void setup(void) 
{
  Serial.begin(9600);
  dht.begin();
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
  float umidade = dht.readHumidity();
  float temperatura = dht.readTemperature();
  u8g.firstPage();   
  do {
   tela_temperatura(temperatura);
  }
  while( u8g.nextPage() );//end of picture loop
  delay(1000);
  u8g.firstPage();   
  do {
   tela_umidade(umidade);
  }
  while( u8g.nextPage() );//end of picture loop 
   
  delay(2000);
}
