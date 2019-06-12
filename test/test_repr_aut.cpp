/**
 * @file test/test_repr_aut.cpp
 * @brief Test functionality of aut/repr/aut.h
 */
#include <gtest/gtest.h>
#include <aut/repr.h>

extern "C" {
  #include <stdlib.h>
  #include <string.h>
}

TEST(aut_create, valid_stack_values)
{
  aut_t *aut;
  autError_t err;
  autDescriptor_t desc;
  err = aut_descriptor_init(&desc, 0, 1, 2);
  EXPECT_EQ(err, AUT_ESUCCESS);
#if __AUT_MAJOR == 0
  err = aut_create( &aut, &desc, "t");
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(aut->size, 0);
  ASSERT_NE(aut->descriptor, nullptr);
  ASSERT_EQ(aut->descriptor->initstate, 0);
  ASSERT_EQ(aut->descriptor->num_transitions, 1);
  ASSERT_EQ(aut->descriptor->num_states, 2);
  ASSERT_NE(aut->transitions, nullptr);
  ASSERT_EQ(aut->transitions[0].source, 0);
  ASSERT_EQ(aut->transitions[0].target, 0);
  ASSERT_EQ(aut->transitions[0].action, nullptr);
  ASSERT_EQ(strcmp(aut->tau, "t"), 0);
#endif
  free(aut);
}

TEST(aut_create, valid_heap_values)
{
  aut_t *aut;
  autError_t err;
  autDescriptor_t *desc;
  err = aut_descriptor_create(&desc, 0, 1, 2);
  EXPECT_EQ(err, AUT_ESUCCESS);
#if __AUT_MAJOR == 0
  err = aut_create( &aut, desc, "t");
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(aut->size, 0);
  ASSERT_NE(aut->descriptor, nullptr);
  ASSERT_EQ(aut->descriptor->initstate, 0);
  ASSERT_EQ(aut->descriptor->num_transitions, 1);
  ASSERT_EQ(aut->descriptor->num_states, 2);
  ASSERT_NE(aut->transitions, nullptr);
  ASSERT_EQ(aut->transitions[0].source, 0);
  ASSERT_EQ(aut->transitions[0].target, 0);
  ASSERT_EQ(aut->transitions[0].action, nullptr);
  ASSERT_EQ(strcmp(aut->tau, "t"), 0);
#endif
  free(desc);
  free(aut);
}

TEST(aut_create, invalid)
{
  aut_t *aut;
  autDescriptor_t *desc = AUT_EMPTY_DESCRIPTOR_H;
  ASSERT_EQ( aut_create(nullptr, nullptr, nullptr), AUT_EINVAL1);
  ASSERT_EQ( aut_create(&aut, nullptr, nullptr), AUT_EINVAL2);
  ASSERT_EQ( aut_create(&aut, desc, AUT_TAU_UNKNOWN), AUT_ESUCCESS);
  ASSERT_EQ( aut_create(&aut, desc, nullptr), AUT_ESUCCESS);
  ASSERT_EQ( aut_create(&aut, desc, NULL), AUT_ESUCCESS);
}

TEST(aut_destroy, valid)
{
  aut_t *lts, *lts1;
  autDescriptor_t *desc = AUT_EMPTY_DESCRIPTOR_H;
  desc->initstate = 10;
  desc->num_transitions = 20;
  EXPECT_EQ( aut_create(&lts, desc, "tau"), AUT_ESUCCESS);
  ASSERT_EQ(lts->descriptor, desc);
  ASSERT_EQ(lts->descriptor->initstate, 10);
  
  lts1 = lts;
  aut_destroy(&lts);
  ASSERT_EQ( lts, nullptr);
  ASSERT_NE(desc, nullptr);
  
  //The following is generally correct however due to allocator metadata
  //written at the start of of the memory of lts mad lts1 it may not be true.
  //In fact it is most likely that the opposite is true since the first bytes
  //will be most likely zeroed out of free. The behaviour depends on the 
  //malloc version.
  //
  //ASSERT_NE( lts1->descriptor, nullptr);
  //
  //So lets at least check for the following. Even in an extreme case that an
  //allocator that keeps out-of-band metadata is used the following should
  //work as after aut_destroy(l), l->descriptor is set to NULL
  ASSERT_NE(lts1->descriptor, desc);
  
  //Since we are now past the metadata, the following being, the last member of
  //the struct, should be fine to check anyway
  ASSERT_EQ( lts1->_capacity, 20);

  ASSERT_EQ(desc->num_transitions, 20);
  ASSERT_NE(desc->initstate, 10);
}


