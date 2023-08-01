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

/**
 * 
 * @file tcs3200.h
 * @author [Nathanne Isip](https://github.com/nthnn/TCS3200)
 * @brief %TCS3200 Color Sensor Arduino Library
 *
 * This library provides a comprehensive set of functions to interface with the
 * %TCS3200 color sensor. It enables users to read color intensity values from the
 * sensor, perform calibration, white balancing, color space conversions, and
 * nearest color detection. The library supports customization of integration time
 * and frequency scaling to optimize color sensing for specific applications.
 * 
 * **Example usage**:
 * @code{.cpp}
 * // TCS3200 Library Full Example
 * // By: Nathanne Isip
 * // 31 July 2023
 * 
 * #include <tcs3200.h>
 * 
 * // Define pin connections
 * #define S0_PIN 15
 * #define S1_PIN 2
 * #define S2_PIN 0
 * #define S3_PIN 4
 * #define OUT_PIN 16
 * 
 * // Create an instance of the TCS3200 class
 * TCS3200 tcs3200(S0_PIN, S1_PIN, S2_PIN, S3_PIN, OUT_PIN);
 * 
 * // Define color labels for identification
 * String color_indices[] = {"Red", "Green", "Blue"};
 * 
 * // Define RGB color values corresponding to the color labels
 * RGBColor color_values[] = {
 *   {255, 0, 0},  // Red
 *   {0, 255, 0},  // Green
 *   {0, 0, 255},  // Blue
 * };
 * 
 * void setup() {
 *   // Initialize the TCS3200 sensor and set frequency scaling to 20%
 *   tcs3200.begin();
 *   tcs3200.frequency_scaling(TCS3200_OFREQ_20P);
 * 
 *   // Initialize Serial communication for output
 *   Serial.begin(115200);
 *   Serial.println("TCS3200 Full Example");
 *   Serial.println("-----------------------------------");
 * 
 *   // Calibrate the sensor for accurate color readings
 *   Serial.println("Calibrating...");
 *   // Calibrate the sensor for light surface (white calibration)
 *   Serial.println("Please face the sensor to white surface.");
 *   delay(1000);
 *   tcs3200.calibrate_light();
 * 
 *   // Calibrate the sensor for dark surface (black calibration)
 *   Serial.println("Please face the sensor to dark surface.");
 *   delay(1000);
 *   tcs3200.calibrate_dark();
 * 
 *   // Complete calibration and enable calibrated readings
 *   Serial.println("Done calibrating!");
 *   tcs3200.calibrate();
 * 
 *   // Add a delay to allow time for the serial output to be read
 *   delay(1000);
 * }
 * 
 * void loop() {
 *   // Allow the TCS3200 sensor to check for interrupt conditions (if set)
 *   tcs3200.loop();
 * 
 *   Serial.println("-----------------------------------");
 * 
 *   // Read and display RGB color values
 *   RGBColor rgb_color = tcs3200.read_rgb_color();
 *   Serial.println("Red: " + String(rgb_color.red) +
 *     ", Green: " + String(rgb_color.green) +
 *     ", Blue: " + String(rgb_color.blue));
 * 
 *   // Read and display CMYK color values
 *   CMYKColor cmyk_color = tcs3200.read_cmyk();
 *   Serial.println("Cyan: " + String(cmyk_color.cyan) +
 *     ", Magenta: " + String(cmyk_color.magenta) +
 *     ", Yellow: " + String(cmyk_color.yellow) +
 *     ", Black: " + String(cmyk_color.black));
 * 
 *   // Read and display HSV (Hue, Saturation, Value) color values
 *   HSVColor hsv = tcs3200.read_hsv();
 *   Serial.println("Hue: " + String(hsv.hue) +
 *     ", Saturation: " + String(hsv.saturation) +
 *     ", Value: " + String(hsv.value));
 * 
 *   // Read and display CIE 1931 color values
 *   CIE1931Color cie1931 = tcs3200.read_cie1931();
 *   Serial.println("X: " + String(cie1931.x) +
 *     ", Y: " + String(cie1931.y) +
 *     ", Z: " + String(cie1931.z));
 * 
 *   // Calculate and display the Chroma value
 *   Serial.println("Chroma: " + String(tcs3200.get_chroma()));
 * 
 *   // Determine the dominant color from RGB values and display the result
 *   Serial.println("Dominant color: " +
 *     color_indices[tcs3200.get_rgb_dominant_color()]);
 * 
 *   // Find and display the nearest color label to the current RGB values
 *   Serial.println("Nearest color: " + 
 *     tcs3200.nearest_color<String>(
 *       color_indices, 
 *       color_values,
 *       sizeof(color_indices) / sizeof(color_indices[0])
 *     )
 *   );
 * 
 *   // Add a delay before repeating the loop
 *   delay(3000);
 * }
 * @endcode
 *
 */
