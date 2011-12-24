#include "CommandStreamParser.h"
#include "CommandDispatcher.h"

CommandStreamParser::CommandStreamParser(CommandDispatcher &dispatcher) {
    minus = 1;
    _dispatcher = &dispatcher;
}

void CommandStreamParser::acceptChar(int b) {
    if (b < 1 || b == '\r')
        return;
    if (b == ' ') {
        x = minus * a/1000.;
        a = 0;
        minus = 1;
        return;
    }
    if (b == '\n') {
        y = minus * a/1000.;
        a = 0;
        minus = 1;
        _dispatcher->drive(x, y);
        return;
    }
    if (b == '-') {
        minus = -1;
        return;
    }
    int c = b - 0x30;
    if (c > 9)
        c = 9;
    a = a*10 + c;
}
