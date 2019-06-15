#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>

#include <aut/util/prettyprint.h>

void aut_pp_descriptor(autDescriptor_t *descriptor)
{
  if ( descriptor != NULL) {
    fprintf(stdout, "des (%u, %lu, %lu)\n", 
      aut_descriptor_get_initstate(descriptor),
      aut_descriptor_get_num_transitions(descriptor),
      aut_descriptor_get_num_states(descriptor));
  }
}

void aut_pp_transition(autTransition_t *transition)
{
  if ( transition != NULL) {
    char *action;
    aut_transition_get_action(transition, &action);
    fprintf(stdout, "t (%u, %u, %s)\n", aut_transition_get_source(transition),
      aut_transition_get_target(transition), action); 
  }
}

void aut_pp(aut_t *aut)
{
  aut_pp_descriptor(aut->descriptor);

  for ( size_t i = 0; i < aut_get_num_transitions(aut); ++i) {  
    fprintf(stdout, "  ");
    aut_pp_transition( aut_get_transition(aut, i));
  }
}

#ifdef __cplusplus
}
#endif