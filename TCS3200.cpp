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

#include "tcs3200.h"

TCS3200::TCS3200(uint8_t s0_pin, uint8_t s1_pin, uint8_t s2_pin, uint8_t s3_pin, uint8_t out_pin):
    _s0_pin(s0_pin),
    _s1_pin(s1_pin),
    _s2_pin(s2_pin),
    _s3_pin(s3_pin),
    _out_pin(out_pin) { }

void TCS3200::begin() {
    pinMode(this->_s0_pin, OUTPUT);
    pinMode(this->_s1_pin, OUTPUT);
    pinMode(this->_s2_pin, OUTPUT);
    pinMode(this->_s3_pin, OUTPUT);
    pinMode(this->_out_pin, INPUT);

    this->_integration_time = 2000;
    this->_frequency_scaling = 1.0;
    this->is_calibrated = false;
}

void TCS3200::select_filter(uint8_t filter) {
    switch(filter) {
        case TCS3200_COLOR_RED:
            digitalWrite(this->_s2_pin, LOW);
            digitalWrite(this->_s3_pin, LOW);
            break;
        case TCS3200_COLOR_GREEN:
            digitalWrite(this->_s2_pin, HIGH);
            digitalWrite(this->_s3_pin, HIGH);
            break;
        case TCS3200_COLOR_BLUE:
            digitalWrite(this->_s2_pin, LOW);
            digitalWrite(this->_s3_pin, HIGH);
            break;
        case TCS3200_COLOR_CLEAR:
            digitalWrite(this->_s2_pin, HIGH);
            digitalWrite(this->_s3_pin, LOW);
            break;
    }
}

uint8_t TCS3200::read_red() {
    this->select_filter(TCS3200_COLOR_RED);

    uint8_t red = pulseIn(this->_out_pin, LOW);
    red = this->is_calibrated ?
        map(red, this->min_r, this->max_r, 255, 0) :
        map(red, 0, 255, 255, 0);

    return red;
}

uint8_t TCS3200::read_green() {
    this->select_filter(TCS3200_COLOR_GREEN);

    uint8_t green = pulseIn(this->_out_pin, LOW);
    green = this->is_calibrated ?
        map(green, this->min_g, this->max_g, 255, 0) :
        map(green, 0, 255, 255, 0);

    return green;
}

uint8_t TCS3200::read_blue() {
    this->select_filter(TCS3200_COLOR_BLUE);

    uint8_t blue = pulseIn(this->_out_pin, LOW);
    blue = this->is_calibrated ?
        map(blue, this->min_b, this->max_b, 255, 0) :
        map(blue, 0, 255, 255, 0);

    return blue;
}

uint8_t TCS3200::read_clear() {
    this->select_filter(TCS3200_COLOR_CLEAR);
    return pulseIn(this->_out_pin, LOW);
}

void TCS3200::calibrate() {
    this->is_calibrated = true;
}

void TCS3200::calibrate_light() {
    uint8_t r = 0, g = 0, b = 0, c = 0;

    delay(this->_integration_time / 2);
    for(int i = 0; i < 10; i++) {
        r += this->read_red();
        g += this->read_green();
        b += this->read_blue();

        delay(this->_integration_time / 10);
    }

    this->white_balance_rgb.red = this->min_r = r / 10;
    this->white_balance_rgb.green = this->min_g = g / 10;
    this->white_balance_rgb.blue = this->min_b = b / 10;
}

void TCS3200::calibrate_dark() {
    uint8_t r = 0, g = 0, b = 0, c = 0;

    delay(this->_integration_time / 2);
    for(int i = 0; i < 10; i++) {
        r += this->read_red();
        g += this->read_green();
        b += this->read_blue();
        c += this->read_clear();

        delay(this->_integration_time / 10);
    }

    this->max_r = r / 10;
    this->max_g = g / 10;
    this->max_b = b / 10;
}

void TCS3200::integration_time(unsigned int time) {
    this->_integration_time = time;
}

unsigned int TCS3200::integration_time() {
    return this->_integration_time;
}

void TCS3200::frequency_scaling(int scaling) {
    this->_frequency_scaling = scaling;

    switch(this->_frequency_scaling) {
        case TCS3200_PWR_DOWN:
            digitalWrite(this->_s0_pin, LOW);
            digitalWrite(this->_s1_pin, LOW);
            break;
        case TCS3200_OFREQ_2P:
            digitalWrite(this->_s0_pin, LOW);
            digitalWrite(this->_s1_pin, HIGH);
            break;
        case TCS3200_OFREQ_20P:
            digitalWrite(this->_s0_pin, HIGH);
            digitalWrite(this->_s1_pin, LOW);
            break;
        case TCS3200_OFREQ_100P:
            digitalWrite(this->_s0_pin, HIGH);
            digitalWrite(this->_s1_pin, HIGH);
            break;
    }
}

int TCS3200::frequency_scaling() {
    return this->_frequency_scaling;
}

void TCS3200::white_balance(RGBColor white_balance_rgb) {
    this->white_balance_rgb = white_balance_rgb;
}

RGBColor TCS3200::white_balance() {
    return this->white_balance_rgb;
}

