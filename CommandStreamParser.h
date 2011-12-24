#ifndef CommandStreamParser_h
#define CommandStreamParser_h

#include "CommandDispatcher.h"

class CommandStreamParser {

public:
    CommandStreamParser(CommandDispatcher &dispatcher);

    void acceptChar(int c);
private:
    float x, y;
    float minus;
    int a;
    CommandDispatcher  *_dispatcher;
};
#endif
