#include "System.h"

System::System(void) : imuSensors(&rawImu, &scaledImu, &accelerometer, &gyro) {
    ticker.attach(this, &System::tick, 0.005);

	mavlink_system.sysid 	= 20;                   		/// ID 20 for this rover
	mavlink_system.compid 	= MAV_COMP_ID_IMU;     			/// The component sending the message is the IMU, it could be also a Linux process
	mavlink_system.type 	= MAV_TYPE_GROUND_ROVER;    	// MAV_TYPE_HELICOPTER
	mavlink_system.state	= MAV_STATE_ACTIVE;
	mavlink_system.mode		= MAV_MODE_PREFLIGHT;			// MAV_MODE_GUIDED_ARMED
	mavlink_system.nav_mode = 0;

	my_heartbeat.autopilot 		= MAV_AUTOPILOT_GENERIC;
	my_heartbeat.type 			= mavlink_system.type;
	my_heartbeat.base_mode 		= mavlink_system.mode;
	my_heartbeat.custom_mode 	= mavlink_system.nav_mode;
	my_heartbeat.system_status 	= mavlink_system.state;

	sys_status.voltage_battery 					= 11000;
	sys_status.current_battery 					= -1;
	sys_status.battery_remaining 				= -1;

	sys_status.load 							= 500;
	sys_status.onboard_control_sensors_present 	= 0x8003;
	sys_status.onboard_control_sensors_enabled 	= 0x8003;
	sys_status.onboard_control_sensors_health  	= 0x8003;

	local_position_ned.x = 0.;
	local_position_ned.y = 0.;
	local_position_ned.z = 0.;
	local_position_ned.vx = 0.;
	local_position_ned.vy = 0.;
	local_position_ned.vz = 0.;

	attitude.roll 		= 1.2;
	attitude.pitch 		= 1.7;
	attitude.yaw 		= 3.14;
	attitude.rollspeed 	= 0.01;
	attitude.pitchspeed = 0.02;
	attitude.yawspeed 	= 0.03;

	timeSinceStart.start();
}

void System::tick(void) {
	sys_status.drop_rate_comm 					= comm_status.packet_rx_drop_count;
	sys_status.errors_comm 						= comm_status.parse_error;

	local_position_ned.time_boot_ms = timeSinceStart.read_us();
	attitude.time_boot_ms = timeSinceStart.read_us();
	rawImu.time_usec = timeSinceStart.read_us();
}
void System::setMode(int target, int base_mode, int custom_mode) {
	DigitalOut led(LED1);
	led = (base_mode != 0);
	mavlink_system.mode = base_mode;
	my_heartbeat.base_mode = base_mode;
	my_heartbeat.custom_mode = custom_mode;
}
void System::sendParamList(uint8_t sys, uint8_t comp) {

}

void System::takeoff() {
	DigitalOut led(LED2);
	led = 1;
}

void System::land() {
	DigitalOut led(LED2);
	led = 0;
}
