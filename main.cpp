#include "mbed.h"
#include "m3pi.h"
#include "XBeeApi.h"
#include "CommandStreamParser.h"
#include "CommandDispatcher.h"
#include "TelemetryEncoder.h"

m3pi                m3pi;

CommandDispatcher   dispatcher(m3pi);
CommandStreamParser cmdr(dispatcher);
TelemetryEncoder    telemetry;
uint8_t currentTelemetryFrame[20];


XBeeApi          xbee(p28, p27, p26);

int main() {
    dispatcher.init();
    
    while (1) {
        wait_ms(1);

        while (xbee.readable()) {
            int c = xbee.getc();
            cmdr.acceptChar(c);
        }
        int len = telemetry.fillFrame(currentTelemetryFrame);
        xbee.send(currentTelemetryFrame, len);
    }
}