RGBColor TCS3200::read_rgb_color() {
    RGBColor readings;
    readings.red = this->read_red();
    readings.green = this->read_green();
    readings.blue = this->read_blue();

    return readings;
}

HSVColor TCS3200::read_hsv() {
    HSVColor hsv_color;

    float r = this->read_red() / 255.0;
    float g = this->read_green() / 255.0;
    float b = this->read_blue() / 255.0;

    r = r * (this->white_balance_rgb.red > 0 ? (this->white_balance_rgb.red / 255.0) : 1.0);
    g = g * (this->white_balance_rgb.green > 0 ? (this->white_balance_rgb.green / 255.0) : 1.0);
    b = b * (this->white_balance_rgb.blue > 0 ? (this->white_balance_rgb.blue / 255.0) : 1.0);

    float max_val = max(r, max(g, b));
    hsv_color.value = max_val;

    float min_val = min(r, min(g, b));
    float delta = max_val - min_val;
    hsv_color.saturation = (max_val > 0.0) ? delta / max_val : 0.0;

    if(delta > 0.0) {
        hsv_color.hue = max_val == r ? (g - b) / delta : (max_val == g ? 2.0 + (b - r) / delta : 4.0 + (r - g) /delta);
        hsv_color.hue *= 60.0;

        if(hsv_color.hue < 0.0)
            hsv_color.hue += 360.0;
    }
    else hsv_color.hue = 0.0;

    return hsv_color;
}

CMYKColor TCS3200::read_cmyk() {
    float r = this->read_red() / 255.0;
    float g = this->read_green() / 255.0;
    float b = this->read_blue() / 255.0;

    float c = 1.0 - r;
    float m = 1.0 - g;
    float y = 1.0 - b;
    float k = min(c, min(m, y));

    c = (c - k) / (1.0 - k);
    m = (m - k) / (1.0 - k);
    y = (y - k) / (1.0 - k);

    CMYKColor cmyk_color;
    cmyk_color.cyan = c;
    cmyk_color.magenta = m;
    cmyk_color.yellow = y;
    cmyk_color.black = k;

    return cmyk_color;
}

CIE1931Color TCS3200::read_cie1931() {
    uint8_t red = this->read_red();
    uint8_t green = this->read_green();
    uint8_t blue = this->read_blue();

    red = red * (this->white_balance_rgb.red > 0 ? (this->white_balance_rgb.red / 255.0) : 1.0);
    green = green * (this->white_balance_rgb.green > 0 ? (this->white_balance_rgb.green / 255.0) : 1.0);
    blue = blue * (this->white_balance_rgb.blue > 0 ? (this->white_balance_rgb.blue / 255.0) : 1.0);

    float r = red / 255.0;
    float g = green / 255.0;
    float b = blue / 255.0;

    CIE1931Color cie1931_color;
    cie1931_color.x = 0.4124564 * r + 0.3575761 * g + 0.1804375 * b;
    cie1931_color.y = 0.2126729 * r + 0.7151522 * g + 0.0721750 * b;
    cie1931_color.z = 0.0193339 * r + 0.1191920 * g + 0.9503041 * b;

    return cie1931_color;
}

float TCS3200::get_chroma() {
    CIE1931Color cie1931_color = this->read_cie1931();

    float dx = cie1931_color.x - 0.95047;
    float dy = cie1931_color.y - 1.0;
    float dz = cie1931_color.z - 1.08883;

    return sqrt(dx * dx + dy * dy + dz * dz);
}

uint8_t TCS3200::get_rgb_dominant_color() {
    RGBColor color = this->read_rgb_color();

    uint8_t max_color = max(color.red, max(color.green, color.blue));
    if(max_color == color.red)
        return TCS3200_COLOR_RED;
    else if(max_color == color.green)
        return TCS3200_COLOR_GREEN;

    return TCS3200_COLOR_BLUE;
}

void TCS3200::upper_bound_interrupt(RGBColor threshold, void (*callback)()) {
    this->upper_bound_interrupt_callback = callback;
    this->ub_threshold = threshold;
}

void TCS3200::lower_bound_interrupt(RGBColor threshold, void (*callback)()) {
    this->lower_bound_interrupt_callback = callback;
    this->lb_threshold = threshold;
}

void TCS3200::clear_upper_bound_interrupt() {
    this->upper_bound_interrupt_callback = nullptr;
}

void TCS3200::clear_lower_bound_interrupt() {
    this->lower_bound_interrupt_callback = nullptr;
}

void TCS3200::loop() {
    if(this->upper_bound_interrupt_callback == nullptr &&
        this->lower_bound_interrupt_callback == nullptr)
        return;

    RGBColor current_reading = this->read_rgb_color();
    if(this->upper_bound_interrupt_callback != nullptr &&
        current_reading.red > this->ub_threshold.red &&
        current_reading.green > this->ub_threshold.green &&
        current_reading.blue > this->ub_threshold.blue)
        this->upper_bound_interrupt_callback();

    if(this->lower_bound_interrupt_callback != nullptr &&
        current_reading.red < this->lb_threshold.red &&
        current_reading.green < this->lb_threshold.green &&
        current_reading.blue < this->lb_threshold.blue)
        this->lower_bound_interrupt_callback();
}
