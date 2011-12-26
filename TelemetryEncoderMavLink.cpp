#include "TelemetryEncoderMavLink.h"
#include "mbed.h"
#include "mavlink_types.h"

TelemetryEncoderMavLink::TelemetryEncoderMavLink(void)  {
	timeSinceStart.start();
}
int TelemetryEncoderMavLink::fillFrame( uint8_t *bp) {

	mavlink_raw_imu_t rawImu;
	mavlink_system_t mavlink_system;

	mavlink_system.sysid = 20;                   		///< ID 20 for this rover
	mavlink_system.compid = MAV_COMP_ID_IMU;     		///< The component sending the message is the IMU, it could be also a Linux process
	mavlink_system.type = UGV_GROUND_ROVER;   			///< This system is a rover

	uint8_t autopilot_type = MAV_AUTOPILOT_GENERIC;

	mavlink_message_t msg;

	if (false) {
		mavlink_msg_heartbeat_pack(mavlink_system.sysid, mavlink_system.compid, &msg, mavlink_system.type, autopilot_type);
	} else {
		rawImu.usec = timeSinceStart.read_us();
		rawImu.xacc = accelerometer.x;
		rawImu.yacc = accelerometer.y;
		rawImu.zacc = accelerometer.z;
		rawImu.xgyro = gyro.x;
		rawImu.ygyro = gyro.y;
		rawImu.zgyro = gyro.z;
		rawImu.xmag = 0;
		rawImu.ymag = 0;
		rawImu.zmag = 0;

		mavlink_msg_raw_imu_encode(mavlink_system.sysid, mavlink_system.compid, &msg, &rawImu);
	}

	uint16_t len = mavlink_msg_to_send_buffer(bp, &msg);
	return len;
}
