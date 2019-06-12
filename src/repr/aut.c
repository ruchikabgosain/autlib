#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <aut/algo/sort.h>
#include <aut/repr/aut.h>
#include <aut/repr/descriptor.h>
#include <aut/repr/transition.h>
#include <aut/util/env.h>
#include <aut/util/prettyprint.h>


#define _AUT_MIN_CAPACITY 128

// static autError_t _aut_increase_capacity(Aut *aut);

#if __AUTLIB_MAJOR >= 1
static int _cmp_source( const void * e1, const void *e2)
static int _cmp_target( const void * e1, const void *e2)
static int _cmp_action( const void * e1, const void *e2)
static int _cmp_action_len( const void * e1, const void *e2)
#endif

#if __AUTLIB_MAJOR == 0

autError_t
aut_create(aut_t **aut, autDescriptor_t * descriptor, const char *tau)
{
  AUT_CHECK_NULL(aut,         AUT_EINVAL1);
  AUT_CHECK_NULL(descriptor,  AUT_EINVAL2);
#ifdef __cplusplus
  *aut = (aut_t *) malloc(sizeof(Aut));
#else
  *aut = malloc(sizeof(aut_t));
#endif
  AUT_CHECK_NULL(*aut, AUT_EMALLOC);
  (*aut)->descriptor  = descriptor;
  size_t ntrans = descriptor->num_transitions;
#ifdef __cplusplus
  (*aut)->transitions  = (autTransition_t*) calloc( ntrans, sizeof(autTransition_t));
#else
  (*aut)->transitions  = calloc( ntrans, sizeof(autTransition_t));
#endif
  AUT_CHECK_NULL((*aut)->transitions, AUT_EMALLOC);
  (*aut)->size        = 0;
  (*aut)->tau         = (tau == AUT_TAU_UNKNOWN)? AUT_TAU_UNKNOWN : strdup(tau);
  (*aut)->_capacity   = ntrans;
  return AUT_ESUCCESS;
}

#else

autError_t
aut_create(aut_t **aut, autDescriptor_t * descriptor, 
  const char *tau, AutOrder order)
{
  AUT_CHECK_NULL(aut,         AUT_EINVAL1);
  AUT_CHECK_NULL(descriptor,  AUT_EINVAL2);
#ifdef __cplusplus
  *aut = (aut_t *) malloc(sizeof(Aut));
#else
  *aut = malloc(sizeof(aut_t));
#endif
  AUT_CHECK_NULL(*aut, AUT_EMALLOC);

  autError_t err;

  (*aut)->descriptor  = descriptor;
#ifdef __cplusplus
  (*aut)->transitions  =\
    (autTransition_t*) calloc( sizeof(autTransition_t), descriptor->num_transitions);
#else
  (*aut)->transitions  =\
    calloc( sizeof(autTransition_t), descriptor->num_transitions);
#endif

  (*aut)->size        = 0;
  (*aut)->order       = order;
  (*aut)->tau         = (tau == AUT_TAU_UNKNOWN)? AUT_TAU_UNKNOWN : strdup(tau);
  (*aut)->_capacity   = descriptor->num_transitions;
  (*aut)->_sorted     = false;

  if ( order != AUT_ORDER_NONE) {
    if ( (err = aut_sort(*aut, order)) != AUT_ESUCCESS ) 
      return AUT_EFAILURE;
    else 
      (*aut)->_sorted = true;
  }

  return AUT_ESUCCESS;
}

#endif


void
aut_destroy(aut_t **aut)
{
  if ( (aut != AUT_NULL) && (*aut != AUT_NULL)) {
    aut_descriptor_destroy(&(*aut)->descriptor);
    autTransition_t *t;
    for ( size_t i = 0; i < (*aut)->size; ++i) {
      t = aut_get_transition(*aut, i);
      if ( t != AUT_NULL)
        free(t->action);
    }
    free((*aut)->transitions);
    free((*aut)->tau);
    free(*aut);
    *aut = NULL;
  }
}

AUT_FORCEINLINE autDescriptor_t *
aut_get_descriptor(aut_t *aut)
{
  return aut->descriptor;
}

AUT_FORCEINLINE autTransition_t *
aut_get_transitions(aut_t *aut)
{
  return aut->transitions;
}

AUT_FORCEINLINE autTransition_t *
aut_get_transition(aut_t *aut, size_t i)
{
  AUT_CHECK_NULL(aut, AUT_NULL)
  return (aut->size && i < aut->size)? &aut->transitions[i] : AUT_NULL;
}

AUT_FORCEINLINE size_t
aut_get_num_transitions(aut_t *aut)
{
  return aut->descriptor->num_transitions;
}

AUT_FORCEINLINE size_t
aut_get_num_states(aut_t *aut)
{
  return aut->descriptor->num_states;
}

AUT_FORCEINLINE size_t
aut_get_size(aut_t *aut)
{
  return aut->size;
}

AUT_FORCEINLINE bool
aut_isempty(aut_t *aut)
{
  return (aut->size == 0);
}

AUT_FORCEINLINE char *
aut_get_tau(aut_t *aut)
{
  return aut->tau;
}

