#ifndef __AUT_REPR_DESCRIPTOR_H_INCLUDED__
#define __AUT_REPR_DESCRIPTOR_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <aut/repr/state.h>
#include <aut/repr/transition.h>
#include <aut/util/error.h>

/**
 * @brief Allocates a new autDescriptor_t object on the heap
 *  and zero initilizes it. <br/>
 * @details The autDescriptor_t is zero initialized and thus,
 *  may not be a valid descriptor (More limits.h). Moreover,
 *  the memory needs to be explicitely freed later on. <br/><br/>
 * Example <br/>
 * @code
 *  autDescriptor_t *d = AUT_EMPTY_DESCRIPTOR_H;
 *  if (!d) {
 *    // malloc error
 *  }
 * @endcode
 * @see aut_descriptor_create, aut_descriptor_init, aut_descriptor_new
 **/
  #ifdef __cplusplus
    #define AUT_EMPTY_DESCRIPTOR_H \
      ((autDescriptor_t *) (calloc( sizeof(autDescriptor_t), 1)))
  #else
    #define AUT_EMPTY_DESCRIPTOR_H \
      (calloc(sizeof(autDescriptor_t), 1))
  #endif

/**
 * @brief Allocates a zero-initilizes autDescriptor_t object on the stack
 * @details The autDescriptor_t is zero initialized and thus,
 *  may not be a valid descriptor (More limits.h).
 * Example <br/>
 * @code
 *  autDescriptor_t d = AUT_EMPTY_DESCRIPTOR_S;
 * @endcode
 * @see aut_descriptor_create, aut_descriptor_init, aut_descriptor_new
 */
  #define AUT_EMPTY_DESCRIPTOR_S   \
    ((autDescriptor_t) {0, 0, 0})

/**
 * @brief Struct representing the descriptor of an AUT file
 * @details An aut descriptor is the first line of an AUT file
 *  and has the form:     <br/>
 *  <code>
 *    des(<initial-state>,<number-of-transitions>,<number-of-states>)
 *  </code><br/>
 *  More: https://cadp.inria.fr/man/aut.html
 */
typedef struct autDescriptor_t
{
  /** The initial state of the transition system */
  autState_t initstate;
  /** The total number of transitions in the transition system */
  size_t num_transitions;
  /** The total number of states in the transition system */
  size_t num_states;
} autDescriptor_t;

/**
 * @brief Create a new autDescriptor_t object and initialize it with values
 * @param [out] <descriptor>      a pointer to an autDescriptor_t pointer
 * @param [in]  <initstate>       id of the initial state
 * @param [in]  <num_transitions> number of transitions
 * @param [in]  <num_states>      number of states
 * @return  An  @ref autError_t indicating the status of the operation.
 *  Possible return values: <ul>
 *    <li>@ref AUT_ESUCCESS on success,            </li>
 *    <li>@ref AUT_EMALLOC on internal malloc error</li>
 *    <li>@ref AUT_EINVAL1 to @ref AUT_EINVAL4 on invalid arguement(s)
 *      (More: autError_t)
 * </ul>
 * @see aut_descriptor_init(), aut_descriptor_new(), aut_descriptor_dup()
 * @details A new @ref autDescriptor_t object is allocated on the heap and
 *  initialized with values. \p descriptor is set to point it. <br/><br/>
 * @b Example Simple usage
 * @code
 * autDescriptor_t *desc;
 * aut_e err = aut_descriptor_create(&desc, 0, 10, 20);
 * if ( desc != AUT_ESUCCESS) {
 *   switch(err) {
 *      case AUT_EMALLOC:
 *        fprintf(stderr, "%s\n", "Malloc Error"); break;
 *      case AUT_EINVAL1:
 *        //Invalid argument 1
 *      ...
 *   }
 * }
 * // ...
 * aut_descriptor_destroy(&desc);
 * @endcode
 * @note if \p descriptor already points to some valid autDescriptor_t, then
 *  if not freed properly, calling this function will result in a memory leak
 */
autError_t
aut_descriptor_create( autDescriptor_t **descriptor,
                       autState_t initstate,
                       size_t num_transitions,
                       size_t num_states);

/**
 * @brief Initialize an @ref autDescriptor_t with values
 * @param [in] <descriptor>       a pointer to an autDescriptor_t pointer
 * @param [in] <initstate>        id of the initial state
 * @param [in] <num_transitions>  number of transitions
 * @param [in] <num_states>       number of states
 * @return An  @ref autError_t indicating the status of the operation.
 * @details The purpose of this function is mostly to provide means for
 *  stack allocated autDescriptor_t objects. <br/><br/>
 * @b Example
 * @code
 *    autDescriptor_t desc;
 *    aut_descriptor_init(&desc, 0, 10, 20);
 * @endcode
 */
autError_t
aut_descriptor_init( autDescriptor_t *descriptor,
                     autState_t initstate,
                     size_t num_transitions,
                     size_t num_states);

/**
 * @brief Create a new, empty autDescriptor_t object. Members are initialized to <code>0</code>
 * @return @ref AUT_ESUCCESS on success, @ref AUT_EMALLOC on internal malloc error
 * @note When use as the descriptor to an Aut object, these values will <i>may</i>
 *  produce an invalid Aut. Attention should be paid that the value are within the range of the
 *  specification.
 * @see aut_validate
 */
