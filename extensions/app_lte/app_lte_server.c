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

#include "app_lte_common.h"

/* handler for DiamEAP server callback */
static struct disp_hdl * handle;

/* session handler for DiamEAP sessions state machine */
static struct session_handler * app_lte_server_reg = NULL;


struct avp_max_occurences auth_avps[] =
{
{ "Service-Type", 1 },
{ "Callback-Number", 1 },
{ "Callback-Id", 1 },
{ "Idle-Timeout", 1 },
{ "Port-Limit", 1 },
{ "NAS-Filter-Rule" - 1 },
{ "Filter-Id", -1 },
{ "Configuration-Token", -1 },
{ "QoS-Filter-Rule", -1 },
{ "Framed-Protocol", 1 },
{ "Framed-Routing", 1 },
{ "Framed-MTU", 1 },
{ "Framed-Compression", -1 },
{ "Framed-IP-Address", 1 },
{ "Framed-IP-Netmask", 1 },
{ "Framed-Route", -1 },
{ "Framed-Pool", 1 },
{ "Framed-Interface-Id", 1 },
{ "Framed-IPv6-Prefix", -1 },
{ "Framed-IPv6-Pool", 1 },
{ "Framed-IPv6-Route", -1 },
{ "Framed-IPX-Network", 1 },
{ "Framed-Appletalk-Link", 1 },
{ "Framed-Appletalk-Network", -1 },
{ "Framed-Appletalk-Zone", 1 },
{ "NAS-IPv6-Address", 0 },
{ "NAS-Identifier", 0 },
{ "NAS-IP-Address", 0 },
{ "NAS-Port", 0 },
{ "NAS-Port-Id", 0 },
{ "NAS-Port-Type", 0 },
{ "Called-Station-Id", 0 },
{ "Calling-Station-Id", 0 },
{ "Connect-Info", 0 },
{ "Originating-Line-Info", 0 } };



void app_lte_cli_sess_cleanup(struct sess_state * app_lte_sess_data, os0_t sid, void * opaque)
{

	CHECK_PARAMS_DO( app_lte_sess_data, return );

	if (app_lte_sess_data != NULL)
	{
		if (app_lte_sess_data->methodData != NULL)
		{
			if (app_lte_sess_data->methodData != NULL)
			{
				free(app_lte_sess_data->methodData);
				app_lte_sess_data->methodData = NULL;
			}
			
			if (app_lte_sess_data->methodData)
			{
				TRACE_DEBUG(INFO,"%sSession state was not been freed correctly!!!",APP_LTE_EXTENSION);
			}
		}

		if (app_lte_sess_data->user.password != NULL)
		{
			free(app_lte_sess_data->user.password);
			app_lte_sess_data->user.password = NULL;
		}

		if (app_lte_sess_data->user.userid != NULL)
		{
			free(app_lte_sess_data->user.userid);
			app_lte_sess_data->user.userid = NULL;
		}
		free(app_lte_sess_data);
		app_lte_sess_data = NULL;
	}
}

static int app_lte_initialize_app_lte_sm(struct app_lte_state_machine * app_lte_sm, struct sess_state * app_lte_sess_data)
{
	fprintf(stderr, "ECHO app_lte_initialize_app_lte_sm ");
	TRACE_ENTRY("%p %p", app_lte_sm, app_lte_sess_data);

	int i;

	/* Initialize Long Term Variables */
	if (app_lte_sess_data != NULL)
	{
		app_lte_sm->invalid_packets = app_lte_sess_data->invalid_packets;

		/* Initialize eap state machine variables */
		/*User*/
		app_lte_sm->lte_sm.user.id = app_lte_sess_data->user.id;

		if ((app_lte_sess_data->user.userid != NULL)
				&& (app_lte_sess_data->user.useridLength > 0))
		{
			app_lte_sm->lte_sm.user.useridLength
					= app_lte_sess_data->user.useridLength;
			CHECK_MALLOC(app_lte_sm->lte_sm.user.userid= malloc(app_lte_sm->lte_sm.user.useridLength+1));
			U8COPY(app_lte_sm->lte_sm.user.userid,0,app_lte_sm->lte_sm.user.useridLength+1,app_lte_sess_data->user.userid);
			free(app_lte_sess_data->user.userid);
			app_lte_sess_data->user.userid = NULL;

		}
		else
		{
			TRACE_DEBUG(INFO,"%s user not identified yet.",APP_LTE_EXTENSION);
			app_lte_sm->lte_sm.user.useridLength = 0;
			app_lte_sm->lte_sm.user.userid = NULL;
		}

		if ((app_lte_sess_data->user.password != NULL)
				&& (app_lte_sess_data->user.passwordLength > 0))
		{
			app_lte_sm->lte_sm.user.passwordLength
					= app_lte_sess_data->user.passwordLength;
			CHECK_MALLOC(app_lte_sm->lte_sm.user.password = malloc(app_lte_sm->lte_sm.user.passwordLength+1));
			U8COPY(app_lte_sm->lte_sm.user.password,0,app_lte_sm->lte_sm.user.passwordLength+1, app_lte_sess_data->user.password);
			free(app_lte_sess_data->user.password);
			app_lte_sess_data->user.password = NULL;
		}
		else
		{
			app_lte_sm->lte_sm.user.passwordLength = 0;
			app_lte_sm->lte_sm.user.password = NULL;
		}

		app_lte_sm->lte_sm.user.pmethods = app_lte_sess_data->user.pmethods;
		app_lte_sm->lte_sm.user.proposed_eap_method_vendor
				= app_lte_sess_data->user.proposed_eap_method_vendor;
		app_lte_sm->lte_sm.user.success = app_lte_sess_data->user.success;

		app_lte_sm->lte_sm.currentId = app_lte_sess_data->currentId;
		app_lte_sm->lte_sm.currentVendor = app_lte_sess_data->currentVendor;
		app_lte_sm->lte_sm.lastId = app_lte_sess_data->lastId;

		app_lte_sm->lte_sm.methodData = app_lte_sess_data->methodData;
		app_lte_sess_data->methodData = NULL;

		/* free session data*/
		free(app_lte_sess_data);
		app_lte_sess_data = NULL;

	}
	else
	{
		app_lte_sm->invalid_packets = 0;

		/* Initialize eap state machine variables */
		/*User*/
		app_lte_sm->lte_sm.user.id = 0;
		app_lte_sm->lte_sm.user.userid = NULL;
		app_lte_sm->lte_sm.user.useridLength = 0;
		app_lte_sm->lte_sm.user.methodId = -1;

		app_lte_sm->lte_sm.user.pmethods = -1;
		app_lte_sm->lte_sm.user.success = FALSE;

		app_lte_sm->lte_sm.currentId = -1;
		app_lte_sm->lte_sm.lastId = -1;
		app_lte_sm->lte_sm.methodData = NULL;

	}

	app_lte_sm->result_code = 0;
	fd_list_init(&app_lte_sm->attributes, NULL);
	fd_list_init(&app_lte_sm->req_attributes, NULL);
	fd_list_init(&app_lte_sm->ans_attributes, NULL);
	app_lte_sm->failedavp = NULL;
	app_lte_sm->auth_request_val = AUTHENTICATE_ONLY;
	app_lte_sm->authSuccess = FALSE;
	app_lte_sm->authFailure = FALSE;
	app_lte_sm->lastReqEAPavp = NULL;
	app_lte_sm->authorized = FALSE;

	app_lte_sm->lte_sm.rxResp = FALSE;
	app_lte_sm->lte_sm.respId = -1;
	app_lte_sm->lte_sm.respVendor = VENDOR_IETF;

	return 0;
}

static int app_lte_failed_avp(struct app_lte_state_machine * app_lte_sm,
		struct avp * invalidavp)
{
	TRACE_ENTRY("%p %p",app_lte_sm,invalidavp);
	if (!invalidavp)
		return EINVAL;

	if (!app_lte_sm)
		return EINVAL;

	if (app_lte_sm->failedavp == NULL)
	{
		CHECK_FCT( fd_msg_avp_new( dataobj_failed_avp, 0, &app_lte_sm->failedavp) );

		CHECK_FCT( fd_msg_avp_add( app_lte_sm->failedavp, MSG_BRW_LAST_CHILD, invalidavp ) );

	}
	else
	{
		//add multiple AVPs in Failed-AVP
	}
	return 0;
}

static int app_lte_parse_eap_resp(struct lte_state_machine * eap_sm,
		struct eap_packet *eappacket)
{
	TRACE_ENTRY("%p %p",eap_sm, eappacket)

	eap_sm->rxResp = FALSE;
	eap_sm->respId = -1;
	eap_sm->respVendor = VENDOR_IETF;

	eap_sm->rxResp = TRUE;
	return 0;
}

