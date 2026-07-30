#include <FelixSense.h>

FelixSense::Potentiometer knob(A2);
FelixSense::Photoresistor ldr(A0, 10.0f, 5.0f, 500.0f);       // pin, Rfixed, vRef, luxCoeff
FelixSense::Thermistor temp(A1, 10000.0f, 10000.0f, 3950.0f); // pin, Rpullup, R25, beta

unsigned long lastPrint = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) {}

  Serial.println("=== FelixSense Library Demo ===");

  knob.begin(10);
  ldr.begin(10);
  temp.begin(10);
}

void loop() {

  knob.update();
  ldr.update();
  temp.update();

  if (AsyncTime::every(250, lastPrint)) {

    Serial.println();
    Serial.println("--- INPUT READINGS ---");
    Serial.print("Knob Voltage: "); Serial.println(knob.voltage());
    Serial.print("Knob Angle: "); Serial.println(knob.angle());
    Serial.print("Knob %: "); Serial.println(knob.percentage());

    Serial.println();
    Serial.println("--- LIGHT SENSOR READINGS ---");
    Serial.print("LDR Raw: "); Serial.println(ldr.readRaw());
    Serial.print("LDR %: ");   Serial.println(ldr.percentage());
    Serial.print("LDR Lux Est.: "); Serial.println(ldr.lux());

    Serial.println();
    Serial.println("--- TEMPERATURE READINGS ---");
    Serial.print("Temp (K): "); Serial.println(temp.getKelvin());
    Serial.print("Temp (C): "); Serial.println(temp.getCelsius());
    Serial.print("Temp (F): "); Serial.println(temp.getFahrenheit());

  }

  /* similar behavior */

  // if (AsyncTime::after(250, lastPrint)) {

  //   Serial.println();
  //   Serial.println("--- INPUT READINGS ---");
  //   Serial.print("Knob Voltage: "); Serial.println(knob.voltage());
  //   Serial.print("Knob Angle: "); Serial.println(knob.angle());
  //   Serial.print("Knob %: "); Serial.println(knob.percentage());

  //   Serial.println();
  //   Serial.println("--- LIGHT SENSOR READINGS ---");
  //   Serial.print("LDR Raw: "); Serial.println(ldr.readRaw());
  //   Serial.print("LDR %: ");   Serial.println(ldr.percentage());
  //   Serial.print("LDR Lux Est.: "); Serial.println(ldr.lux());

  //   Serial.println();
  //   Serial.println("--- TEMPERATURE READINGS ---");
  //   Serial.print("Temp (K): "); Serial.println(temp.getKelvin());
  //   Serial.print("Temp (C): "); Serial.println(temp.getCelsius());
  //   Serial.print("Temp (F): "); Serial.println(temp.getFahrenheit());

  //   AsyncTime::reset(lastPrint); // reset the timer
  // }
}
