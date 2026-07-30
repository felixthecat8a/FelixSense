#ifndef FELIX_SENSE_NIGHT_LIGHT_H
#define FELIX_SENSE_NIGHT_LIGHT_H

#include <Arduino.h>

namespace FelixSense {

  class NightLight {
  public:
    template <typename T> static inline bool hysteresis(T value, T low, T high, bool& state) {
      if (!state && value < low) {
        state = true;
      } else if (state && value > high) {
        state = false;
      }

      return state;
    }

    template <typename T> static bool isAbove(T value, T threshold) { return value > threshold; }

    template <typename T> static bool isBelow(T value, T threshold) { return value < threshold; }
  };

} // namespace FelixSense

#endif // FELIX_SENSE_NIGHT_LIGHT_H
