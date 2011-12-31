
#ifndef IMsgSource_H_
#define IMsgSource_H_

#include "mavlink.h"

class IMsgSource {
public:
	virtual ~IMsgSource() {};

	virtual int available(void) = 0;
	virtual mavlink_message_t *nextMessage() = 0;
private:

};

#endif /* IMsgSource_H_ */
