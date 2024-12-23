#ifndef PCA9685_H
#define PCA9685_H

#include <string>
#include <memory>

class I2CPeripheral;

namespace PCA9685 {

constexpr uint16_t ms500 = 0x4B;
constexpr uint16_t ms1000 = 0xCA;
constexpr uint16_t ms1500 = 0x125;
constexpr uint16_t ms2000 = 0x18A;
constexpr uint16_t ms2500 = 0x1EF;
constexpr uint16_t step = 0x15;


class PCA9685 {
public:
    explicit PCA9685(const std::string &device = "/dev/i2c-1", int address = 0x40);
    ~PCA9685();

    void set_pwm_freq(const double freq_hz);

    void set_pwm(const int channel, const uint16_t on, const uint16_t off);

    void set_all_pwm(const uint16_t on, const uint16_t off);

    void set_pwm_ms(const int channel, const double ms);

private:
    std::unique_ptr<I2CPeripheral> i2c_dev;

    // Default frequency pulled from PCA9685 datasheet.
    double frequency = 200.0;

};
};


#endif // PCA9685_H