static int app_lte_parse_avps(struct app_lte_state_machine * app_lte_sm, struct msg * req)
{
	TRACE_ENTRY("%p %p",app_lte_sm,req);
	struct avp * avp, *avp2;
	struct avp_hdr * avpdata;
	int ret;
	int depth;

	/* CC Request type data*/
	avp = NULL;
	CHECK_FCT(fd_msg_search_avp(req, dataobj_cc_request_type, &avp));
	if (avp != NULL)
	{
		CHECK_FCT(fd_msg_avp_hdr(avp, &avpdata));
		app_lte_sm->cc_request_type = avpdata->avp_value->i32;
		fprintf(stderr, "\nECHO CC-Request %i", app_lte_sm->cc_request_type);
	}

	/* User-Name / Subscription ID Data AVP */
	avp = NULL;
	CHECK_FCT(fd_msg_search_avp(req, dataobj_subscription_id_data, &avp));
	if (avp != NULL)
	{
		CHECK_FCT(fd_msg_avp_hdr(avp, &avpdata));
		struct avp_attribute * attribute;
		fprintf(stderr, "\nECHO Subscription-Id-Data %s", avpdata->avp_value->os.data);
		CHECK_MALLOC(attribute = malloc(sizeof(struct avp_attribute)));
		memset(attribute, 0, sizeof(struct avp_attribute));
		fd_list_init(&attribute->chain, attribute);
		attribute->attrib = "Subscription-Id-Data";
		attribute->value.os.data = avpdata->avp_value->os.data;
		attribute->value.os.len = avpdata->avp_value->os.len;
		fd_list_insert_before(&app_lte_sm->req_attributes, &attribute->chain);

		CHECK_FCT_DO(get_lte_subscriber(&app_lte_sm->lte_sm.user, attribute->value.os.data), TRACE_DEBUG(INFO,"%s Unable to parse LTE-Request AVPs.",APP_LTE_EXTENSION));
	}

	/* Subscription ID AVP */
	avp = NULL;
	avp2 = NULL;
	CHECK_FCT(fd_msg_search_avp(req, dataobj_subscription_id, &avp));
	if (avp != NULL)
	{
		CHECK_FCT(fd_msg_avp_hdr(avp, &avpdata));
		fprintf(stderr, "\nECHO Subscription-Id %i", avpdata->avp_code);
		u32 Pi_Code = avpdata->avp_code;
		int depth;
		do
		{
			struct avp_attribute * attribute;
			CHECK_MALLOC(attribute = malloc(sizeof(struct avp_attribute)));
			memset(attribute, 0, sizeof(struct avp_attribute));
			fd_list_init(&attribute->chain, attribute);
			attribute->attrib = "Subscription-Id";
			//grouped AVP
			fd_list_insert_before(&app_lte_sm->req_attributes,&attribute->chain);
			ret = 0;
			depth = 0;
			ret = fd_msg_browse ( avp, MSG_BRW_NEXT, &avp2, &depth);
			if (avp2 != NULL)
			{
				CHECK_FCT(fd_msg_avp_hdr(avp2, &avpdata));
				if(!avpdata->avp_value->i32 ){
					fprintf(stderr, "\nECHO Subscription-Id-Data %s", avpdata->avp_value->os.data);
				}
				if(avpdata->avp_value->i32){
					fprintf(stderr, "\nECHO Subscription-Id-Type %i", avpdata->avp_value->i32);
				}
			}
			avp = avp2;
		} while ((avp2 != NULL) && (ret == 0) && (ret == 0)
				&& (avpdata->avp_code == Pi_Code));
	}

	/* CC Request Number AVP */
	avp = NULL;
	CHECK_FCT(fd_msg_search_avp(req, dataobj_cc_request_num, &avp));
	if (avp != NULL)
	{
		CHECK_FCT(fd_msg_avp_hdr(avp, &avpdata));
		app_lte_sm->cc_request_num = avpdata->avp_value->i32;
	}

	return 0;
}


static int app_lte_sess_data_new(struct sess_state *app_lte_sess_data, struct app_lte_state_machine *app_lte_sm)
{
	if (!app_lte_sm)
		return EINVAL;

	int i;

	app_lte_sess_data->invalid_packets = app_lte_sm->invalid_packets;

	app_lte_sess_data->user.id = app_lte_sm->lte_sm.user.id;

	if ((app_lte_sm->lte_sm.user.userid != NULL)
			&& (app_lte_sm->lte_sm.user.useridLength > 0))
	{
		app_lte_sess_data->user.useridLength
				= app_lte_sm->lte_sm.user.useridLength;
		CHECK_MALLOC(app_lte_sess_data->user.userid= malloc(app_lte_sess_data->user.useridLength+1));
		U8COPY(app_lte_sess_data->user.userid,0,app_lte_sess_data->user.useridLength+1,app_lte_sm->lte_sm.user.userid);
		free(app_lte_sm->lte_sm.user.userid);
		app_lte_sm->lte_sm.user.userid = NULL;

	}
	else
	{
		app_lte_sess_data->user.useridLength = 0;
		app_lte_sess_data->user.userid = NULL;
	}

	if ((app_lte_sm->lte_sm.user.password != NULL)
			&& (app_lte_sm->lte_sm.user.passwordLength > 0))
	{
		app_lte_sess_data->user.passwordLength
				= app_lte_sm->lte_sm.user.passwordLength;
		CHECK_MALLOC(app_lte_sess_data->user.password = malloc(app_lte_sess_data->user.passwordLength+1));
		U8COPY(app_lte_sess_data->user.password,0,app_lte_sess_data->user.passwordLength+1,app_lte_sm->lte_sm.user.password);
		free(app_lte_sm->lte_sm.user.password);
		app_lte_sm->lte_sm.user.password = NULL;
	}
	else
	{
		app_lte_sess_data->user.passwordLength = 0;
		app_lte_sess_data->user.password = NULL;
	}

	app_lte_sess_data->user.methodId = app_lte_sm->lte_sm.user.methodId;

	app_lte_sess_data->user.pmethods = app_lte_sm->lte_sm.user.pmethods;
	app_lte_sess_data->user.proposed_eap_method_vendor
			= app_lte_sm->lte_sm.user.proposed_eap_method_vendor;
	app_lte_sess_data->user.success = app_lte_sm->lte_sm.user.success;

	app_lte_sess_data->currentId = app_lte_sm->lte_sm.currentId;
	app_lte_sess_data->currentVendor = app_lte_sm->lte_sm.currentVendor;
	app_lte_sess_data->lastId = app_lte_sm->lte_sm.lastId;

	app_lte_sess_data->methodData = app_lte_sm->lte_sm.methodData;
	app_lte_sm->lte_sm.methodData = NULL;

	return 0;
}

static void free_attrib(struct auth_attribute * auth_attrib)
{
	if (auth_attrib == NULL)
	{
		return;
	}
	if (auth_attrib->attrib != NULL)
	{
		free(auth_attrib->attrib);
		auth_attrib->attrib = NULL;
	}
	if (auth_attrib->op != NULL)
	{
		free(auth_attrib->op);
		auth_attrib->op = NULL;
	}
	if (auth_attrib->value != NULL)
	{
		free(auth_attrib->value);
		auth_attrib->value = NULL;
	}
	free(auth_attrib);
	auth_attrib = NULL;
}

static void free_avp_attrib(struct avp_attribute * avp_attrib)
{
	if(avp_attrib){
	free(avp_attrib);
	avp_attrib = NULL;
	}
}

static void free_ans_attrib(struct avp_attribute * ans_attrib)
{
	if(ans_attrib){
		if (ans_attrib->tofree == 1)
		{
			if(ans_attrib->value.os.data){
			free(ans_attrib->value.os.data);
			ans_attrib->value.os.data = NULL;
			}
		}
		free(ans_attrib);
		ans_attrib = NULL;
	}
}

static int app_lte_unlink_attributes_lists(struct app_lte_state_machine * app_lte_sm)
{
	TRACE_ENTRY("%p ", app_lte_sm);
	if (app_lte_sm == NULL)
	{
		return EINVAL;
	}

	while (!FD_IS_LIST_EMPTY(&app_lte_sm->attributes))
	{
		struct fd_list * item = (struct fd_list *) app_lte_sm->attributes.next;
		struct auth_attribute * auth = (struct auth_attribute *) item;
		fd_list_unlink(item);
		free_attrib(auth);
	}

	while (!FD_IS_LIST_EMPTY(&app_lte_sm->req_attributes))
	{
		struct fd_list * item =
				(struct fd_list *) app_lte_sm->req_attributes.next;
		struct avp_attribute * avp = (struct avp_attribute *) item;
		fd_list_unlink(item);
		free_avp_attrib(avp);
	}

	while (!FD_IS_LIST_EMPTY(&app_lte_sm->ans_attributes))
	{
		struct fd_list * item =
				(struct fd_list *) app_lte_sm->ans_attributes.next;
		struct avp_attribute * avp_ans = (struct avp_attribute *) item;
		fd_list_unlink(item);
		free_ans_attrib(avp_ans);
	}

	return 0;
}

static void app_lte_free(struct app_lte_state_machine * app_lte_sm)
{

	if (app_lte_sm != NULL)
	{
		if (app_lte_sm->lte_sm.user.userid != NULL)
		{
			free(app_lte_sm->lte_sm.user.userid);
			app_lte_sm->lte_sm.user.userid = NULL;
		}

		if (app_lte_sm->lte_sm.user.password != NULL)
		{
			free(app_lte_sm->lte_sm.user.password);
			app_lte_sm->lte_sm.user.password = NULL;
		}

		app_lte_sm->lte_sm.selectedMethod = NULL;

		if (app_lte_sm->lte_sm.methodData != NULL)
		{
			if (app_lte_sm->lte_sm.methodData)
			{
				TRACE_DEBUG(INFO,"%sSession state was not been freed correctly!!!",APP_LTE_EXTENSION);
			}
		}

		if (app_lte_sm->failedavp != NULL)
		{
			CHECK_FCT_DO(fd_msg_free(app_lte_sm->failedavp), );
		}

		if (app_lte_sm->lastReqEAPavp != NULL)
		{
			CHECK_FCT_DO(fd_msg_free(app_lte_sm->lastReqEAPavp), );
		}

		CHECK_FCT_DO(app_lte_unlink_attributes_lists(app_lte_sm), );

		free(app_lte_sm);
		app_lte_sm = NULL;
	}

}

static int app_lte_get_avp_attribute(struct fd_list * avp_attributes, char * attribute, struct avp_attribute ** avp_attrib, int unlink, int *ret)
{
	TRACE_ENTRY("%p %p %p %d %p", avp_attributes, attribute, avp_attrib, unlink, ret);
	if (avp_attributes == NULL)
	{
		return EINVAL;
	}
	if (attribute == NULL)
	{
		return EINVAL;
	}
	struct fd_list * attrib;
	for (attrib = avp_attributes->next; attrib != avp_attributes; attrib
			= attrib->next)
	{
		*avp_attrib = (struct avp_attribute *) attrib;
		if (strcmp((*avp_attrib)->attrib, attribute) == 0)
		{
			*ret = 0;
			if (unlink == 1)
			{
				fd_list_unlink(&(*avp_attrib)->chain);
			}
			return 0;
		}
	}
	*avp_attrib = NULL;
	*ret = 1;
	return 0;
}

