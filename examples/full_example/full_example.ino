#include <tcs3200.h>

#define S0_PIN 15
#define S1_PIN 2
#define S2_PIN 0
#define S3_PIN 4
#define OUT_PIN 16

TCS3200 tcs3200(S0_PIN, S1_PIN, S2_PIN, S3_PIN, OUT_PIN);
String color_indices[] = {"Red", "Green", "Blue"};

RGBColor color_values[] = {
  {255, 0, 0},
  {0, 255, 0},
  {0, 0, 255},
};

void setup() {
  tcs3200.begin();
  tcs3200.frequency_scaling(TCS3200_OFREQ_20P);

  Serial.begin(115200);
  Serial.println("TCS3200 Full Example");
  Serial.println("-----------------------------------");
  Serial.println("Calibrating...");

  Serial.println("Please face the sensor to white surface.");
  delay(1000);
  tcs3200.calibrate_light();

  Serial.println("Please face the sensor to dark surface.");
  delay(1000);
  tcs3200.calibrate_dark();

  Serial.println("Done calibrating!");
  tcs3200.calibrate();

  delay(1000);
}

void loop() {
  tcs3200.loop();
  Serial.println("-----------------------------------");

  RGBColor rgb_color = tcs3200.read_rgb_color();
  Serial.println("Red: " + String(rgb_color.red) +
    ", Green: " + String(rgb_color.green) +
    ", Blue: " + String(rgb_color.blue));

  CMYKColor cmyk_color = tcs3200.read_cmyk();
  Serial.println("Cyan: " + String(cmyk_color.cyan) +
    ", Magenta: " + String(cmyk_color.magenta) +
    ", Yellow: " + String(cmyk_color.yellow) +
    ", Black: " + String(cmyk_color.black));

  HSVColor hsv = tcs3200.read_hsv();
  Serial.println("Hue: " + String(hsv.hue) +
    ", Saturation: " + String(hsv.saturation) +
    ", Value: " + String(hsv.value));

  CIE1931Color cie1931 = tcs3200.read_cie1931();
  Serial.println("X: " + String(cie1931.x) +
    ", Y: " + String(cie1931.y) +
    ", Z: " + String(cie1931.z));

  Serial.println("Chroma: " + String(tcs3200.get_chroma()));
  Serial.println("Dominant color: " +
    color_indices[tcs3200.get_rgb_dominant_color()]);
  Serial.println("Nearest color: " + 
    tcs3200.nearest_color<String>(
      color_indices, 
      color_values,
      sizeof(color_indices) / sizeof(color_indices[0])
    )
  );

  delay(3000);
}