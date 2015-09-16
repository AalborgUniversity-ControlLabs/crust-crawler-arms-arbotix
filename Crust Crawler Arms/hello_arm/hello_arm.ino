/***********************************
 * Hello Robot Arm Example
 * This sketch is for use with one of the dynamixel based
 * robot arms at the Automation and Control labs, Aalborg
 * University.
 * This sketch brings the arm to an upright position from
 * whichever position it was in, and starts swaying each
 * joint +/- 180 degrees sequentially.
 * Everything happens quite slowly, so you can run this
 * even if you are not that comfortable with the arms yet.
 *
 * 2015 Karl D. Hansen - kdh@es.aau.dk
 ***********************************/

// Import the ax12 library that provides
// commands to control the Dynamixel servos.
#include <ax12.h>
// Additional dynamixel functionality for MX servos.
#include <dynamixel_mx.h>

int nominal_positions[5];
int dir[5];

void setup(){
  // Initialize the communication with the servos.
  // The default baud rate for the robot arms is
  // 1 Mbps.
  ax12Init(1000000);
  
  // Set torque on (stiffen the joints) on all servos.
  // (ID 254 is the braoadcasting address).
  TorqueOn(254);
  // Delay a short while to get correct readings.
  delay(100);
  
  // Raise the arm to nominal
  // - Set nominal positions
  nominal_positions[0] = 2048;
  nominal_positions[1] = 2048;
  nominal_positions[2] = 2048;
  nominal_positions[3] = 2048;
  nominal_positions[4] = 2048;
  
  // - check how far we are off
  for(int i = 0; i < 5; ++i){
    dir[i] = GetPosition(i + 1) - nominal_positions[i];
  }

  // - Send trajectory
  bool at_home = false;
  while(! at_home){
    for(int i = 0; i < 5; ++i){
      int set_point = nominal_positions[i] + dir[i];
      if(dir[i] > 0){
        dir[i] -= 1;
      }else if(dir[i] < 0){
        dir[i] += 1;
      }
      SetPosition(i+1, set_point);
    }
    
    // - Check if we are done
    at_home = true;
    for(int i = 0; i < 5; ++i){
      if(dir[i] != 0){
        at_home = false;
        break;
      }
    }
    
    // - Delay a while. Increase to move slower.
    delay(5);
  }
}

void loop()
{
  // Sway each joint
  // - First the three joints of the arm.
  for(int i = 1; i < 4; ++i){
    for(int pos = 2048; pos > 1024; --pos){
      SetPosition(i, pos);
      delay(2);
    }
    for(int pos = 1024; pos < 3072; ++pos){
      SetPosition(i, pos);
      delay(2);
    }
    for(int pos = 3072; pos > 2048; --pos){
      SetPosition(i, pos);
      delay(2);
    }
  }
  
  // - Then the two fingers
  //   - Left
  for(int pos = 2048; pos < 3072; ++pos){
    SetPosition(4, pos);
    delay(2);
  }
  for(int pos = 3072; pos > 2048; --pos){
    SetPosition(4, pos);
    delay(2);
  }
  //    - Right
  for(int pos = 2048; pos > 1024; --pos){
    SetPosition(5, pos);
    delay(2);
  }
  for(int pos = 1024; pos < 2048; ++pos){
    SetPosition(5, pos);
    delay(2);
  }
}

