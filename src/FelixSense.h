#ifndef FELIX_SENSE_H
#define FELIX_SENSE_H

#include "helper/AsyncTime.h"
#include "helper/HeatMap.h"
#include "helper/NightLignt.h"
#include "util/Sensor.h"
#include <Arduino.h>

namespace FelixSense {

  class Potentiometer : public Sensor {
  public:
    explicit Potentiometer(uint8_t pin, float vRef = 5.0f) : Sensor(pin), _vRef(vRef) {}

    float angle(float maxDegrees = 270.0f) const { return read() * maxDegrees; }
    float angleSmoothed(float maxDegrees = 270.0f) const { return readSmooth() * maxDegrees; }

    float voltage() const { return readVoltage(_vRef); }
    float voltageSmoothed() const { return readVoltageSmoothed(_vRef); }

    float percentage() const { return constrain(read(), 0.0f, 1.0f) * 100.0f; }
    float percentageSmoothed() const { return constrain(readSmooth(), 0.0f, 1.0f) * 100.0f; }

  private:
    float _vRef;
  };

  /* Vcc >> Photoresistor >> A# >> 10kohm Resistor >> GND */

  class Photoresistor : public Sensor {
  public:
    Photoresistor(uint8_t pin, float rFixed = 10000.0, float vRef = 5.0, float luxCoeff = 500.0)
      : Sensor(pin), _rFixed(rFixed), _vRef(vRef), _luxCoeff(luxCoeff) {}

    float lux() const { return _estimateLux(readVoltage(_vRef)); }
    float luxSmoothed() const { return _estimateLux(readVoltageSmoothed(_vRef)); }

    bool night(float low, float high) { return NightLight::hysteresis(read(), low, high, _state); }
    bool above(float threshold) { return NightLight::isAbove(read(), threshold); }
    bool below(float threshold) { return NightLight::isBelow(read(), threshold); }

    float percentage() const { return constrain(read(), 0.0f, 1.0f) * 100.0f; }
    float percentageSmoothed() const { return constrain(readSmooth(), 0.0f, 1.0f) * 100.0f; }

    uint8_t level(uint8_t steps = 10) const {
      float n = constrain(read(), 0.0f, 0.9999f);
      return min((uint8_t)(n * steps), (uint8_t)(steps - 1));
    }

    uint8_t levelSmoothed(uint8_t steps = 10) const {
      float n = constrain(readSmooth(), 0.0f, 0.9999f);
      return min((uint8_t)(n * steps), (uint8_t)(steps - 1));
    }

  private:
    float _rFixed, _vRef, _luxCoeff;

    static constexpr float LDR_EXPONENT = 1.4f;

    float _estimateLux(float voltage) const {
      if (voltage <= 0.0f) return 0.0f;
      voltage = constrain(voltage, 0.0f, _vRef);

      float resistance = _rFixed * ((_vRef / voltage) - 1.0f);
      if (resistance <= 0.0f) return 0.0f;

      float r_kOhm = resistance / 1000.0f;
      return _luxCoeff / pow(r_kOhm, LDR_EXPONENT);
    }

    mutable bool _state = false;
  };

  /* Vcc >> 10kohm Pull-up Resistor >> A# >> NTC Thermistor >> GND */

  class Thermistor : public Sensor {
  public:
    Thermistor(uint8_t pin, float r25, float beta, float rPullup = 10000.0, float vRef = 5.0)
      : Sensor(pin), _r25(r25), _beta(beta), _rPullup(rPullup), _vRef(vRef) {}

    float getKelvin() const {
      float r = _readResistance();
      if (!isfinite(r) || r <= 0.0f) return NAN;
      return 1.0f / ((1.0f / KELVIN_25C) + (1.0f / _beta) * log(r / _r25));
    }

    float getCelsius() const { return Temperature::KtoC(getKelvin()); }
    float getFahrenheit() const { return Temperature::CtoF(getCelsius()); }

  private:
    static constexpr float KELVIN_25C = 298.15f;

    float _r25, _beta, _rPullup, _vRef;

    float _readResistance() const {
      float v = readVoltageSmoothed(_vRef);
      if (v <= 0.001f) return INFINITY;
      if (v >= (_vRef - 0.001f)) return 0.0f;
      return (_rPullup * v) / (_vRef - v);
    }
  };

} // namespace FelixSense

#endif // FELIX_SENSE_H
