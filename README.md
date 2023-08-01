# TCS3200 Color Sensor Arduino Library

![Arduino CI Workflow](https://github.com/nthnn/TCS3200/actions/workflows/ci.yml/badge.svg)

Color sensing is a crucial aspect of many modern applications, from color detection and sorting in industrial processes to smart home automation systems. The TCS3200 color sensor is a widely used device for color sensing due to its simplicity, accuracy, and ease of integration. To harness the full potential of this sensor, this library was developed, a powerful and user-friendly API that allows Arduino developers to interface with the TCS3200 sensor effortlessly. This comprehensive documentation will delve into the intricacies of the TCS3200 sensor, the algorithm behind the library, and the mathematical equations used to convert raw sensor readings into meaningful color data.

The TCS3200 color sensor is a programmable device that can detect and measure the intensity of light across different color channels. It comes equipped with an array of photodiodes, each covered by a specific color filter: red, green, blue, and clear. The clear photodiode captures ambient light and is used to calculate the overall intensity.

Also, the sensor has two main operating modes: frequency and analog output. In frequency mode, the sensor outputs a square wave with a frequency proportional to the intensity of light detected. In analog output mode, the sensor provides a voltage output proportional to the intensity.

## Library Overview

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

## Getting Started

To start using TCS3200 library in your Arduino projects, follow these simple steps:

1. Download the TCS3200 library from the GitHub repository.
2. Extract the downloaded archive and rename the folder to "TCS3200".
3. Move the "TCS3200" folder to the Arduino libraries directory on your computer.
    - Windows: `Documents\Arduino\libraries\`
    - MacOS: `~/Documents/Arduino/libraries/`
    - Linux: `~/Arduino/libraries/`

4. Launch the Arduino IDE.
5. Click on `Sketch > Include Library > TCS3200` to include the library in your sketch.

You are now ready to use TCS3200 library in your Arduino projects! For detailed information about using this library, please refer to the [Documentation](https://nthnn.github.io/TCS3200/).

## Examples

To access the examples:

1. Open the Arduino IDE.
2. Click on `File > Examples > TCS3200` to see the list of available examples.
3. Upload the example sketch to your Arduino board and see the results in action.

## Contribution and Feedback

Contributions and feedback are all welcome to enhance this library. If you encounter any issues, have suggestions for improvements, or would like to contribute code, please do so.

## License

Copyright 2023 - Nathanne Isip

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

```THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.```