#pragma once
#include "intake.hpp"
#include "main.h"
#include "pros/adi.hpp"

extern pros::adi::Pneumatics BackMogoActuator;

extern bool back_mogo_actuated_value;

void actuate_back_mogo(bool out_value);