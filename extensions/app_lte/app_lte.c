/*********************************************************************************************************
 * Software License Agreement (BSD License)                                                               *								 *
 * 													 							 *
 * Redistribution and use of this software in source and binary forms, with or without modification, are  *
 * permitted provided that the following conditions are met:						 *
 * 													                             *
 * * Redistributions of source code must retain the above 						 *
 *   copyright notice, this list of conditions and the 							 *
 *   following disclaimer.										                 *
 *    													                         *
 * * Redistributions in binary form must reproduce the above 					 *
 *   copyright notice, this list of conditions and the 							 *
 *   following disclaimer in the documentation and/or other						 *
 *   materials provided with the distribution.								     *
 * 													                             *
 * * Neither the name of the WIDE Project or NICT nor the 						 *
 *   names of its contributors may be used to endorse or 						 *
 *   promote products derived from this software without 						 *
 *   specific prior written permission of WIDE Project and 						 *
 *   NICT.																		 *
 * 																				 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED *
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A *
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR *
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 	 *
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 	 *
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR *
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF   *
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.								 *
 *********************************************************************************************************/

/*
 * Test application for freeDiameter.
 */

#include "app_lte_common.h"

#ifndef HAVE_MYSQL_MY_BOOL
#include <stdbool.h>
typedef bool my_bool;
#endif /* HAVE_MYSQL_MY_BOOL */

// struct app_lte
static struct app_lte_conf conf;
struct app_lte_conf *lte_config = &conf;

