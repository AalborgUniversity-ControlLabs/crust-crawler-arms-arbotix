/***********************************
 * Set PID parameters Example
 * This sketch is for use with one of the dynamixel based
 * robot arms at the Automation and Control labs, Aalborg
 * University.
 * This sketch sets the PID parameters of servo 2, so you
 * can feel the diference by pulling on it.
 *
 * 2015 Karl D. Hansen - kdh@es.aau.dk
 ***********************************/
// Import the ax12 library that provides
// commands to control the Dynamixel servos.
#include <ax12.h>
 // Additional dynamixel functionality for MX servos.
#include <dynamixel_mx.h>

void setup() {
    // Setup connection to the pc
    Serial.begin(9600);

    // Initialize the communication with the servos.
    // The default baud rate for the robot arms is
    // 1 Mbps.
    ax12Init(1000000);

    // Set torque on (stiffen the joints) on all servos.
    // (ID 254 is the braoadcasting address).
    TorqueOn(254);
}

void loop() {
    String command = "";

    // If the user sends something
    if (Serial.available()) {
        // Read the characters into a command string.
        char in_char = Serial.read();
        while (in_char != -1) {
            command += in_char;
        }

        // Check that it is a command (which is "pid(...)")
        // and that it is long enough.
        if (command.startsWith("pid(") && command.length() >= 5) {
            // If there are no parameters we just read back
            // the PID values.
            if (command[4] == ')') {
                printPid();
            } else {
                // Else get the parameters
                float p_gain;
                float i_gain;
                float d_gain;

                // Read P until a comma
                int i = 4;
                for (int k = 0; i < command.length(); ++i) {
                    char buffer[10];
                    if (command[i] == ',' || k > 9) {
                        break;
                    }
                    buffer[k++] += command[i];
                    p_gain = atof(buffer);
                }
                // Then I
                for (int k = 0; i < command.length(); ++i) {
                    char buffer[10];
                    if (command[i] == ',' || k > 9) {
                        break;
                    }
                    buffer[k++] += command[i];
                    i_gain = atof(buffer);
                }
                // And D until the end parenthesis.
                for (int k = 0; i < command.length(); ++i) {
                    char buffer[10];
                    if (command[i] == ')' || k > 9) {
                        break;
                    }
                    buffer[k++] += command[i];
                    d_gain = atof(buffer);
                }

                // Tell the user what we got
                Serial.print("Got: ");
                printFloat(p_gain, 1000);
                Serial.print(" ");
                printFloat(i_gain, 1000);
                Serial.print(" ");
                printFloat(d_gain, 1000);
                Serial.println();

                // Set the parameters
                SetPidGains(2, p_gain, i_gain, d_gain);
            }
        }
    }
}

void printPid()
{
    int p = ax12GetRegister(2, MX_P_GAIN, 1);
    printFloat(p / 8.0, 1000);
    Serial.print(", ");

    int i = ax12GetRegister(2, MX_I_GAIN, 1);
    printFloat(i / 2.048, 1000);
    Serial.print(", ");

    int d = ax12GetRegister(2, MX_D_GAIN, 1);
    printFloat(d / 250, 1000);
    Serial.println();
}

void printFloat(float val, unsigned int precision){
// prints val with number of decimal places determine by precision
// NOTE: precision is 1 followed by the number of zeros for the desired number of decimial places
// example: printFloat( 3.1415, 100); // prints 3.14 (two decimal places)

    Serial.print (int(val));  //prints the int part
    Serial.print("."); // print the decimal point
    unsigned int frac;
    if(val >= 0)
        frac = (val - int(val)) * precision;
    else
        frac = (int(val)- val ) * precision;
    Serial.print(frac,DEC) ;
} 