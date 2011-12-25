#include "TelemetryEncoderMavLink.h"
#include "mbed.h"
#include "mavlink_types.h"

TelemetryEncoderMavLink::TelemetryEncoderMavLink(void) {
}
int TelemetryEncoderMavLink::fillFrame( uint8_t *bp) {

	mavlink_system_t mavlink_system;

	mavlink_system.sysid = 20;                   		///< ID 20 for this airplane
	mavlink_system.compid = MAV_COMP_ID_IMU;     		///< The component sending the message is the IMU, it could be also a Linux process
	mavlink_system.type = UGV_GROUND_ROVER;   			///< This system is a rover

	uint8_t autopilot_type = MAV_AUTOPILOT_GENERIC;

	mavlink_message_t msg;

	mavlink_msg_heartbeat_pack(mavlink_system.sysid, mavlink_system.compid, &msg, mavlink_system.type, autopilot_type);

	uint16_t len = mavlink_msg_to_send_buffer(bp, &msg);
	return len;
}
