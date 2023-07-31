/*
 * This file is part of the TCS3200 Color Sensor Arduino library.
 * Copyright (c) 2023 Nathanne Isip
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef TCS3200_H
#define TCS3200_H

#include <Arduino.h>

#define TCS3200_COLOR_RED     0x00
#define TCS3200_COLOR_GREEN   0x01
#define TCS3200_COLOR_BLUE    0x02
#define TCS3200_COLOR_CLEAR   0x03

#define TCS3200_PWR_DOWN      0x00
#define TCS3200_OFREQ_2P      0x01
#define TCS3200_OFREQ_20P     0x02
#define TCS3200_OFREQ_100P    0x03

typedef struct _RGBColor {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
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

    void frequency_scaling(int scaling);
    int frequency_scaling();

    RGBColor read_rgb_color();
    RGBColor white_balance();
    void white_balance(RGBColor white_balance_rgb);

    HSVColor read_hsv();
    CMYKColor read_cmyk();
    CIE1931Color read_cie1931();

    float get_chroma();
    uint8_t get_rgb_dominant_color();

    void loop();

    void upper_bound_interrupt(RGBColor threshold, void (*callback)());
    void lower_bound_interrupt(RGBColor threshold, void (*callback)());

    void clear_upper_bound_interrupt();
    void clear_lower_bound_interrupt();

    template <typename T>
    T nearest_color(T *color_labels, RGBColor *color_values, int size) {
        T nearest;

        RGBColor readings = this->read_rgb_color();
        uint16_t min_dist = 0xffff;

        for(int i = 0; i < size; i++) {
            uint16_t dist = abs(readings.red - color_values[i].red) +
                            abs(readings.green - color_values[i].green) +
                            abs(readings.blue - color_values[i].blue);

            if(dist < min_dist) {
                min_dist = dist;
                nearest = color_labels[i];
            }
        }

        return nearest;
    }

private:
    uint8_t _s0_pin, _s1_pin, _s2_pin, _s3_pin, _out_pin;
    uint8_t max_r, max_g, max_b;
    uint8_t min_r, min_g, min_b;

    unsigned int _integration_time;
    int _frequency_scaling;
    bool is_calibrated;

    void (*upper_bound_interrupt_callback)();
    void (*lower_bound_interrupt_callback)();

    RGBColor white_balance_rgb, ub_threshold, lb_threshold;

    void select_filter(uint8_t filter);
};

#endif
