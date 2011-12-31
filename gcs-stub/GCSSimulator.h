#ifndef GCSSIMULATOR_H_
#define GCSSIMULATOR_H_

#include "mavlink.h"
#include "../CommandParser.h"

class GCSSimulator {
public:
	GCSSimulator(CommandParser &parser);
	virtual ~GCSSimulator();

	void requestDataStream(int streamId);
private:
	CommandParser	*parser;
};

#endif /* GCSSIMULATOR_H_ */