autError_t
aut_descriptor_new(autDescriptor_t **descriptor);

/**
 * @brief Safe destruction of an autDescriptor_t object
 * @param[in]  <descriptor> a pointer to an autDescriptor_t pointer.
 *   <code>NULL</code> is allowed and is a no-op.
 * @details The memory pointed to by <code>*descriptor</code> is freed and
 *    the pointer is set to point to  <code>NULL</code>.
 * @code
 * autDescriptor_t *desc;
 * aut_e err = aut_descriptor_new(&desc);
 * if ( desc != AUT_ESUCCESS) {
 *   switch(err) {
 *      case AUT_EMALLOC:
 *        fprintf(stderr, "%s\n", "Malloc Error"); break;
 *      case AUT_EINVAL1:
 *        //Invalid argument 1
 *      // ...
 *   }
 * }
 * @endcode
 * @note Undefined bahavior when \p descriptor is allocated on the stack
 **/
void
aut_descriptor_destroy(autDescriptor_t **descriptor);

/**
 * @brief Create a copy of an autDescriptor_t
 * @param [in] <src> a pointer to the autDescriptor_t to be copied
 * @param [out] <copy> a pointer to an autDescriptor_t pointer that will
 *  point to the copy
 * @return An  @ref autError_t indicating the status of the operation.
 * @details A new autDescriptor_t object is allocated, initialized with
 *  values from \p src and <code>*copy</code> is set to point to it
 */
autError_t
aut_descriptor_dup(autDescriptor_t *src, autDescriptor_t **copy);

/**
 * @brief Copy the values from one autDescriptor_t to another
 * @param [in] <src> a pointer to the autDescriptor_t to be copied
 * @param [in] <copy> a pointer to the target autDescriptor_t object
 * @return A @ref autError_t indicating the status of the operation
 * @details \p copy must be a valid pointer to an autDescriptor_t object
 */
autError_t
aut_descriptor_dup2(autDescriptor_t *src, autDescriptor_t *copy);

/**
 * @brief Set the values of an autDescriptor_t
 * @param [in] <descriptor>      a pointer to an autDescriptor_t
 * @param [in] <initstate>       the initial state
 * @param [in] <num_transitions> the number of transitions
 * @param [in] <num_states>      the number of states
 * @return An  @ref autError_t indicating the status of the operation.
 */
autError_t
aut_descriptor_set( autDescriptor_t *descriptor,
                    autState_t initstate,
                    size_t num_transitions,
                    size_t num_states);
/**
 * @brief Set the initial state of an autDescriptor_t
 * @param [in] <descriptor> a pointer to an autDescriptor_t
 * @param [in] <initstate> new value for the initial state
 * @return An  @ref autError_t indicating the status of the operation.
 */
autError_t
aut_descriptor_set_initstate( autDescriptor_t *descriptor,
                              autState_t initstate);

/**
 * @brief Retrieve the initial state specified in an autDescriptor_t
 * @param [in] <descriptor> a pointer to an autDescriptor_t
 * @return The initial state of the \p descriptor.
 * @pre \p descriptor <code> != NULL</code>
 */
autState_t
aut_descriptor_get_initstate( autDescriptor_t *descriptor);

/**
 * @brief Set the number of transitions of an autDescriptor_t
 * @param [in] <descriptor> a pointer to an autDescriptor_t
 * @param [in] <num_transitions> new value for the number of transitions
 * @return An  @ref autError_t indicating the status of the operation.
 */
autError_t
aut_descriptor_set_num_transitions( autDescriptor_t *descriptor,
                                    size_t num_transitions);

/**
 * @brief Retrieve the number of transitions specified in an autDescriptor_t
 * @param [in] <descriptor> a pointer to an autDescriptor_t
 * @return The number of transitions of the \p descriptor
 */
size_t
aut_descriptor_get_num_transitions(autDescriptor_t *descriptor);

/**
 * @brief Increment the number of transition by 1
 * @param [in] <descriptor> a pointer to an autDescriptor_t
 * @return An  @ref autError_t indicating the status of the operation.
 */
autError_t
aut_descriptor_num_transitions_inc(autDescriptor_t *descriptor);

/**
 * @brief Set the number of states of an autDescriptor_t
 * @param [in] <descriptor> a pointer to an autDescriptor_t
 * @param [in] <num_states> new value for the number of states
 * @return An  @ref autError_t indicating the status of the operation.
 */
autError_t
aut_descriptor_set_num_states( autDescriptor_t *descriptor,
                               size_t num_states);

/**
 * @brief Retrieve the number of states specified in an autDescriptor_t
 * @param [in] <descriptor> a pointer to an autDescriptor_t
 * @return The number of states of the \p descriptor
 */
size_t
aut_descriptor_get_num_states(autDescriptor_t *descriptor);

/**
 * @brief Increment the number of states by 1
 * @param [in] <descriptor> a pointer to an autDescriptor_t
 * @return On success the new number on states is returned. The old
 *  number of states is returned on failure.
 */
autError_t
aut_descriptor_num_states_inc(autDescriptor_t *descriptor);

#ifdef __cplusplus
}
#endif

#endif /* __AUT_REPR_DESCRIPTOR_H_INCLUDED__ */
