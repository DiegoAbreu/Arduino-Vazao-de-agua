//Importa a biblioteca do display
#include <LiquidCrystal.h>

//Mapeamento dos pinos do display
LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

//Define as variáveis e as inicia com valor zero
float vazao;
float media = 0; 
int contaPulso; 
int i = 0; 
int Min = 00; 
float Litros = 0;
float MiliLitros = 0;

//Inicia medição da vazão da água
void setup()
{ 
  Serial.begin(9600); 
  
  pinMode(2, INPUT);
  attachInterrupt(0, incpulso, RISING);
  Serial.println("\n\nInício da medição\n\n");

//Apresenta "SENSOR DE VAZAO DE AGUA" no display
 lcd.begin(16, 2);
 lcd.setCursor( 0, 0);
 lcd.print("   SENSOR DE ");
 lcd.setCursor( 0, 1);
 lcd.print(" VAZAO DE AGUA ");
 delay(3000);
 lcd.clear();
} 

//Loop com cálculo de vazão
void loop ()
{
  contaPulso = 0;
  sei();
  delay (1000);
  cli();
  
  vazao = contaPulso / 5.5;
  media=media+vazao;
  i++;
 
 MiliLitros = vazao / 60;
 Litros = Litros + MiliLitros;  

//Apresenta a medição no display. Ex: "1.02 L/min  0:48 Min  0.89L"
 lcd.setCursor(0, 0);
 lcd.print(vazao);
 lcd.print(" L/min ");
 lcd.setCursor(0, 1);
 lcd.print(Min);
 lcd.print(":"); 
 lcd.print(i);
 lcd.print("Min ");
 lcd.print(Litros);
 lcd.print("L ");
  
 if(i==60)
 {
 Min++;
 lcd.print(Min);
  
 if (Min >= 60)
 {
 Min = 0;
 }
 media = media / 60;
 Serial.print("\nMedia por minuto = ");
 Serial.print(media);
 Serial.println(" L/min - ");
 media = 0;
 i = 0;
 }
}

// Conta os pulsos
void incpulso ()
{
 contaPulso++;
}
