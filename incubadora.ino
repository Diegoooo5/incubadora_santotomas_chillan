#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// -----------------------------
// Configuración del DHT22
// -----------------------------
#define DHTPIN 2        // Pin de datos del DHT22
#define DHTTYPE DHT22   // Tipo de sensor
DHT dht(DHTPIN, DHTTYPE);

// -----------------------------
// Configuración del LCD 1602A
// -----------------------------
LiquidCrystal_I2C lcd(0x27, 16, 2); 
// OJO: algunas pantallas usan 0x3F, si no ves nada, cambia 0x27 por 0x3F

// -----------------------------
// Configuración incubadora
// -----------------------------
int dias_totales = 21;   // Ejemplo: pollos = 21 días
int dias_restantes;      
unsigned long inicio;    

void setup() {
  dht.begin();
  lcd.init();
  lcd.backlight();

  inicio = millis(); // Guardar el tiempo de inicio en milisegundos

  lcd.setCursor(0,0);
  lcd.print(" Incubadora ON ");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Calcular días transcurridos
  unsigned long tiempoTranscurrido = millis() - inicio;
  int dias_pasados = tiempoTranscurrido / (1000UL * 60 * 60 * 24);
  dias_restantes = dias_totales - dias_pasados;

  if (dias_restantes < 0) dias_restantes = 0; // Evitar negativos

  // Leer sensor
  float temp = dht.readTemperature(); 
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    lcd.setCursor(0,0);
    lcd.print("Error DHT22   ");
    lcd.setCursor(0,1);
    lcd.print("Check sensor! ");
    delay(2000);
    return;
  }

  // Mostrar en pantalla
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temp,1);
  lcd.print((char)223); // Símbolo ° en LCD
  lcd.print("C");

  lcd.setCursor(0,1);
  lcd.print("Faltan: ");
  lcd.print(dias_restantes);
  lcd.print(" dias");

  delay(2000);
}