static int app_lte_get_auth_attribute(struct fd_list * auth_attributes, char * attribute, struct auth_attribute ** auth_attrib, int unlink, int *ret)
{

	TRACE_ENTRY("%p %p %p %d %p", auth_attributes, attribute, auth_attrib, unlink, ret);

	if (auth_attributes == NULL)
	{
		return EINVAL;
	}
	if (attribute == NULL)
	{
		return EINVAL;
	}

	struct fd_list * attrib;

	for (attrib = auth_attributes->next; attrib != auth_attributes; attrib
			= attrib->next)
	{
		*auth_attrib = (struct auth_attribute *) attrib;
		if (strcmp((*auth_attrib)->attrib, attribute) == 0)
		{
			*ret = 0;
			if (unlink == 1)
			{
				fd_list_unlink(&(*auth_attrib)->chain);
			}
			return 0;
		}
	}
	*auth_attrib = NULL;
	*ret = 1;
	return 0;
}

static int app_lte_get_ans_attribute(struct fd_list * ans_attributes, char * attribute, struct avp_attribute ** ans_attrib, int unlink, int *ret)
{
	TRACE_ENTRY("%p %p %p %d %p", ans_attributes, attribute, ans_attrib, unlink, ret);
	if (ans_attributes == NULL)
	{
		return EINVAL;
	}
	if (attribute == NULL)
	{
		return EINVAL;
	}
	struct fd_list * attrib;
	for (attrib = ans_attributes->next; attrib != ans_attributes; attrib
			= attrib->next)
	{
		*ans_attrib = (struct avp_attribute *) attrib;
		if (strcmp((*ans_attrib)->attrib, attribute) == 0)
		{
			*ret = 0;
			if (unlink == 1)
			{
				fd_list_unlink(&(*ans_attrib)->chain);
			}
			return 0;
		}
	}
	*ans_attrib = NULL;
	*ret = 1;
	return 0;
}

static int app_lte_answer_avp_attributes(struct app_lte_state_machine * app_lte_sm)
{
	TRACE_ENTRY("%p",app_lte_sm);

	if (app_lte_sm == NULL)
	{
		return EINVAL;
	}
	int ret1, ret2;
	struct avp_attribute * avp_attrib;
	struct avp_attribute * ans_attrib;
	struct auth_attribute * auth_attrib;

	/* Authorization-Lifetime */
	{
		CHECK_FCT(app_lte_get_avp_attribute(&app_lte_sm->req_attributes, "Authorization-Lifetime", &avp_attrib,1, &ret1));

		CHECK_FCT(app_lte_get_auth_attribute(&app_lte_sm->attributes, "Authorization-Lifetime", &auth_attrib,1, &ret2));

		if ((ret1 == 1) && (ret2 == 0) && (auth_attrib != NULL))
		{

			CHECK_MALLOC(ans_attrib = malloc(sizeof(struct avp_attribute)));

			memset(ans_attrib, 0, sizeof(struct avp_attribute));

			fd_list_init(&ans_attrib->chain, NULL);

			ans_attrib->attrib = "Authorization-Lifetime";

			ans_attrib->value.u32 = atoi(auth_attrib->value);

			fd_list_insert_before(&app_lte_sm->ans_attributes,
					&ans_attrib->chain);

			free_attrib(auth_attrib);

		}
		if ((ret1 == 0) && (ret2 == 1) && (avp_attrib != NULL))
		{

			CHECK_MALLOC(ans_attrib = malloc(sizeof(struct avp_attribute)));

			memset(ans_attrib, 0, sizeof(struct avp_attribute));

			fd_list_init(&ans_attrib->chain, NULL);

			ans_attrib->attrib = "Authorization-Lifetime";

			ans_attrib->value.u32 = avp_attrib->value.u32;

			fd_list_insert_before(&app_lte_sm->ans_attributes,
					&ans_attrib->chain);

			free_avp_attrib(avp_attrib);

		}
		if ((ret1 == 0) && (ret2 == 0) && (auth_attrib != NULL) && (avp_attrib
				!= NULL))
		{

			CHECK_MALLOC(ans_attrib = malloc(sizeof(struct avp_attribute)));

			memset(ans_attrib, 0, sizeof(struct avp_attribute));
			fd_list_init(&ans_attrib->chain, NULL);
			ans_attrib->attrib = "Authorization-Lifetime";
			if (avp_attrib->value.u32 < atoi(auth_attrib->value))
			{
				ans_attrib->value.u32 = avp_attrib->value.u32;
			}
			else
			{
				ans_attrib->value.u32 = atoi(auth_attrib->value);
			}
			fd_list_insert_before(&app_lte_sm->ans_attributes,
					&ans_attrib->chain);
			free_avp_attrib(avp_attrib);
			free_attrib(auth_attrib);
		}
	}

	/* Auth-Grace-Period */
	{
		CHECK_FCT(app_lte_get_avp_attribute(&app_lte_sm->req_attributes, "Auth-Grace-Period", &avp_attrib,1, &ret1));

		CHECK_FCT(app_lte_get_auth_attribute(&app_lte_sm->attributes, "Auth-Grace-Period", &auth_attrib,1, &ret2));

		if ((ret1 == 1) && (ret2 == 0) && (auth_attrib != NULL))
		{
			CHECK_MALLOC(ans_attrib = malloc(sizeof(struct avp_attribute)));
			memset(ans_attrib, 0, sizeof(struct avp_attribute));
			fd_list_init(&ans_attrib->chain, NULL);
			ans_attrib->attrib = "Auth-Grace-Period";
			ans_attrib->value.u32 = atoi(auth_attrib->value);
			fd_list_insert_before(&app_lte_sm->ans_attributes,
					&ans_attrib->chain);
			free_attrib(auth_attrib);
		}
		if ((ret1 == 0) && (ret2 == 1) && (avp_attrib != NULL))
		{
			CHECK_MALLOC(ans_attrib = malloc(sizeof(struct avp_attribute)));
			memset(ans_attrib, 0, sizeof(struct avp_attribute));
			fd_list_init(&ans_attrib->chain, NULL);
			ans_attrib->attrib = "Auth-Grace-Period";
			ans_attrib->value.u32 = avp_attrib->value.u32;
			fd_list_insert_before(&app_lte_sm->ans_attributes,
					&ans_attrib->chain);
			free_avp_attrib(avp_attrib);
		}
		if ((ret1 == 0) && (ret2 == 0) && (auth_attrib != NULL) && (avp_attrib
				!= NULL))
		{
			CHECK_MALLOC(ans_attrib = malloc(sizeof(struct avp_attribute)));
			memset(ans_attrib, 0, sizeof(struct avp_attribute));
			fd_list_init(&ans_attrib->chain, NULL);
			ans_attrib->attrib = "Auth-Grace-Period";
			if (avp_attrib->value.u32 < atoi(auth_attrib->value))
			{
				ans_attrib->value.u32 = avp_attrib->value.u32;
			}
			else
			{
				ans_attrib->value.u32 = atoi(auth_attrib->value);
			}
			fd_list_insert_before(&app_lte_sm->ans_attributes,
					&ans_attrib->chain);
			free_attrib(auth_attrib);
			free_avp_attrib(avp_attrib);
		}
	}

	/* Auth-Session-State */
	{
		CHECK_FCT(app_lte_get_auth_attribute(&app_lte_sm->attributes, "Auth-Session-State", &auth_attrib,1, &ret2));
		if ((ret2 == 0) && (auth_attrib != NULL))
		{
			CHECK_MALLOC(ans_attrib = malloc(sizeof(struct avp_attribute)));
			memset(ans_attrib, 0, sizeof(struct avp_attribute));
			fd_list_init(&ans_attrib->chain, NULL);
			ans_attrib->attrib = "Auth-Session-State";
			ans_attrib->value.i32 = atoi(auth_attrib->value);
			fd_list_insert_before(&app_lte_sm->ans_attributes,
					&ans_attrib->chain);
			free_attrib(auth_attrib);
		}
	}

	/* Re-Auth-Request-Type */
	{
		CHECK_FCT(app_lte_get_auth_attribute(&app_lte_sm->attributes, "Re-Auth-Request-Type", &auth_attrib,1, &ret2));
		if ((ret2 == 0) && (auth_attrib != NULL))
		{
			CHECK_MALLOC(ans_attrib = malloc(sizeof(struct avp_attribute)));
			memset(ans_attrib, 0, sizeof(struct avp_attribute));
			fd_list_init(&ans_attrib->chain, NULL);
			ans_attrib->attrib = "Re-Auth-Request-Type";
			ans_attrib->value.i32 = atoi(auth_attrib->value);
			fd_list_insert_before(&app_lte_sm->ans_attributes,
					&ans_attrib->chain);
			free_attrib(auth_attrib);
		}
		else
		{
			ans_attrib = NULL;
			CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes, "Authorization-Lifetime", &ans_attrib,0, &ret1));
			if ((ret1 == 0) && (ans_attrib != NULL))
			{
				CHECK_MALLOC(ans_attrib = malloc(sizeof(struct avp_attribute)));
				memset(ans_attrib, 0, sizeof(struct avp_attribute));
				fd_list_init(&ans_attrib->chain, NULL);
				ans_attrib->attrib = "Re-Auth-Request-Type";
				ans_attrib->value.i32 = 0;
				fd_list_insert_before(&app_lte_sm->ans_attributes,
						&ans_attrib->chain);
			}
		}
	}

	/* Session-Timeout */
	{
		CHECK_FCT(app_lte_get_auth_attribute(&app_lte_sm->attributes, "Session-Timeout", &auth_attrib,1, &ret2));
		if ((ret2 == 0) && (auth_attrib != NULL))
		{
			CHECK_MALLOC(ans_attrib = malloc(sizeof(struct avp_attribute)));
			memset(ans_attrib, 0, sizeof(struct avp_attribute));
			fd_list_init(&ans_attrib->chain, NULL);
			ans_attrib->attrib = "Session-Timeout";
			ans_attrib->value.u32 = atoi(auth_attrib->value);
			fd_list_insert_before(&app_lte_sm->ans_attributes,
					&ans_attrib->chain);
			free_attrib(auth_attrib);
		}
	}

	/* Multi-Round-Time-Out */
	{
		CHECK_FCT(app_lte_get_auth_attribute(&app_lte_sm->attributes, "Multi-Round-Time-Out", &auth_attrib,1, &ret2));
		if ((ret2 == 0) && (auth_attrib != NULL))
		{
			CHECK_MALLOC(ans_attrib = malloc(sizeof(struct avp_attribute)));
			memset(ans_attrib, 0, sizeof(struct avp_attribute));
			fd_list_init(&ans_attrib->chain, NULL);
			ans_attrib->attrib = "Multi-Round-Time-Out";
			ans_attrib->value.u32 = atoi(auth_attrib->value);
			fd_list_insert_before(&app_lte_sm->ans_attributes,
					&ans_attrib->chain);
			free_attrib(auth_attrib);
		}
	}

	/* Acct-Interim-Interval */
	{
		CHECK_FCT(app_lte_get_auth_attribute(&app_lte_sm->attributes, "Acct-Interim-Interval", &auth_attrib,1, &ret2));
		if ((ret2 == 0) && (auth_attrib != NULL))
		{
			CHECK_MALLOC(ans_attrib = malloc(sizeof(struct avp_attribute)));
			memset(ans_attrib, 0, sizeof(struct avp_attribute));
			fd_list_init(&ans_attrib->chain, NULL);
			ans_attrib->attrib = "Acct-Interim-Interval";
			ans_attrib->value.u32 = atoi(auth_attrib->value);
			fd_list_insert_before(&app_lte_sm->ans_attributes,
					&ans_attrib->chain);
			free_attrib(auth_attrib);
		}
	}

	return 0;
}

