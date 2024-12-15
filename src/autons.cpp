#include "liblvgl/misc/lv_txt.h"
#include "main.h"
#include "drive.hpp"
#include "intake.hpp"
#include "pistons.hpp"

void goofy_auton() {
    // drive_left.move_relative(-600, 200);
    // drive_right.move_relative(600, 200);


    chassis.setPose(-59, 16, 0);

    chassis.moveToPoint(-59, 0, 2000, {false});
    chassis.turnToHeading(90, 2000, {.maxSpeed=80});
        
    chassis.moveToPoint( -59.05,  0, 2000, {false});
    
    pros::delay(1000);
    chassis.cancelAllMotions();
    
    spin_intake_auto(true, 600);
    pros::delay(1000);

    stop_intake_auto();
    return;
}

void skillz() {
    chassis.setPose(-61, 0, 90);
    spin_intake_auto(true, 600);
    pros::delay(500);
    
    stop_intake_auto();
    chassis.moveToPoint(-48, 0, 2000);

    chassis.turnToHeading(10, 2000);

    chassis.moveToPoint(-48, -26, 2000, {.forwards = false});

    chassis.waitUntilDone();

    actuate_back_mogo(true);

    pros::delay(200);

    // chassis.turnToHeading(45, 2000);

    chassis.moveToPoint(-52, -34, 2000, {.forwards=false});

    // chassis.moveToPoint(float x, float y, int timeout)

    chassis.moveToPoint(-64, -60, 2000, {.forwards=false});

    chassis.waitUntilDone();

    actuate_back_mogo(true);

    chassis.moveToPoint(-64, -40, 2000, {.forwards=false});



}

void red_negative() {
    chassis.setPose(-54, 24, 270);

    // chassis.moveToPoint(-48, 24, );
    
    chassis.moveToPoint(-26, 30, 2500, {.forwards=false, .maxSpeed=65});
    chassis.waitUntilDone();

    actuate_back_mogo(true);

    pros::delay(400);

    spin_intake_auto(true, 600);
    
    chassis.moveToPoint(-27, 50, 2000, {.maxSpeed=60});

    pros::delay(4000);

    stop_intake_auto();
}