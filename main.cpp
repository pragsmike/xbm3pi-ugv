#include "m3pi.h"
#include "Log.h"
#include "Rover.h"
#include "IMU.h"
#include "IMUSensors.h"
#include "System.h"
#include "XBeeApi.h"
#include "USBSerial.h"
#include "CommandParser.h"
#include "link/MissionSyncer.h"
#include "link/ParamSyncer.h"
#include "link/SystemState.h"
#include "link/DownLink.h"
#include "link/TelemetrySource.h"
#include "TelemetryEncoderMavLink.h"


#define link xbee
//#define link usb

m3pi                		m3pi;
Gyro            			gyro;
Accelerometer   			accelerometer;
XBeeApi          			xbee(p28, p27, p26);
Serial						pc(USBTX, USBRX);

Log							_log(pc);
StatusDisplay				_status;
//USBSerial					usb(pc);

Rover   					rover(m3pi);

TelemetryData				telemetryData;

IMUSensors					imuSensors(telemetryData.rawImu, telemetryData.scaledImu, accelerometer, gyro, _log);
IMU							imu(telemetryData.attitude, telemetryData.scaledImu, .005f, .001);

System						thisSystem(telemetryData, _status);
TelemetryEncoderMavLink    	telemetry(telemetryData);
DownLink					downLink;
TelemetrySource				telemetrySource(telemetry);
ParamSyncer					param(telemetryData);
SystemState					systemState(telemetryData);
MissionSyncer		   		mission(telemetryData);
CommandParser 				cmdr(mission, param, systemState, thisSystem, _log, telemetryData);

uint8_t 					currentTelemetryFrame[MAVLINK_MAX_PACKET_LEN];

int main() {
	_log.printf("main starting\r\n");
	rover.init();
    int count = 0;
    downLink.addSource(systemState);
    downLink.addSource(mission);
    downLink.addSource(param);
    downLink.addSource(telemetrySource);

    while (1) {
        wait_us(1000);
        while (link.readable()) {
        	uint8_t c = link.getc();
            cmdr.acceptChar(c);
        }
        telemetrySource.setTick(count++);
        if (downLink.available()) {
			int len = downLink.nextMessageBytes(currentTelemetryFrame);
			link.send(currentTelemetryFrame, len);
        }
    }
}