TEST(aut_get_descriptor, _)
{
  aut_t *lts;
  autDescriptor_t *desc = AUT_EMPTY_DESCRIPTOR_H;
  desc->initstate = 42;
  EXPECT_EQ( aut_create(&lts, desc, "tau"), AUT_ESUCCESS);

  autDescriptor_t *d = aut_get_descriptor(lts);
  EXPECT_NE(d, nullptr);
  ASSERT_EQ(d, desc);
  ASSERT_EQ(d->initstate, 42);
  free(lts);
}

TEST(aut_get_transitions,)
{
  aut_t *lts;
  autDescriptor_t *desc = AUT_EMPTY_DESCRIPTOR_H;
  desc->initstate = 0;
  desc->num_transitions = 2;
  desc->num_states = 3;
  EXPECT_EQ( aut_create(&lts, desc, "tau"), AUT_ESUCCESS);
  autTransition_t *transitions = (autTransition_t *) malloc( sizeof(autTransition_t) * 2);
  transitions[0].source = 0;
  transitions[0].target = 1;
  transitions[0].action = strdup("a");
  transitions[1].source = 1;
  transitions[1].target = 2;
  transitions[1].action = strdup("b");
  lts->transitions = transitions;
  ASSERT_EQ( lts->_capacity, 2);

  autTransition_t *ts = aut_get_transitions(lts);
  EXPECT_NE(ts, nullptr);
  ASSERT_EQ(ts, transitions);
  ASSERT_EQ(ts[0].source, 0);
  ASSERT_EQ(ts[0].target, 1);
  ASSERT_EQ(strcmp(ts[0].action, "a"), 0);
  ASSERT_EQ(ts[1].source, 1);
  ASSERT_EQ(ts[1].target, 2);
  ASSERT_EQ(strcmp(ts[1].action, "b"), 0);
  free(transitions);
  free(desc);
  free(lts);
}

TEST(aut_get_transition, invalid_null_arg1)
{
  autTransition_t *transition = aut_get_transition(nullptr, 0);
  EXPECT_EQ(transition, nullptr);
}

TEST(aut_get_transition, invalid_outofrange_arg2)
{
  aut_t *lts;
  autDescriptor_t *desc = AUT_EMPTY_DESCRIPTOR_H;
  desc->initstate = 0;
  desc->num_transitions = 2;
  desc->num_states = 3;
  EXPECT_EQ( aut_create(&lts, desc, "tau"), AUT_ESUCCESS);
  autTransition_t *transition = aut_get_transition(lts, 0);
  ASSERT_EQ(transition, nullptr);
  transition = aut_get_transition(lts, 1);
  ASSERT_EQ(transition, nullptr);
  aut_destroy(&lts);
}

TEST(aut_get_num_transitions,)
{
  aut_t *lts;
  autDescriptor_t *desc = AUT_EMPTY_DESCRIPTOR_H;
  desc->initstate = 0;
  desc->num_transitions = 2;
  EXPECT_EQ( aut_create(&lts, desc, "tau"), AUT_ESUCCESS);

  size_t m = aut_get_num_transitions(lts);
  ASSERT_EQ(m, 2);
  ASSERT_EQ(m, lts->descriptor->num_transitions);
  ASSERT_EQ(m, lts->_capacity);
  ASSERT_NE(m, lts->size);
  free(desc);
  free(lts);
}

TEST(aut_get_num_states,)
{
  aut_t *lts;
  autDescriptor_t *desc = AUT_EMPTY_DESCRIPTOR_H;
  desc->initstate = 0;
  desc->num_states = 2;
  EXPECT_EQ( aut_create(&lts, desc, "tau"), AUT_ESUCCESS);
  size_t m = aut_get_num_states(lts);
  ASSERT_EQ(m, 2);
  free(desc);
  free(lts);
}

TEST(aut_add_transition, invalid_args)
{
  aut_t *lts;
  autDescriptor_t *desc = AUT_EMPTY_DESCRIPTOR_H;
  EXPECT_EQ( aut_create(&lts, desc, "tau"), AUT_ESUCCESS);
  autError_t err = aut_add_transition(nullptr, 0, 1, nullptr);
  ASSERT_EQ(err, AUT_EINVAL1);
  err = aut_add_transition(lts, AUT_STATE_MAX + 1, 1, nullptr);
  ASSERT_EQ(err, AUT_EINVAL2);
  err = aut_add_transition(lts, 1, AUT_STATE_MAX + 1, nullptr);
  ASSERT_EQ(err, AUT_EINVAL3);
  free(desc);
  free(lts);
}

