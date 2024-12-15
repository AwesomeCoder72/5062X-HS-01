#pragma once
#include "pros/motor_group.hpp"
#include "lemlib/chassis/chassis.hpp"

extern pros::MotorGroup drive_left;
extern pros::MotorGroup drive_right;

extern lemlib::Chassis chassis;

extern pros::MotorGroup drive_left;
extern pros::MotorGroup drive_right;

float curve_drive_values(int input_value, float scalar);

float scale_drive_values(float inputValue);

int ceiling_drive_values(int inputValue, int ceilingValue, int ceiling_pressed);

void split_arcade(int leftX, int leftY, int rightX, int rightY, int leftDeadzone, int rightDeadzone, float ceiling_value, int ceiling_pressed);