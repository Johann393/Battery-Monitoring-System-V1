#include <Wire.h>
#include <Adafruit_INA219.h>
#include <math.h>

// ===== INA219 =====
Adafruit_INA219 ina1(0x40);
Adafruit_INA219 ina2(0x44);

// ===== NTC =====
#define NTC1 A0
#define NTC2 A2
#define BUZZER 7

const float VCC = 5.0;
const float R_FIXO = 9900.0;

// NTC 222
const float R0 = 2200.0;
const float T0 = 298.15;
const float BETA = 3977.0;

// Limites com histerese
const float TEMP_LIGA = 27.0;
const float TEMP_DESLIGA = 26.0;

bool alertaLigado = false;

// ===== Função para ler temperatura =====
float lerTemperatura(int pino) {
  int soma = 0;
  for (int i = 0; i < 10; i++) {
    soma += analogRead(pino);
    delay(2);
  }
  int adc = soma / 10;

  if (adc <= 0 || adc >= 1023) return -100;

  float Vout = adc * (VCC / 1023.0);
  float R_ntc = R_FIXO * (Vout / (VCC - Vout));

  float tempK = 1.0 / ((1.0/T0) + (1.0/BETA) * log(R_ntc / R0));
  return tempK - 273.15;
}

void setup() {
  Serial.begin(9600);
  Wire.begin();

  if (!ina1.begin()) {
    Serial.println("Erro INA219 1 (0x40)");
    while (1);
  }

  if (!ina2.begin()) {
    Serial.println("Erro INA219 2 (0x44)");
    while (1);
  }

  pinMode(BUZZER, OUTPUT);
}

void loop() {

  // ===== Temperaturas =====
  float temp1 = lerTemperatura(NTC1);
  float temp2 = lerTemperatura(NTC2);

  // ===== INA219 =====
  float V1 = ina1.getBusVoltage_V();
  float I1 = ina1.getCurrent_mA();

  float V2 = ina2.getBusVoltage_V();
  float I2 = ina2.getCurrent_mA();

  // ===== Controle do buzzer =====
  float tempMax = max(temp1, temp2);

  // Liga
  if (tempMax >= TEMP_LIGA) {
    alertaLigado = true;
  }

  // Desliga
  if (tempMax <= TEMP_DESLIGA) {
    alertaLigado = false;
  }

  // Buzzer ativo
  if (alertaLigado) {
    digitalWrite(BUZZER, HIGH);
  } else {
    digitalWrite(BUZZER, LOW);
  }

  // ===== Serial =====
  Serial.print("B1 -> Temp: ");
  Serial.print(temp1);
  Serial.print(" °C | V: ");
  Serial.print(V1);
  Serial.print(" V | I: ");
  Serial.print(I1);
  Serial.print(" mA || ");

  Serial.print("B2 -> Temp: ");
  Serial.print(temp2);
  Serial.print(" °C | V: ");
  Serial.print(V2);
  Serial.print(" V | I: ");
  Serial.print(I2);
  Serial.println(" mA");

  delay(500);
}
