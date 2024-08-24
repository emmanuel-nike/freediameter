/*****************************************************************************************************
 * Software License Agreement (BSD License)
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

#include "app_lte_mysql.h"

static pthread_mutex_t db_cs_mutex = PTHREAD_MUTEX_INITIALIZER;

int update_lte_subscriber_acct(struct lte_subscriber_acct *user_acct) 
{
	fprintf(stderr, "\nMYSQL_UPDATING_USER_ACCT %s", user_acct->userid);
	TRACE_ENTRY("%p %p", user_acct->userid, user_acct->userimsi);
	if (db_conn == NULL)
	{
		TRACE_DEBUG(INFO, "%sNot connected to the MySQL Database server.", APP_LTE_EXTENSION);
		return EINVAL;
	}
	mysql_thread_init();

	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query;
	CHECK_MALLOC(query = (char *)malloc(sizeof(char) * 300));

	if(user_acct->cc_request_type == INITIAL_REQUEST) {
		sprintf(query, "INSERT INTO lte_subscriber_acct(session_id,username,imsi) values ('%s', '%s', '%s')", user_acct->sessionId, user_acct->userid, user_acct->userimsi);
	}
	else if(user_acct->cc_request_type == UPDATE_REQUEST) {
		sprintf(query, "UPDATE lte_subscriber_acct SET total_time = total_time + %d, total_octets = total_octets + %d, input_octets = input_octets + %d, output_octets = output_octets + %d, cc_request_type = %d, cc_request_num = %d WHERE session_id = '%s' AND username = '%s'", user_acct->ccTime, user_acct->totalOctets, user_acct->inputOctets, user_acct->outputOctets, user_acct->cc_request_type, user_acct->cc_request_num, user_acct->sessionId, user_acct->userid);
	}
	else if(user_acct->cc_request_type == TERMINATION_REQUEST) {
		sprintf(query, "UPDATE lte_subscriber_acct SET total_time = total_time + %d, total_octets = total_octets + %d, input_octets = input_octets + %d, output_octets = output_octets + %d, cc_request_type = %d, cc_request_num = %d, end_time = current_timestamp WHERE session_id = '%s' AND username = '%s'", user_acct->ccTime, user_acct->totalOctets, user_acct->inputOctets, user_acct->outputOctets, user_acct->cc_request_type, user_acct->cc_request_num, user_acct->sessionId, user_acct->userid);
	} else {
		TRACE_DEBUG(INFO, "%sRequest type unknown.", APP_LTE_EXTENSION);
		return EINVAL;
	}
	fprintf(stderr, "\n%s", query);
	if (mysql_query(db_conn, query))
	{
		CHECK_POSIX(pthread_mutex_unlock(&db_cs_mutex));
		TRACE_DEBUG(INFO, "%sQuery execution fail. %s", APP_LTE_EXTENSION, mysql_error(db_conn));
		mysql_thread_end();
		free(query);
		query = NULL;
		return EINVAL;
	}

	res = mysql_store_result(db_conn);

	CHECK_POSIX(pthread_mutex_unlock(&db_cs_mutex));
	mysql_free_result(res);
	mysql_thread_end();
	free(query);
	query = NULL;
	return 0;
}

int get_lte_subscriber(struct lte_subscriber *user, char *username)
{
	fprintf(stderr, "\nMYSQL_CHECKING_USER %s", username);
	TRACE_ENTRY("%p %p", user, username);
	if (db_conn == NULL)
	{
		TRACE_DEBUG(INFO, "%sNot connected to the MySQL Database server.", APP_LTE_EXTENSION);
		return EINVAL;
	}
	mysql_thread_init();

	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query;
	CHECK_MALLOC(query = (char *)malloc(sizeof(char) * 255));

	sprintf(query, "SELECT id,username FROM lte_subscribers WHERE username='%s' and active='Y' ", username);

	CHECK_POSIX(pthread_mutex_lock(&db_cs_mutex));

	if (mysql_query(db_conn, query))
	{
		CHECK_POSIX(pthread_mutex_unlock(&db_cs_mutex));
		TRACE_DEBUG(INFO, "%sQuery execution fail. %s", APP_LTE_EXTENSION, mysql_error(db_conn));
		fprintf(stderr, "\nQuery execution fail. %s", mysql_error(db_conn));
		mysql_thread_end();
		free(query);
		query = NULL;
		return EINVAL;
	}

	res = mysql_store_result(db_conn);

	CHECK_POSIX(pthread_mutex_unlock(&db_cs_mutex));

	if ((row = mysql_fetch_row(res)) != NULL)
	{

		user->id = atoi(row[0]);
		CHECK_MALLOC(user->userid = malloc(strlen(row[1]) + 1));
		memcpy(user->userid, row[1], strlen(row[1]) + 1);
		user->useridLength = strlen(row[1]);

		mysql_free_result(res);
		mysql_thread_end();
		free(query);
		query = NULL;
		return 0;
	}

	TRACE_DEBUG(INFO, "%sUser unavailable.", APP_LTE_EXTENSION);
	fprintf(stderr, "\nUser not found.");
	mysql_free_result(res);
	mysql_thread_end();
	free(query);
	query = NULL;
	return EINVAL;
}

int app_lte_authentication_get_attribs(struct lte_subscriber *user, struct fd_list *attribute_list)
{
	TRACE_ENTRY("%p %p", user, attribute_list);

	if (db_conn == NULL)
	{
		TRACE_DEBUG(INFO, "%sNot connected to the MySQL Database server.", APP_LTE_EXTENSION);

		return EINVAL;
	}

	mysql_thread_init();
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query;
	CHECK_MALLOC(query = malloc(sizeof(char) * 255));

	sprintf(
		query,
		"SELECT `lte_authe`.`attribute` ,`lte_authe`.`value` FROM `lte_authe` WHERE `lte_authe`.`grp` IN ( SELECT `lte_user_grp`.`grp` FROM `lte_user_grp` WHERE `lte_user_grp`.`user` = %d ) ",
		user->id);

	CHECK_POSIX(pthread_mutex_lock(&db_cs_mutex));

	if (mysql_query(db_conn, query))
	{
		CHECK_POSIX(pthread_mutex_unlock(&db_cs_mutex));
		TRACE_DEBUG(INFO, "%sQuery execution fail. %s", APP_LTE_EXTENSION, mysql_error(db_conn));
		mysql_thread_end();
		free(query);
		query = NULL;
		return EINVAL;
	}

	res = mysql_store_result(db_conn);

	CHECK_POSIX(pthread_mutex_unlock(&db_cs_mutex));

	while ((row = mysql_fetch_row(res)))
	{
		struct auth_attribute *attribute;
		CHECK_MALLOC(attribute = malloc(sizeof(struct auth_attribute)));
		memset(attribute, 0, sizeof(struct auth_attribute));
		fd_list_init(&attribute->chain, NULL);
		attribute->attrib = strdup(row[0]);
		attribute->op = NULL;
		attribute->value = strdup(row[1]);
		fd_list_insert_before(attribute_list, &attribute->chain);
	}

	mysql_free_result(res);
	mysql_thread_end();
	free(query);
	query = NULL;
	return 0;
}

int app_lte_authorization_get_attribs(struct lte_subscriber *user, struct fd_list *attribute_list)
{
	TRACE_ENTRY("%p %p", user, attribute_list);
	fprintf(stderr, "\nMYSQL_AUTHORIZING %s", user->userid);

	if (db_conn == NULL)
	{
		TRACE_DEBUG(INFO, "%sNot connected to the MySQL Database server.", APP_LTE_EXTENSION);

		return EINVAL;
	}

	mysql_thread_init();

	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query;
	CHECK_MALLOC(query = malloc(sizeof(char) * 255));

	sprintf(
		query,
		"SELECT `attribute` , `op` , `value` FROM `lte_authz` WHERE `grp` IN ( SELECT `grp` FROM `lte_subscriber_grp` WHERE `lte_subscriber` = %d )",
		user->id);

	CHECK_POSIX(pthread_mutex_lock(&db_cs_mutex));

	if (mysql_query(db_conn, query))
	{
		CHECK_POSIX(pthread_mutex_unlock(&db_cs_mutex));
		TRACE_DEBUG(INFO, "%sQuery execution fail. %s", APP_LTE_EXTENSION, mysql_error(db_conn));
		mysql_thread_end();
		free(query);
		query = NULL;
		return EINVAL;
	}

	res = mysql_store_result(db_conn);

	CHECK_POSIX(pthread_mutex_unlock(&db_cs_mutex));

	while ((row = mysql_fetch_row(res)))
	{
		struct auth_attribute *attribute;
		CHECK_MALLOC(attribute = malloc(sizeof(struct auth_attribute)));
		memset(attribute, 0, sizeof(struct auth_attribute));
		fd_list_init(&attribute->chain, NULL);
		attribute->attrib = strdup(row[0]);
		attribute->op = strdup(row[1]);
		attribute->value = strdup(row[2]);
		fd_list_insert_before(attribute_list, &attribute->chain);
	}

	mysql_free_result(res);
	mysql_thread_end();
	free(query);
	query = NULL;
	return 0;
}

void app_lte_mysql_disconnect()
{
	mysql_close(db_conn);
}
