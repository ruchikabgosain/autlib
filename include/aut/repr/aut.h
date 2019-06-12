#ifndef __AUT_REPR_AUT_H_INCLUDED__
#define __AUT_REPR_AUT_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <aut/repr/descriptor.h>
#include <aut/repr/transition.h>
#include <aut/util/env.h>

#define AUT_TAU_UNKNOWN (char *) AUT_NULL

#if __AUTLIB_MAJOR < 1

/**
 * @brief Represents and AUT file
 * @details An AUT file consists of a descriptor followed by a list of
 * transitions. More: https://cadp.inria.fr/man/aut.html 
 **/
typedef struct aut_t {
  /** The descriptor of the AUT file */
  autDescriptor_t *descriptor;
  /** The transitions of the AUT file */
  autTransition_t *transitions;
  /** The number of transitions inserted in this aut_t object */
  size_t size;
  /** The action label for tau. No taus if AUT_TAU_UNKNOWN */
  char *tau;
  /** The maximum number of transitions that can fit */
  uint64_t _capacity;
} aut_t;

/**
 * @brief Create a new aut_t object and initialize it with values
 * @param [out] <aut>         a pointer to an aut_t pointer. Will point to the result
 * @param [in] <descriptor>   a pointer to an autDescriptor_t
 * @param [in] <transitions>  a pointer to an autTransition_t array
 * @param [in] <len>          the number of autTransition_t objects starting from \p transitions
 * @param [in] <tau>          a value for the tau action. if AUT_TAU_UNKNOWN then there are no taus
 * @return An  @ref autError_t indicating the status of the operation. 
 **/
autError_t
aut_create( aut_t **aut,
            autDescriptor_t *descriptor,
            const char *tau);


#elif __AUTLIB_MAJOR >= 1

#include <aut/algo/sort.h>

/**
 * @brief Represents and AUT file
 * @details An AUT file consists of a descriptor followed by a list of
 * transitions. More: https://cadp.inria.fr/man/aut.html 
 **/
typedef struct aut_t
{
  /** The descriptor of the AUT file */
  autDescriptor_t *descriptor;
  /** The transitions of the AUT file */
  autTransition_t *transitions;
  /** The number of transitions inserted in this aut_t object */
  size_t size;
  /** The order of transitions */
  AutOrder order;
  /** The action label for tau. No taus if AUT_TAU_UNKNOWN */
  char * tau;
  /** If <code>true</code> then transitions are (currently) in order. <br/>
   *  Inserting transitions may violated the order */
  bool volatile _sorted;
  /** The maximum number of transitions that can fit */
  uint64_t _capacity;
} aut_t;

/**
 * @brief Create a new aut_t object and initialize it with values
 * @param [out] <aut>         a pointer to an aut_t pointer. Will point to the result
 * @param [in] <descriptor>   a pointer to an autDescriptor_t
 * @param [in] <transitions>  a pointer to an autTransition_t array
 * @param [in] <len>          the number of autTransition_t objects starting from \p transitions
 * @param [in] <tau>          a value for the tau action. if AUT_TAU_UNKNOWN then there are no taus
 * @param [in] <AutOrder>     define an order for the transitions to be sorted on.
 *  Passing AUT_ORDER_NONE is in effect a no-op. Passing any other value will result
 *  in a sorting of the transitions.
 * @return An  @ref autError_t indicating the status of the operation.
 * @see #aut_new, #aut_new_sorted
 **/
autError_t
aut_create( aut_t **aut,
            autDescriptor_t *descriptor,
            const char *tau,
            AutOrder order);

#elif !defined(__AUTLIB_MAJOR)
  #error __AUTLIB_MAJOR is not defined
#elif !defined(__AUTLIB_MINOR)
  #error __AUTLIB_MINOR is not defined
#else
  #error Invalid autlib version. Consider compiling from official repo
#endif

/**  
 * @brief Safe destruction of an aut_t object
 * @param[in]  <aut> a pointer to an aut_t pointer
 * @details The memory pointed to by <code>*aut</code> is freed and
 *  the pointer is set to point to <code>NULL</code>. The descriptor
 *  has to be explicitely destroyed to avoid leaks. 
 * @see aut_descriptor_destroy()
 **/
void
aut_destroy(aut_t **aut);

autDescriptor_t *
aut_get_descriptor(aut_t *aut);

autTransition_t *
aut_get_transitions(aut_t *aut);

autTransition_t *
aut_get_transition(aut_t *aut, size_t i);

size_t
aut_get_num_transitions(aut_t *aut);

size_t
aut_get_num_states(aut_t *aut);

autError_t
aut_add_transition(aut_t *aut, autState_t from, autState_t to, const char *action);

size_t
aut_get_size(aut_t *aut);

bool 
aut_isempty(aut_t *aut);

char *
aut_get_tau(aut_t *aut);

// /**
//  * @brief Create a new, empty aut_t object with enough space allocated to fit
//  *    \p initial_capacity number of autTransition_t (s)
//  * @param [in] <initial_capacity> Number of transitions to be allocated initially
//  * @return A pointer to the newly allocated aut_t object. <code>NULL</code> on error
//  * @details The aut_t object is expanded (realloc) when new transitions, past
//  *  \p initial_capacity, are inserted.
//  * @see #aut_add_transition
//  */
// autError_t
// aut_new(aut_t **aut, uint64_t initial_capacity);

// autDescriptor_t *
// aut_set_descriptor(aut_t *aut, autDescriptor_t *descriptor);

// autTransition_t *
// aut_remove_transition(aut_t *aut, uint32_t from, uint32_t to, const char *action);

// bool
// aut_contains_tau(aut_t *aut);

// char *
// aut_get_tau(aut_t *aut);


// //TODO
// void
// aut_multisort(aut_t *aut, AutSortKey k1, AutSortKey k2, AutSortKey k3);

// bool
// aut_validate(aut_t *aut);

#ifdef __cplusplus
}
#endif

#endif /* __AUT_REPR_AUT_H_INCLUDED__ */
