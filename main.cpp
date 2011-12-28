#include "m3pi.h"
#include "XBeeApi.h"
#include "CommandParser.h"
#include "CommandDispatcher.h"
#include "TelemetryEncoderMavLink.h"

m3pi                		m3pi;

System						thisSystem;
CommandDispatcher   		dispatcher(m3pi);
CommandParser 				cmdr(dispatcher, thisSystem);
TelemetryEncoderMavLink    	telemetry(thisSystem);
XBeeApi          			xbee(p28, p27, p26);

uint8_t 					currentTelemetryFrame[MAVLINK_MAX_PACKET_LEN];


int main() {
	Serial pc(USBTX, USBRX);
	pc.printf("main starting\r\n");
	dispatcher.init();
    int count = 0;
    while (1) {
        wait_ms(1);

        while (xbee.readable()) {
            uint8_t c = xbee.getc();
            cmdr.acceptChar(c);
        }
        if ((count++ % 100) == 0) {
			int len = telemetry.fillFrame(currentTelemetryFrame);
			xbee.send(currentTelemetryFrame, len);
        }
    }
}
