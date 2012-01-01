#include "TelemetryEncoderMavLink.h"

TelemetryEncoderMavLink::TelemetryEncoderMavLink(TelemetryData &td)  {
	comm_status			= &td.comm_status;
	my_heartbeat 		= &td.my_heartbeat;
	mavlink_system		= &td.mavlink_system;
	sys_status 			= &td.sys_status;
	local_position_ned 	= &td.local_position_ned;
	attitude 			= &td.attitude;
	rawImu 				= &td.rawImu;
	scaledImu			= &td.scaledImu;
}

void TelemetryEncoderMavLink::fillMsg(mavlink_message_t &msg, int msgType) {
	switch (msgType) {
		case MAVLINK_MSG_ID_HEARTBEAT:
			mavlink_msg_heartbeat_encode(mavlink_system->sysid, mavlink_system->compid, &msg, my_heartbeat);
			break;
		case MAVLINK_MSG_ID_SYS_STATUS:
			mavlink_msg_sys_status_encode(mavlink_system->sysid, mavlink_system->compid, &msg, sys_status);
			break;
		case MAVLINK_MSG_ID_LOCAL_POSITION_NED:
			mavlink_msg_local_position_ned_encode(mavlink_system->sysid, mavlink_system->compid, &msg, local_position_ned);
			break;
		case MAVLINK_MSG_ID_ATTITUDE:
			mavlink_msg_attitude_encode(mavlink_system->sysid, mavlink_system->compid, &msg, attitude);
			break;
		case MAVLINK_MSG_ID_RAW_IMU:
			mavlink_msg_raw_imu_encode(mavlink_system->sysid, mavlink_system->compid, &msg, rawImu);
			break;
		case MAVLINK_MSG_ID_SCALED_IMU:
			mavlink_msg_scaled_imu_encode(mavlink_system->sysid, mavlink_system->compid, &msg, scaledImu);
			break;
		default:
			break;
		}
}
