@mainpage %TCS3200 Color Sensor Arduino Library
@tableofcontents

## Overview

Color sensing is a crucial aspect of many modern applications, from color detection and sorting in industrial processes to smart home automation systems. The %TCS3200 color sensor is a widely used device for color sensing due to its simplicity, accuracy, and ease of integration. To harness the full potential of this sensor, this library was developed, a powerful and user-friendly API that allows Arduino developers to interface with the %TCS3200 sensor effortlessly. This comprehensive documentation will delve into the intricacies of the %TCS3200 sensor, the algorithm behind the library, and the mathematical equations used to convert raw sensor readings into meaningful color data.

## Understanding the TCS3200 Color Sensor

The %TCS3200 color sensor is a programmable device that can detect and measure the intensity of light across different color channels. It comes equipped with an array of photodiodes, each covered by a specific color filter: red, green, blue, and clear. The clear photodiode captures ambient light and is used to calculate the overall intensity.

The sensor has two main operating modes: frequency and analog output. In frequency mode, the sensor outputs a square wave with a frequency proportional to the intensity of light detected. In analog output mode, the sensor provides a voltage output proportional to the intensity.

To achieve accurate color sensing, the %TCS3200 library employs both frequency and analog output modes to calibrate and interpret color data. Additionally, the library allows users to customize the integration time and frequency scaling of the sensor to optimize performance for specific applications.

## Algorithm Overview

The TCS3200 Arduino Library is designed with simplicity and extensibility in mind. It offers a wide range of functionalities, from basic color sensing to advanced features like white balancing, color space conversions, and nearest color detection.

Here's an overview of the key functions and their roles in the library:

- **Initialization**

  The `begin()` function initializes the %TCS3200 sensor by configuring the necessary pins and setting default integration time and frequency scaling.

- **Color Reading**

  The library provides four functions to read the intensity of each color channel: `read_red()`, `read_green()`, `read_blue()`, and `read_clear()`. The clear channel reading is used for calibration and to calculate the RGB color intensity values.

- **Calibration**

  The `calibrate()`, `calibrate_light()`, and `calibrate_dark()` function enables calibration of the sensor. Calibration involves capturing readings for both the lightest and darkest colors to establish the range for color intensity mapping.

- **Integration Time**

  The `integration_time()` function allows users to get and set the integration time for each color reading, affecting the accuracy and sensitivity of color measurements.

- **Frequency Scaling**

  The `frequency_scaling()` function gets and sets the scaling factor for the sensor's frequency output to optimize the trade-off between accuracy and response time.

- **White Balancing**

  The `white_balance()` functions provide the ability to calibrate the sensor based on a known white color to achieve accurate color measurements.

- **Color Space Conversions**

  The library offers functions to convert RGB color values to other color spaces such as HSV, CMYK, and CIE 1931 XYZ.

- **Nearest Color Detection**

  The `nearest_color()` template function takes an array of color labels and RGBColor values and returns the nearest color label based on the current sensor readings.

## Mathematical Equations

### HSV Color Space Conversion

The HSV color space represents colors using three components: hue, saturation, and value. The hue component represents the color type (e.g., red, green, blue), saturation represents the color purity, and value represents the brightness.

The conversion from RGB to HSV is achieved using the following equations:

\f{equation}{
V = \max(R, G, B)
\f}

\f{equation}{
\Delta = \max(R, G, B) - \min(R, G, B)
\f}

\f{equation}{
S = \begin{cases} 
  \frac{\Delta}{V} & \text{if } V \neq 0 \\
    0 & \text{otherwise}
  \end{cases}
\f}

\f{equation}{
H = \begin{cases} 
  0 & \text{if } \Delta = 0 \\
    60^\circ \times \frac{(G - B)}{\Delta} + 360^\circ & \text{if } V = R \\
    60^\circ \times \frac{(B - R)}{\Delta} + 120^\circ & \text{if } V = G \\
    60^\circ \times \frac{(R - G)}{\Delta} + 240^\circ & \text{if } V = B
  \end{cases}
\f}

### CMYK Color Space Conversion

The CMYK color space represents colors using four components: cyan, magenta, yellow, and black. Cyan, magenta, and yellow represent the primary subtractive colors, and black represents the key color

@page example Example Usage
@tableofcontents

## Full Example

```cpp

```