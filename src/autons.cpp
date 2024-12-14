#include "main.h"
#include "intake.hpp"
#include "drive.hpp"
#include "pistons.hpp"

void goofy_auton() {
    chassis.setPose(-60, 12, 0);

    spin_intake_auto(true, 600);

    chassis.moveToPoint(-60, 0, 2000);
    return;
}