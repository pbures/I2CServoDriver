/*
 * Servo.h
 *
 *  Created on: 16. 4. 2016
 *      Author: pbures
 */

#ifndef SERVO_SERVO_H_
#define SERVO_SERVO_H_

#define PULSE_MIN          500
#define PULSE_MAX         2500
#define PULSE_MID         1500

int turnDegrees(uint16_t degrees);
void initTimer1Servo();

#endif /* SERVO_SERVO_H_ */