#ifndef TCS3200_H
#define TCS3200_H

#include <Arduino.h>

#define TCS3200_COLOR_RED     0x00  ///< Red color channel for filtering
#define TCS3200_COLOR_GREEN   0x01  ///< Green color channel for filtering
#define TCS3200_COLOR_BLUE    0x02  ///< Blue color channel for filtering
#define TCS3200_COLOR_CLEAR   0x03  ///< Clear color channel for filtering

#define TCS3200_PWR_DOWN      0x00  ///< Power down mode
#define TCS3200_OFREQ_2P      0x01  ///< 2% frequency scaling
#define TCS3200_OFREQ_20P     0x02  ///< 20% frequency scaling
#define TCS3200_OFREQ_100P    0x03  ///< 100% frequency scaling

/**
 * 
 * @brief Structure to represent RGB color values.
 * 
 */
typedef struct _RGBColor {
    uint8_t red;    ///< Red color intensity (0-255)
    uint8_t green;  ///< Green color intensity (0-255)
    uint8_t blue;   ///< Blue color intensity (0-255)
} RGBColor;

/**
 * 
 * @brief Structure to represent HSV color values.
 * 
 */
typedef struct _HSVColor {
    float hue;          ///< Hue value in degrees (0-360)
    float saturation;   ///< Saturation value (0-1)
    float value;        ///< Value (brightness) value (0-1)
} HSVColor;

/**
 * 
 * @brief Structure to represent CMYK color values.
 * 
 */
typedef struct _CMYKColor {
    float cyan;     ///< Cyan color intensity (0-1)
    float magenta;  ///< Magenta color intensity (0-1)
    float yellow;   ///< Yellow color intensity (0-1)
    float black;    ///< Black (Key) color intensity (0-1)
} CMYKColor;

/**
 * 
 * @brief Structure to represent CIE 1931 XYZ color values.
 * 
 */
typedef struct _CIE1931 {
    float x;    ///< X value
    float y;    ///< Y value
    float z;    ///< Z value
} CIE1931Color;

/**
 * 
 * @class TCS3200
 * @brief Class representing the TCS3200 color sensor.
 *
 * This class provides functions to interface with the %TCS3200 color
 * sensor, read color intensity values, perform calibration, white
 * balancing, color space conversions, and nearest color detection.
 * It also supports customization of integration time and frequency
 * scaling.
 * 
 */
class TCS3200 {
public:
    /**
     * 
     * @brief Constructor for TCS3200 class.
     * 
     * @param s0_pin Arduino pin connected to S0 pin of the %TCS3200.
     * @param s1_pin Arduino pin connected to S1 pin of the %TCS3200.
     * @param s2_pin Arduino pin connected to S2 pin of the %TCS3200.
     * @param s3_pin Arduino pin connected to S3 pin of the %TCS3200.
     * @param out_pin Arduino pin connected to OUT pin of the %TCS3200.
     * 
     */
    TCS3200(uint8_t s0_pin, uint8_t s1_pin, uint8_t s2_pin, uint8_t s3_pin, uint8_t out_pin);

    /**
     * 
     * @brief Initialize the %TCS3200 sensor and configure pins.
     * 
     */
    void begin();

    /**
     * 
     * @brief Read the intensity of the red color channel.
     * 
     * @return Red color intensity (0-255).
     * 
     */
    uint8_t read_red();

    /**
     * 
     * @brief Read the intensity of the green color channel.
     * 
     * @return Green color intensity (0-255).
     * 
     */
    uint8_t read_green();

    /**
     * 
     * @brief Read the intensity of the blue color channel.
     * 
     * @return Blue color intensity (0-255).
     * 
     */
    uint8_t read_blue();

    /**
     * 
     * @brief Read the intensity of the clear (ambient) color channel.
     * 
     * @return Clear color intensity (0-255).
     * 
     */
    uint8_t read_clear();

    /**
     * 
     * @brief Perform definition of the sensor as calibrated.
     *
     * This function defines the sensor as calibrated for the
     * next reading to be more accurate. This function must be
     * invoked after calling the functions `calibrate_light()`
     * and `calibrate_dark()`.
     * 
     */
    void calibrate();

    /**
     * 
     * @brief Perform light calibration for white balancing.
     *
     * This function reads color intensity values from the sensor
     * under a well-lit white surface and calculates the average
     * values for each color channel. These values are used for
     * white balancing future color readings.
     * 
     */
    void calibrate_light();

    /**
     * 
     * @brief Perform dark calibration for white balancing.
     *
     * This function reads color intensity values from the sensor under
     * a dark surface and calculates the average values for each color
     * channel. These values are used for white balancing future color
     * readings.
     * 
     */
    void calibrate_dark();

    /**
     * 
     * @brief Set the integration time for color sensing.
     * 
     * @param time Integration time in microseconds.
     * 
     */
    void integration_time(unsigned int time);

