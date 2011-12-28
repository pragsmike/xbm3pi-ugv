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

#ifndef IMUSensors_H
#define IMUSensors_H

#include "Accelerometer.h"
#include "Gyro.h"
#include "Timer.h"
#include "mavlink.h"	// for sensor and IMU data structures


/**
 * Defines
 */
#define IMU_RATE           0.025
#define ACCELEROMETER_RATE 0.005
#define GYROSCOPE_RATE     0.005
#define GYRO_MEAS_ERROR    0.3 //IMUfilter tuning parameter.

//Gravity at Earth's surface in m/s/s
#define g0 9.812865328
//Number of samples to average
#define SAMPLES 4
#define CALIBRATION_SAMPLES 128
//Multiply radians to get degrees.
#define toDegrees(x) (x * 57.2957795)
//Multiply degrees to get radians.
#define toRadians(x) (x * 0.01745329252)
//Full scale resolution on the ADXL345 is 4mg/LSB.
//Multiply ADC count readings from ADXL345 to get acceleration in m/s/s.
#define toAcceleration(x) (x * (4 * g0 * 0.001))
//14.375 LSB/(degrees/sec)
#define GYROSCOPE_GAIN (1 / 14.375)
#define ACCELEROMETER_GAIN (0.004 * g0)

class IMUSensors {

public:

	IMUSensors(mavlink_raw_imu_t *raw_imu,  mavlink_scaled_imu_t *scaled_imu, Accelerometer *accelerometer, Gyro *gyro);
	void tick(void);

private:
	void calibrateAccelerometer(void);
	void sampleAccelerometer(void);
	void initializeGyroscope(void);
	void calibrateGyroscope(void);
	void sampleGyroscope(void);

    //Offsets for the gyroscope.
    //The readings we take when the gyroscope is stationary won't be 0, so we'll
    //average a set of readings we do get when the gyroscope is stationary and
    //take those away from subsequent readings to ensure the gyroscope is offset
    //or biased to 0.
    double w_xBias;
    double w_yBias;
    double w_zBias;

    double a_xBias;
    double a_yBias;
    double a_zBias;

    volatile double a_xAccumulator;
    volatile double a_yAccumulator;
    volatile double a_zAccumulator;
    volatile double w_xAccumulator;
    volatile double w_yAccumulator;
    volatile double w_zAccumulator;

    int accelerometerSamples;
    int gyroscopeSamples;

    mavlink_raw_imu_t 		*_raw_imu;
    mavlink_scaled_imu_t 	*_scaled_imu;
    Accelerometer			*_accelerometer;
    Gyro					*_gyro;

    Ticker					gyroTicker;
    Ticker					accelerometerTicker;
    Ticker					imuSensorsTicker;

    float accelerometerRate_;
    float gyroscopeRate_;
    float imuSensorsRate_;

};

#endif /* MBED_IMU_H */