#define	APP_LTE_STR	1
#define	APP_LTE_NUM	2

#define APP_LTE_OP_NO	0	//Not supported operator
#define	APP_LTE_OP_EQ	1	//==
#define	APP_LTE_OP_GT	2	//>
#define	APP_LTE_OP_LT	3	//<
#define	APP_LTE_OP_GE	4	//>=
#define	APP_LTE_OP_LE	5	//<=
#define	APP_LTE_OP_NE	6	//!=
#define	APP_LTE_OP_EX	7	//~=
#define EQ(A,B) A==B ? TRUE : FALSE
#define GT(A,B) A>B ? TRUE : FALSE
#define GE(A,B) A>=B ? TRUE : FALSE
#define LT(A,B) A<B ? TRUE : FALSE
#define LE(A,B) A<=B ? TRUE : FALSE
#define NE(A,B) A!=B ? TRUE : FALSE

int app_lte_get_operator(char *operator)
{
	TRACE_ENTRY("%p",operator);
	if (strcmp(operator, "==") == 0)
	{
		return APP_LTE_OP_EQ;
	}
	if (strcmp(operator, ">") == 0)
	{
		return APP_LTE_OP_GT;
	}
	if (strcmp(operator, "<") == 0)
	{
		return APP_LTE_OP_LT;
	}
	if (strcmp(operator, ">=") == 0)
	{
		return APP_LTE_OP_GE;
	}
	if (strcmp(operator, "<=") == 0)
	{
		return APP_LTE_OP_LE;
	}
	if (strcmp(operator, "!=") == 0)
	{
		return APP_LTE_OP_NE;
	}
	if (strcmp(operator, "~=") == 0)
	{
		return APP_LTE_OP_EX;
	}
	return APP_LTE_OP_NO;
}

boolean is_operator(int format_type, char * operator)
{
	TRACE_ENTRY("%d %p",format_type,operator);
	if ((format_type == APP_LTE_STR) && (strcmp(operator, "==") == 0 || strcmp(
			operator, "~=") == 0 || strcmp(operator, "!=") == 0))
	{
		return TRUE;
	}
	if ((format_type == APP_LTE_NUM) && (strcmp(operator, "~=") != 0))
	{
		return TRUE;
	}
	return FALSE;
}

union avp_value app_lte_get_num(char * num, enum dict_avp_basetype datatype)
{
	TRACE_ENTRY("%p %d",num,datatype);
	union avp_value val;
	switch (datatype)
	{
	case AVP_TYPE_INTEGER32://i32
		val.i32 = atoi(num);
		break;
	case AVP_TYPE_INTEGER64://i64
		val.i64 = atoll(num);
		break;
	case AVP_TYPE_UNSIGNED32://u32
		val.u32 = strtoul(num, NULL, 10);
		break;
	case AVP_TYPE_UNSIGNED64://u64
		val.u64 = strtoull(num, NULL, 10);
		break;
	case AVP_TYPE_FLOAT32://f32
		val.f32 = atof(num);
		break;
	case AVP_TYPE_FLOAT64://f64
		val.f64 = strtod(num, NULL);
		break;
	default:
		TRACE_DEBUG(INFO, "%sUnknown AVP Base Type.",APP_LTE_EXTENSION)
		memset(&val, 0, sizeof(val));
		;
	}
	return val;
}

boolean app_lte_check(union avp_value *A, char * B, char * operator, enum dict_avp_basetype datatype)
{
	TRACE_ENTRY("%p %p %p %d",A,B,operator,datatype);
	if (((datatype == AVP_TYPE_OCTETSTRING) && (is_operator(APP_LTE_STR,
			operator) == TRUE)) || ((datatype != AVP_TYPE_OCTETSTRING)
			&& (datatype != AVP_TYPE_GROUPED) && (is_operator(APP_LTE_NUM,
			operator) == TRUE)))
	{
		switch (app_lte_get_operator(operator))
		{
		case APP_LTE_OP_EQ:
			if ((datatype == AVP_TYPE_OCTETSTRING) && (is_operator(APP_LTE_STR,
					operator) == TRUE))
			{
				if (strcmp((char *)A->os.data, B) == 0)
					return TRUE;
				else
					return FALSE;
			}
			else if ((datatype != AVP_TYPE_OCTETSTRING) && (datatype
					!= AVP_TYPE_GROUPED) && (is_operator(APP_LTE_NUM, operator)
					== TRUE))
			{

				switch (datatype)
				{
				case AVP_TYPE_INTEGER32://i32
					return EQ(A->i32,app_lte_get_num(B, datatype).i32);
					break;
				case AVP_TYPE_INTEGER64://i64
					return EQ(A->i64,app_lte_get_num(B, datatype).i64);
					break;
				case AVP_TYPE_UNSIGNED32://u32
					return EQ(A->u32,app_lte_get_num(B, datatype).u32);
					break;
				case AVP_TYPE_UNSIGNED64://u64
					return EQ(A->u64,app_lte_get_num(B, datatype).u64);
					break;
				case AVP_TYPE_FLOAT32://f32
					return EQ(A->f32,app_lte_get_num(B, datatype).f32);
					break;
				case AVP_TYPE_FLOAT64://f64
					return EQ(A->f64,app_lte_get_num(B, datatype).f64);
					break;
				default:
					return FALSE;
				}
			}
			else
			{
				return FALSE;
			}
			break;
		case APP_LTE_OP_EX:
		{
			//string only
			boolean authorized = FALSE;
			if ((datatype == AVP_TYPE_OCTETSTRING) && (is_operator(APP_LTE_STR,
					operator) == TRUE))
			{
				regex_t rule_regexp;
				regcomp(&rule_regexp, B, REG_EXTENDED | REG_NOSUB | REG_ICASE);
				if (regexec(&rule_regexp, (char *)A->os.data, 0, NULL, 0) != 0)
				{
					authorized = FALSE;
				}
				else
				{
					authorized = TRUE;
				}
				regfree(&rule_regexp);
			}
			return authorized;
		}
		case APP_LTE_OP_GT:

			if ((datatype != AVP_TYPE_OCTETSTRING) && (datatype
					!= AVP_TYPE_GROUPED) && (is_operator(APP_LTE_NUM, operator)
					== TRUE))
			{
				switch (datatype)
				{
				case AVP_TYPE_INTEGER32://i32
					return GT(A->i32, app_lte_get_num(B, datatype).i32);
					break;
				case AVP_TYPE_INTEGER64://i64
					return GT(A->i64, app_lte_get_num(B, datatype).i64);
					break;
				case AVP_TYPE_UNSIGNED32://u32
					return GT(A->u32, app_lte_get_num(B, datatype).u32);
					break;
				case AVP_TYPE_UNSIGNED64://u64
					return GT(A->u64, app_lte_get_num(B, datatype).u64);
					break;
				case AVP_TYPE_FLOAT32://f32
					return GT(A->f32, app_lte_get_num(B, datatype).f32);
					break;
				case AVP_TYPE_FLOAT64://f64
					return GT(A->f64, app_lte_get_num(B, datatype).f64);
					break;
				default:
					return FALSE;
				}
			}
			else
			{
				return FALSE;
			}
			break;
		case APP_LTE_OP_GE:
			if ((datatype != AVP_TYPE_OCTETSTRING) && (datatype
					!= AVP_TYPE_GROUPED) && (is_operator(APP_LTE_NUM, operator)
					== TRUE))
			{
				switch (datatype)
				{
				case AVP_TYPE_INTEGER32://i32
					return GE(A->i32,app_lte_get_num(B, datatype).i32);
					break;
				case AVP_TYPE_INTEGER64://i64
					return GE(A->i64,app_lte_get_num(B, datatype).i64);
					break;
				case AVP_TYPE_UNSIGNED32://u32
					return GE(A->u32,app_lte_get_num(B, datatype).u32);
					break;
				case AVP_TYPE_UNSIGNED64://u64
					return GE(A->u64,app_lte_get_num(B, datatype).u64);
					break;
				case AVP_TYPE_FLOAT32://f32
					return GE(A->f32,app_lte_get_num(B, datatype).f32);
					break;
				case AVP_TYPE_FLOAT64://f64
					return GE(A->f64,app_lte_get_num(B, datatype).f64);
					break;
				default:
					return FALSE;
				}
			}
			else
			{
				return FALSE;
			}
			break;
		case APP_LTE_OP_LT:
			if ((datatype != AVP_TYPE_OCTETSTRING) && (datatype
					!= AVP_TYPE_GROUPED) && (is_operator(APP_LTE_NUM, operator)
					== TRUE))
			{
				switch (datatype)
				{
				case AVP_TYPE_INTEGER32://i32
					return LT(A->i32, app_lte_get_num(B, datatype).i32);
					break;
				case AVP_TYPE_INTEGER64://i64
					return LT(A->i64, app_lte_get_num(B, datatype).i64);
					break;
				case AVP_TYPE_UNSIGNED32://u32
					return LT(A->u32, app_lte_get_num(B, datatype).u32);
					break;
				case AVP_TYPE_UNSIGNED64://u64
					return LT(A->u64, app_lte_get_num(B, datatype).u64);
					break;
				case AVP_TYPE_FLOAT32://f32
					return LT(A->f32, app_lte_get_num(B, datatype).f32);
					break;
				case AVP_TYPE_FLOAT64://f64
					return LT(A->f64, app_lte_get_num(B, datatype).f64);
					break;
				default:
					return FALSE;
				}
			}
			else
			{
				return FALSE;
			}
			break;
		case APP_LTE_OP_LE:
			if ((datatype != AVP_TYPE_OCTETSTRING) && (datatype
					!= AVP_TYPE_GROUPED) && (is_operator(APP_LTE_NUM, operator)
					== TRUE))
			{
				switch (datatype)
				{
				case AVP_TYPE_INTEGER32://i32
					return LE(A->i32, app_lte_get_num(B, datatype).i32);
					break;
				case AVP_TYPE_INTEGER64://i64
					return LE(A->i64, app_lte_get_num(B, datatype).i64);
					break;
				case AVP_TYPE_UNSIGNED32://u32
					return LE(A->u32, app_lte_get_num(B, datatype).u32);
					break;
				case AVP_TYPE_UNSIGNED64://u64
					return LE(A->u64, app_lte_get_num(B, datatype).u64);
					break;
				case AVP_TYPE_FLOAT32://f32
					return LE(A->f32, app_lte_get_num(B, datatype).f32);
					break;
				case AVP_TYPE_FLOAT64://f64
					return LE(A->f64, app_lte_get_num(B, datatype).f64);
					break;
				default:
					return FALSE;
				}
			}
			else
			{
				return FALSE;
			}
			break;
		case APP_LTE_OP_NE:
			if ((datatype == AVP_TYPE_OCTETSTRING) && (is_operator(APP_LTE_STR,
					operator) == TRUE))
			{
				if (strcmp((char *)A->os.data, B) != 0)
					return TRUE;
				else
					return FALSE;
			}
			else if ((datatype != AVP_TYPE_OCTETSTRING) && (datatype
					!= AVP_TYPE_GROUPED) && (is_operator(APP_LTE_NUM, operator)
					== TRUE))
			{
				switch (datatype)
				{
				case AVP_TYPE_INTEGER32://i32
					return NE(A->i32, app_lte_get_num(B, datatype).i32);
					break;
				case AVP_TYPE_INTEGER64://i64
					return NE(A->i64, app_lte_get_num(B, datatype).i64);
					break;
				case AVP_TYPE_UNSIGNED32://u32
					return NE(A->u32, app_lte_get_num(B, datatype).u32);
					break;
				case AVP_TYPE_UNSIGNED64://u64
					return NE(A->u64, app_lte_get_num(B, datatype).u64);
					break;
				case AVP_TYPE_FLOAT32://f32
					return NE(A->f32, app_lte_get_num(B, datatype).f32);
					break;
				case AVP_TYPE_FLOAT64://f64
					return NE(A->f64, app_lte_get_num(B, datatype).f64);
					break;
				default:
					return FALSE;
				}
			}
			else
			{
				return FALSE;
			}
			break;
		}
	}
	return FALSE;
}

