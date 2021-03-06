#include "CommandParser.h"

CommandParser::CommandParser(MissionSyncer &mission, ParamSyncer &param, SystemState &systemState,System &thisSystem, Log &log, TelemetryData &td) {
	_mission = &mission;
	_param = &param;
	_systemState = &systemState;
	_system = &thisSystem;
	_log = &log;
	comm_status = &td.comm_status;
	gcs_heartbeat = &td.gcs_heartbeat;
}

bool CommandParser::acceptChar(uint8_t c) {
//	_log->putc('.');
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
			_log->printf("Inbound set_mode base %d custom %d\r\n",		base_mode, custom_mode);
			_system->setMode(target, base_mode, custom_mode);
		}
			break;
		case MAVLINK_MSG_ID_PARAM_REQUEST_LIST: {
				uint8_t sys = mavlink_msg_param_request_list_get_target_system(&msg);
				uint8_t comp = mavlink_msg_param_request_list_get_target_component(&msg);
				_log->printf("Inbound send param list sys %d comp %d\r\n",		sys, comp);
				_param->sendParamList();
		}
			break;
		case MAVLINK_MSG_ID_PARAM_SET: {
			uint8_t comp = mavlink_msg_param_set_get_target_component(&msg);
			char id[16];
			uint16_t param_id = mavlink_msg_param_set_get_param_id(&msg, id);
			float param_value = mavlink_msg_param_set_get_param_value(&msg);
			_log->printf("Inbound set param comp %d %d %d\r\n",		comp, param_id, param_value);
			_param->setParamValue(id, 16, param_value);
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
			_log->printf("Inbound command_long, command %d target comp %d\r\n",	command_long.command, command_long.target_component);
			_systemState->sendCommandAck(command_long.command, MAV_CMD_ACK_OK);
		}
		break;
		case MAVLINK_MSG_ID_MISSION_COUNT: {
			mavlink_msg_mission_count_decode(&msg, &mc);
			_log->printf("Inbound mission count, count %d target sys %d comp %d\r\n",	(int)mc.count, (int)mc.target_system, (int)mc.target_component);
			_mission->sendMissionRequest(12, MAV_COMP_ID_MISSIONPLANNER, 0);
		}
		break;
		default:
			_log->printf("Inbound msg type %d component %d\r\n", msg.msgid, msg.compid);
			break;
		}
		return true;
	}
	return false;
}
