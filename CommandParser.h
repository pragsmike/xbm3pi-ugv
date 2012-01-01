#ifndef CommandParser_h
#define CommandParser_h
#include <stdint.h>
#include "mavlink.h"
#include "link/MissionSyncer.h"
#include "link/ParamSyncer.h"
#include "link/SystemState.h"
#include "System.h"

class CommandParser {

public:
	CommandParser(MissionSyncer &mission, ParamSyncer &param, SystemState &systemState, System &system, Log &log, TelemetryData &td);

    bool acceptChar(uint8_t c);
private:
    MissionSyncer 			*_mission;
    ParamSyncer 			*_param;
    SystemState				*_systemState;
    System					*_system;
    Log						*_log;

	mavlink_status_t 		*comm_status;
	mavlink_heartbeat_t 	*gcs_heartbeat;

	mavlink_message_t 		msg;
	mavlink_command_long_t 	command_long;
	mavlink_mission_count_t mc;

};
#endif
