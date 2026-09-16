#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <MD_MAX72xx.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW // If data looks upside-down, backwards or scrambled, change this to GENERIC_HW, ICSTATION_HW or PAROLA_HW
#define MAX_DEVICES 1

const int CS1 = 27; // D1
const int IO = 28;  // D2
const int SW = 29;  // D3

const byte LEVEL_HEX[8]={      //Hex pattern when PCB is direclty parallel to surface
  0x18, // ◯◯◯●●◯◯◯
  0x18, // ◯◯◯●●◯◯◯
  0x18, // ◯◯◯●●◯◯◯
  0xFF, // ●●●●●●●●
  0xFF, // ●●●●●●●●
  0x18, // ◯◯◯●●◯◯◯
  0x18, // ◯◯◯●●◯◯◯
  0x18  // ◯◯◯●●◯◯◯
};

MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS1, MAX_DEVICES);

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

const float LEVEL_TOLERANCE = 0.40; // Adjust based on vibration levels
const float MAX_VISIBLE_ANGLE = 45.0;

void displayParallel() {
  for (uint8_t row = 0; row < 8; row++) {
    mx.setRow(0, row, LEVEL_HEX[row]);
  }
}

void setup() {
  Wire.begin();
  Serial.begin(115200);

  pinMode(CS1, OUTPUT);
  pinMode(IO, OUTPUT);
  pinMode(SW, INPUT_PULLUP);

  Serial.println("Initialising");

  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 5); // Brightness (0-15)
  mx.clear();

  accel.begin();
  accel.setRange(ADXL345_RANGE_2_G);
  
  Serial.println("Starting");
}

void loop() {
  sensors_event_t event; 
  accel.getEvent(&event);

  float xForce = event.acceleration.x;
  float yForce = event.acceleration.y;
  float zForce = event.acceleration.z;

  float angle = atan2(yForce, zForce) * 180.0 / M_PI; // Converted to angle in degrees

  mx.clear();

  if (angle >= -LEVEL_TOLERANCE && angle <= LEVEL_TOLERANCE) {
    displayParallel();
  }
  else {
    float constrainedAngle = constrain(angle, -MAX_VISIBLE_ANGLE, MAX_VISIBLE_ANGLE);
    int centerRow = map(constrainedAngle, -MAX_VISIBLE_ANGLE, MAX_VISIBLE_ANGLE, 0, 7);

    for (int col = 0; col < 8; col++) {
      int targetRow = centerRow + (col - 4); 

      if (targetRow >= 0 && targetRow < 8) {
        mx.setPoint(targetRow, col, true); 
      }
    }
  }

  delay(100);
}


