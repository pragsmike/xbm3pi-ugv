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

#include "IMU.h"

IMU::IMU(mavlink_attitude_t &attitude, mavlink_scaled_imu_t &scaled_imu,
		 float imuRate,
         double gyroscopeMeasurementError) : imuFilter(imuRate, gyroscopeMeasurementError) {

	_attitude 	= &attitude;
	_scaled_imu = &scaled_imu;
    imuRate_ 	= imuRate;

    filterTicker.attach(this, &IMU::tick, imuRate_);

}

void IMU::tick(void) {

    //Update the filter variables.
    imuFilter.updateFilter(_scaled_imu->ygyro, _scaled_imu->xgyro, _scaled_imu->zgyro,
    		_scaled_imu->yacc, _scaled_imu->xacc, _scaled_imu->zacc);

    //Calculate the new Euler angles.
    imuFilter.computeEuler();
    _attitude->pitch = toDegrees(imuFilter.getPitch());
    _attitude->roll = toDegrees(imuFilter.getRoll());
    _attitude->yaw = toDegrees(imuFilter.getYaw());
}
