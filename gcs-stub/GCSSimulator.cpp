
#include "GCSSimulator.h"

GCSSimulator::GCSSimulator(CommandParser &p) {
	parser = &p;
}

GCSSimulator::~GCSSimulator() {
}

void GCSSimulator::requestDataStream(int streamId) {
	uint8_t 					buf[MAVLINK_MAX_PACKET_LEN];
	mavlink_request_data_stream_t req;

	mavlink_message_t msg;

	uint16_t len = mavlink_msg_to_send_buffer(buf, &msg);
	for (int i = 0; i < len; i++) {
		parser->acceptChar(0);
	}
}