char * app_lte_attribute_operator(char * op, int * toadd, boolean *isrule)
{
	TRACE_ENTRY("%p %p %p",op,toadd,isrule);
	char * attribute_op;

	if (op[0] == '+')
	{
		*toadd = 1;
	}
	else if (op[strlen(op) - 1] == '+')
	{
		*toadd = 2;
	}
	else
	{
		*toadd = 0;
	}

	switch (*toadd)
	{
	case 1:
		attribute_op = calloc(strlen(op), sizeof(char *));
		memcpy(attribute_op, op + 1, strlen(op) - 1);
		break;
	case 2:
		attribute_op = calloc(strlen(op), sizeof(char *));
		memcpy(attribute_op, op, strlen(op) - 1);
		break;
	default:
		attribute_op = calloc(strlen(op) + 1, sizeof(char *));
		memcpy(attribute_op, op, strlen(op));
	}
	if (strcmp(attribute_op, "=") == 0)
	{
		*isrule = FALSE;
		*toadd = 2;
	}
	else
	{
		*isrule = TRUE;
	}

	return attribute_op;
}

int app_lte_answer_set_attribute_valueA(union avp_value *A, int *tofree, enum dict_avp_basetype datatype, union avp_value * rval)
{
	TRACE_ENTRY("%p %p %d %p",A,tofree,datatype,rval);
	if (datatype == AVP_TYPE_OCTETSTRING)
	{
		CHECK_MALLOC(rval->os.data=malloc(A->os.len));
		memcpy(rval->os.data,A->os.data,A->os.len);
		rval->os.len = A->os.len;
		*tofree = 1;
	}
	else
	{
		*rval = *A;
	}
	return 0;
}

int app_lte_answer_set_attribute_valueB(char * B, int *tofree, enum dict_avp_basetype datatype, union avp_value * rval)
{
	TRACE_ENTRY("%p %p %d %p",B,tofree,datatype,rval);
	if (datatype == AVP_TYPE_OCTETSTRING)
	{
		CHECK_MALLOC(rval->os.data=malloc(strlen(B)));
		memcpy(rval->os.data,B,strlen(B));
		rval->os.len = strlen(B);

		*tofree = 1;
	}
	else
	{

		*rval = app_lte_get_num(B, datatype);
	}

	return 0;
}

static int app_lte_attribute_limits(char * attrib, int * max, int *ret)
{
	TRACE_ENTRY("%p %p %p",attrib,max,ret);
	if (attrib == NULL)
	{
		return EINVAL;
	}
	int i;
	for (i = 0; i < sizeof(auth_avps); i++)
	{
		if (strcmp(auth_avps[i].avp_attribute, attrib) == 0)
		{
			*max = auth_avps[i].max;
			*ret = 0;
			return 0;
		}
	}
	*max = 0;
	*ret = 1;
	return 0;
}

static int app_lte_answer_authorization_attributes(struct app_lte_state_machine * app_lte_sm)
{
	TRACE_ENTRY("%p",app_lte_sm);

	if (app_lte_sm == NULL)
	{
		return EINVAL;
	}
	boolean checked = TRUE;

	struct fd_list * attrib;
	struct auth_attribute * auth_attrib;
	struct avp_attribute * avp_attrib;
	int ret;

	for (attrib = (&app_lte_sm->attributes)->next; attrib
			!= (&app_lte_sm->attributes); attrib = attrib->next)
	{
		avp_attrib = NULL;
		auth_attrib = (struct auth_attribute *) attrib;

		int toadd = 0;
		boolean isrule = FALSE;
		char * op;

		op = app_lte_attribute_operator(auth_attrib->op, &toadd, &isrule);

		struct dict_object * dobj;
		struct dict_avp_data avpdata;
		fd_dict_search(fd_g_config->cnf_dict, DICT_AVP, AVP_BY_NAME,
				auth_attrib->attrib, &dobj, ENOENT);
		fd_dict_getval(dobj, &avpdata);

		checked = TRUE;
		if (isrule == TRUE)
		{
			CHECK_FCT(app_lte_get_avp_attribute(&app_lte_sm->req_attributes,auth_attrib->attrib,&avp_attrib,0,&ret));
			if (ret == 0)
			{
				checked = app_lte_check(&avp_attrib->value, auth_attrib->value,
						op, avpdata.avp_basetype);
			}
		}
		if (checked == TRUE && toadd != 0)
		{

			struct avp_attribute * ans_attrib;
			int max = 0;
			app_lte_attribute_limits(auth_attrib->attrib, &max, &ret);
			if ((ret == 0) && (max != 0))
			{
				if (max == 1)//only one
				{
					int ret = 0;
					app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,
							auth_attrib->attrib, &ans_attrib, 0, &ret);
					if (ret == 1)
					{
						ans_attrib = NULL;
						CHECK_MALLOC(ans_attrib = malloc(sizeof(struct avp_attribute)));
						memset(ans_attrib, 0, sizeof(struct avp_attribute));
						fd_list_init(&ans_attrib->chain, NULL);
						ans_attrib->attrib = strdup(auth_attrib->attrib);
						if (toadd == 1)
						{
							app_lte_answer_set_attribute_valueA(
									&avp_attrib->value, &ans_attrib->tofree,
									avpdata.avp_basetype, &ans_attrib->value);
						}
						else
						{
							app_lte_answer_set_attribute_valueB(
									auth_attrib->value, &ans_attrib->tofree,
									avpdata.avp_basetype, &ans_attrib->value);
						}
						fd_list_insert_before(&app_lte_sm->ans_attributes,
								&ans_attrib->chain);

					}
					else
					{
						//an answer avp is already added
					}
				}
				else
				{
					ans_attrib = NULL;
					CHECK_MALLOC(ans_attrib = malloc(sizeof(struct avp_attribute)));
					memset(ans_attrib, 0, sizeof(struct avp_attribute));
					fd_list_init(&ans_attrib->chain, NULL);
					ans_attrib->attrib = auth_attrib->attrib;
					if (toadd == 1)
					{
						app_lte_answer_set_attribute_valueA(&avp_attrib->value,
								&ans_attrib->tofree, avpdata.avp_basetype,
								&ans_attrib->value);
					}
					else
					{
						app_lte_answer_set_attribute_valueB(auth_attrib->value,
								&ans_attrib->tofree, avpdata.avp_basetype,
								&ans_attrib->value);
					}
					fd_list_insert_before(&app_lte_sm->ans_attributes,
							&ans_attrib->chain);
				}
			}
		}
		if (checked == FALSE)
		{

			app_lte_sm->authorized = FALSE;
			return 0;
		}
	}
	app_lte_sm->authorized = checked;
	return 0;

	return 0;
}


