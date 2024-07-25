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

#include "lib_app_lte.h"

int app_lte_subscriber_get_userid(struct lte_subscriber *user, u8 *userid)
{
	TRACE_ENTRY("%p %p", user, userid);
	if (user->userid == NULL)
		return EINVAL;
	userid = user->userid;
	return 0;
}

int app_lte_subscriber_set_userid(struct lte_subscriber *user, u8 *userid,
								  u16 useridLength)
{
	TRACE_ENTRY("%p %p %hu", user, userid, useridLength);
	if (userid == NULL)
		return EINVAL;
	if (useridLength < 1)
		return EINVAL;
	user->userid = userid;
	user->useridLength = useridLength;
	return 0;
}

int app_lte_subscriber_get_methodid(struct lte_subscriber *user, int *methodid)
{
	TRACE_ENTRY("%p %p", user, methodid);
	if (user->password == NULL)
		return EINVAL;
	*methodid = user->methodId;
	return 0;
}

int app_lte_subscriber_set_methodid(struct lte_subscriber *user, int methodId)
{
	TRACE_ENTRY("%p %d", user, methodId);
	if (user->password == NULL)
		return EINVAL;
	if (methodId < 0)
		return EINVAL;
	user->methodId = methodId;
	return 0;
}

boolean app_lte_subscriber_issuccess(struct lte_subscriber *user)
{
	TRACE_ENTRY("%p", user);
	if (user->password == NULL)
		return FALSE;
	return user->success;
}

int app_lte_subscriber_set_success(struct lte_subscriber *user)
{
	TRACE_ENTRY("%p", user);
	if (user->password == NULL)
		return EINVAL;
	user->success = TRUE;
	return 0;
}
