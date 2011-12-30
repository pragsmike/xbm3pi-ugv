#include "m3pi.h"
#include "Log.h"
#include "Rover.h"
#include "IMU.h"
#include "IMUSensors.h"
#include "System.h"
#include "XBeeApi.h"
#include "USBSerial.h"
#include "CommandParser.h"
#include "CommandDispatcher.h"
#include "TelemetryEncoderMavLink.h"


//#define link xbee
#define link usb

m3pi                		m3pi;
Gyro            			gyro;
Accelerometer   			accelerometer;
XBeeApi          			xbee(p28, p27, p26);
Serial						pc(USBTX, USBRX);

Log							_log(pc);
StatusDisplay				_status;
USBSerial					usb(pc);

Rover   					rover(m3pi);

TelemetryData				telemetryData;

IMUSensors					imuSensors(telemetryData.rawImu, telemetryData.scaledImu, accelerometer, gyro, _log);
IMU							imu(telemetryData.attitude, telemetryData.scaledImu, .005f, .001);
System						thisSystem(telemetryData, _status);
TelemetryEncoderMavLink    	telemetry(telemetryData);
CommandDispatcher   		dispatcher;
CommandParser 				cmdr(dispatcher, telemetry, thisSystem, _log, telemetryData);

uint8_t 					currentTelemetryFrame[MAVLINK_MAX_PACKET_LEN];

int main() {
	_log.printf("main starting\r\n");
	rover.init();
    int count = 0;
    while (1) {
        wait_us(100);

        while (link.readable()) {
            uint8_t c = link.getc();
            cmdr.acceptChar(c);
        }
        if ((count++ % 10) == 0) {
			int len = telemetry.fillFrame(currentTelemetryFrame);
			link.send(currentTelemetryFrame, len);
        }
    }
}
