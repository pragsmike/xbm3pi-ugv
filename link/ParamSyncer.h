/*
 * ParamSyncer.h
 *
 *  Created on: Dec 31, 2011
 *      Author: mg
 */

#ifndef PARAMSYNCER_H_
#define PARAMSYNCER_H_

#include "mavlink.h"
#include "../TelemetryData.h"
#include "IMsgSource.h"

class ParamSyncer : public IMsgSource {
public:
	ParamSyncer(TelemetryData &data);
	virtual ~ParamSyncer();

	int available(void);
	mavlink_message_t *nextMessage();

    void sendParamList();
private:
    int 					pending;
    TelemetryData 			*telemetryData;
	mavlink_param_value_t 	param;
	mavlink_message_t 		msg;

};

#endif /* PARAMSYNCER_H_ */
