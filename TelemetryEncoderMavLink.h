#ifndef TelemetryEncoderMavLink_h
#define TelemetryEncoderMavLink_h

#include "mbed.h"
#include "mavlink.h"
#include "System.h"

class TelemetryEncoderMavLink {

public:
    TelemetryEncoderMavLink(TelemetryData &td);
    int fillFrame(uint8_t *bp);
    void sendParamList(uint8_t sys, uint8_t comp);
    void sendCommandAck(uint16_t command, uint8_t result);
    void sendMissionRequest(uint8_t system, uint8_t component, uint8_t index);

	mavlink_raw_imu_t 				*rawImu;
	mavlink_scaled_imu_t			*scaledImu;
private:
    mavlink_status_t				*comm_status;
	mavlink_system_t 				*mavlink_system;
	mavlink_sys_status_t 			*sys_status;
	mavlink_heartbeat_t				*my_heartbeat;
	mavlink_local_position_ned_t 	*local_position_ned;
	mavlink_attitude_t				*attitude;

	mavlink_param_value_t 		param;
	mavlink_command_ack_t		command_ack;
	mavlink_mission_request_t	mission_request;

	bool _sendParameters;
	bool _sendCommandAck;
	bool _sendMissionRequest;
    int which;
};
#endif
