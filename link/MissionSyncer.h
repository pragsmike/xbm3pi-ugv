/*
 * MissionSyncer.h
 *
 *  Created on: Dec 31, 2011
 *      Author: mg
 */

#ifndef MISSIONSYNCER_H_
#define MISSIONSYNCER_H_

#include "mavlink.h"
#include "../TelemetryData.h"
#include "IMsgSource.h"

class MissionSyncer : public IMsgSource {
public:
	MissionSyncer(TelemetryData &data);
	virtual ~MissionSyncer();

	int available(void);
	mavlink_message_t *nextMessage();

    void sendMissionList();
    void sendMissionRequest(uint8_t system, uint8_t component, uint8_t index);

private:
    int 					pending;

    TelemetryData 			*telemetryData;
	mavlink_mission_count_t		param;
	mavlink_mission_request_t	mission_request;
	mavlink_message_t 			msg;

};

#endif /* MISSIONSYNCER_H_ */
