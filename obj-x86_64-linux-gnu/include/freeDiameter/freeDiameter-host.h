/*********************************************************************************************************
* Software License Agreement (BSD License)                                                               *
* Author: Sebastien Decugis <sdecugis@freediameter.net>							 *
*													 *
* Copyright (c) 2016, WIDE Project and NICT								 *
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

/* Configuration from compile-time */
#ifndef FD_IS_CONFIG
#define FD_IS_CONFIG

#ifdef __cplusplus
extern "C" {
#endif

/* #undef HAVE_NTOHLL */
#define HAVE_MALLOC_H
/* #undef HAVE_SIGNALENT_H */
#define HAVE_AI_ADDRCONFIG
#define HAVE_CLOCK_GETTIME
#define HAVE_STRNDUP
#define HAVE_PTHREAD_BAR

/* #undef HOST_BIG_ENDIAN */

/* #undef DISABLE_SCTP */
/* #undef DEBUG_SCTP */
/* #undef DEBUG_WITH_META */
/* #undef SCTP_USE_MAPPED_ADDRESSES */
#define SCTP_CONNECTX_4_ARGS
/* #undef SKIP_DLCLOSE */
/* #undef DIAMID_IDNA_IGNORE */
/* #undef DIAMID_IDNA_REJECT */
/* #undef DISABLE_PEER_EXPIRY */
/* #undef WORKAROUND_ACCEPT_INVALID_VSAI */
#define GNUTLS_VERSION_210
#define GNUTLS_VERSION_212
#define GNUTLS_VERSION_300
#define GNUTLS_VERSION_310

/* #undef ERRORS_ON_TODO */
/* #undef DEBUG */

#define FD_PROJECT_BINARY "freeDiameterd"
#define FD_PROJECT_NAME "freeDiameter"
#define FD_PROJECT_VERSION_MAJOR 1
#ifndef FD_PROJECT_VERSION_MAJOR
# define FD_PROJECT_VERSION_MAJOR 0
#endif /*FD_PROJECT_VERSION_MAJOR*/
#define FD_PROJECT_VERSION_MINOR 5
#ifndef FD_PROJECT_VERSION_MINOR
# define FD_PROJECT_VERSION_MINOR 0
#endif /*FD_PROJECT_VERSION_MINOR*/
/* #undef FD_PROJECT_VERSION_REV */
#ifndef FD_PROJECT_VERSION_REV
# define FD_PROJECT_VERSION_REV 0
#endif /*FD_PROJECT_VERSION_REV*/
#define FD_PROJECT_VERSION_API   6
#ifndef FD_PROJECT_VERSION_API
# define FD_PROJECT_VERSION_API 0
#endif /*FD_PROJECT_VERSION_API*/
#define FD_PROJECT_COPYRIGHT "Copyright (c) 2008-2015, WIDE Project (www.wide.ad.jp) and NICT (www.nict.go.jp)"

#define DEFAULT_CONF_PATH "/etc/freeDiameter"
#define DEFAULT_EXTENSIONS_PATH "/usr/lib/freeDiameter"

#ifndef FD_DEFAULT_CONF_FILENAME
#define FD_DEFAULT_CONF_FILENAME "freeDiameter.conf"
#endif /* FD_DEFAULT_CONF_FILENAME */

/* Maximum number of hooks handlers that can be registered. Make this compilation option if needed */
#define FD_HOOK_HANDLE_LIMIT	5

#ifdef __cplusplus
}
#endif

#endif /* FD_IS_CONFIG */
