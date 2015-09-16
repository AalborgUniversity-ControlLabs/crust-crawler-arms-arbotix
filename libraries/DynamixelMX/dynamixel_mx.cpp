#include "dynamixel_mx.h"
#include <ax12.h>

// Set the PID gains of an MX servo
// id: The ID of the servo to setup.
// p_gain: The proportional gain [0; 31,75] (default for dynamixels is 4)
// i_gain: The integral gain [0; 124,02] (default for dynamixels is 0)
// d_gain: The diferential gain [0; 1.016] (default for dynamixels is 0)
void mxSetPidGains(int id, float p_gain, float i_gain, float d_gain)
{
    char p = (char)(p_gain * 8);
    ax12SetRegister(id, MX_P_GAIN, p);

    char i = (char)(i_gain * 2.048);
    ax12SetRegister(id, MX_I_GAIN, i);

    char d = (char)(d_gain * 250);
    ax12SetRegister(id, MX_D_GAIN, d);
}
