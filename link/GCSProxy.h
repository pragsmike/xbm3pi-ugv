#ifndef GCSPROXY_H_
#define GCSPROXY_H_

#include "mbed.h"	// uint8_t
#include "mavlink.h"

class GCSProxy {
public:
	GCSProxy();
	virtual ~GCSProxy();

	void sendMissionRequest(uint8_t system, uint8_t component, uint8_t index);
};

#endif /* GCSPROXY_H_ */