    /**
     * 
     * @brief Get the current integration time setting.
     * 
     * @return Integration time in microseconds.
     * 
     */
    unsigned int integration_time();

    /**
     * 
     * @brief Set the frequency scaling for color sensing.
     * 
     * @param scaling Frequency scaling value.
     * 
     */
    void frequency_scaling(int scaling);

    /**
     * 
     * @brief Get the current frequency scaling setting.
     * 
     * @return Frequency scaling value.
     * 
     */
    int frequency_scaling();

    /**
     * 
     * @brief Read the RGB color values from the sensor.
     * 
     * @return `RGBColor` representing the current color readings.
     * 
     */
    RGBColor read_rgb_color();

    /**
     * 
     * @brief Get the current white balance RGB values.
     * 
     * @return `RGBColor` representing white balance values.
     * 
     */
    RGBColor white_balance();

    /**
     * 
     * @brief Set the white balance RGB values.
     * 
     * @param white_balance_rgb RGBColor representing white balance values.
     * 
     */
    void white_balance(RGBColor white_balance_rgb);

    /**
     * 
     * @brief Read the HSV color values from the sensor.
     * 
     * @return HSVColor representing the current color
     *         readings in the HSV color space.
     * 
     */
    HSVColor read_hsv();

    /**
     * 
     * @brief Read the CMYK color values from the sensor.
     * 
     * @return CMYKColor representing the current color
     *         readings in the CMYK color space.
     * 
     */
    CMYKColor read_cmyk();

    /**
     * 
     * @brief Read the CIE 1931 XYZ color values from the sensor.
     * 
     * @return CIE1931Color representing the current color
     *         readings in the CIE 1931 XYZ color space.
     * 
     */
    CIE1931Color read_cie1931();

    /**
     * 
     * @brief Calculate the chroma of the current color readings.
     *
     * Chroma represents the vividness or saturation of a color.
     * It is calculated as the Euclidean distance of the color
     * from the white point in the CIE 1931 XYZ color space.
     *
     * \f{equation}{
     * \text{Chroma} = \sqrt{(X - 0.95047)^2 + (Y - 1.0)^2 + (Z - 1.08883)^2}
     * \f}
     *
     * @return Chroma value.
     * 
     */
    float get_chroma();

    /**
     * 
     * @brief Get the dominant RGB color channel.
     * 
     * @return Dominant RGB color channel.
     * 
     */
    uint8_t get_rgb_dominant_color();

    /**
     * 
     * @brief Continuously monitor color intensity values and
     *        trigger callbacks for interrupt conditions.
     *
     * This function should be called repeatedly in the main
     * loop of your Arduino sketch to continuously monitor
     * color intensity values from the sensor. If any interrupt
     * conditions have been set using the `upper_bound_interrupt()`
     * or `lower_bound_interrupt()` functions, the corresponding
     * registered callback functions will be executed when the
     * color intensity values meet the specified conditions.
     *
     * For example, if an upper bound interrupt is set with
     * a certain threshold color intensity, the callback
     * function will be executed when the RGB color intensity
     * values exceed the threshold. Similarly, if a lower
     * bound interrupt is set, the callback function will be
     * executed when the RGB color intensity values go below
     * the threshold.
     * 
     */
    void loop();

    /**
     * 
     * @brief Enable an upper bound interrupt with a given threshold.
     *
     * When the color intensity values exceed the threshold,
     * the registered callback function will be executed.
     *
     * @param threshold `RGBColor` threshold for the upper bound interrupt.
     * @param callback Function pointer to the callback function.
     * 
     */
    void upper_bound_interrupt(RGBColor threshold, void (*callback)());

    /**
     * 
     * @brief Enable a lower bound interrupt with a given threshold.
     *
     * When the color intensity values go below the threshold,
     * the registered callback function will be executed.
     *
     * @param threshold `RGBColor` threshold for the lower bound interrupt.
     * @param callback Function pointer to the callback function.
     */
    void lower_bound_interrupt(RGBColor threshold, void (*callback)());

    /**
     * 
     * @brief Clear the upper bound interrupt.
     * 
     * The previously registered callback function will no
     * longer be executed when the condition is met.
     * 
     */
    void clear_upper_bound_interrupt();

    /**
     * 
     * @brief Clear the lower bound interrupt.
     * 
     * The previously registered callback function will no
     * longer be executed when the condition is met.
     * 
     */
    void clear_lower_bound_interrupt();

    /**
     * 
     * @brief Find the nearest color label based on the current sensor readings.
     * 
     * @tparam T Type of the color label (e.g., String, char[]).
     * 
     * @param color_labels Array of color labels.
     * @param color_values Array of corresponding RGBColor values.
     * @param size Size of the arrays.
     * 
     * @return Nearest color label of type T.
     * 
     */
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
