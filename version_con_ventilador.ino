#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// -----------------------------
// Configuración del DHT22
// -----------------------------
#define DHTPIN 2        
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE);

// -----------------------------
// Configuración del LCD 1602A
// -----------------------------
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// -----------------------------
// Configuración del relé y ventilador
// -----------------------------
#define RELAY_FOCO 8       // Relé para el foco
#define RELAY_VENTILADOR 9 // Relé o MOSFET para ventilador

// -----------------------------
// Configuración incubadora
// -----------------------------
int dias_totales = 21;   
int dias_restantes;      
unsigned long inicio;    

// Rango de temperatura (histeresis)
float tempMin = 37.2;
float tempMax = 37.8;

// Control del ventilador
float fanOnTemp  = 38.0;
float fanOffTemp = 37.5;

void setup() {
  dht.begin();
  lcd.init();
  lcd.backlight();
  
  pinMode(RELAY_FOCO, OUTPUT);
  pinMode(RELAY_VENTILADOR, OUTPUT);
  digitalWrite(RELAY_FOCO, LOW);      
  digitalWrite(RELAY_VENTILADOR, LOW);

  inicio = millis();

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
  if (dias_restantes < 0) dias_restantes = 0;

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

  // -----------------------------
  // Control del foco (relé)
  // -----------------------------
  if (temp < tempMin) {
    digitalWrite(RELAY_FOCO, HIGH);  // Encender foco
  } else if (temp > tempMax) {
    digitalWrite(RELAY_FOCO, LOW);   // Apagar foco
  }

  // -----------------------------
  // Control del ventilador
  // -----------------------------
  if (temp > fanOnTemp) {
    digitalWrite(RELAY_VENTILADOR, HIGH);  // Encender ventilador
  } else if (temp < fanOffTemp) {
    digitalWrite(RELAY_VENTILADOR, LOW);   // Apagar ventilador
  }

  // -----------------------------
  // Mostrar en pantalla
  // -----------------------------
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temp,1);
  lcd.print((char)223); // símbolo °
  lcd.print("C");

  lcd.setCursor(0,1);
  lcd.print("Faltan: ");
  lcd.print(dias_restantes);
  lcd.print(" dias");

  delay(2000);
}