static int app_lte_policy_decision(struct app_lte_state_machine * app_lte_sm, struct app_lte_eap_interface *eap_i)
{
	TRACE_ENTRY("%p %p",app_lte_sm,eap_i);

	// app_lte_sm->result_code = 4001; /* DIAMETER_AUTHENTICATION_REJECTED 4001 */
	// app_lte_sm->authFailure = TRUE;
	// TRACE_DEBUG(FULL+1,"%s Auth failure: Authentication Rejected ",APP_LTE_EXTENSION);
	// return 0;
}

static int app_lte_add_avps(struct app_lte_state_machine * app_lte_sm, struct msg * ans, struct msg * req)
{
	TRACE_ENTRY("%p %p %p",app_lte_sm,ans,req);

	struct avp * avp, *avp2;
	struct avp_hdr * avpdata;
	union avp_value avp_val;
	int ret = 0;

	/* Origin-Host AVP and Origin-Realm AVP */
	{
		CHECK_FCT( fd_msg_add_origin ( ans, 0 ) );
	}

	/* Auth-Application-Id AVP */
	{
		CHECK_FCT(fd_msg_avp_new(dataobj_auth_application_id, 0, &avp));
		avp_val.u32 = lte_config->application_id;
		CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
		CHECK_FCT(fd_msg_avp_add(ans, MSG_BRW_LAST_CHILD, avp));
	}

	/* CC-Request-Type AVP */
	{
		CHECK_FCT(fd_msg_avp_new(dataobj_cc_request_type, 0, &avp));
		CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
		CHECK_FCT(fd_msg_avp_add(ans, MSG_BRW_LAST_CHILD, avp));
	}

	{
		CHECK_FCT(fd_msg_avp_new(dataobj_subscription_id_data, 0, &avp));
		avp_val.os.data = app_lte_sm->lte_sm.user.userid;
		avp_val.os.len = app_lte_sm->lte_sm.user.useridLength;
		CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
		CHECK_FCT(fd_msg_avp_add(ans, MSG_BRW_LAST_CHILD, avp));
	}
	return 0;
}

static int app_lte_add_user_sessions_avps(struct app_lte_state_machine * app_lte_sm, struct msg * ans)
{
	TRACE_ENTRY("%p %p",app_lte_sm,ans);

	struct avp * avp;
	union avp_value avp_val;
	int ret;

	/* Authorization-Lifetime AVP */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Authorization-Lifetime",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_authorization_lifetime, 0, &avp));
			avp_val.u32 = ans_attrib->value.u32;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}
	}

	/* Auth-Grace-Period AVP */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Auth-Grace-Period",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_auth_grace_period, 0, &avp));
			avp_val.u32 = ans_attrib->value.u32;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}
	}

	/* Auth-Session-State AVP */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Auth-Session-State",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_auth_session_state, 0, &avp));
			avp_val.i32 = ans_attrib->value.i32;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}
	}

	/* Re-Auth-Request-Type AVP */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Re-Auth-Request-Type",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_re_auth_request_type, 0, &avp));
			avp_val.i32 = ans_attrib->value.i32;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}
	}

	/* Session-Timeout AVP */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Session-Timeout",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_session_timeout, 0, &avp));
			avp_val.u32 = ans_attrib->value.u32;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}
	}

	/* Acct-Interim-Interval AVP */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Acct-Interim-Interval",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_acct_interim_interval, 0, &avp));
			avp_val.u32 = ans_attrib->value.u32;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}
	}
	return 0;
}

static int app_lte_add_authorization_avps(struct app_lte_state_machine * app_lte_sm, struct msg * ans)
{

	TRACE_ENTRY("%p %p",app_lte_sm, ans);

	struct avp * avp;
	union avp_value avp_val;
	int ret;

	if (app_lte_sm == NULL)
	{
		return EINVAL;
	}
	if (ans == NULL)
	{
		return EINVAL;
	}

	/* Reply-Message */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Reply-Message",&ans_attrib,1,&ret));
		while ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_reply_message, 0, &avp));
			avp_val.os.data = ans_attrib->value.os.data;
			avp_val.os.len = ans_attrib->value.os.len;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
			CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Reply-Message",&ans_attrib,1,&ret));
		}

	}

	/* Service-Type */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Service-Type",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_service_type, 0, &avp));
			avp_val.i32 = ans_attrib->value.i32;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}
	}

	/* Callback-Number */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Callback-Number",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_callback_number, 0, &avp));
			avp_val.os.data = ans_attrib->value.os.data;
			avp_val.os.len = ans_attrib->value.os.len;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}
	}

	/* Callback-Id */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Callback-Id",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_callback_id, 0, &avp));
			avp_val.os.data = ans_attrib->value.os.data;
			avp_val.os.len = ans_attrib->value.os.len;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}
	}

	/* Idle-Timeout */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Idle-Timeout",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_idle_timeout, 0, &avp));
			avp_val.u32 = ans_attrib->value.u32;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}
	}

	/* NAS-Filter-Rule */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"NAS-Filter-Rule",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_nas_filter_rule, 0, &avp));
			avp_val.u32 = ans_attrib->value.u32;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}
	}

	/* Filter-Id */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Filter-Id",&ans_attrib,1,&ret));
		while ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_filter_id, 0, &avp));
			avp_val.os.data = ans_attrib->value.os.data;
			avp_val.os.len = ans_attrib->value.os.len;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
			CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Filter-Id",&ans_attrib,1,&ret));
		}

	}

	/* Configuration-Token */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Configuration-Token",&ans_attrib,1,&ret));
		while ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_configuration_token, 0, &avp));
			avp_val.os.data = ans_attrib->value.os.data;
			avp_val.os.len = ans_attrib->value.os.len;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
			CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Configuration-Token",&ans_attrib,1,&ret));
		}
	}

	/* QoS-Filter-Rule */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"QoS-Filter-Rule",&ans_attrib,1,&ret));
		while ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_qos_filter_rule, 0, &avp));
			avp_val.os.data = ans_attrib->value.os.data;
			avp_val.os.len = ans_attrib->value.os.len;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
			CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"QoS-Filter-Rule",&ans_attrib,1,&ret));
		}

	}

	/* Framed-Protocol */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-Protocol",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_framed_protocol, 0, &avp));
			avp_val.i32 = ans_attrib->value.i32;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}
	}

	/* Framed-Routing */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-Routing",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_framed_routing, 0, &avp));
			avp_val.i32 = ans_attrib->value.i32;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}

	}

	/* Framed-MTU */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-MTU",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_framed_mtu, 0, &avp));
			avp_val.u32 = ans_attrib->value.u32;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}
	}

	/* Framed-Compression */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-Compression",&ans_attrib,1,&ret));
		while ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_framed_compression, 0, &avp));
			avp_val.i32 = ans_attrib->value.i32;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
			CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-Compression",&ans_attrib,1,&ret));
		}

	}
	/* Framed-IP-Address */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-IP-Address",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_framed_ip_address, 0, &avp));
			avp_val.os.data = ans_attrib->value.os.data;
			avp_val.os.len = ans_attrib->value.os.len;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}
	}

	/* Framed-IP-Netmask */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-IP-Netmask",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_framed_ip_netmask, 0, &avp));
			avp_val.os.data = ans_attrib->value.os.data;
			avp_val.os.len = ans_attrib->value.os.len;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}
	}

	/* Framed-Route */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-Route",&ans_attrib,1,&ret));
		while ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_framed_route, 0, &avp));
			avp_val.os.data = ans_attrib->value.os.data;
			avp_val.os.len = ans_attrib->value.os.len;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
			CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-Route",&ans_attrib,1,&ret));
		}
	}

	/* Framed-Pool */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-Pool",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_framed_pool, 0, &avp));
			avp_val.os.data = ans_attrib->value.os.data;
			avp_val.os.len = ans_attrib->value.os.len;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}
	}

	/* Framed-Interface-Id */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-Interface-Id",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_framed_interface_id, 0, &avp));
			avp_val.u64 = ans_attrib->value.u64;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}
	}

	/* Framed-IPv6-Prefix */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-IPv6-Prefix",&ans_attrib,1,&ret));
		while ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_framed_ipv6_prefix, 0, &avp));
			avp_val.os.data = ans_attrib->value.os.data;
			avp_val.os.len = ans_attrib->value.os.len;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
			CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-IPv6-Prefix",&ans_attrib,1,&ret));
		}
	}

	/* Framed-IPv6-Route */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-IPv6-Route",&ans_attrib,1,&ret));
		while ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_framed_ipv6_route, 0, &avp));
			avp_val.os.data = ans_attrib->value.os.data;
			avp_val.os.len = ans_attrib->value.os.len;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
			CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-IPv6-Route",&ans_attrib,1,&ret));
		}
	}

	/* Framed-IPv6-Pool */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-IPv6-Pool",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_framed_ipv6_pool, 0, &avp));
			avp_val.os.data = ans_attrib->value.os.data;
			avp_val.os.len = ans_attrib->value.os.len;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}
	}

	/* Framed-IPX-Network */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-IPX-Network",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_framed_ipx_network, 0, &avp));
			avp_val.u32 = ans_attrib->value.u32;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}

	}
	/* Framed-AppleTalk-Link */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-AppleTalk-Link",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_framed_appletalk_link, 0, &avp));
			avp_val.u32 = ans_attrib->value.u32;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}

	}

	/* Framed-AppleTalk-Network */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-AppleTalk-Network",&ans_attrib,1,&ret));
		while ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_framed_appletalk_network, 0, &avp));
			avp_val.u32 = ans_attrib->value.u32;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
			CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-AppleTalk-Network",&ans_attrib,1,&ret));
		}

	}

	/* Framed-AppleTalk-Zone */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-AppleTalk-Zone",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_framed_appletalk_zone, 0, &avp));
			avp_val.os.data = ans_attrib->value.os.data;
			avp_val.os.len = ans_attrib->value.os.len;
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_ans_attrib(ans_attrib);
		}
	}

	/* Tunneling */
	//

	/* State */
	//
	return 0;
}

