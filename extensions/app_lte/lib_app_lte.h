/*****************************************************************************************************
 * Software License Agreement (BSD License)
 * Author : Souheil Ben Ayed <souheil@tera.ics.keio.ac.jp>
 *
 * Copyright (c) 2009-2010, Souheil Ben Ayed, Teraoka Laboratory of Keio University, and the WIDE Project
 * All rights reserved.
 *
 * Redistribution and use of this software in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by Souheil Ben Ayed <souheil@tera.ics.keio.ac.jp>.
 *
 * 4. Neither the name of Souheil Ben Ayed, Teraoka Laboratory of Keio University or the WIDE Project nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ''AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************************************/

#ifndef LIB_APP_LTE_H_
#define LIB_APP_LTE_H_

#include <freeDiameter/extension.h>

#define APP_LTE_EXTENSION "[App LTE extension] "

#include "app_lte_defs.h"
// #include "diameap_eappacket.h"
#include "app_lte_subscriber.h"
#include "app_lte_mysql.h"

#include <math.h>
#include <dlfcn.h>

/* authentication and authorization attributes  */

struct auth_attribute
{
	struct fd_list chain;
	char *attrib;
	char *op;
	char *value;
};

struct avp_attribute
{
	struct fd_list chain;
	char *attrib;
	union avp_value value;
	int tofree;
};

/************************************************/
/*		EAP Methods	plugins							*/
/************************************************/

/* The register functions of an EAP method */
struct register_plugin
{
	char *configure;
	char *init;
	char *initPickUp;
	char *buildReq;
	char *isDone;
	char *process;
	char *check;
	char *getTimeout;
	char *getKey;
	char *unregister;
	char *datafree;
};

/* EAP Backend Authenticator State Machine (RFC4137) */
/* Most of variables are described in the part 6 of the RFC 4137 */
/* */
struct lte_state_machine
{
	/*Local state Machine Variables*/

	/* Long-Term (Maintained between Packets) */
	u32 currentVendor;
	int currentId;
	int lastId;
	void * methodData;
	struct plugin *selectedMethod;
	u8 NAKproposedMethods[251];

	struct lte_subscriber user;

	/* Short-Term (Not Maintained between exchanged Diameter EAP messages)*/
	boolean rxResp;
	int respId;
	int respVendorMethod;
	u32 respVendor;
	enum
	{
		EAP_INITIALIZE,
		EAP_PICK_UP_METHOD,
		EAP_IDLE,
		EAP_RECEIVED,
		EAP_SEND_REQUEST,
		EAP_INTEGRITY_CHECK,
		EAP_METHOD_REQUEST,
		EAP_METHOD_RESPONSE,
		EAP_PROPOSE_METHOD,
		EAP_NAK,
		EAP_SELECT_ACTION,
		EAP_END,
		EAP_DISCARD
	} eap_state;

};



#endif /* LIB_APP_LTE_H_ */
