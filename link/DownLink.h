/*
 * DownLink.h
 *
 *  Created on: Dec 31, 2011
 *      Author: mg
 */

#ifndef DOWNLINK_H_
#define DOWNLINK_H_

#include "mavlink.h"
#include "IMsgSource.h"

class DownLink : public IMsgSource {
public:
	DownLink();
	virtual ~DownLink();

	int available(void);
	mavlink_message_t *nextMessage();

	void addSource(IMsgSource &src);
	void clearSources();
    int nextMessageBytes(uint8_t *bp);
private:
	IMsgSource	*sources[10];
	unsigned int sourceCount;
};

#endif /* DOWNLINK_H_ */
