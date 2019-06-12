#ifndef __AUT_REPR_TRANSITION_H_INCLUDED__
#define __AUT_REPR_TRANSITION_H_INCLUDED__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include <aut/repr/action.h>
#include <aut/repr/limits.h>
#include <aut/repr/state.h>
#include <aut/util/error.h>

#define EMPTY_STR           ""
// #define EMPTY_TRANSITION    (aut_transition_create(STATE_MIN, STATE_MIN, EMPTY_STR))

#ifdef __cplusplus
  #define AUT_EMPTY_TRANSITION_H \
    (autTransition_t *) (calloc( sizeof( autTransition_t), 1))
#else
  #define AUT_EMPTY_TRANSITION_H \
    (calloc(sizeof( autTransition_t), 1))
#endif

#define AUT_EMPTY_TRANSITION_S \
  ((autTransition_t) {0, 0, AUT_ACTION_NONINIT})

/**
 * @brief Used to count the number of transitions
 */
// typedef size_t autsize_t;

/**
 * @brief Represents a transition in an AUT file
 * @details Each individual line after the descriptor is considered a transition.
 *    An AUT transition has the form:                  <br/>
 *    <code>(<from-state>, <label>, <to-state>)</code> <br/>
 *    More: https://cadp.inria.fr/man/aut.html         <br/>
 *    An autTransition_t is meant to be an immutable object and thus no setter
 *    functions are provided through the API. <br/> Modifying an autTransition_t
 *    is only possible by writting the struct fields directly. <br/> This is
 *    generaly  not encouraged and care should be taken when doing so. <br>
 *    In general, the API functions provided is the recommended way to handle autTransition_t
 *    objects.
 */
typedef struct autTransition_t
{
  /** The source state of the transition */
  autState_t source;
  /** The target state of the transition */
  autState_t target;
  /** The action of the transition */
  char *action;
} autTransition_t;

/**
 * @brief Create a new autTransition_t object and initialize it with values
 * @param [in] <source>      the source state of the transition
 * @param [in] <target>      the target state of the transition
 * @param [in] <action>      the action of the transition
 * @param [out]<transition>  a pointer to an autTransition_t pointer. Will be written
 *  to point to the newly allocated autTransition_t
 * @return An  @ref autError_t indicating the status of the operation.
 * @details A copy of \p action is stored
 */
autError_t
aut_transition_create( autTransition_t **transition,
                       autState_t source,
                       autState_t target,
                       const char * action);

autError_t
aut_transition_init( autTransition_t *transition,
                     autState_t source,
                     autState_t target,
                     const char * action);

/**
 * @brief Create a new, empty autTransition_t object. Source and target states are
 *  initialized to <code>0</code> and action to <code> NULL </code>.
 * @return @ref AUT_ESUCCESS on success, @ref AUT_EMALLOC on internal malloc error
 */
autError_t
aut_transition_new( autTransition_t **transition);

/**
 * @brief Safe destruction of an autTransition_t object
 * @param[in]  <transition> a pointer to an autTransition_t pointer
 * @details The memory pointed to by <code>*transition</code> is freed and
 *    the pointer is set to point to  <code>NULL</code>.
 */
void
aut_transition_destroy( autTransition_t **transition);

/**
 * @brief Create a copy of an autTransition_t
 * @param [in] a pointer to the autTransition_t to be copied
 * @return A pointer to a new autTransition_t object that is a copy
 *  of \p descriptor on success. <code>NULL</code> or error
 */
autError_t
aut_transition_dup( autTransition_t *orig,
                    autTransition_t **copy);

/**
 * @brief Copy the values from one autTransition_t to another
 * @param [in] <src> a pointer to the autTransition_t to be copied
 * @param [in] <copy> a pointer to the target autTransition_t object
 * @return A @ref autError_t indicating the status of the operation
 * @details \p copy must be a valid pointer to an autDescriptor_t object
 */
autError_t
aut_transition_dup2( autTransition_t *orig,
                    autTransition_t *copy);

/**
 * @brief Set the fields of an autTransition_t
 * @param[in] <transition> a pointer to an autTransition_t
 * @param[in] the source state of the transition
 * @param[in] the target state of the transition
 * @param[in] the action of the transition
 * @return A pointer to the (modified) autTransition_t object on success.
 *    <code>NULL</code> on error.
 * @details A copy of \p action is stored and the previous memory pointer
 *  to by the action member is freed.
 */
autError_t
aut_transition_set( autTransition_t *transition,
                    autState_t source,
                    autState_t target,
                    const char *action );

/**
 * @brief Set the source state of an autTransition_t
 * @param [in] <transition> a pointer to an autTransition_t
 * @param [in] <source> new value for the source state
 * @return A pointer to the (modified) autTransition_t object on success.
 *    <code>NULL</code> on error.
 */
autError_t
aut_transition_set_source( autTransition_t *transition,
                           autState_t source);

/**
 * @brief Retrieve the source state of an autTransition_t
 * @param [in] <transition> a pointer to an autTransition_t
 * @return The source state of the \p transition
 */
autState_t
aut_transition_get_source( autTransition_t *transition);

/**
 * @brief Set the target state of an autTransition_t
 * @param [in] <transition> a pointer to an autTransition_t
 * @param [in] <source> new value for the target state
 * @return A pointer to the (modified) autTransition_t object on success.
 *    <code>NULL</code> on error.
 */
autError_t
aut_transition_set_target(autTransition_t *transition, autState_t target);

/**
 * @brief Retrieve the target state of an autTransition_t
 * @param [in] <transition> a pointer to an autTransition_t
 * @return The target state of the \p transition
 */
autState_t
aut_transition_get_target(autTransition_t *transition);

/**
 * @brief Set the action of an autTransition_t
 * @param [in] <transition> a pointer to an autTransition_t
 * @param [in] <action>     a pointer to the new action
 * @param [in] <copy>       if <code>true</code> a copy of \p will be used,
 *  otherwise \p itself.
 * @return An  @ref autError_t indicating the status of the operation
 * @note The previous action is freed.
 */
autError_t
aut_transition_set_action( autTransition_t *transition, 
                           const char *action);

/**
 * @brief Retrieve the action of an autTransition_t
 * @param [in]  <transition> a pointer to an autTransition_t
 * @param [out] <action> a pointer what will point to the action after the operation
 * @note A  pointer to the actual value is returned, <b>not</b> a pointer to a copy.
    Thus, be careful to not accidentally free it.
 */
autError_t
aut_transition_get_action( autTransition_t *transition, 
                           char **action);

/**
 * @brief Retrieve a copy of the action of an autTransition_t
 */
autError_t
aut_transition_get_action_dup( autTransition_t *transition,
                               char **action);

/**
 * @brief Retrieve the length of the action string of an autTransition_t
 * @param [in] <transition> a pointer to an autTransition_t
 * @return The length of the action of  \p transition
 */
size_t
aut_transition_get_action_len(autTransition_t *transition);

#ifdef __cplusplus
}
#endif

#endif /* __AUT_REPR_TRANSITION_H_INCLUDED__ */
