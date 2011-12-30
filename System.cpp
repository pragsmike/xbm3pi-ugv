#include "System.h"

System::System(TelemetryData &telemetryData, StatusDisplay &status) {
	td = &telemetryData;
	_status = &status;

	timeSinceStart.start();
    ticker.attach(this, &System::tick, 0.005);
}

void System::tick(void) {
	td->sys_status.drop_rate_comm 					= td->comm_status.packet_rx_drop_count;
	td->sys_status.errors_comm 						= td->comm_status.parse_error;

	td->local_position_ned.time_boot_ms = timeSinceStart.read_us();
	td->attitude.time_boot_ms = timeSinceStart.read_us();
	td->scaledImu.time_boot_ms = timeSinceStart.read_us();
	td->rawImu.time_usec = timeSinceStart.read_us();
}
void System::setMode(int target, int base_mode, int custom_mode) {
	_status->showMode(base_mode);
	td->mavlink_system.mode = base_mode;
	td->my_heartbeat.base_mode = base_mode;
	td->my_heartbeat.custom_mode = custom_mode;
}

void System::takeoff() {
	_status->showActive(true);
}

void System::land() {
	_status->showActive(false);
}