static int app_lte_add_result_code(struct app_lte_state_machine * app_lte_sm, struct msg * ans, struct session * sess)
{
	TRACE_ENTRY("%p %p",app_lte_sm,ans);
	struct avp * avp;
	union avp_value avp_val;
	int ret;

	/* Result-Code AVP */
	CHECK_FCT(fd_msg_avp_new(dataobj_result_code, 0, &avp));
	avp_val.u32 = app_lte_sm->result_code;
	CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
	/* Add Result-Code AVP to the message */
	CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );

	/* Multi_Round_Time_Out AVP */
	if (app_lte_sm->result_code == 1001)
	{
		struct timespec sess_timeout;
		CHECK_FCT(fd_msg_avp_new(dataobj_multi_round_time_out, 0, &avp));
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Multi-Round-Time-Out",&ans_attrib,1,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			avp_val.u32 = ans_attrib->value.u32;
			/* Update the session timeout with multi-round-time-out value */
			CHECK_SYS(clock_gettime(CLOCK_REALTIME,&sess_timeout));
			sess_timeout.tv_sec += lte_config->multi_round_time_out;
			CHECK_FCT(fd_sess_settimeout(sess, &sess_timeout));
			free_ans_attrib(ans_attrib);
		}
		else
		{
			avp_val.u32 = lte_config->multi_round_time_out;
			/* Update the session timeout with multi-round-time-out value */
			CHECK_SYS(clock_gettime(CLOCK_REALTIME,&sess_timeout));
			sess_timeout.tv_sec += lte_config->multi_round_time_out;
			CHECK_FCT(fd_sess_settimeout(sess, &sess_timeout));
		}
		CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
		CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
	}
	return 0;
}

static int app_lte_add_eap_payload(struct app_lte_state_machine * app_lte_sm, struct msg * ans, struct app_lte_eap_interface *eap_i)
{
	TRACE_ENTRY("%p %p",app_lte_sm,ans);
	struct avp * avp;
	union avp_value avp_val;
	int ret;
	u32 Framed_MTU = 1500; //1500 default value
	u32 NAS_Port_Type_HeaderLength = 4;
	int EAP_Max_Length = 0;

	/* get Framed-MTU AVP value */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"Framed-MTU",&ans_attrib,0,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			Framed_MTU = ans_attrib->value.u32;
		}
	}

	/* get NAS-Port-Type AVP value */
	{
		struct avp_attribute * ans_attrib;
		CHECK_FCT(app_lte_get_ans_attribute(&app_lte_sm->ans_attributes,"NAS-Port-Type",&ans_attrib,0,&ret));
		if ((ret == 0) && (ans_attrib != NULL))
		{
			// = ans_attrib->value.i32;
		}
	}

	//TD take the link type into consideration when calculating EAP_MAX_Length
	EAP_Max_Length = Framed_MTU - NAS_Port_Type_HeaderLength;
	return 0;
}

static int app_lte_send(struct msg ** rmsg)
{
	TRACE_ENTRY("%p",rmsg);
	CHECK_FCT( fd_msg_send( rmsg, NULL, NULL));
	return 0;
}

static int app_lte_add_eap_success_avps(struct app_lte_state_machine * app_lte_sm, struct msg * ans, struct app_lte_eap_interface *eap_i)
{
	TRACE_ENTRY("%p %p %p",app_lte_sm,ans,eap_i);
	struct avp * avp;
	union avp_value avp_val;
	int ret;

	/* EAP-Key-Name AVP */
	struct avp_attribute * avp_attrib = NULL;

	CHECK_FCT(app_lte_get_avp_attribute(&app_lte_sm->req_attributes,"EAP-Key-Name",&avp_attrib,1,&ret))
	if ((avp_attrib != NULL) && (ret != 1))
	{
		if (avp_attrib->value.os.len == 0)
		{
			CHECK_FCT(fd_msg_avp_new(dataobj_eap_key_name, 0, &avp));
			avp_val.os.data = NULL;//
			avp_val.os.len = 0;//
			CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
			CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
			free_avp_attrib(avp_attrib);
		}
	}

	return 0;
}

int app_lte_authorize(struct app_lte_state_machine * app_lte_sm)
{
	TRACE_ENTRY("%p",app_lte_sm);

	CHECK_FCT(app_lte_authorization_get_attribs(&app_lte_sm->lte_sm.user, &app_lte_sm->attributes));

	app_lte_sm->authorized = TRUE;

	CHECK_FCT_DO(app_lte_answer_authorization_attributes(app_lte_sm),
	);
	if (app_lte_sm->authorized == FALSE)
	{
		app_lte_sm->result_code = 4001; /* DIAMETER_AUTHENTICATION_REJECTED 4001 */
	}
	return 0;
}

static int app_lte_add_accounting_eap_auth_method(struct app_lte_state_machine * app_lte_sm, struct msg * ans)
{
	TRACE_ENTRY("%p %p",app_lte_sm,ans);
	int i = 0;
	struct avp * avp;
	union avp_value avp_val;
	/* Accounting-EAP-Auth-Method AVP */
	while (i < app_lte_sm->lte_sm.user.methodId)
	{
		CHECK_FCT(fd_msg_avp_new(dataobj_accounting_eap_auth_method, 0, &avp));

		// avp_val.u64 = (u64) (((app_lte_sm->lte_sm.user.methods[i].vendor)
		// 		* pow((double) 2, (double) 32))
		// 		+ app_lte_sm->lte_sm.user.methods[i].method);
		CHECK_FCT(fd_msg_avp_setvalue(avp, &avp_val));
		CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, avp ) );
		i++;
	}
	return 0;
}

static int app_lte_add_eap_reissued_payload(struct msg * ans, struct msg * req)
{
	TRACE_ENTRY("%p %p", ans, req);
	struct avp * avp, *re_avp;
	union avp_value avp_val;
	struct avp_hdr * avphdr;

	if ((ans == NULL) || (req == NULL))
	{
		return EINVAL;
	}
	avp = NULL;
	CHECK_FCT(fd_msg_search_avp(req, dataobj_cc_request_type, &avp));
	if (avp != NULL)
	{
		CHECK_FCT( fd_msg_avp_hdr(avp, &avphdr));
		CHECK_FCT( fd_msg_avp_new(dataobj_eap_reissued_payload, 0, &re_avp));
		CHECK_MALLOC(avp_val.os.data=malloc(avphdr->avp_value->os.len));
		memcpy(avp_val.os.data,avphdr->avp_value->os.data,avphdr->avp_value->os.len);
		avp_val.os.len = avphdr->avp_value->os.len;
		CHECK_FCT(fd_msg_avp_setvalue(re_avp, &avp_val));
		CHECK_FCT( fd_msg_avp_add( ans, MSG_BRW_LAST_CHILD, re_avp ) );
	}
	else
	{
		TRACE_DEBUG(INFO,"%sUnable to find EAP-Payload AVP in received Diameter-EAP-Request.",APP_LTE_EXTENSION);
		return 1;
	}

	return 0;
}


