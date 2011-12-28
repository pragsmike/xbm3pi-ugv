#ifndef CommandParser_h
#define CommandParser_h
#include "mavlink.h"
#include "CommandDispatcher.h"
#include "mbed.h"
#include "System.h"

class CommandParser {

public:
	CommandParser(CommandDispatcher &dispatcher, System &system);

    void acceptChar(uint8_t c);
private:
    CommandDispatcher  	*_dispatcher;
    System				*_system;
    Serial				pc;

	mavlink_status_t 	*comm_status;
	mavlink_heartbeat_t *gcs_heartbeat;

	mavlink_message_t 	msg;
	mavlink_command_long_t command_long;
};
#endif
