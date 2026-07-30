#ifndef FELIX_SENSE_FILTER_H
#define FELIX_SENSE_FILTER_H

#include <Arduino.h>

namespace FelixSense {
  /* Simple Moving Average Filter */
  template <uint8_t SMA_SIZE>
  class SMA_Filter {
    public:
      SMA_Filter() = default;

      void begin(int initialValue = 0) {
        _runningSum = 0;

        for (uint8_t i = 0; i < SMA_SIZE; i++) {
          _samples[i] = initialValue;
          _runningSum += initialValue;
        }

        _sampleIndex = 0;
        _bufferFilled = true;
      }

      void reset(int value = 0) {
        begin(value);
      }

      void update(int newSample) {
        _runningSum -= _samples[_sampleIndex];
        _samples[_sampleIndex] = newSample;
        _runningSum += newSample;

        _sampleIndex++;
        if (_sampleIndex >= SMA_SIZE) {
          _sampleIndex = 0;
          _bufferFilled = true;
        }
      }

      int get() const {
        uint8_t count = _bufferFilled ? SMA_SIZE : _sampleIndex;
        if (count == 0) return 0;

        return _runningSum / count;
      }

    private:
      int _samples[SMA_SIZE] = {0};
      long _runningSum = 0;

      uint8_t _sampleIndex = 0;
      bool _bufferFilled = false;
  };

  /* Exponential Moving Average Filter */
  class EMA_Filter {
    public:
      // alpha: 0.0 → heavy smoothing, 1.0 → no smoothing
      explicit EMA_Filter(float alpha = 0.1f) : _alpha(alpha) {}

      void begin(int initialValue = 0) {
        _value = initialValue;
        _initialized = true;
      }

      void reset(int value = 0) {
        begin(value);
      }

      void setAlpha(float alpha) {
        _alpha = constrain(alpha, 0.0f, 1.0f);
      }

      float getAlpha() const {
        return _alpha;
      }

      void update(int newSample) {
        if (!_initialized) {
          begin(newSample);
          return;
        }
        // EMA formula: y[n] = α*x[n] + (1-α)*y[n-1]
        _value = _alpha * newSample + (1.0f - _alpha) * _value;
      }

      int get() const {
        return static_cast<int>(_value);
      }

      float getFloat() const {
        return _value;
      }

    private:
      float _alpha = 0.1f;
      float _value = 0.0f;
      bool _initialized = false;
  };

} // namespace FelixSense

#endif //FELIX_SENSE_FILTER_H