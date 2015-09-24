#include "dynamixel_mx.h"
#include <ax12.h>

// Set the PID gains of an MX servo.
//
// Parameters:
// id: The ID of the servo to setup.
// p_gain: The proportional gain [0; 31,75] (default for dynamixels is 4)
// i_gain: The integral gain [0; 124,02] (default for dynamixels is 0)
// d_gain: The diferential gain [0; 1.016] (default for dynamixels is 0)
void SetPidGains(int id, float p_gain, float i_gain, float d_gain)
{
    char p = (char)(p_gain * 8);
    ax12SetRegister(id, MX_P_GAIN, p);

    char i = (char)(i_gain * 2.048);
    ax12SetRegister(id, MX_I_GAIN, i);

    char d = (char)(d_gain * 250);
    ax12SetRegister(id, MX_D_GAIN, d);
}

// Get the voltage supplied to an MX servo.
//
// Parameters:
// id: ID of the servo to query.
//
// Returns the voltage in V. The reading is precise to
// one decimal.
float GetVoltage(int id)
{
    int v = ax12GetRegister(id, MX_PRESENT_VOLTAGE, 1);
    return v / 10.0;
}

// Get the current consumption of an MX servo.
//
// Parameters:
// id: ID of the servo to query.
//
// Returns the current in mA. The reading is precise to
// one half digit.
float GetCurrent(int id)
{
    int i = ax12GetRegister(id, MX_CURRENT_L, 2);
    return 4.5 * (i - 2048);
}

// Get the present speed of an MX servo.
//
// Parameters:
// id: ID of the servo to query.
//
// Returns the speed in rpm. Negative is clockwise.
float GetSpeed(int id)
{
    int v = ax12GetRegister(id, MX_PRESENT_SPEED_L, 2);
    float velocity = 1;
    if (v > 1023) { // clockwise
        velocity = -1;
        v -= 1024;
    }
    velocity *= v * 0.11443;
    return velocity;
}

// Set the torque setpoint.
//
// Parameters:
// id: ID of the servo to control
// torque: The current to apply to the servo in mA. Negative
//         currents moves clockwise. Range is [-4600, 4600].
void SetTorque(int id, float torque)
{
    int torque_code = abs(torque) / 4.5;
    if (torque < 0) { // counter-clockwise
        torque_code += 1024;
    }
    ax12SetRegister2(id, MX_GOAL_TORQUE_L, torque_code);
}