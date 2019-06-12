#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include <aut.h>

/*
 * generic helper macros
 */
#define CALL(macro, arguments) macro arguments
#define STR(...) STR_(__VA_ARGS__)
#define STR_(...) #__VA_ARGS__

/*
 * dumps a macro and its expansion to stdout
 * the second argument is optional and specifies the number of
 * arguments that macro takes: 0 means macro takes zero arguments
 * no second argument means macro is not function-like
 */
#define DUMP_MACRO(macro, ...)                                                                                               \
  do                                                                                                                         \
  {                                                                                                                          \
    puts(                                                                                                                    \
        "'" #macro STR(DUMP_MACRO_ARGS_##__VA_ARGS__) "' expands to '" STR(CALL(macro, DUMP_MACRO_ARGS_##__VA_ARGS__)) "'"); \
  } while (0)
/* helpers for DUMP_MACRO, add more if required */
#define DUMP_MACRO_ARGS_
#define DUMP_MACRO_ARGS_0 ()
#define DUMP_MACRO_ARGS_1 (<1>)
#define DUMP_MACRO_ARGS_2 (<1>, <2>)
#define DUMP_MACRO_ARGS_3 (<1>, <2>, <3>)


bool find_transition(aut_t *lts, autState_t from, autState_t to, const char *action)
{
  autTransition_t *t;

  fprintf(stderr, "Find in LTS of size: %ld\n", aut_get_size(lts));

  for ( size_t i = 0; i < aut_get_size(lts); ++i) {
    t = aut_get_transition(lts, i);
    if ( t->source == from && t->target == to 
      && strcmp(t->action, action) == 0 )  
        return true;
  }
  
  return false;
}

#define SMALL_FILE "../files/simple/anton.aut"

int main(void)
{
  aut_t *lts;
  autError_t err = aut_read("../files/invalid/invalid_transition1.aut", &lts);
  // autError_t err = aut_read("../files/simple/anton.aut", &lts);

  if ( err == AUT_ESUCCESS)
    aut_pp(lts);

  printf("Err: %d %s\n", err, aut_error_str(err));
}
