#ifndef DYNAMIXEL_H
#define DYNAMIXEL_H

/** EEPROM AREA **/
#define MX_MODEL_NUMBER_L               0
#define MX_MODEL_NUMBER_H               1
#define MX_VERSION                      2
#define MX_ID                           3
#define MX_BAUD_RATE                    4
#define MX_RETURN_DELAY_TIME            5
#define MX_CW_ANGLE_LIMIT_L             6
#define MX_CW_ANGLE_LIMIT_H             7
#define MX_CCW_ANGLE_LIMIT_L            8
#define MX_CCW_ANGLE_LIMIT_H            9
#define MX_LIMIT_TEMPERATURE            11
#define MX_DOWN_LIMIT_VOLTAGE           12
#define MX_UP_LIMIT_VOLTAGE             13
#define MX_MAX_TORQUE_L                 14
#define MX_MAX_TORQUE_H                 15
#define MX_RETURN_LEVEL                 16
#define MX_ALARM_LED                    17
#define MX_ALARM_SHUTDOWN               18
#define MX_MULTI_TURN_OFFSET_L          20
#define MX_MULTI_TURN_OFFSET_H          21
#define MX_RESOLUTION_DIVIDER           22
/** RAM AREA **/
#define MX_TORQUE_ENABLE                24
#define MX_LED                          25
#define MX_D_GAIN                       26
#define MX_I_GAIN                       27
#define MX_P_GAIN                       28
#define MX_GOAL_POSITION_L              30
#define MX_GOAL_POSITION_H              31
#define MX_GOAL_SPEED_L                 32
#define MX_GOAL_SPEED_H                 33
#define MX_TORQUE_LIMIT_L               34
#define MX_TORQUE_LIMIT_H               35
#define MX_PRESENT_POSITION_L           36
#define MX_PRESENT_POSITION_H           37
#define MX_PRESENT_SPEED_L              38
#define MX_PRESENT_SPEED_H              39
#define MX_PRESENT_LOAD_L               40
#define MX_PRESENT_LOAD_H               41
#define MX_PRESENT_VOLTAGE              42
#define MX_PRESENT_TEMPERATURE          43
#define MX_REGISTERED_INSTRUCTION       44
#define MX_PAUSE_TIME                   45
#define MX_MOVING                       46
#define MX_LOCK                         47
#define MX_PUNCH_L                      48
#define MX_PUNCH_H                      49
#define MX_CURRENT_L                    68
#define MX_CURRENT_H                    69
#define MX_TORQUE_CONTROL_MODE_ENABLE   70
#define MX_GOAL_TORQUE_L                71
#define MX_GOAL_TORQUE_H                72
#define MX_GOAL_ACCELERATION            73

// Set the PID gains of an MX servo.
void SetPidGains(int id, float p_gain, float i_gain, float d_gain);

// Get the voltage supplied to an MX servo.
float GetVoltage(int id);

// Get the current consumption of an MX servo.
float GetCurrent(int id);

// Get the present speed of an MX servo.
float GetSpeed(int id);

// Set the torque setpoint.
void SetTorque(int id, float torque);

#define GetLowerAngleLimit(id) (ax12GetRegister(id, MX_CW_ANGLE_LIMIT_L, 2))
#define GetUpperAngleLimit(id) (ax12GetRegister(id, MX_CCW_ANGLE_LIMIT_L, 2))

#define TorqueControlEnable(id) (ax12SetRegister(id, MX_TORQUE_CONTROL_MODE_ENABLE, 1))
#define TorqueControlDisable(id) (ax12SetRegister(id, MX_TORQUE_CONTROL_MODE_ENABLE, 0))

#endif //DYNAMIXEL_H
