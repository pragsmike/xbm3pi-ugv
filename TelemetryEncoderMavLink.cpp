#include "TelemetryEncoderMavLink.h"

TelemetryEncoderMavLink::TelemetryEncoderMavLink(System &system)  {
	comm_status			= &system.comm_status;
	my_heartbeat 		= &system.my_heartbeat;
	mavlink_system		= &system.mavlink_system;
	sys_status 			= &system.sys_status;
	local_position_ned 	= &system.local_position_ned;
	attitude 			= &system.attitude;
	rawImu 				= &system.rawImu;
	scaledImu			= &system.scaledImu;

	param.param_count = 1;
	param.param_index = 0;
	param.param_id[0] = 'A';
	param.param_id[1] = 'Y';
	param.param_id[3] = 0;
	param.param_type = MAVLINK_TYPE_FLOAT;
	param.param_value = 12.;
}
int TelemetryEncoderMavLink::fillFrame( uint8_t *bp) {

	mavlink_message_t msg;

	switch (which++ & 0x7) {
	case 0:
		mavlink_msg_heartbeat_encode(mavlink_system->sysid, mavlink_system->compid, &msg, my_heartbeat);
		break;
	case 1:
		mavlink_msg_sys_status_encode(mavlink_system->sysid, mavlink_system->compid, &msg, sys_status);
		break;
	case 2:
		mavlink_msg_local_position_ned_encode(mavlink_system->sysid, mavlink_system->compid, &msg, local_position_ned);
		break;
	case 3:
		mavlink_msg_attitude_encode(mavlink_system->sysid, mavlink_system->compid, &msg, attitude);
		break;
	case 4:
		mavlink_msg_raw_imu_encode(mavlink_system->sysid, mavlink_system->compid, &msg, rawImu);
		break;
	case 5:
		mavlink_msg_param_value_encode(mavlink_system->sysid, mavlink_system->compid, &msg, &param);
		break;

	default:
		mavlink_msg_scaled_imu_encode(mavlink_system->sysid, mavlink_system->compid, &msg, scaledImu);
		break;
	}

	uint16_t len = mavlink_msg_to_send_buffer(bp, &msg);
	return len;
}
