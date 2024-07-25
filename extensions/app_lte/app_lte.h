/*********************************************************************************************************
 * Software License Agreement (BSD License)                                                               *
 * Author: Sebastien Decugis <sdecugis@freediameter.net>							 *
 *													 *
 * Copyright (c) 2013, WIDE Project and NICT								 *
 * All rights reserved.											 *
 * 													 *
 * Redistribution and use of this software in source and binary forms, with or without modification, are  *
 * permitted provided that the following conditions are met:						 *
 * 													 *
 * * Redistributions of source code must retain the above 						 *
 *   copyright notice, this list of conditions and the 							 *
 *   following disclaimer.										 *
 *    													 *
 * * Redistributions in binary form must reproduce the above 						 *
 *   copyright notice, this list of conditions and the 							 *
 *   following disclaimer in the documentation and/or other						 *
 *   materials provided with the distribution.								 *
 * 													 *
 * * Neither the name of the WIDE Project or NICT nor the 						 *
 *   names of its contributors may be used to endorse or 						 *
 *   promote products derived from this software without 						 *
 *   specific prior written permission of WIDE Project and 						 *
 *   NICT.												 *
 * 													 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED *
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A *
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR *
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 	 *
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 	 *
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR *
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF   *
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.								 *
 *********************************************************************************************************/

/* Header file for the app_test extension.
 *
 *  This extension provides a way to send configurable messages on the network
 *
 *  See the app_test.conf.sample file for the format of the configuration file.
 */

#include <freeDiameter/extension.h>
#include <signal.h>

typedef uint32_t u32; /* unsigned long int */

#ifndef TEST_APP_DEFAULT_SIGNAL
#define TEST_APP_DEFAULT_SIGNAL SIGUSR1
#endif /* TEST_APP_DEFAULT_SIGNAL */

/* Mode for the extension */
#define MODE_SERV 0x1
#define MODE_CLI 0x2
#define MODE_BENCH 0x4

/* Structure to hold configuration of LTE*/
struct app_lte_conf
{
	char *conffile; /* configuration file of the extension*/

	// int authorize; /* Set to 1 if provides Authorization. Otherwise set to 0. (by default set to 0)*/

	u32 vendor_id;		/* Vendor ID*/
	u32 application_id; /* Application ID. Value set to 4. */
	u32 command_code;	/* Application Command Code. Value set to 272. */

	char *diam_realm; /* Diameter realm of the peer */

	/*Diameter EAP Server*/
	int max_invalid_packet;

	// MySQL Database parameters

	struct
	{
		char *server;
		char *user;
		char *password;
		char *database;
	} db;

	u32 multi_round_time_out;
};

/* The pointer to access configuration*/
extern struct app_lte_conf *lte_config;

/* Parse the configuration file */
static int app_lte_init_config(char *conffile);
static int app_lte_parse_conffile(void);

/* Configuration dump */
static void app_lte_conf_dump(void);

/* Handle incoming messages (server) */
int ta_serv_init(void);
void ta_serv_fini(void);

/* Create outgoing message (client) */
// int ta_cli_init(void);
// void ta_cli_fini(void);

/* Benchmark flavour */
int ta_bench_init(void);
void ta_bench_fini(void);

/* Initialize dictionary definitions */
int ta_dict_init(void);

/* Some global variables for dictionary */
extern struct dict_object *ta_vendor;
extern struct dict_object *ta_appli;
extern struct dict_object *ta_cmd_r;
extern struct dict_object *ta_cmd_a;
extern struct dict_object *ta_avp;
extern struct dict_object *ta_avp_long;

extern struct dict_object *ta_sess_id;
extern struct dict_object *ta_origin_host;
extern struct dict_object *ta_origin_realm;
extern struct dict_object *ta_dest_host;
extern struct dict_object *ta_dest_realm;
extern struct dict_object *ta_user_name;
extern struct dict_object *ta_res_code;

/* parser */
int app_lte_confparse(struct app_lte_conf * config);
