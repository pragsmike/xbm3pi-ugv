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

	_sendParameters = false;
	_sendCommandAck = false;
	_sendMissionRequest = false;

	param.param_count = 1;
	param.param_index = 0;
	param.param_id[0] = 'A';
	param.param_id[1] = 'Y';
	param.param_id[3] = 0;
	param.param_type = MAVLINK_TYPE_FLOAT;
	param.param_value = 12.;
}
void TelemetryEncoderMavLink::sendParamList(uint8_t sys, uint8_t comp) {
	_sendParameters = true;
}
void TelemetryEncoderMavLink::sendCommandAck(uint16_t command, uint8_t result) {
	command_ack.command = command;
	command_ack.result = result;
	_sendCommandAck = true;
}
void TelemetryEncoderMavLink::sendMissionRequest(uint8_t system, uint8_t component, uint8_t index) {
	mission_request.target_system = system;
	mission_request.target_component = component;
	mission_request.seq = index;
	_sendMissionRequest = true;
}
int TelemetryEncoderMavLink::fillFrame( uint8_t *bp) {

	mavlink_message_t msg;
	int type = 0;

	if (_sendCommandAck) {
		mavlink_msg_command_ack_encode(mavlink_system->sysid, mavlink_system->compid, &msg, &command_ack);
		_sendCommandAck = false;
	} else if (_sendParameters) {
		mavlink_msg_param_value_encode(mavlink_system->sysid, mavlink_system->compid, &msg, &param);
		_sendParameters = false;
	} else if (_sendMissionRequest) {
		mavlink_msg_mission_request_encode(mavlink_system->sysid, mavlink_system->compid, &msg, &mission_request);
		_sendMissionRequest = false;

	} else switch (which++ & 0x7) {
	case 0:
		type = MAVLINK_MSG_ID_HEARTBEAT;
		break;
	case 1:
		type = MAVLINK_MSG_ID_SYS_STATUS;
		break;
	case 2:
		type = MAVLINK_MSG_ID_LOCAL_POSITION_NED;
		break;
	case 3:
		type = MAVLINK_MSG_ID_ATTITUDE;
		break;
	case 4:
		type = MAVLINK_MSG_ID_RAW_IMU;
		break;

	default:
		type = MAVLINK_MSG_ID_SCALED_IMU;
		break;
	}
	fillMsg(msg, type);

	uint16_t len = mavlink_msg_to_send_buffer(bp, &msg);
	return len;
}

void TelemetryEncoderMavLink::fillMsg(mavlink_message_t &msg, int msgType) {
	switch (msgType & 0x7) {
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