// static pthread_t ta_stats_th = (pthread_t)NULL;
struct dict_object *dataobj_lte_cmd = NULL; /* Diameter-LTE-Request Command Code */
struct dict_object *dataobj_lte_app = NULL; /* Diameter LTE Application object */
struct dict_object *dataobj_lte_ven = NULL; /* Diameter LTE Application Vendor object */
struct dict_object *dataobj_cc_request_type = NULL;
struct dict_object *dataobj_cc_request_num = NULL;
struct dict_object *dataobj_accounting_eap_auth_method = NULL;
struct dict_object *dataobj_acct_interim_interval = NULL;
struct dict_object *dataobj_auth_application_id = NULL;
struct dict_object *dataobj_auth_grace_period = NULL;
struct dict_object *dataobj_auth_request_type = NULL;
struct dict_object *dataobj_auth_session_state = NULL;
struct dict_object *dataobj_authorization_lifetime = NULL;
struct dict_object *dataobj_callback_id = NULL;
struct dict_object *dataobj_callback_number = NULL;
struct dict_object *dataobj_called_station_id = NULL;
struct dict_object *dataobj_calling_station_id = NULL;
struct dict_object *dataobj_class = NULL;
struct dict_object *dataobj_configuration_token = NULL;
struct dict_object *dataobj_connect_info = NULL;
struct dict_object *dataobj_destination_host = NULL;
struct dict_object *dataobj_destination_realm = NULL;
struct dict_object *dataobj_eap_master_session_key = NULL;
struct dict_object *dataobj_eap_key_name = NULL;
//struct dict_object *dataobj_eap_payload = NULL;
struct dict_object *dataobj_eap_reissued_payload = NULL;
struct dict_object *dataobj_error_message = NULL;
struct dict_object *dataobj_error_reporting_host = NULL;
struct dict_object *dataobj_failed_avp = NULL;
struct dict_object *dataobj_filter_id = NULL;
struct dict_object *dataobj_framed_appletalk_link = NULL;
struct dict_object *dataobj_framed_appletalk_network = NULL;
struct dict_object *dataobj_framed_appletalk_zone = NULL;
struct dict_object *dataobj_framed_compression = NULL;
struct dict_object *dataobj_framed_interface_id = NULL;
struct dict_object *dataobj_framed_ip_address = NULL;
struct dict_object *dataobj_framed_ip_netmask = NULL;
struct dict_object *dataobj_framed_ipv6_prefix = NULL;
struct dict_object *dataobj_framed_ipv6_pool = NULL;
struct dict_object *dataobj_framed_ipv6_route = NULL;
struct dict_object *dataobj_framed_ipx_network = NULL;
struct dict_object *dataobj_framed_mtu = NULL;
struct dict_object *dataobj_framed_pool = NULL;
struct dict_object *dataobj_framed_protocol = NULL;
struct dict_object *dataobj_framed_route = NULL;
struct dict_object *dataobj_framed_routing = NULL;
struct dict_object *dataobj_idle_timeout = NULL;
struct dict_object *dataobj_multi_round_time_out = NULL;
struct dict_object *dataobj_nas_filter_rule = NULL;
struct dict_object *dataobj_nas_identifier = NULL;
struct dict_object *dataobj_nas_ip_address = NULL;
struct dict_object *dataobj_nas_ipv6_address = NULL;
struct dict_object *dataobj_nas_port = NULL;
struct dict_object *dataobj_nas_port_id = NULL;
struct dict_object *dataobj_nas_port_type = NULL;
struct dict_object *dataobj_originating_line_info = NULL;
struct dict_object *dataobj_origin_host = NULL;
struct dict_object *dataobj_origin_realm = NULL;
struct dict_object *dataobj_origin_state_id = NULL;
struct dict_object *dataobj_port_limit = NULL;
struct dict_object *dataobj_proxy_info = NULL;
struct dict_object *dataobj_qos_filter_rule = NULL;
struct dict_object *dataobj_re_auth_request_type = NULL;
struct dict_object *dataobj_redirect_host = NULL;
struct dict_object *dataobj_redirect_host_usage = NULL;
struct dict_object *dataobj_redirect_max_cache_time = NULL;
struct dict_object *dataobj_reply_message = NULL;
struct dict_object *dataobj_result_code = NULL;
struct dict_object *dataobj_route_record = NULL;
struct dict_object *dataobj_service_type = NULL;
struct dict_object *dataobj_service_context_id = NULL;
struct dict_object *dataobj_session_id = NULL;
struct dict_object *dataobj_session_timeout = NULL;
struct dict_object *dataobj_state = NULL;
struct dict_object *dataobj_tunneling = NULL;
//struct dict_object *dataobj_user_name = NULL;
struct dict_object *dataobj_subscription_id = NULL;
struct dict_object *dataobj_subscription_id_data = NULL;
struct dict_object *dataobj_subscription_id_type = NULL;
struct dict_object *dataobj_mscc = NULL;
struct dict_object *dataobj_gsu = NULL;
struct dict_object *dataobj_cc_total_octets = NULL;
struct dict_object *dataobj_cc_input_octets = NULL;
struct dict_object *dataobj_cc_output_octets = NULL;
struct dict_object *dataobj_cc_time = NULL;
struct dict_object *dataobj_rating_group = NULL;
struct dict_object *dataobj_validity_time = NULL;

int app_lte_set_mysql_param(char *user, char *passwd, char *server, char *database)
{
	TRACE_ENTRY("%p %p %p %p", user, passwd, server, database);
	if (user == NULL)
	{
		TRACE_DEBUG(INFO, "%sUnable to connect to MySQL Database Server: Empty user name or missing in the configuration file.", APP_LTE_EXTENSION);
		return EINVAL;
	}

	if (server == NULL)
	{
		TRACE_DEBUG(INFO, "%sUnable to connect to MySQL Database Server: MySQL Database Server address missing in the configuration file.", APP_LTE_EXTENSION);
		return EINVAL;
	}
	if (database == NULL)
	{
		TRACE_DEBUG(INFO, "%sUnable to connect to MySQL Database Server: MySQL Database name missing in configuration file.", APP_LTE_EXTENSION);
		return EINVAL;
	}
	lte_config->db.user = user;
	lte_config->db.password = passwd;
	lte_config->db.server = server;
	lte_config->db.database = database;
	return 0;
}

