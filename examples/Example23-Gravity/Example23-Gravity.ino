/*
  Using the BNO085 for finding the direction of gravity.
  By: Anant Sharma

  Date: January 23rd, 2023
  SparkFun code, firmware, and software is released under the MIT License.
  Please see LICENSE.md for further details.
  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14586
  This example outputs a vector pointing towards the ground.

  It takes about 1ms at 400kHz I2C to read a record from the sensor, but we are polling the sensor continually
  between updates from the sensor. Use the interrupt pin on the BNO080 breakout to avoid polling.
  
  Hardware Connections:
  Attach the Qwiic Shield to your Arduino/Photon/ESP32 or other
  Plug the sensor onto the shield
  
  Serial.print it out at 9600 baud to serial monitor.
*/

#include <Wire.h>
#include "SparkFun_BNO080_Arduino_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_BNO080
BNO080 myIMU;



void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("BNO080 Read Example");

  Wire.begin();

    //Are you using a ESP? Check this issue for more information: https://github.com/sparkfun/SparkFun_BNO080_Arduino_Library/issues/16
//  //=================================
//  delay(100); //  Wait for BNO to boot
//  // Start i2c and BNO080
//  Wire.flush();   // Reset I2C
//  IMU.begin(BNO080_DEFAULT_ADDRESS, Wire);
//  Wire.begin(4, 5);
//  Wire.setClockStretchLimit(4000);
//  //=================================

  if (myIMU.begin() == false)
  {
    Serial.println("BNO080 not detected at default I2C address. Check your jumpers and the hookup guide. Freezing...");
    while (1);
  }

  Wire.setClock(400000); //Increase I2C data rate to 400kHz

  myIMU.enableGravity(10); //Send data update every 50ms

  Serial.println(F("Rotation vector enabled"));
  Serial.println(F("Output in form i, j, k, real, accuracy"));

}

void loop() {
    //Look for reports from the IMU
  if (myIMU.dataAvailable() == true)
  {
    float gravityX = myIMU.getGravityX();
    float gravityY = myIMU.getGravityY();
    float gravityZ = myIMU.getGravityZ();
    float gravityAccuracy = myIMU.getGravityAccuracy();

    Serial.print(gravityX, 2);
    Serial.print(F(","));
    Serial.print(gravityY, 2);
    Serial.print(F(","));
    Serial.print(gravityZ, 2);
    Serial.print(F(","));
    Serial.print(gravityAccuracy, 2);
    Serial.print(F(","));
    

    Serial.println();
  }
}