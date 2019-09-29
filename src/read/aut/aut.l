%option noyywrap
%option reentrant
%option bison-bridge

%{
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "_parser_.h"
%}

%option yylineno

DQUOTE           "\""
STAR            "*"

%%

[ \t]+ /* ignore whitespace */;
[\r\n]   { return NEWLINE; }
"("      { return LPAREN;  }
")"      { return RPAREN;  }
","      { return COMMA;   }
"des"    { return DES; 	  }

[0-9]+ {
  size_t ul = strtoull(yytext, NULL, 10);
  yylval->uint = ul;
  return NUMBER;
} 

[A-Za-z][A-Za-z0-9_]* {
  yylval->string = strdup(yytext);
  return ACTION_LABEL; 
}

{STAR} {
  yylval->string = strdup(yytext);
  return ACTION_LABEL;
}

{DQUOTE}[ -~]*{DQUOTE}  {
  yylval->string = (char *) malloc(strlen(yytext) - 2 + 1);
  /* trim the quotes */
  strncpy(yylval->string, &yytext[1], strlen(yytext) - 2);
  yylval->string[strlen(yytext) - 2] = '\0';
  // fprintf(stderr, "%s\n", yylval->string);
  return ACTION_LABEL; 	 
}

. {
  yylval->string = yytext; 
  return INVALID_TOKEN;
}
        
%%