/* Connecting to MySQL Database */
int app_lte_mysql_connect(void)
{
	TRACE_ENTRY();
	db_conn = mysql_init(NULL);
	const my_bool mysql_reconnect_val = 1;
	mysql_options(db_conn, MYSQL_OPT_RECONNECT, &mysql_reconnect_val);
	/* Connect to database */
	if (!mysql_real_connect(db_conn, lte_config->db.server, lte_config->db.user, lte_config->db.password, lte_config->db.database, 0, NULL, 0))
	{
		TRACE_DEBUG(INFO, "%sConnection to MySQL Database Server failed: %s", APP_LTE_EXTENSION, mysql_error(db_conn));
		return errno;
	}
	return 0;
}

static int app_lte_init_obj(void)
{

	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_APPLICATION, APPLICATION_BY_ID, &(lte_config->application_id), &dataobj_lte_app, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_COMMAND, CMD_BY_CODE_R, &(lte_config->command_code), &dataobj_lte_cmd, ENOENT));
	// CHECK_FCT( fd_dict_search( fd_g_config->cnf_dict, DICT_VENDOR, VENDOR_OF_APPLICATION, &dataobj_lte_app, &dataobj_lte_ven, ENOENT));
	
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Auth-Application-Id", &dataobj_auth_application_id, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "CC-Request-Type", &dataobj_cc_request_type, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "CC-Request-Number", &dataobj_cc_request_num, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "CC-Total-Octets", &dataobj_cc_total_octets, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "CC-Input-Octets", &dataobj_cc_input_octets, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "CC-Output-Octets", &dataobj_cc_output_octets, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "CC-Time", &dataobj_cc_time, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Service-Context-Id", &dataobj_service_context_id, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Multiple-Services-Credit-Control", &dataobj_mscc, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Granted-Service-Unit", &dataobj_gsu, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Origin-Host", &dataobj_origin_host, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Origin-Realm", &dataobj_origin_realm, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Origin-State-Id", &dataobj_origin_state_id, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Rating-Group", &dataobj_rating_group, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Result-Code", &dataobj_result_code, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Route-Record", &dataobj_route_record, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Session-Id", &dataobj_session_id, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Session-Timeout", &dataobj_session_timeout, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Subscription-Id", &dataobj_subscription_id, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Subscription-Id-Data", &dataobj_subscription_id_data, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Subscription-Id-Type", &dataobj_subscription_id_type, ENOENT));
	CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "Validity-Time", &dataobj_validity_time, ENOENT));

	// CHECK_FCT(fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME, "User-Name", &dataobj_user_name, ENOENT));

	return 0;
}

static int app_lte_init_config(char *conffile)
{
	TRACE_ENTRY("%p", conffile);

	if (conffile != NULL)
	{
		lte_config->conffile = conffile;
	}
	else
	{
		TRACE_DEBUG(FULL, "%sNo configuration file provided with the LTE extension: default parameters will be used.", APP_LTE_EXTENSION);
	}

	lte_config->application_id = 4;
	lte_config->vendor_id = 10415;
	lte_config->command_code = 272;
	// lte_config->diam_realm = strdup(fd_g_config->cnf_diamrlm);
	lte_config->multi_round_time_out = 30;

	return 0;
}

static int app_lte_parse_conffile(void)
{
	if (!lte_config->conffile)
	{
		TRACE_DEBUG(INFO, "%sNo configuration file to parse for LTE Extension.", APP_LTE_EXTENSION);
		return EINVAL;
	}
	extern FILE * app_lte_confin;

	TRACE_DEBUG(FULL, "%sParsing configuration file: %s", APP_LTE_EXTENSION, lte_config->conffile);
	app_lte_confin = fopen(lte_config->conffile, "r");
	if (!app_lte_confin)
	{
		TRACE_DEBUG(INFO, "%sUnable to open configuration file %s for reading: %s", APP_LTE_EXTENSION, lte_config->conffile, strerror(errno));
		return errno;
	}

	/* call yacc parser */
	CHECK_FCT(app_lte_confparse(lte_config));

	/* close the file */
	CHECK_FCT(fclose(app_lte_confin));
	return 0;
}

