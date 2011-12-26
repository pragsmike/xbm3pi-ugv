#include "mbed.h"
#include "m3pi.h"
#include "XBeeApi.h"
#include "CommandStreamParser.h"
#include "CommandDispatcher.h"
#include "TelemetryEncoderMavLink.h"

m3pi                m3pi;

CommandDispatcher   dispatcher(m3pi);
CommandStreamParser cmdr(dispatcher);
TelemetryEncoderMavLink    telemetry;
uint8_t currentTelemetryFrame[MAVLINK_MAX_PACKET_LEN];


XBeeApi          xbee(p28, p27, p26);

int main() {
    dispatcher.init();
    
    while (1) {
        wait_ms(20);

        int len = telemetry.fillFrame(currentTelemetryFrame);
        xbee.send(currentTelemetryFrame, len);
        while (xbee.readable()) {
            int c = xbee.getc();
            cmdr.acceptChar(c);
        }
    }
}
