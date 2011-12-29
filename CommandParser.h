#ifndef CommandParser_h
#define CommandParser_h
#include "mavlink.h"
#include "CommandDispatcher.h"
#include "TelemetryEncoderMavLink.h"
#include "System.h"

class CommandParser {

public:
	CommandParser(CommandDispatcher &dispatcher, TelemetryEncoderMavLink &telemetry, System &system, Log &log, TelemetryData &td);

    void acceptChar(uint8_t c);
private:
    CommandDispatcher  	*_dispatcher;
    TelemetryEncoderMavLink *_telemetry;
    System				*_system;
    Log					*_log;

	mavlink_status_t 	*comm_status;
	mavlink_heartbeat_t *gcs_heartbeat;

	mavlink_message_t 		msg;
	mavlink_command_long_t 	command_long;
	mavlink_mission_count_t mc;

};
#endif