int app_lte_init(char *conffile)
{
	TRACE_ENTRY("%p", conffile);

	/* Initialize the diameap_config structure*/
	CHECK_FCT(app_lte_init_config(conffile));

	if (lte_config->conffile)
	{
		/* parse the configuration file*/
		CHECK_FCT(app_lte_parse_conffile());
	}
	else
	{
		TRACE_DEBUG(FULL, "%sNo default configuration.", APP_LTE_EXTENSION);
	}

	/* Initialize Dictionary templates */
	CHECK_FCT(app_lte_init_obj());

	/* Initialize access to user's information Database */
	CHECK_FCT(app_lte_mysql_connect());

	/* Dump DiamEAP extension configuration */
	app_lte_conf_dump();

	return 0;
}

static void app_lte_conf_dump(void)
{
	if (!TRACE_BOOL(INFO))
		return;

	fd_log_debug("-------- LTE extension : Configuration parameters (Dump) -------------");
	fd_log_debug("\t-Configuration file.....: %s", lte_config->conffile);
	fd_log_debug("\t-LTE Application Id.....: %u", lte_config->application_id);
	fd_log_debug("\t-LTE Application Command: %u", lte_config->command_code);
	fd_log_debug("\t-LTE Application Vendor.: %u", lte_config->vendor_id);
	if (lte_config->db.user)
	{
		fd_log_debug("\t-MySQL Database Params..:");
		fd_log_debug("\t\tUser .......:%s", lte_config->db.user);
		fd_log_debug("\t\tServer .....:%s", lte_config->db.server);
		fd_log_debug("\t\tDatabase....:%s", lte_config->db.database);
	}

	fd_log_debug("-------- LTE extension : Configuration parameters (End) ---------------");
}

static struct fd_hook_hdl *hookhdl[2] = {NULL, NULL};

static void ta_hook_cb_silent(enum fd_hook_type type, struct msg *msg, struct peer_hdr *peer, void *other, struct fd_hook_permsgdata *pmd, void *regdata)
{
}

static void ta_hook_cb_oneline(enum fd_hook_type type, struct msg *msg, struct peer_hdr *peer, void *other, struct fd_hook_permsgdata *pmd, void *regdata)
{
	char *buf = NULL;
	size_t len;

	CHECK_MALLOC_DO(fd_msg_dump_summary(&buf, &len, NULL, msg, NULL, 0, 0),
					{ LOG_E("Error while dumping a message"); return; });

	LOG_N("{%d} %s: %s", type, (char *)other ?: "<nil>", buf ?: "<nil>");

	free(buf);
}

/* entry point */
static int lte_main(char *conffile)
{
	TRACE_ENTRY("%p", conffile);

	memset(lte_config, 0, sizeof(struct app_lte_conf));

	/* Initialize configuration */
	CHECK_FCT(app_lte_init(conffile));


	TRACE_DEBUG(INFO, "Extension LTE initialized with configuration: '%s'", conffile);

	/* Start Diameter LTE Application (Back-end Authenticator ) */
	CHECK_FCT(app_lte_start_server());

	/* Announce the support of Diameter LTE Application to other peers */
	CHECK_FCT(fd_disp_app_support(dataobj_lte_app, NULL, 1, 1));

	LOG_D("%sLTE Application Extension started successfully.", APP_LTE_EXTENSION);

	/* Start the statistics thread */
	// CHECK_POSIX( pthread_create(&ta_stats_th, NULL, ta_stats, NULL) );

	return 0;
}

/* Unload */
void fd_ext_fini(void)
{
	TRACE_DEBUG(FULL,"%sStopping the server",APP_LTE_EXTENSION);
	CHECK_FCT_DO(app_lte_stop_server(), {TRACE_DEBUG(INFO,"%sStopping the server: Error occurred.",APP_LTE_EXTENSION);});

	if (db_conn)
	{
		TRACE_DEBUG(FULL,"%sDisconnecting from MySQL Server",APP_LTE_EXTENSION);
		app_lte_mysql_disconnect();
	}

	return;
}

EXTENSION_ENTRY("lte_app", lte_main, "dict_dcca");
