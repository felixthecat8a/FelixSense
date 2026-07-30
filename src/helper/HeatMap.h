#ifndef FELIX_SENSE_HEAT_MAP_H
#define FELIX_SENSE_HEAT_MAP_H

#include <Arduino.h>

namespace FelixSense {

  class HeatMap {
  public:
    static float getHue(float temp, float roomTemp, float maxShift) {
      const float GREEN_HUE = 120.0f;
      const float RANGE     = 120.0f;

      float diff;
      float scale = RANGE / maxShift;

      if (temp >= roomTemp) {
        diff = min(temp - roomTemp, maxShift);
        return constrain(GREEN_HUE - (diff * scale), 0.0f, 240.0f);
      } else {
        diff = min(roomTemp - temp, maxShift);
        return constrain(GREEN_HUE + (diff * scale), 0.0f, 240.0f);
      }
    }

    static uint8_t toRed(float hue) {
      hue = constrain(hue, 0.0f, 240.0f);

      if (hue < 120.0f) {
        return 255 * (1.0f - (hue / 120.0f));
      } else {
        return 0;
      }
    }

    static uint8_t toGreen(float hue) {
      hue = constrain(hue, 0.0f, 240.0f);

      if (hue < 120.0f) {
        return 255 * (hue / 120.0f);
      } else {
        return 255 * (1.0f - ((hue - 120.0f) / 120.0f));
      }
    }

    static uint8_t toBlue(float hue) {
      hue = constrain(hue, 0.0f, 240.0f);

      if (hue < 120.0f) {
        return 0;
      } else {
        return 255 * ((hue - 120.0f) / 120.0f);
      }
    }
  };

  class Temperature {
  public:
    // Celsius/Fahrenheit
    static float CtoF(float c) { return c * 9.0f / 5.0f + 32.0f; }
    static float FtoC(float f) { return (f - 32.0f) * 5.0f / 9.0f; }

    // Celsius/Kelvin
    static float CtoK(float c) { return c + 273.15f; }
    static float KtoC(float k) { return k - 273.15f; }

    // Fahrenheit/Kelvin
    static float FtoK(float f) { return CtoK(FtoC(f)); }
    static float KtoF(float k) { return CtoF(KtoC(k)); }
  };

} // namespace FelixSense

#endif // FELIX_SENSE_HEAT_MAP_H
