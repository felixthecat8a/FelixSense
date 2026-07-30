#ifndef FELIX_SENSE_SENSOR_H
#define FELIX_SENSE_SENSOR_H

#include "Filter.h"
#include "Math.h"
#include <Arduino.h>

namespace FelixSense {

  enum class FilterType { SMA, EMA };

  class AnalogInputPin {
  public:
    AnalogInputPin(uint8_t pin) : _pin(pin) {}
    void begin() { pinMode(_pin, INPUT); }
    uint16_t read() { return analogRead(_pin); }

  private:
    uint8_t _pin;
  };

  class Sensor {
  public:
    static constexpr uint8_t SIMPLE_MOVING_AVERAGE_SIZE = 5;

    explicit Sensor(uint8_t pin);
    virtual ~Sensor() = default;

    virtual void begin(uint16_t resolutionADC = 10);
    virtual uint16_t readHardware();
    virtual void update();

    uint16_t readRaw() const;
    uint16_t readSmoothed() const;

    float readNormalized() const { return normalize(readRaw()); }
    float readNormalizedSmoothed() const { return normalize(readSmoothed()); }

    float read() const { return readNormalized(); }
    float readSmooth() const { return readNormalizedSmoothed(); }

    float readVoltage(float vRef) const { return read() * vRef; }
    float readVoltageSmoothed(float vRef) const { return readSmooth() * vRef; }

    uint16_t readMapped(uint16_t minOut, uint16_t maxOut) const;
    uint16_t readMappedSmoothed(uint16_t minOut, uint16_t maxOut) const;

    uint16_t getScale() const { return _scaleADC; }

    void setFilter(FilterType type) { _filterType = type; }
    void setEMAAlpha(float alpha) { _ema.setAlpha(alpha); }

    bool isReady() const { return _initialized; }

  private:
    float normalize(uint16_t value) const { return value * (1.0f / _scaleADC); }

  protected:
    AnalogInputPin _pin; // uint8_t _pin;

    uint16_t _scaleADC = 1023;
    uint16_t _lastRaw = 0;

    bool _initialized = false;

    SMA_Filter<SIMPLE_MOVING_AVERAGE_SIZE> _sma;
    EMA_Filter _ema;

    FilterType _filterType = FilterType::SMA;
  };

} // namespace FelixSense

#endif // FELIX_SENSE_SENSOR_H
