/*
 *
 * TCS3200 Library Full Example
 *
 * By: Nathanne Isip
 * 31 July 2023
 *
 */
#include <TCS3200.h>

// Define pin connections
#define S0_PIN 15
#define S1_PIN 2
#define S2_PIN 0
#define S3_PIN 4
#define OUT_PIN 16

// Create an instance of the TCS3200 class
TCS3200 tcs3200(S0_PIN, S1_PIN, S2_PIN, S3_PIN, OUT_PIN);

// Define color labels for identification
String color_indices[] = {"Red", "Green", "Blue"};

// Define RGB color values corresponding to the color labels
RGBColor color_values[] = {
  {255, 0, 0},  // Red
  {0, 255, 0},  // Green
  {0, 0, 255},  // Blue
};

void setup() {
  // Initialize the TCS3200 sensor and set frequency scaling to 20%
  tcs3200.begin();
  tcs3200.frequency_scaling(TCS3200_OFREQ_20P);

  // Initialize Serial communication for output
  Serial.begin(115200);
  Serial.println("TCS3200 Full Example");
  Serial.println("-----------------------------------");

  // Calibrate the sensor for accurate color readings
  Serial.println("Calibrating...");

  // Calibrate the sensor for light surface (white calibration)
  Serial.println("Please face the sensor to white surface.");
  delay(1000);
  tcs3200.calibrate_light();

  // Calibrate the sensor for dark surface (black calibration)
  Serial.println("Please face the sensor to dark surface.");
  delay(1000);
  tcs3200.calibrate_dark();

  // Complete calibration and enable calibrated readings
  Serial.println("Done calibrating!");
  tcs3200.calibrate();

  // Add a delay to allow time for the serial output to be read
  delay(1000);
}

void loop() {
  // Allow the TCS3200 sensor to check for interrupt conditions (if set)
  tcs3200.loop();

  Serial.println("-----------------------------------");

  // Read and display RGB color values
  RGBColor rgb_color = tcs3200.read_rgb_color();
  Serial.println("Red: " + String(rgb_color.red) +
    ", Green: " + String(rgb_color.green) +
    ", Blue: " + String(rgb_color.blue));

  // Read and display CMYK color values
  CMYKColor cmyk_color = tcs3200.read_cmyk();
  Serial.println("Cyan: " + String(cmyk_color.cyan) +
    ", Magenta: " + String(cmyk_color.magenta) +
    ", Yellow: " + String(cmyk_color.yellow) +
    ", Black: " + String(cmyk_color.black));

  // Read and display HSV (Hue, Saturation, Value) color values
  HSVColor hsv = tcs3200.read_hsv();
  Serial.println("Hue: " + String(hsv.hue) +
    ", Saturation: " + String(hsv.saturation) +
    ", Value: " + String(hsv.value));

  // Read and display CIE 1931 color values
  CIE1931Color cie1931 = tcs3200.read_cie1931();
  Serial.println("X: " + String(cie1931.x) +
    ", Y: " + String(cie1931.y) +
    ", Z: " + String(cie1931.z));

  // Calculate and display the Chroma value
  Serial.println("Chroma: " + String(tcs3200.get_chroma()));

  // Determine the dominant color from RGB values and display the result
  Serial.println("Dominant color: " +
    color_indices[tcs3200.get_rgb_dominant_color()]);

  // Find and display the nearest color label to the current RGB values
  Serial.println("Nearest color: " + 
    tcs3200.nearest_color<String>(
      color_indices, 
      color_values,
      sizeof(color_indices) / sizeof(color_indices[0])
    )
  );

  // Add a delay before repeating the loop
  delay(3000);
}