autError_t
aut_add_transition(aut_t *aut, autState_t from, autState_t to, const char *action)
{
  AUT_CHECK_NULL        (aut,  AUT_EINVAL1);
  AUT_CHECK_LIMIT_STATE (from, AUT_EINVAL2);
  AUT_CHECK_LIMIT_STATE (to,   AUT_EINVAL3);
  if ( aut->size == aut->_capacity) {
    return AUT_EFULL;
    // autError_t err = _aut_increase_capacity(aut);
    // if ( err != AUT_ESUCCESS)
    //   return err;
  }
  (aut->transitions)[aut->size].source = from;
  (aut->transitions)[aut->size].target = to;
  (aut->transitions)[aut->size++].action = \
    (action == AUT_NULL)? AUT_NULL : strdup((char *) action);

  return AUT_ESUCCESS;
}

static autError_t _aut_increase_capacity(aut_t *aut)
{
  size_t new_capacity = (aut->_capacity) ? (aut->_capacity / 4) : 4;

  autTransition_t *new_transitions = \
    realloc(aut->transitions, new_capacity * sizeof( autTransition_t));
  
  AUT_CHECK_NULL(new_transitions, AUT_EMALLOC);

  aut->transitions = new_transitions;

  return AUT_ESUCCESS;
}

//
// Aut *
// aut_new(uint64_t initial_capacity)
// {
//   if ( !initial_capacity)
//     return NULL;
//
// #ifdef __cplusplus
//   Aut *res = (Aut *) malloc(sizeof(Aut));
// #else
//   Aut *res = malloc(sizeof(Aut));
// #endif
//
//   autDescriptor_t *descriptor = aut_descriptor_new();
//
//   if ( res == NULL || descriptor == NULL)
//     return NULL;
//
// #ifdef __cplusplus
//   autTransition_t *transitions = (autTransition_t *) calloc(initial_capacity, sizeof(autTransition_t));
// #else
//   autTransition_t *transitions = calloc( initial_capacity, sizeof(autTransition_t));
// #endif
//   if (transitions == NULL)
//     return NULL;
//
//   res->descriptor  = descriptor;
//   res->transitions = transitions;
//   res->key         = KEY_NONE;
//   res->order       = ORDER_NONE;
//   res->tau         = AUT_TAU_UNKNOWN;
//   res->_sorted      = true;
//   res->_capacity   = initial_capacity;
//
//   return res;
// }
//
// AUT_FORCEINLINE autTransition_t *
// aut_get_transitions(Aut *aut)
// {
//   return aut->transitions;
// }
//
// AUT_FORCEINLINE STATE_COUNT_TYPE
// aut_get_num_transitions(Aut *aut)
// {
//   return aut_descriptor_get_num_transitions(aut->descriptor);
// }
//
// static int _cmp_source( const void * e1, const void *e2)
// {
//   uint32_t source1 = ((autTransition_t*) e1)->source;
//   uint32_t source2 = ((autTransition_t*) e2)->source;
//   return ( source1 < source2) ? -1 : (int) (source1 > source2);
// }
//
// static int _cmp_target( const void * e1, const void *e2)
// {
//   uint32_t target1 = ((autTransition_t*) e1)->target;
//   uint32_t target2 = ((autTransition_t*) e2)->target;
//   return ( target1 < target2) ? -1 : (int) (target1 > target2);
// }
//
// static int _cmp_action( const void * e1, const void *e2)
// {
//   char * action1 = ((autTransition_t*) e1)->action;
//   char * action2 = ((autTransition_t*) e2)->action;
//   return strcmp(action1, action2);
// }
//
// static int _cmp_action_len( const void * e1, const void *e2)
// {
//   uint32_t action_len1 = strlen(((autTransition_t*) e1)->action);
//   uint32_t action_len2 = strlen(((autTransition_t*) e2)->action);
//   return ( action_len1 < action_len2) ? -1 : (int) (action_len1 > action_len2);
// }
//
// bool
// aut_sort(Aut *aut, AutSortKey key)
// {
//   if (aut == NULL || aut->transitions == NULL)
//     return false;
//
// #if defined(__cplusplus) || defined(_GLIBCXX_) || defined(_LIBCPP_VERSION)
//   //use STL sort which is faster
//   #include <iostream>
//   #include <algorithm>
//
// #else
//   autTransition_t *transitions = aut_get_transitions(aut);
//   uint32_t len = aut_get_num_transitions(aut);
//   size_t sz = sizeof(autTransition_t);
//
//   switch(key) {
//     case KEY_SOURCE:
//       qsort(transitions, len, sz, _cmp_source); break;
//     case KEY_TARGET:
//       qsort(transitions, len, sz, _cmp_target); break;
//     case KEY_ACTION:
//       qsort(transitions, len, sz, _cmp_action); break;
//     case KEY_ACTION_LEN:
//       qsort(transitions, len, sz, _cmp_action_len); break;
//     case KEY_NONE:
//     default:
//       break;
//   }
// #endif
// }
//

#ifdef __cplusplus
}
#endif
