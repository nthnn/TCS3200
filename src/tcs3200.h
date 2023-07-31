#ifndef TCS3200_H
#define TCS3200_H

#include <Arduino.h>

#define TCS3200_COLOR_RED     0x00
#define TCS3200_COLOR_GREEN   0x01
#define TCS3200_COLOR_BLUE    0x02
#define TCS3200_COLOR_CLEAR   0x03

typedef struct _RGBColor {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t clear;
} RGBColor;

typedef struct _HSVColor {
    float hue;
    float saturation;
    float value;
} HSVColor;

typedef struct _CMYKColor {
    float cyan;
    float magenta;
    float yellow;
    float black;
} CMYKColor;

typedef struct _CIE1931 {
    float x;
    float y;
    float z;
} CIE1931Color;

class TCS3200 {
public:
    TCS3200(uint8_t s0_pin, uint8_t s1_pin, uint8_t s2_pin, uint8_t s3_pin, uint8_t out_pin);
    void begin();

    uint8_t read_red();
    uint8_t read_green();
    uint8_t read_blue();
    uint8_t read_clear();

    void calibrate();
    void calibrate_light();
    void calibrate_dark();

    void integration_time(unsigned int time);
    unsigned int integration_time();

    void frequency_scaling(float scaling);
    float frequency_scaling();

    RGBColor read_rgb_color();
    RGBColor white_balance();
    void white_balance(RGBColor white_balance_rgb);

    HSVColor read_hsv();
    CMYKColor read_cmyk();
    CIE1931Color read_cie1931();

    float get_chroma();
    uint8_t get_rgb_dominant_color();

private:
    uint8_t _s0_pin, _s1_pin, _s2_pin, _s3_pin, _out_pin;
    uint8_t max_r, max_g, max_b, max_c;
    uint8_t min_r, min_g, min_b, min_c;

    unsigned int _integration_time;
    float _frequency_scaling;
    bool is_calibrated;

    RGBColor white_balance_rgb;

    void select_filter(uint8_t filter);
};

#endif
