#include "Sensor.h"

namespace FelixSense {

  Sensor::Sensor(uint8_t pin) : _pin(pin) {}

  void Sensor::begin(uint16_t resolutionADC) {
    #if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_SAMD)
      analogReadResolution(resolutionADC);
      _scaleADC = (1UL << resolutionADC) - 1UL;
    #else
      _scaleADC = 1023;
    #endif

    _pin.begin(); // pinMode(_pin, INPUT);
    _lastRaw = _pin.read(); // analogRead(_pin);
    _sma.begin(_lastRaw);
    _ema.begin(_lastRaw);
    _initialized = true;
  }

  uint16_t Sensor::readHardware() {
    return _pin.read(); // analogRead(_pin);
  }

  void Sensor::update() {
    if (!_initialized) return;

    uint16_t newSample = readHardware();
    _lastRaw = newSample;
    _sma.update(newSample);
    _ema.update(newSample);
  }

  uint16_t Sensor::readRaw() const { return _lastRaw; }

  uint16_t Sensor::readSmoothed() const {
    switch (_filterType) {
      case FilterType::EMA:
        return _ema.get();
      case FilterType::SMA:
      default:
        return _sma.get();
    }
  }

  uint16_t Sensor::readMapped(uint16_t minOut, uint16_t maxOut) const {
    uint16_t value = constrain(readRaw(), 0, _scaleADC);
    return map(value, 0, _scaleADC, minOut, maxOut);
  }

  uint16_t Sensor::readMappedSmoothed(uint16_t minOut, uint16_t maxOut) const {
    uint16_t value = constrain(readSmoothed(), 0, _scaleADC);
    return map(value, 0, _scaleADC, minOut, maxOut);
  }

} // namespace FelixSense
