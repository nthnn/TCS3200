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

The CMYK color space represents colors using four components: cyan, magenta, yellow, and black. Cyan, magenta, and yellow represent the primary subtractive colors, and black represents the key color.

The conversion from RGB to CMYK is achieved using the following equations:

\f{equation}{
K = 1 - max(R,G,B)
\f}

\f{equation}{
C = \frac{1-R-K}{1-K}
\f}

\f{equation}{
M = \frac{1-G-K}{1-K}
\f}

\f{equation}{
Y = \frac{1-B-K}{1-K}
\f}

### CIE 1931 XYZ Color Space Conversion

The CIE 1931 XYZ color space is a standard color space based on human color perception. It consists of three components: X, Y, and Z. The conversion from RGB to CIE 1931 XYZ is achieved using the following equations:

\f{equation}{
X = 0.4124564 × R + 0.3575761 × G + 0.1804375 × B
\f}

\f{equation}{
Y = 0.2126729 × R + 0.7151522 × G + 0.0721750 × B
\f}

\f{equation}{
Z = 0.0193339 × R + 0.1191920 × G + 0.9503041 × B
\f}

@page example Examples and Usage
@brief This page contains the comprehensive list of examples and usage of TCS3200 Arduino library.
@tableofcontents

# Setup and Initialization

To use the %TCS3200 Arduino Library, include the "tcs3200.h" header file and create an instance of the TCS3200 class.
Use the `begin()` function to initialize the %TCS3200 sensor, configure pins, and set default integration time
and frequency scaling.

```cpp
#include "tcs3200.h"

// Pin assignments for S0, S1, S2, S3, and OUT pins
#define S0_PIN 2
#define S1_PIN 3
#define S2_PIN 4
#define S3_PIN 5
#define OUT_PIN 6

// Create an instance of TCS3200
TCS3200 colorSensor(S0_PIN, S1_PIN, S2_PIN, S3_PIN, OUT_PIN);

void setup() {
    // Initialize the sensor
    colorSensor.begin();
}
```

# Calibration

The %TCS3200 sensor requires calibration for accurate color sensing. Calibration involves capturing readings
for both the lightest and darkest colors to establish the range for color intensity mapping. Use the `calibrate()`
function to enable calibration mode, and after invoking `calibrate_light()` and `calibrate_dark()` functions to calibrate
the sensor with white and black reference colors, respectively.

```cpp
void setup() {
    // Initialize the sensor
    colorSensor.begin();

    // Perform the actual calibration
    Serial.println("Please face the sensor to light surface.");
    colorSensor.calibrate_light(); // Calibrate with a white reference color
    delay(2000);

    Serial.println("Please face the sensor to dark surface.");
    colorSensor.calibrate_dark();  // Calibrate with a black reference color

    colorSensor.calibrate();
}
```

# Reading Color Intensity

To obtain color intensity values for individual color channels (red, green, blue, and clear), use the following functions:
`read_red()`, `read_green()`, `read_blue()`, and `read_clear()`. The `read_rgb_color()` function returns the RGB color
intensity values as an RGBColor structure.

```cpp
void loop() {
    // Read color intensity values for individual color channels
    uint8_t redIntensity = colorSensor.read_red();
    uint8_t greenIntensity = colorSensor.read_green();
    uint8_t blueIntensity = colorSensor.read_blue();
    uint8_t clearIntensity = colorSensor.read_clear();

    // Or read RGB color intensity values as an RGBColor structure
    RGBColor color = colorSensor.read_rgb_color();
}
```

# Integration Time and Frequency Scaling

The library provides control over the integration time and frequency scaling of the %TCS3200 sensor. Integration time
is set using the `integration_time()` function, and frequency scaling is set using the `frequency_scaling()` function.
Integration time affects the accuracy and sensitivity of color measurements, while frequency scaling optimizes the trade-off
between accuracy and response time.

```cpp
void setup() {
    // Initialize the sensor
    colorSensor.begin();

    // Set integration time to 2500 milliseconds (2.5 seconds)
    colorSensor.integration_time(2500);

    // Set frequency scaling to 20%
    colorSensor.frequency_scaling(TCS3200_OFREQ_20P);
}
```

# White Balancing

White balancing is essential for achieving accurate color measurements. It allows users to calibrate the sensor based on a
known white reference color. Use the `white_balance()` function to set the white balance with an RGBColor structure, and
`white_balance()` to retrieve the current white balance settings.

```cpp
void setup() {
    // Initialize the sensor
    colorSensor.begin();

    // Perform white balancing with a known white reference color (255, 255, 255)
    RGBColor whiteReference = {255, 255, 255};
    colorSensor.white_balance(whiteReference);
}
```

# Color Space Conversions

The %TCS3200 library supports color space conversions from RGB to other color spaces, including HSV, CMYK, and CIE 1931 XYZ.
Use the corresponding functions (`read_hsv()`, `read_cmyk()`, and `read_cie1931()`) to obtain color representations in
the desired color space.

```cpp
void loop() {
    // Read color in HSV color space
    HSVColor hsvColor = colorSensor.read_hsv();

    // Read color in CMYK color space
    CMYKColor cmykColor = colorSensor.read_cmyk();

    // Read color in CIE 1931 XYZ color space
    CIE1931Color cie1931Color = colorSensor.read_cie1931();
}
```

# Nearest Color Detection
The library provides a template function `nearest_color()` that allows users to find the nearest color label based on the
current sensor readings. This is useful for applications like color classification and sorting.

```cpp
void setup() {
    // Initialize the sensor
    colorSensor.begin();

    // Color labels and corresponding RGBColor values
    String colorLabels[] = {"Red", "Green", "Blue", "Yellow", "Orange"};
    RGBColor colorValues[] = {
      {255, 0, 0},
      {0, 255, 0},
      {0, 0, 255},
      {255, 255, 0},
      {255, 165, 0}
    };

    // Find the nearest color label based on current sensor readings
    String nearestColorLabel = colorSensor.nearest_color<String>(colorLabels, colorValues, 5);
}
```

# Interrupt Callbacks

The library allows users to define interrupt callbacks that trigger when the sensor readings exceed specified color thresholds. Use the `upper_bound_interrupt()` and `lower_bound_interrupt()` functions to set upper and lower color thresholds, respectively.

```cpp
// Define callback functions
void upperThresholdExceeded() {
    // Code to execute when the sensor readings exceed the upper threshold
}

void lowerThresholdExceeded() {
    // Code to execute when the sensor readings fall below the lower threshold
}

void setup() {
    // Initialize the sensor
    colorSensor.begin();

    // Set interrupt callbacks with upper and lower color thresholds
    RGBColor upperThreshold = {200, 200, 200};
    RGBColor lowerThreshold = {100, 100, 100};

    colorSensor.upper_bound_interrupt(upperThreshold, upperThresholdExceeded);
    colorSensor.lower_bound_interrupt(lowerThreshold, lowerThresholdExceeded);
}
```

# Integration in the Loop

The %TCS3200 library supports continuous color sensing and interrupt triggering in the loop. The `loop()` function should be called in the main loop to trigger interrupt callbacks if defined.

```cpp
void loop() {
    // Perform color sensing and execute interrupt callbacks if thresholds are exceeded
    colorSensor.loop();
}
```