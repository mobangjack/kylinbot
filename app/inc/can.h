/**
 * Copyright (c) 2016, Jack Mo (mobangjack@foxmail.com).
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __CAN_H__
#define __CAN_H__

/*********************************************/
/*          Controller Area Network          */
/*********************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include "est.h"
#include "wdg.h"

#define ZGYRO_FDB_CAN_MSG_ID   0x401
#define MOTOR1_FDB_CAN_MSG_ID  0x201
#define MOTOR2_FDB_CAN_MSG_ID  0x202
#define MOTOR3_FDB_CAN_MSG_ID  0x203
#define MOTOR4_FDB_CAN_MSG_ID  0x204
#define MOTOR5_FDB_CAN_MSG_ID  0x205
#define MOTOR6_FDB_CAN_MSG_ID  0x206

#define MOTOR_ESC_CURRENT_FDB_MAX 13000
#define MOTOR_ECD_MOD 8192
#define MOTOR_ECD_GAP 4000

#define MOTOR_NUM 6
#define MOTOR_BUF_N 10
#define MOTOR_EKF_Q 0.1f
#define MOTOR_EKF_R 0.9f

typedef struct
{
	uint8_t ini;
	int32_t angle_fdb;
	int32_t bias;
	int32_t rate;
	int32_t angle;
}ZGyro_t;

typedef struct
{
	uint8_t ini;
	int32_t old;
	int32_t del;
	int16_t buf[MOTOR_BUF_N];
	int32_t sum;
	int16_t dsum;
	uint8_t i;
	int16_t ret;
	Ekf_t ekf;
	uint16_t angle_fdb;
	int32_t current_fdb;
	int32_t current_ref;
	uint16_t bias;
	int32_t round;
	int16_t rate;
	int32_t angle;
}Motor_t;

void ZGyro_Process(ZGyro_t* zgyro, uint8_t* data);
void Motor_Process(Motor_t* motor, uint8_t* data);
void ZGyro_Reset(void);
void Motor_Reset(void);

void Can_Init(void);
void Can_Proc(uint32_t id, uint8_t* data);

extern ZGyro_t zgyro;
extern Motor_t motor[MOTOR_NUM];

#ifdef __cplusplus
}
#endif

#endif

