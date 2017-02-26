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

#include "dci.h"

/*****************************************/
/*     DBUS Direct Control Interface     */
/*****************************************/

DBUS_t dbus;

void DCI_Init(void)
{
	RCI_Init();
	HCI_Init();
	DBUS_Rst(&dbus);
}

void DCI_Proc(void)
{
	if (switchStates[SW_IDX_R] == SW_UP) {
		RCI_Proc(&dbus.rcp);
	} else if (switchStates[SW_IDX_R] == SW_MD) {
		HCI_Proc(&dbus.hcp);
	} else if (switchStates[SW_IDX_R] == SW_DN) {
	} else {
		// Should never reach here
	}
}

void Rcv_Proc(uint8_t* dbuf)
{
	Wdg_Feed(WDG_IDX_RCV);
	DBUS_Dec(&dbus, dbuf);
	GetSwitchStates(&dbus.rcp);
	GetSwitchEvents(&dbus.rcp);
}
