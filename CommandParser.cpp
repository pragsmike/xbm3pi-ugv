#include "CommandParser.h"

CommandParser::CommandParser(CommandDispatcher &dispatcher, System &thisSystem) : pc(USBTX, USBRX) {
	_dispatcher = &dispatcher;
	_system = &thisSystem;
	comm_status = &thisSystem.comm_status;
	gcs_heartbeat = &thisSystem.gcs_heartbeat;
}

void CommandParser::acceptChar(uint8_t c) {
	pc.putc('.');
	if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, comm_status)) {

		switch (msg.msgid) {
		case MAVLINK_MSG_ID_HEARTBEAT: {
			mavlink_msg_heartbeat_decode(&msg, gcs_heartbeat);
			pc.printf("Inbound heartbeat, status %d\r\n", gcs_heartbeat->system_status);
			// go into comm lost mode if timer times out
		}
			break;
		case MAVLINK_MSG_ID_SET_MODE: {
			int target = mavlink_msg_set_mode_get_target_system(&msg);
			int base_mode = mavlink_msg_set_mode_get_base_mode(&msg);
			int custom_mode = mavlink_msg_set_mode_get_custom_mode(&msg);
			pc.printf("Inbound set_mode %d target %d\r\n",		base_mode, target);
			_system->setMode(target, base_mode, custom_mode);
		}
			break;
		case MAVLINK_MSG_ID_PARAM_REQUEST_LIST: {
				uint8_t sys = mavlink_msg_param_request_list_get_target_system(&msg);
				uint8_t comp = mavlink_msg_param_request_list_get_target_component(&msg);
				pc.printf("Inbound send param list sys %d comp %d\r\n",		sys, comp);
				_system->sendParamList(sys, comp);
		}
			break;
		case MAVLINK_MSG_ID_COMMAND_LONG:
			mavlink_msg_command_long_decode(&msg, &command_long);
			switch (command_long.command) {
			case MAV_CMD_NAV_TAKEOFF:		// Start
				_system->takeoff();
				break;
			case MAV_CMD_OVERRIDE_GOTO:		// Land
				_system->land();
				break;
			}
			pc.printf("Inbound command_long, command %d target %d\r\n",		command_long.command, command_long.target_component);
			break;
		default:
			pc.printf("Inbound msg type %d\r\n", msg.msgid);
			break;
		}
	}
}
