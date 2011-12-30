#include "CommandParser.h"

CommandParser::CommandParser(CommandDispatcher &dispatcher, TelemetryEncoderMavLink &telemetry, System &thisSystem, Log &log, TelemetryData &td) {
	_dispatcher = &dispatcher;
	_telemetry = &telemetry;
	_system = &thisSystem;
	_log = &log;
	comm_status = &td.comm_status;
	gcs_heartbeat = &td.gcs_heartbeat;
}

void CommandParser::acceptChar(uint8_t c) {
	//_log->putc('.');
	if (mavlink_parse_char(MAVLINK_COMM_0, c, &msg, comm_status)) {

		switch (msg.msgid) {
		case MAVLINK_MSG_ID_HEARTBEAT: {
			mavlink_msg_heartbeat_decode(&msg, gcs_heartbeat);
			_log->printf("Inbound heartbeat, status %d type %d\r\n", (int)gcs_heartbeat->system_status, (int)gcs_heartbeat->type);
			// go into comm lost mode if timer times out
		}
			break;
		case MAVLINK_MSG_ID_SET_MODE: {
			int target = mavlink_msg_set_mode_get_target_system(&msg);
			int base_mode = mavlink_msg_set_mode_get_base_mode(&msg);
			int custom_mode = mavlink_msg_set_mode_get_custom_mode(&msg);
			_log->printf("Inbound set_mode %d target %d\r\n",		base_mode, target);
			_system->setMode(target, base_mode, custom_mode);
		}
			break;
		case MAVLINK_MSG_ID_PARAM_REQUEST_LIST: {
				uint8_t sys = mavlink_msg_param_request_list_get_target_system(&msg);
				uint8_t comp = mavlink_msg_param_request_list_get_target_component(&msg);
				_log->printf("Inbound send param list sys %d comp %d\r\n",		sys, comp);
				_telemetry->sendParamList(sys, comp);
		}
			break;
		case MAVLINK_MSG_ID_COMMAND_LONG: {
			mavlink_msg_command_long_decode(&msg, &command_long);
			switch (command_long.command) {
			case MAV_CMD_NAV_TAKEOFF:		// Start
				_system->takeoff();
				break;
			case MAV_CMD_OVERRIDE_GOTO:		// Land
				_system->land();
				break;
			}
			_telemetry->sendCommandAck(command_long.command, MAV_RESULT_ACCEPTED);
			_log->printf("Inbound command_long, command %d target %d\r\n",		command_long.command, command_long.target_component);
		}
		break;
		case MAVLINK_MSG_ID_MISSION_COUNT: {
			mavlink_msg_mission_count_decode(&msg, &mc);
			_log->printf("Inbound mission count, count %d target sys %d comp %d\r\n",	(int)mc.count, (int)mc.target_system, (int)mc.target_component);
			_telemetry->sendMissionRequest(12, MAV_COMP_ID_MISSIONPLANNER, 0);
		}
		break;
		default:
			_log->printf("Inbound msg type %d\r\n", msg.msgid);
			break;
		}
	}
}
