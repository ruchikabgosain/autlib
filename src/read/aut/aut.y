%define api.pure full
%define parse.trace true
%define parse.error verbose

%{
  #include <stdio.h>
  #include <stddef.h>
  #include <aut/repr/aut.h>
  #include <aut/util/error.h>
  #include "_parser_.h"
  #include "_scanner_.h"
  
  char *concat(const char *format, const char *s1, const char *s2);
  void yyerror(yyscan_t *sc, aut_t **aut, autError_t *err, const char *msg);
%}

%code requires {
  #include <aut/read/aut.h>
}

%lex-param    { void *scanner}
%parse-param  { void *scanner}
%parse-param  { aut_t **aut}
%parse-param  { autError_t *err}


%union 
{
  size_t uint;
  char *string;
  autDescriptor_t *descriptor;
  autTransition_t *transition;
  autError_t err;
}



%type <descriptor> descriptor
%type <transition_list> transitions
%type <transition> transition

%token <string> DES
%token <uint>   NUMBER
%token <string> ACTION_LABEL
%token COMMA LPAREN RPAREN NEWLINE END_OF_FILE INVALID_TOKEN NUMBER_OOR

%start aut

%%

aut : descriptor transitions 
    {}
    | descriptor transitions newlines
    {}
    ;

newlines : newlines NEWLINE
         {}
         | NEWLINE
         ;

descriptor  : DES LPAREN NUMBER COMMA NUMBER COMMA NUMBER RPAREN NEWLINE
            {	
              if ( $3 >= UINT32_MAX) { // range-check initstate
                yyerror( scanner, aut, err, "state id out of range");
                YYABORT;
              }

              if ( $7 > UINT32_MAX) { // range-check number of states
                yyerror( scanner, aut, err, "number of states out of range");
                YYABORT;
              }

              autDescriptor_t *d;
              if ( (*err = aut_descriptor_create(&d, $3, $5, $7)) != AUT_ESUCCESS) {
                yyerror( scanner, aut, err, aut_error_str(*err));
                YYABORT;
              }

            #if __AUTLIB_MAJOR >= 1
              if ( (*err = aut_create( aut, d, AUT_TAU_UNKNOWN, AUT_ORDER_NONE)) != AUT_ESUCCESS)
            #else
              if ( (*err = aut_create( aut, d, AUT_TAU_UNKNOWN)) != AUT_ESUCCESS)
            #endif
              {
                yyerror(scanner, aut, err, aut_error_str(*err));
                YYABORT;
              }
            }
			      ;

transitions : transitions NEWLINE transition
            {}
            | transition
            {}
            ;
  
transition  : LPAREN NUMBER COMMA ACTION_LABEL COMMA NUMBER RPAREN 
            { 
              if ( $2 >= UINT32_MAX) { 
                yyerror( scanner, aut, err, "state id out of range");
                YYABORT;
              }

              if ( $6 >= UINT32_MAX) { 
                yyerror( scanner, aut, err, "state id out of range");
                YYABORT;
              }

              if ( (*err = aut_add_transition( *aut, $2, $6, $4)) != AUT_ESUCCESS) {
                yyerror(scanner, aut, err, aut_error_str(*err));
                YYABORT;
              }
            }
            ;

%%

char *concat(const char *format, const char *s1, const char *s2)
{
  size_t len = strlen(s1) + strlen(s2) + strlen(format);
  char *res = calloc(len, 1);
  snprintf(res, len, format, s1, s2);
  return res;
}

void yyerror(yyscan_t *sc, aut_t **aut, autError_t *err, const char *msg)
{
  if ( *err != AUT_ESUCCESS ) {
    char *errstr = concat("%s (%s)", "internal error", msg);
    fprintf(stderr, "aut.parse: line %d: %s\n", yyget_lineno(sc), errstr);
    *err = AUT_EINTERNAL;
    free(errstr);
  } else {
    *err = AUT_ESYNTAX;
    fprintf(stderr, "aut.parse: line %d, near \'%s\': %s\n", yyget_lineno(sc), yyget_text(sc), "invalid syntax");
  }
}
