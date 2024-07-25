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


%{
#include <stdio.h>
#include "app_lte_common.h"
#include "app_lte_conf.tab.h"

void yyerror (YYLTYPE *llocp, struct app_lte_conf * config, const char *s);

extern int yywrap();
extern int yylex();


/* The Lex parser prototype */
int app_ltelex(YYSTYPE *lvalp, YYLTYPE *llocp);


%}

%locations
%parse-param {struct app_lte_conf * config} 
%pure_parser
/*%defines */
%error-verbose
%debug 

%union {
	char *str;
	int val;
	char byte;
}



/* In case of error in the lexical analysis */
%token 		LEX_ERROR

%token 	<val>	NUM

%token 	<str>	iSTRING

%token  <byte>	iBYTE

%token 		MODE
%token 		APP_LTE_MYSQL
%token		MAX_INVALID_PACKET
%token		MULTI_ROUND_TIMEOUT
%token		CHECK_USER_IDENTITY

%%	

confparams : 	/* empty */
		| confparams APP_LTE_MySQL
		| confparams MAX_Invalid_Packet
		| confparams Check_User_Identity
		| confparams errors
		{
			yyerror(&yylloc, config, "Unrecognized configuration parameter.");
			return EINVAL;
		}
		;

errors :	LEX_ERROR
		| error
		;

APP_LTE_MySQL :	APP_LTE_MYSQL '=' iSTRING ',' iSTRING ',' iSTRING ',' iSTRING ';'
		{
		app_lte_set_mysql_param($3,$5,$7,$9);
		}
		;

MAX_Invalid_Packet : MAX_INVALID_PACKET '=' NUM ';'
		{
		config->max_invalid_packet=(int)$3;
		};

Check_User_Identity: CHECK_USER_IDENTITY '=' NUM ';'
		{
			if((int)$3){
				check_user_identity = TRUE;
			}else{
				check_user_identity = FALSE;
			}
		};

%%

void yyerror(YYLTYPE *llocp, struct app_lte_conf * config,const char *str)
{
         fprintf(stderr,"Error in %s ( on line %i column %i -> line %i column %i) : %s\n",config->conffile, llocp->first_line, llocp->first_column, llocp->last_line, llocp->last_column, str);
}