TEST(aut_add_transition, invalid_full)
{
  aut_t *lts;
  autDescriptor_t *desc = AUT_EMPTY_DESCRIPTOR_H;
  EXPECT_EQ( aut_create(&lts, desc, "tau"), AUT_ESUCCESS);
  ASSERT_EQ( lts->size, 0);
  ASSERT_EQ( lts->_capacity, 0);
  autError_t err = aut_add_transition(lts, 0, 1, "a");
  ASSERT_EQ(err, AUT_EFULL);
  ASSERT_NE( lts->size, 1);
  aut_destroy(&lts);

  desc = AUT_EMPTY_DESCRIPTOR_H;
  desc->num_transitions = 2;
  EXPECT_EQ( aut_create(&lts, desc, "tau"), AUT_ESUCCESS);
  ASSERT_EQ(lts->size, 0);
  ASSERT_EQ(lts->_capacity, 2);
  err = aut_add_transition(lts, 0, 1, "a");
  ASSERT_EQ(err, AUT_ESUCCESS);
  err = aut_add_transition(lts, 1, 2, "b");
  ASSERT_EQ(err, AUT_ESUCCESS);
  err = aut_add_transition(lts, 0, 2, "c");
  ASSERT_EQ(err, AUT_EFULL);
  free(desc);
  free(lts);
}

TEST(aut_add_transition, valid)
{
  aut_t *lts;
  autDescriptor_t *desc = AUT_EMPTY_DESCRIPTOR_H;
  desc->num_transitions = 2;
  EXPECT_EQ(aut_create(&lts, desc, "tau"), AUT_ESUCCESS);
  ASSERT_EQ(lts->size, 0);
  EXPECT_EQ(aut_add_transition(lts, 0, 1, "a"), AUT_ESUCCESS);
  EXPECT_EQ(aut_add_transition(lts, 1, 2, "b"), AUT_ESUCCESS);
  ASSERT_EQ(aut_add_transition(lts, 1, 2, "b"), AUT_EFULL);
  autTransition_t *t = aut_get_transition(lts, 0);
  EXPECT_NE(t, nullptr);
  ASSERT_EQ(t->source, 0);
  ASSERT_EQ(t->target, 1);
  ASSERT_EQ(strcmp(t->action, "a"), 0);
  t = aut_get_transition(lts, 1);
  EXPECT_NE(t, nullptr);
  ASSERT_EQ(t->source, 1);
  ASSERT_EQ(t->target, 2);
  ASSERT_EQ(strcmp(t->action, "b"), 0);
  t = aut_get_transition(lts, 2);
  ASSERT_EQ(t, nullptr);
  aut_destroy(&lts);
}

TEST(aut_get_size, __)
{
  aut_t *lts;
  autDescriptor_t *desc = AUT_EMPTY_DESCRIPTOR_H;
  desc->num_transitions = 2;
  std::string action("tau");
  EXPECT_EQ( aut_create(&lts, desc, action.c_str()), AUT_ESUCCESS);
  ASSERT_EQ( aut_get_size(lts), 0);
  autError_t err = aut_add_transition(lts, 0, 1, "ab");
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(aut_get_size(lts), 1);
  err = aut_add_transition(lts, 1, 2, "bc");
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(aut_get_size(lts), 2);
  err = aut_add_transition(lts, 1, 2, "bc");
  ASSERT_EQ(err, AUT_EFULL);
  ASSERT_EQ(aut_get_size(lts), 2);
  free(desc);
  free(lts->transitions); 
  free(lts);
}

TEST(aut_isempty, )
{
  aut_t *lts;
  autDescriptor_t *desc = AUT_EMPTY_DESCRIPTOR_H;
  desc->num_transitions = 2;
  EXPECT_EQ( aut_create(&lts, desc, "tau"), AUT_ESUCCESS);
  ASSERT_EQ( aut_get_size(lts), 0);
  ASSERT_EQ( aut_isempty(lts), true);
  autError_t err = aut_add_transition(lts, 0, 1, "ab");
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(aut_get_size(lts), 1);
  ASSERT_EQ( aut_isempty(lts), false);
  free(desc);
  free(lts);
}

TEST(aut_get_tau, _)
{
  aut_t *lts;
  autDescriptor_t *desc;
  autError_t err;
  err = aut_descriptor_create(&desc, 0, 10, 10);
  EXPECT_EQ(err, AUT_ESUCCESS);
  err = aut_create(&lts, desc, "abcd");
  EXPECT_EQ(err, AUT_ESUCCESS);
  char *tau = aut_get_tau(lts);
  EXPECT_NE(tau, AUT_NULL);
  ASSERT_EQ(strcmp(tau, "abcd"), 0);
}
