/*
	API INCLUDES
*/

#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep

/*
	USER-MADE INCLUDES
*/

// #include "catapult.hpp"
#include "autons.hpp"
#include "intake.hpp"
// #include "pistons.hpp"
// #include "pot_auton_selector.hpp"
#include "drive.hpp"
#include "pistons.hpp"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motor_group.hpp"

// RADIO PORT - 13

/*
	MOTOR PORT DEFINITIONS
*/

#define RING_LIFT_MOTOR_PORT 20
#define INTAKE_MOTOR_PORT 4

#define DRIVE_LB_PORT 17
#define DRIVE_LT_PORT 19
#define DRIVE_LF_PORT 18

#define DRIVE_RB_PORT 15
#define DRIVE_RT_PORT 11
#define DRIVE_RF_PORT 12

/*
	IMU PORT DEFINITIONS
*/

#define IMU_PORT 15

/*
	SMART SENSOR PORT DEFINTIONS
*/

#define CATA_DISTANCE_SENSOR_PORT 20

/*
	DIGITAL PORT DEFINITIONS
*/

#define CATA_LIMIT_SWITCH_PORT 'H'
#define AUTON_POT_PORT 'E'

// #define INTAKE_ACTUATOR_PORT 'G'
#define RIGHT_FRONT_WING_ACTUATOR_PORT 'A'
#define LEFT_FRONT_WING_ACTUATOR_PORT 'B'



/*
	CONTROLLER BUTTON DEFINITIONS
*/

// #define AUTON_SELECT_BUTTON pros::E_CONTROLLER_DIGITAL_UP

#define INTAKE_INTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_L1
#define INTAKE_OUTTAKE_BUTTON pros::E_CONTROLLER_DIGITAL_L2

#define ACTUATE_MOGO_BUTTON pros::E_CONTROLLER_DIGITAL_R2


// #define UP_MATCH_LOAD_SPEED_BUTTON pros::E_CONTROLLER_DIGITAL_LEFT
// #define DOWN_MATCH_LOAD_SPEED_BUTTON pros::E_CONTROLLER_DIGITAL_DOWN

#define LIMIT_DRIVE_SPEED_BUTTON pros::E_CONTROLLER_DIGITAL_LEFT

/*
	CONTROLLER ARCADE DRIVE AXES
*/

#define ARCADE_DRIVE_FORWARD_BACKWARD_CHANNEL 

/*
	CONTROLLER DEFINITION
*/


/*
	MOTOR INITIALIZATIONS
*/

pros::Motor Intake(-INTAKE_MOTOR_PORT, pros::v5::MotorGears::blue);
pros::Motor RingLift(-RING_LIFT_MOTOR_PORT, pros::v5::MotorGears::blue);

/*
	SENSOR INITIALIZATIONS
*/

pros::Distance CataDistance(CATA_DISTANCE_SENSOR_PORT);

/*
	PISTON INITIALIZATIONS
*/

pros::adi::Pneumatics BackMogoActuator('a', false);

/*
	LEMLIB DRIVE MOTOR INITIALIZATIONS
*/

pros::Motor drive_lb(DRIVE_LB_PORT);
pros::Motor drive_lt(DRIVE_LT_PORT);
pros::Motor drive_lf(DRIVE_LF_PORT);

pros::Motor drive_rb(DRIVE_RB_PORT);
pros::Motor drive_rt(DRIVE_RT_PORT);
pros::Motor drive_rf(DRIVE_RF_PORT);

/*
	LEMLIB DRIVE MOTOR GROUP INITIALIZATIONS
*/

pros::MotorGroup drive_left({-DRIVE_LB_PORT, DRIVE_LT_PORT, -DRIVE_LF_PORT});
pros::MotorGroup drive_right({DRIVE_RB_PORT, -DRIVE_RT_PORT, DRIVE_RF_PORT});


