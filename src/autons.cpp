#include "main.h"
#include "drive.hpp"
#include "intake.hpp"
#include "pistons.hpp"

void goofy_auton() {
    spin_intake_auto(true, 600);
    return;
}