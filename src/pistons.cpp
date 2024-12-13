#include  "pistons.hpp"
#include "main.h"

bool back_mogo_actuated_value = false;

void actuate_back_mogo(bool out_value) {
  BackMogoActuator.set_value(out_value);
  back_mogo_actuated_value = out_value;
}