static int app_lte_server_callback(struct msg ** rmsg, struct avp * ravp, struct session * sess, void * opaque, enum disp_action * action)
{
	fprintf(stderr, "ECHO app_lte_server_callback ");
	TRACE_ENTRY("%p %p %p %p", rmsg, ravp, sess, action);

	struct sess_state * app_lte_sess_data = NULL;
	struct app_lte_state_machine * app_lte_sm = NULL;
	struct msg *req, *ans = NULL;
	boolean non_fatal_error = FALSE;

	if (rmsg == NULL)
		return EINVAL;

	req = *rmsg;

	struct avp * a;
	
	CHECK_FCT_DO(fd_sess_state_retrieve(app_lte_server_reg, sess, &app_lte_sess_data), {TRACE_DEBUG(INFO,"%s retrieving session state failed.",APP_LTE_EXTENSION); goto s_end;});
	CHECK_MALLOC_DO(app_lte_sm = malloc(sizeof(struct app_lte_state_machine)), goto s_end);
	memset(app_lte_sm, 0, sizeof(struct app_lte_state_machine));

	fprintf(stderr, "ECHO Test-Request received from ");
	CHECK_FCT( fd_msg_search_avp ( *rmsg, dataobj_origin_host, &a) );
	if (a) {
		struct avp_hdr * hdr;
		CHECK_FCT( fd_msg_avp_hdr( a, &hdr ) );
		fprintf(stderr, "'%.*s'", (int)hdr->avp_value->os.len, hdr->avp_value->os.data);
	} else {
		fprintf(stderr, "no_Origin-Host");
	}
	fprintf(stderr, ", replying...\n");


	if (app_lte_sess_data)
	{
		app_lte_sm->state = APP_LTE_RECEIVED;
	}
	else
	{
		app_lte_sm->state = APP_LTE_DISABLED;
	}

	while (app_lte_sm->state != APP_LTE_IDLE && app_lte_sm->state != APP_LTE_END)
	{
		switch (app_lte_sm->state)
		{
			case APP_LTE_DISABLED:
				if (rmsg)
				{
					app_lte_sm->state = APP_LTE_INITIALIZE;
				}
				else
				{
					TRACE_DEBUG(INFO,"%sReceived empty Diameter EAP Request message.",APP_LTE_EXTENSION);
					goto s_end;
				}
				break;

			case APP_LTE_INITIALIZE:

				CHECK_FCT_DO(app_lte_initialize_app_lte_sm(app_lte_sm,app_lte_sess_data), {	TRACE_DEBUG(INFO,"%s Initializing LTE state machine failed.",APP_LTE_EXTENSION); goto s_end;});
				TRACE_DEBUG(FULL+1,"%sParsing AVPs",APP_LTE_EXTENSION);
				CHECK_FCT_DO(app_lte_parse_avps(app_lte_sm, req), TRACE_DEBUG(INFO,"%s Unable to parse LTE-Request AVPs.",APP_LTE_EXTENSION));

				if ((app_lte_sm->result_code != 0))
				{
					app_lte_sm->state = APP_LTE_SEND_ERROR_MSG;
				}
				else
				{
					app_lte_sm->state = APP_LTE_DIAMETER_EAP_ANSWER;
				}
				break;

			case APP_LTE_RECEIVED:
				fprintf(stderr, "ECHO APP_LTE_RECEIVED ");
				CHECK_FCT_DO(app_lte_initialize_app_lte_sm(app_lte_sm,app_lte_sess_data), { TRACE_DEBUG(INFO,"%s Initializing LTE state machine failed.",APP_LTE_EXTENSION); goto s_end;});
				TRACE_DEBUG(FULL+1,"%sParsing AVPs",APP_LTE_EXTENSION);
				CHECK_FCT_DO(app_lte_parse_avps(app_lte_sm, req), TRACE_DEBUG(INFO,"%s Unable to parse Diameter-EAP-Request AVPs.",APP_LTE_EXTENSION));

				if (app_lte_sm->result_code != 0)
				{
					app_lte_sm->state = APP_LTE_SEND_ERROR_MSG;
				}
				else
				{
					app_lte_sm->state = APP_LTE_DIAMETER_EAP_ANSWER;
				}
				break;

			case APP_LTE_AUTHORIZATION_VERIFY:
				app_lte_sm->verify_authorization = TRUE;
				TRACE_DEBUG(FULL+1,"%sVerify authorization",APP_LTE_EXTENSION)
				;
				CHECK_FCT_DO(app_lte_authorize(app_lte_sm),
						{	TRACE_DEBUG(INFO,"%s Authorization check process failed.",APP_LTE_EXTENSION); goto s_end;})
				;
				app_lte_sm->state = APP_LTE_SELECT_DECISION;

				break;

			case APP_LTE_DIAMETER_EAP_ANSWER:
				fprintf(stderr, "\nECHO APP_LTE_DIAMETER_EAP_ANSWER ");
				TRACE_DEBUG(FULL+1,"%screate LTE Answer",APP_LTE_EXTENSION);
				CHECK_FCT_DO(fd_msg_new_answer_from_req(fd_g_config->cnf_dict, rmsg, 0), goto s_end);
				ans = *rmsg;
				TRACE_DEBUG(FULL+1,"%sAdding AVPs to LTE Answer.",APP_LTE_EXTENSION);
				CHECK_FCT_DO( app_lte_add_avps(app_lte_sm, ans,req), {TRACE_DEBUG(INFO,"%s Unable to add AVPs to Answer message.",APP_LTE_EXTENSION); goto s_end;});
				if (app_lte_sm->authFailure == FALSE)
				{
					TRACE_DEBUG(FULL+1,"%sSelect authentication attributes.",APP_LTE_EXTENSION);
					CHECK_FCT_DO(app_lte_authentication_get_attribs(&app_lte_sm->lte_sm.user, &app_lte_sm->attributes), {TRACE_DEBUG(INFO,"%s Unable to get user's session attributes.",APP_LTE_EXTENSION); goto s_end;});
					TRACE_DEBUG(FULL+1,"%sCreate answer authentication attributes.",APP_LTE_EXTENSION);
					CHECK_FCT_DO(app_lte_answer_avp_attributes(app_lte_sm), {TRACE_DEBUG(INFO,"%s Unable to generate answer attributes.",APP_LTE_EXTENSION); goto s_end;});

					if (app_lte_sm->authSuccess == FALSE)
					{
						fprintf(stderr, "\nECHO AUTHENTICATING FAILURE ");
						app_lte_sm->state = APP_LTE_SEND_FAILURE;
					}
					else
					{
						fprintf(stderr, "\nECHO AUTHENTICATING SUCCESS ");
						app_lte_sm->state = APP_LTE_SEND_SUCCESS;
					}
				}
				else
				{
					app_lte_sm->state = APP_LTE_SEND_FAILURE;
				}
				break;

			case APP_LTE_SEND_FAILURE:
				fprintf(stderr, "\nECHO APP_LTE_SEND_FAILURE ");
				TRACE_DEBUG(FULL+1,"%sAdding Result Code AVP to LTE-Answer.",APP_LTE_EXTENSION);
				CHECK_FCT_DO( app_lte_add_result_code(app_lte_sm, ans, sess),{TRACE_DEBUG(INFO,"%s Adding Result-Code AVP failed.",APP_LTE_EXTENSION); goto s_end;});
				TRACE_DEBUG(FULL+1,"%sAdding EAP-Payload to LTE-Answer.",APP_LTE_EXTENSION);

				LOG_N("%s Auth FAIL: %.*s",APP_LTE_EXTENSION, app_lte_sm->lte_sm.user.useridLength, app_lte_sm->lte_sm.user.userid);
				
				CHECK_FCT_DO( app_lte_send(rmsg), goto s_end);

				app_lte_sm->state = APP_LTE_END;
				break;

			case APP_LTE_SEND_SUCCESS:
				fprintf(stderr, "\nECHO APP_LTE_SEND_SUCCESS ");
				TRACE_DEBUG(FULL+1,"%sAdding User session AVPs to Diameter-EAP-Answer.",APP_LTE_EXTENSION);
				CHECK_FCT_DO(app_lte_add_user_sessions_avps(app_lte_sm,ans),{TRACE_DEBUG(INFO,"%s Adding user's session AVPs failed.",APP_LTE_EXTENSION); goto s_end;});

				if (app_lte_sm->auth_request_val == AUTHORIZE_AUTHENTICATE)
				{
					TRACE_DEBUG(FULL+1,"%sAdding Authorization AVPs to Diameter-EAP-Answer.",APP_LTE_EXTENSION);
					CHECK_FCT_DO(app_lte_add_authorization_avps(app_lte_sm,ans),{TRACE_DEBUG(INFO,"%s Adding Authorization AVPs failed.",APP_LTE_EXTENSION); goto s_end;});
				}
				TRACE_DEBUG(FULL+1,"%sAdding Result Code AVP to Diameter-EAP-Answer.",APP_LTE_EXTENSION);
				CHECK_FCT_DO( app_lte_add_result_code(app_lte_sm, ans, sess),{TRACE_DEBUG(INFO,"%s Adding Result-Code AVP failed.",APP_LTE_EXTENSION); goto s_end;});
				TRACE_DEBUG(FULL+1,"%sAdding EAP-Payload to Diameter-EAP-Answer.",APP_LTE_EXTENSION);
				TRACE_DEBUG(FULL+1,"%sAdding EAP success AVPs AVPs to Diameter-EAP-Answer.",APP_LTE_EXTENSION);
				TRACE_DEBUG(FULL+1,"%sAdding Accounting-EAP-Auth-Method AVPs to Diameter-EAP-Answer.",APP_LTE_EXTENSION);
				CHECK_FCT_DO(app_lte_add_accounting_eap_auth_method(app_lte_sm, ans),{TRACE_DEBUG(INFO,"%s Adding accounting AVP failed",APP_LTE_EXTENSION); goto s_end;});
				
				LOG_N("%s Auth Success: %.*s",APP_LTE_EXTENSION, app_lte_sm->lte_sm.user.useridLength, app_lte_sm->lte_sm.user.userid);
				
				CHECK_FCT_DO( app_lte_send(rmsg),goto s_end);

				app_lte_sm->state = APP_LTE_END;
				break;

			case APP_LTE_SEND_ERROR_MSG:
				app_lte_sm->invalid_packets++;
				// if (app_lte_sm->invalid_eappackets == lte_config->max_invalid_eap_packet){
				// 	app_lte_sm->result_code = 4001;//DIAMETER_AUTHENTICATION_REJECTED
				// 	TRACE_DEBUG(FULL,"%s Maximum permitted invalid EAP Packet reached. Diameter Authentication Rejected.",APP_LTE_EXTENSION);
				// }

				CHECK_FCT_DO(fd_msg_new_answer_from_req(fd_g_config->cnf_dict, rmsg, 0),goto s_end);

				ans = *rmsg;
				CHECK_FCT_DO( app_lte_add_avps(app_lte_sm, ans,req),{TRACE_DEBUG(INFO,"%s Adding AVPs to Diameter-EAP-Answer message failed.",APP_LTE_EXTENSION);goto s_end;});
				if ((non_fatal_error == TRUE) && (app_lte_sm->result_code == 0))
				{
					app_lte_sm->result_code = 1001;
				}

				if (app_lte_sm->result_code == 1001)
				{
					CHECK_FCT_DO( app_lte_add_eap_reissued_payload(ans,req), goto s_end);
				}

				if (app_lte_sm->result_code == 5004)
				{
					CHECK_FCT_DO( fd_msg_avp_add( ans , MSG_BRW_LAST_CHILD, app_lte_sm->failedavp ),goto s_end );
				}

				CHECK_FCT_DO( app_lte_add_result_code(app_lte_sm, ans, sess), goto s_end);

				CHECK_FCT_DO( app_lte_send(rmsg), goto s_end);
				app_lte_sm->state = APP_LTE_IDLE;
				break;

			case APP_LTE_END:
				break;

			case APP_LTE_IDLE:
				break;
		}
	}

	app_lte_free(app_lte_sm);

	s_end: return 0;
}

int app_lte_start_server(void)
{
	struct disp_when when;

	/*create handler for sessions */
	CHECK_FCT(fd_sess_handler_create(&app_lte_server_reg, app_lte_cli_sess_cleanup, NULL, NULL));

	/* Register the callback */
	memset(&when, 0, sizeof(when));
	when.command = dataobj_lte_cmd;
	when.app = dataobj_lte_app;

	/* Register the callback for EAP Application */
	CHECK_FCT(fd_disp_register(app_lte_server_callback, DISP_HOW_CC, &when, NULL,
					&handle));

	if (handle == NULL)
	{
		TRACE_DEBUG(INFO, "%sCannot register the callback !!!",APP_LTE_EXTENSION);
		return 1;
	}
	return 0;
}

int app_lte_stop_server(void)
{
	CHECK_FCT(fd_sess_handler_destroy(&app_lte_server_reg, NULL));
	CHECK_FCT(fd_disp_unregister(&handle, NULL));

	return 0;
}
