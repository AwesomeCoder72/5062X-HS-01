#include "drive.hpp"
#include "main.h"

float curve_drive_values(int input_value, float scalar) {
    return (exp( - (scalar / 10.0)) + exp( (abs(input_value) - 127) / 10.0 ) * (1 - exp(-(scalar/10.0))) * input_value);
}

float scale_drive_values(float inputValue) {
    return (inputValue * (12000.0/127.0));
}

int ceiling_drive_values(int inputValue, int ceilingValue, int ceiling_pressed) {
    if (ceiling_pressed) {
        if (abs(inputValue) > ceilingValue) {
            if (inputValue > 0) {
                return ceilingValue;
            } else {
                return (-ceilingValue);
            } 
        }
    }

    return inputValue;
}

void split_arcade(int leftX, int leftY, int rightX, int rightY, int leftDeadzone, int rightDeadzone, float ceiling_value, int ceiling_pressed) {
    if ((abs(rightY) > rightDeadzone) || ((abs(leftX) > leftDeadzone))) {
        if (ceiling_value > 0) { 
            drive_right.move_voltage(scale_drive_values(ceiling_drive_values(rightY-leftX, ceiling_value, ceiling_pressed)));
            drive_left.move_voltage(scale_drive_values(ceiling_drive_values(rightY+leftX, ceiling_value, ceiling_pressed)));
        } else {
            drive_right.move_voltage((rightY-leftX));
            drive_left.move_voltage(rightY+leftX);
        }
    } else {
        drive_right.move_voltage(0);
        drive_left.move_voltage(0);
    }
}