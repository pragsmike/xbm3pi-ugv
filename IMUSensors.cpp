/**
 * @section LICENSE
 *
 * Copyright (c) 2010 ARM Limited
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * IMU consisting of ADXL345 accelerometer and ITG-3200 gyroscope using
 * orientation filter developed by Sebastian Madgwick.
 *
 * Find more details about his paper here:
 *
 * http://code.google.com/p/imumargalgorithm30042010sohm/ 
 */

/**
 * Includes
 */
#include "IMUSensors.h"

IMUSensors::IMUSensors(mavlink_raw_imu_t &raw_imu, mavlink_scaled_imu_t &scaled_imu, Accelerometer &accelerometer, Gyro &gyro, Log &log) {

	_raw_imu 		= &raw_imu;
	_scaled_imu 	= &scaled_imu;
	_accelerometer 	= &accelerometer;
	_gyro 			= &gyro;
	_log			= &log;

    a_xAccumulator = 0;
    a_yAccumulator = 0;
    a_zAccumulator = 0;
    w_xAccumulator = 0;
    w_yAccumulator = 0;
    w_zAccumulator = 0;

    accelerometerSamples = 0;
    gyroscopeSamples = 0;
    raw_imu.xmag = 0;
    raw_imu.ymag = 0;
    raw_imu.zmag = 0;

    calibrateAccelerometer();
    initializeGyroscope();
    calibrateGyroscope();

    float accelerometerRate_ = 0.005;
    float gyroscopeRate_ = 0.005;
    float imuSensorsRate_ = 0.005;

    accelerometerTicker.attach(_accelerometer, &Accelerometer::tick, accelerometerRate_);
    gyroTicker.attach(_gyro, &Gyro::tick, gyroscopeRate_);
    imuSensorsTicker.attach(this, &IMUSensors::tick, imuSensorsRate_);

    log.printf("Started sensor tickers\r\n");

}

void IMUSensors::tick(void) {
	sampleAccelerometer();
	sampleGyroscope();
}

void IMUSensors::sampleAccelerometer(void) {

    if (accelerometerSamples == SAMPLES) {

        _scaled_imu->xacc = ((a_xAccumulator / SAMPLES) - a_xBias) * ACCELEROMETER_GAIN;
        _scaled_imu->yacc = ((a_yAccumulator / SAMPLES) - a_yBias) * ACCELEROMETER_GAIN;
        _scaled_imu->zacc = ((a_zAccumulator / SAMPLES) - a_zBias) * ACCELEROMETER_GAIN;

        a_xAccumulator = 0;
        a_yAccumulator = 0;
        a_zAccumulator = 0;
        accelerometerSamples = 0;

    } else {
    	_raw_imu->xacc = _accelerometer->x;
    	_raw_imu->yacc = _accelerometer->y;
    	_raw_imu->zacc = _accelerometer->z;

        a_xAccumulator += (int16_t) _raw_imu->xacc;
        a_yAccumulator += (int16_t) _raw_imu->yacc;
        a_zAccumulator += (int16_t) _raw_imu->zacc;

        accelerometerSamples++;
    }
}

void IMUSensors::calibrateAccelerometer(void) {

    a_xAccumulator = 0;
    a_yAccumulator = 0;
    a_zAccumulator = 0;

    for (int i = 0; i < CALIBRATION_SAMPLES; i++) {

        a_xAccumulator += (int16_t) _raw_imu->xacc;
        a_yAccumulator += (int16_t) _raw_imu->yacc;
        a_zAccumulator += (int16_t) _raw_imu->zacc;

        wait(accelerometerRate_);
    }

    a_xAccumulator /= CALIBRATION_SAMPLES;
    a_yAccumulator /= CALIBRATION_SAMPLES;
    a_zAccumulator /= CALIBRATION_SAMPLES;

    a_xBias = a_xAccumulator;
    a_yBias = a_yAccumulator;
    a_zBias = (a_zAccumulator - 250);

    a_xAccumulator = 0;
    a_yAccumulator = 0;
    a_zAccumulator = 0;
}

void IMUSensors::initializeGyroscope(void) {

    //Low pass filter bandwidth of 42Hz.
//    gyroscope.setLpBandwidth(LPFBW_42HZ);
    //Internal sample rate of 200Hz.
//    gyroscope.setSampleRateDivider(4);

}

void IMUSensors::calibrateGyroscope(void) {

    w_xAccumulator = 0;
    w_yAccumulator = 0;
    w_zAccumulator = 0;

    for (int i = 0; i < CALIBRATION_SAMPLES; i++) {

        w_xAccumulator += _raw_imu->xgyro;
        w_yAccumulator += _raw_imu->ygyro;
        w_zAccumulator += _raw_imu->zgyro;
        wait(gyroscopeRate_);
    }

    //Average the samples.
    w_xAccumulator /= CALIBRATION_SAMPLES;
    w_yAccumulator /= CALIBRATION_SAMPLES;
    w_zAccumulator /= CALIBRATION_SAMPLES;

    w_xBias = w_xAccumulator;
    w_yBias = w_yAccumulator;
    w_zBias = w_zAccumulator;

    w_xAccumulator = 0;
    w_yAccumulator = 0;
    w_zAccumulator = 0;
}

void IMUSensors::sampleGyroscope(void) {

    if (gyroscopeSamples == SAMPLES) {

    	_scaled_imu->xgyro = toRadians(((w_xAccumulator / SAMPLES) - w_xBias) * GYROSCOPE_GAIN);
    	_scaled_imu->ygyro = toRadians(((w_yAccumulator / SAMPLES) - w_yBias) * GYROSCOPE_GAIN);
    	_scaled_imu->zgyro = toRadians(((w_zAccumulator / SAMPLES) - w_zBias) * GYROSCOPE_GAIN);

        w_xAccumulator = 0;
        w_yAccumulator = 0;
        w_zAccumulator = 0;
        gyroscopeSamples = 0;

    } else {
    	_raw_imu->xgyro = _gyro->x;
    	_raw_imu->ygyro = _gyro->y;
    	_raw_imu->zgyro = _gyro->z;

        w_xAccumulator += _raw_imu->xgyro;
        w_yAccumulator += _raw_imu->ygyro;
        w_zAccumulator += _raw_imu->zgyro;

        gyroscopeSamples++;
    }
}