/*
	LEMLIB DRIVE IMU INITIALIZATION
*/

pros::Imu inertial_sensor(IMU_PORT);

/*
	LEMLIB DRIVE Drivetrain INITIALIZATION
*/

lemlib::Drivetrain drivetrain {
    &drive_left, // left drivetrain motors
    &drive_right, // right drivetrain motors
    10.25, // track width
    3.25, // wheel diameter // 3.175
    450, // wheel rpm
	10 // chase power
};

/*
	LEMLIB DRIVE OdomSensors INITIALIZATION
*/

lemlib::OdomSensors sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor // inertial sensor
};

/*
	LEMLIB DRIVE LATERAL_PID (forward/backward) INITIALIZATION
*/

lemlib::ControllerSettings lateralPIDController {
    15.4, // kP // last : 160
    0, // kI
	63.5, // kD // last : 1700
	0, // antiWindUp ???
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};

/*
	LEMLIB DRIVE ANGULAR_PID (left/right) INITIALIZATION
*/
 
lemlib::ControllerSettings angularPIDController {
    2.9, // kP // 2.2 // 2.67
	0, // kI
    24.68, // kD // 20
	0, // antiWindUp ???
    3, // smallErrorRange
    100, // smallErrorTimeout
    10, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};

/*
	LEMLIB DRIVE CHASSIS CONSTRUCTOR INITIALIZATION
*/

/*
	CATAPULT CONFIG
*/

int cata_distance_away_to_shoot = 30;


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();

	chassis.calibrate();


	// pros::Task CataTask(cata_task_function);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */

void autonomous() {
	goofy_auton();
//   switch (get_selected_auton(AutonPot.get_value())) {
//     case 1:
//     	return;

//     case 2:
//     	return;

//     case 3:
//     	return;
    
//     case 4:
// 		return;

//     case 5:
// 		return;

//     case 6: 
//     	return;

//     case 7:
//     	return;

//     case 8:
//     	return;
    
//     case 9:
// 		return;

//     case 10:
//       chassis.setPose(-50, -56, 240);
// 	  skills();
//   }
return;
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

int match_load_speed = 200;

bool actuate_mogo_btn_pressed = false;
bool actuate_mogo_btn_pressed_last = false;

void opcontrol() {
	while (true) {

		// chassis.arcade(127, 127, 0.0);

		split_arcade(controller.get_analog(pros::controller_analog_e_t::E_CONTROLLER_ANALOG_LEFT_X),
                     controller.get_analog(pros::controller_analog_e_t::E_CONTROLLER_ANALOG_LEFT_Y), 
                     controller.get_analog(pros::controller_analog_e_t::E_CONTROLLER_ANALOG_RIGHT_X), 
                     controller.get_analog(pros::controller_analog_e_t::E_CONTROLLER_ANALOG_RIGHT_Y), 
                     15, 
                     15, 
                     80, 
                     controller.get_digital(LIMIT_DRIVE_SPEED_BUTTON));

		// spin_cata_driver(controller.get_digital(CATA_SHOOT_CONTINUALLY_BUTTON), match_load_speed);

		spin_intake_driver(controller.get_digital(INTAKE_INTAKE_BUTTON), controller.get_digital(INTAKE_OUTTAKE_BUTTON));

		if (controller.get_digital(ACTUATE_MOGO_BUTTON)) {
				actuate_mogo_btn_pressed = true;
			} else {
				actuate_mogo_btn_pressed = false;
		}

		if (actuate_mogo_btn_pressed && ! actuate_mogo_btn_pressed_last) {
			if (!back_mogo_actuated_value) actuate_back_mogo(true);
			else actuate_back_mogo(false);
		}

    	actuate_mogo_btn_pressed_last = actuate_mogo_btn_pressed;
		/////////////////
		// TODO - MAKE INTO A SMALLER FUNCTION
		////////////////////////////////////////
		pros::delay(5);

	}
}