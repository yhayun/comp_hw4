%{
/* Declerations */

/* includes— */
#include <stdio.h>
#include "output.hpp"
#include "attributes.h"
#include "parser.tab.hpp"
#include <string.h>
/* functions —*/
char *getToken();
%}

/* definitions */
%option yylineno
%option noyywrap

VOID 		void
INT 		int
BYTE 		byte
B 			b
BOOL 		bool
AND 		and
OR 			or
NOT 		not
TRUE 		true
FALSE 		false
RETURN 		return
IF 			if
ELSE  		else
WHILE  		while
SWITCH		switch
CASE		case
BREAK		break
COLON		\:
SC 			\;
COMMA 		\,
LPAREN		\(
RPAREN		\)
LBRACE		\{
RBRACE		\}
ASSIGN		\=
RELOP		\=\=|\!\=|\<|\>|\>\=|\<\=
BINOP		\+|\-|\*|\/
ID 			[a-zA-Z][a-zA-Z0-9]*
NUM 		0|[1-9][0-9]*
STRING		\"([^\n\r\"\\]|\\[rnt"\\])+\"
whitespace	[\n\t\r ]
comment		\/\/[^\r\n]*[\r|\n|\r\n]?

%%

{VOID}		{yylval.name = yytext ;return VOID;}
{INT}		{yylval.name = yytext ;return INT;}
{BYTE}		{yylval.name = yytext ;return BYTE;}
{B}			{yylval.name = yytext ;return B;}
{BOOL}		{yylval.name = yytext ;return BOOL;}
{AND}		{yylval.name = yytext ;return AND;}
{OR}		{yylval.name = yytext ;return OR;}
{NOT}		{yylval.name = yytext ;return NOT;}
{TRUE}		{yylval.name = yytext ;return TRUE;}
{FALSE}		{yylval.name = yytext ;return FALSE;}
{RETURN}	{yylval.name = yytext ;return RETURN;}
{IF}		{yylval.name = yytext ;return IF;}
{ELSE}		{yylval.name = yytext ;return ELSE;}
{WHILE}		{yylval.name = yytext ;return WHILE;}
{SWITCH}	{yylval.name = yytext ;return SWITCH;}
{CASE}		{yylval.name = yytext ;return CASE;}
{BREAK}		{yylval.name = yytext ;return BREAK;}
{COLON}		{yylval.name = yytext ;return COLON;}
{SC}		{yylval.name = yytext ;return SC;}
{COMMA}		{yylval.name = yytext ;return COMMA;}
{LPAREN}	{yylval.name = yytext ;return LPAREN;}
{RPAREN}	{yylval.name = yytext ;return RPAREN;}
{LBRACE}	{yylval.name = yytext ;return LBRACE;}
{RBRACE}	{yylval.name = yytext ;return RBRACE;}
{ASSIGN}	{yylval.name = yytext ;return ASSIGN;}
{RELOP}		{yylval.name = yytext ;return RELOP;}
{BINOP}		{yylval.name = yytext ;return BINOP;}

{ID}		{	
			yylval.name = yytext ;
			return ID;
		}
{NUM}		{
			yylval.value = atoi(yytext);
			yylval.name = yytext;
			return NUM;
		}
{STRING}	{       yylval.name = yytext;
                        return STRING;
                }
{whitespace} ;
{comment}	;
.		{output::errorLex(yylineno);exit(1);}
%%


