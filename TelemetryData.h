#ifndef TelemetryData_h
#define TelemetryData_h

#include "mavlink.h"


class TelemetryData {

public:
	TelemetryData();

    mavlink_status_t				comm_status;
	mavlink_raw_imu_t 				rawImu;
	mavlink_scaled_imu_t			scaledImu;
	mavlink_system_t 				mavlink_system;
	mavlink_sys_status_t 			sys_status;
	mavlink_heartbeat_t				my_heartbeat;
	mavlink_heartbeat_t				gcs_heartbeat;
	mavlink_local_position_ned_t 	local_position_ned;
	mavlink_attitude_t				attitude;

private:
};
#endif
