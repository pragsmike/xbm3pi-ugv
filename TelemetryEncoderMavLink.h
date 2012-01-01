#ifndef TelemetryEncoderMavLink_h
#define TelemetryEncoderMavLink_h

#include "TelemetryData.h"

class TelemetryEncoderMavLink {

public:
    TelemetryEncoderMavLink(TelemetryData &td);
    void fillMsg(mavlink_message_t &msg, int msgType);

	mavlink_raw_imu_t 				*rawImu;
	mavlink_scaled_imu_t			*scaledImu;
private:
    mavlink_status_t				*comm_status;
	mavlink_system_t 				*mavlink_system;
	mavlink_sys_status_t 			*sys_status;
	mavlink_heartbeat_t				*my_heartbeat;
	mavlink_local_position_ned_t 	*local_position_ned;
	mavlink_attitude_t				*attitude;

    int which;
};
#endif
