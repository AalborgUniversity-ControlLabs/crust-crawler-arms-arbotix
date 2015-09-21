/***********************************
 * Read Joint Positions Example
 * This sketch is for use with one of the dynamixel based
 * robot arms at the Automation and Control labs, Aalborg
 * University.
 * This sketch reads the positions of each joint of the arm
 * and sends these to a pc over the serial connection.
 *
 * 2015 Karl D. Hansen - kdh@es.aau.dk
 ***********************************/

// Import the ax12 library that provides
// commands to control the Dynamixel servos.
#include <ax12.h>
// Additional dynamixel functionality for MX servos.
#include <dynamixel_mx.h>

void setup(){
  // Setup connection to the pc
  Serial.begin(9600);
  
  // Initialize the communication with the servos.
  // The default baud rate for the robot arms is
  // 1 Mbps.
  ax12Init(1000000);
  
  // Set torque off (loosen the joints) on all servos.
  // (ID 254 is the braoadcasting address).
  Relax(254);
  // Delay a short while to get correct readings.
  delay(100); 
}

void loop(){
  // Go through each joint, note the position
  // and send it to the PC.
  for(int i = 1; i < 6; ++i){
    int pos = GetPosition(i);
    String report;
    report = i + ": " + pos;
    Serial.println(report);
  }
  
  // Wait a while, to not spam the PC.
  delay(100);
}
