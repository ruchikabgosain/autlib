/**
 * @file test/test_repr_descriptor.cpp
 * @brief Test functionality of aut/repr/descriptor.h
 */
#include <gtest/gtest.h>

extern "C" {
  #include <aut/repr.h>
}

TEST(MACRO__aut_empty_descriptor_h, _)
{
  autDescriptor_t *d = AUT_EMPTY_DESCRIPTOR_H;
  EXPECT_NE(d, nullptr);
  ASSERT_EQ(d->initstate, 0);
  ASSERT_EQ(d->num_states, 0);
  ASSERT_EQ(d->num_transitions, 0);
  free(d);
}

TEST(MACRO__aut_empty_descriptor_s, _)
{
  autDescriptor_t d = AUT_EMPTY_DESCRIPTOR_S;
  ASSERT_EQ(d.initstate, 0);
  ASSERT_EQ(d.num_states, 0);
  ASSERT_EQ(d.num_transitions, 0);
}

TEST(aut_descriptor_create, zeros)
{
  autDescriptor_t *d, *d2;
  d2 = d;
  auto err = aut_descriptor_create(&d, 0, 0, 0);

#if (AUT_STATE_COUNT_MIN > 0x0 || AUT_TRANS_COUNT_MIN > 0x0)
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(d, d2);
#else
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_NE(d, d2);
  ASSERT_EQ(d->initstate, 0);
  ASSERT_EQ(d->num_states, 0);
  ASSERT_EQ(d->num_transitions, 0);
  free(d);
#endif
}

TEST(aut_descriptor_create, valid)
{
  autDescriptor_t *d = nullptr;
  auto err = aut_descriptor_create(&d, 0, 10, 20);
  EXPECT_EQ(err, AUT_ESUCCESS);
  EXPECT_NE(d, nullptr);
  ASSERT_EQ(d->initstate, 0);
  ASSERT_EQ(d->num_transitions, 10);
  ASSERT_EQ(d->num_states, 20);
  free(d);
}

TEST(aut_descriptor_create, invalid_arg1)
{
  auto err = aut_descriptor_create(nullptr, 0, 10, 20);
  EXPECT_EQ(err, AUT_EINVAL1);
}

TEST(aut_descriptor_create, invalid_arg2)
{
  autDescriptor_t *d;
  auto err = aut_descriptor_create(&d, AUT_STATE_MAX + 1, 10, 20);
  EXPECT_EQ(err, AUT_EINVAL2);
}

TEST(aut_descriptor_create, invalid_arg3)
{
  autDescriptor_t *d;
  auto err = aut_descriptor_create(&d, 0, 0, 20);
  EXPECT_EQ(err, AUT_EINVAL3);
}

TEST(aut_descriptor_create, invalid_arg4)
{
  autDescriptor_t *d;
  auto err = aut_descriptor_create(&d, 0, 10, 0);
  EXPECT_EQ(err, AUT_EINVAL4);
}

TEST(aut_descriptor_init, valid)
{
  autDescriptor_t *d = (autDescriptor_t *) malloc(sizeof(autDescriptor_t));
  if (d) {
    auto err = aut_descriptor_init(d, 0, 10, 20);
    EXPECT_EQ(err, AUT_ESUCCESS);
    ASSERT_EQ(d->initstate, 0);
    ASSERT_EQ(d->num_transitions, 10);
    ASSERT_EQ(d->num_states, 20);
    free(d);
  }
}

TEST(aut_descriptor_init, invalid)
{
  autDescriptor_t *d = (autDescriptor_t *) malloc(sizeof(autDescriptor_t));
  if (d) {
    auto err = aut_descriptor_init(d, AUT_STATE_MAX + 1, 10, 20);
    EXPECT_NE(err, AUT_ESUCCESS);
    ASSERT_EQ(err, AUT_EINVAL2);
    free(d);
  }
}

TEST(aut_descriptor_new, _)
{
  autDescriptor_t *d;
  auto err = aut_descriptor_new(&d);
  EXPECT_EQ(err, AUT_ESUCCESS);
  EXPECT_NE(d, nullptr);
  ASSERT_EQ(d->initstate, 0);
  ASSERT_EQ(d->num_transitions, 0);
  ASSERT_EQ(d->num_states, 0);
  free(d);
}

TEST(aut_descriptor_destroy, _)
{
  autDescriptor_t *d;
  auto err = aut_descriptor_create(&d, 0, 10, 20);
  EXPECT_EQ(err, AUT_ESUCCESS);
  aut_descriptor_destroy(&d);
  ASSERT_EQ(nullptr, d);
  free(d);
}

TEST(aut_descriptor_dup, AUT_EMPTY_DESCRIPTOR_H__)
{
  autDescriptor_t *d = AUT_EMPTY_DESCRIPTOR_H;
  EXPECT_NE(d, nullptr);

  autDescriptor_t *dd;
  autError_t err = aut_descriptor_dup(d, &dd);

  EXPECT_NE(dd, nullptr);
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(dd->initstate,        d->initstate);
  ASSERT_EQ(dd->num_transitions,  d->num_transitions);
  ASSERT_EQ(dd->num_states,       d->num_states);

  free(d);
  free(dd);
}

TEST(aut_descriptor_dup, AUT_EMPTY_DESCRIPTOR_S__)
{
  autDescriptor_t d = AUT_EMPTY_DESCRIPTOR_S;
  autDescriptor_t *dd;
  autError_t err = aut_descriptor_dup(&d, &dd);
  EXPECT_NE(dd, nullptr);
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(dd->initstate,        d.initstate);
  ASSERT_EQ(dd->num_transitions,  d.num_transitions);
  ASSERT_EQ(dd->num_states,       d.num_states);
  free(dd);
}

TEST(aut_descriptor_dup, valid_stack)
{
  autDescriptor_t d = (autDescriptor_t) {0, 10, 20};
  autDescriptor_t *dd;
  autError_t err = aut_descriptor_dup(&d, &dd);
  EXPECT_NE(dd, nullptr);
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(dd->initstate,        d.initstate);
  ASSERT_EQ(dd->num_transitions,  d.num_transitions);
  ASSERT_EQ(dd->num_states,       d.num_states);
  free(dd);
}

TEST(aut_descriptor_dup, valid_heap)
{
  autDescriptor_t *d = (autDescriptor_t *) malloc(sizeof(autDescriptor_t));
  autDescriptor_t *dd;
  
  EXPECT_NE(d, nullptr);

  d->initstate        = 0; 
  d->num_transitions  = 1;
  d->num_states       = 2;
  
  autError_t err = aut_descriptor_dup(d, &dd);

  EXPECT_NE(dd, nullptr);
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(dd->initstate,        d->initstate);
  ASSERT_EQ(dd->num_transitions,  d->num_transitions);
  ASSERT_EQ(dd->num_states,       d->num_states);

  free(d);
  free(dd);
}

TEST(aut_descriptor_dup, invalid_nullarg1)
{
  autDescriptor_t *dd;

  autError_t err = aut_descriptor_dup(nullptr, &dd);

  EXPECT_EQ(err, AUT_EINVAL1);
}

TEST(aut_descriptor_dup, invalid_nullarg2)
{
  
  autDescriptor_t *d = (autDescriptor_t *) malloc(sizeof(autDescriptor_t));

  autError_t err = aut_descriptor_dup(d, nullptr);

  EXPECT_EQ(err, AUT_EINVAL2);

  free(d);
}


TEST(aut_descriptor_dup2, AUT_EMPTY_DESCRIPTOR_H__)
{
  autDescriptor_t *d = AUT_EMPTY_DESCRIPTOR_H;
  EXPECT_NE(d, nullptr);
  d->initstate       = 0;
  d->num_transitions = 10;
  d->num_states      = 20;

  autDescriptor_t *dd = AUT_EMPTY_DESCRIPTOR_H;
  EXPECT_NE(dd, nullptr);
  autError_t err = aut_descriptor_dup2(d, dd);
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(dd->initstate,        d->initstate);
  ASSERT_EQ(dd->num_transitions,  d->num_transitions);
  ASSERT_EQ(dd->num_states,       d->num_states);

  free(d);
  free(dd);
}

TEST(aut_descriptor_dup2, AUT_EMPTY_DESCRIPTOR_S__)
{
  autDescriptor_t *d = AUT_EMPTY_DESCRIPTOR_H;
  EXPECT_NE(d, nullptr);
  d->initstate       = 0;
  d->num_transitions = 10;
  d->num_states      = 20;

  autDescriptor_t dd = AUT_EMPTY_DESCRIPTOR_S;
  autError_t err = aut_descriptor_dup2(d, &dd);
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(dd.initstate,         d->initstate);
  ASSERT_EQ(dd.num_transitions,  d->num_transitions);
  ASSERT_EQ(dd.num_states,       d->num_states);

  free(d);
}

TEST(aut_descriptor_dup2, valid_stack_to_heap)
{
  autDescriptor_t d   = AUT_EMPTY_DESCRIPTOR_S;
  d.initstate       = 0;
  d.num_transitions = 10;
  d.num_states      = 20;
  autDescriptor_t *dd = AUT_EMPTY_DESCRIPTOR_H;
  EXPECT_NE(dd, nullptr);
  autError_t err = aut_descriptor_dup2(&d, dd);
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(dd->initstate,        d.initstate);
  ASSERT_EQ(dd->num_transitions,  d.num_transitions);
  ASSERT_EQ(dd->num_states,       d.num_states);
  free(dd);
}

TEST(aut_descriptor_dup2, invalid_nullarg1)
{
  autDescriptor_t *dd;
  autError_t err = aut_descriptor_dup2(nullptr, dd);
  EXPECT_EQ(err, AUT_EINVAL1);
}

TEST(aut_descriptor_dup2, invalid_nullarg2)
{
  autDescriptor_t *d = (autDescriptor_t *) malloc(sizeof(autDescriptor_t));
  autError_t err = aut_descriptor_dup2(d, nullptr);
  EXPECT_EQ(err, AUT_EINVAL2);
  free(d);
}

TEST(aut_descriptor_set, valid)
{
  autDescriptor_t *d;
  auto err = aut_descriptor_new(&d);
  EXPECT_EQ(err, AUT_ESUCCESS);
  EXPECT_NE(d, nullptr);
  ASSERT_EQ(d->initstate, 0);
  ASSERT_EQ(d->num_transitions, 0);
  ASSERT_EQ(d->num_states, 0);
  err = aut_descriptor_set(d, 2, 10, 20);
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(d->initstate, 2);
  ASSERT_EQ(d->num_transitions, 10);
  ASSERT_EQ(d->num_states, 20);
}

TEST(aut_descriptor_set, invalid_arg1)
{
  auto err = aut_descriptor_set(nullptr, 0, 10, 20);
  EXPECT_EQ(err, AUT_EINVAL1);
}

TEST(aut_descriptor_set, invalid_arg2)
{
  autDescriptor_t *d;
  auto err = aut_descriptor_new(&d);
  EXPECT_EQ(err, AUT_ESUCCESS);
  EXPECT_NE(d, nullptr);
  err = aut_descriptor_set(d, AUT_STATE_MAX + 1, 10, 20);
  EXPECT_EQ(err, AUT_EINVAL2);
}

TEST(aut_descriptor_set, invalid_arg3)
{
  autDescriptor_t *d;
  auto err = aut_descriptor_new(&d);
  EXPECT_EQ(err, AUT_ESUCCESS);
  EXPECT_NE(d, nullptr);
  err = aut_descriptor_set(d, 0, 0, 20);
  EXPECT_EQ(err, AUT_EINVAL3);
}

TEST(aut_descriptor_set, invalid_arg4)
{
  autDescriptor_t *d;
  auto err = aut_descriptor_new(&d);
  EXPECT_EQ(err, AUT_ESUCCESS);
  EXPECT_NE(d, nullptr);
  err = aut_descriptor_set(d, 0, 10, 0);
  EXPECT_EQ(err, AUT_EINVAL4);
}

TEST(aut_descriptor_set_initstate, valid)
{
  autDescriptor_t d    = AUT_EMPTY_DESCRIPTOR_S;
  autDescriptor_t *dd  = AUT_EMPTY_DESCRIPTOR_H;
  autError_t err;

  err = aut_descriptor_set_initstate(&d, 10);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(d.initstate, 10);
  err = aut_descriptor_set_initstate(&d, 20);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(d.initstate, 20);

  EXPECT_NE(dd, nullptr);
  err = aut_descriptor_set_initstate(dd, 10);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(dd->initstate, 10);
  err = aut_descriptor_set_initstate(dd, 20);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(dd->initstate, 20);
  free(dd);
}

TEST(aut_descriptor_set_initstate, invalid)
{
  autError_t err = aut_descriptor_set_initstate(nullptr, 10);
  ASSERT_EQ(err, AUT_EINVAL1);
  autDescriptor_t *d  = AUT_EMPTY_DESCRIPTOR_H;
  EXPECT_NE(d, nullptr);
  err = aut_descriptor_set_initstate(d, AUT_STATE_T_MAX);
  ASSERT_NE(err, AUT_EINVAL1);
#if AUT_STATE_MAX < AUT_STATE_T_MAX
  ASSERT_EQ(err, AUT_EINVAL2);
#endif
  free(d);
}

TEST(aut_descriptor_get_initstate, _)
{
  autState_t s;
  autDescriptor_t d   = AUT_EMPTY_DESCRIPTOR_S;
  s = aut_descriptor_get_initstate(&d);
  ASSERT_EQ(s, 0);
  d.initstate = 10;
  s = aut_descriptor_get_initstate(&d);
  ASSERT_EQ(s, 10);

  autDescriptor_t *dd  = AUT_EMPTY_DESCRIPTOR_H;
  EXPECT_NE(dd, nullptr);
  s = aut_descriptor_get_initstate(dd);
  ASSERT_EQ(s, 0);
  dd->initstate = 20;
  s = aut_descriptor_get_initstate(dd);
  ASSERT_EQ(s, 20);

  free(dd);
}

TEST(aut_descriptor_set_num_transitions, valid)
{
  autDescriptor_t d    = AUT_EMPTY_DESCRIPTOR_S;
  autDescriptor_t *dd  = AUT_EMPTY_DESCRIPTOR_H;
  autError_t err;

  err = aut_descriptor_set_num_transitions(&d, 10);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(d.num_transitions, 10);
  err = aut_descriptor_set_num_transitions(&d, 20);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(d.num_transitions, 20);

  EXPECT_NE(dd, nullptr);
  err = aut_descriptor_set_num_transitions(dd, 10);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(dd->num_transitions, 10);
  err = aut_descriptor_set_num_transitions(dd, 20);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(dd->num_transitions, 20);
  free(dd);
}

TEST(aut_descriptor_set_num_transitions, invalid)
{
  autError_t err = aut_descriptor_set_num_transitions(nullptr, 10);
  ASSERT_EQ(err, AUT_EINVAL1);
  autDescriptor_t *d  = AUT_EMPTY_DESCRIPTOR_H;
  EXPECT_NE(d, nullptr);
  err = aut_descriptor_set_num_transitions(d, AUT_TRANS_COUNT_T_MAX);
  ASSERT_NE(err, AUT_EINVAL1);
#if AUT_TRANS_COUNT_MAX < AUT_TRANS_COUNT_T_MAX
  ASSERT_EQ(err, AUT_EINVAL2);
#endif

  err = aut_descriptor_set_num_transitions(d, 0);
  ASSERT_NE(err, AUT_EINVAL1);
#if AUT_TRANS_COUNT_MIN > 0
  ASSERT_EQ(err, AUT_EINVAL2);
#endif

  free(d);
}

TEST(aut_descriptor_get_num_transitions, _)
{
  AUT_TRANS_COUNT_T t;
  autDescriptor_t d   = AUT_EMPTY_DESCRIPTOR_S;
  t = aut_descriptor_get_num_transitions(&d);
  ASSERT_EQ(t, 0);
  d.num_transitions = 10;
  t = aut_descriptor_get_num_transitions(&d);
  ASSERT_EQ(t, 10);

  autDescriptor_t *dd  = AUT_EMPTY_DESCRIPTOR_H;
  EXPECT_NE(dd, nullptr);
  t = aut_descriptor_get_num_transitions(dd);
  ASSERT_EQ(t, 0);
  dd->num_transitions = 20;
  t = aut_descriptor_get_num_transitions(dd);
  ASSERT_EQ(t, 20);

  free(dd);
}

TEST(aut_descriptor_num_transitions_inc, valid)
{
  autError_t err;
  autDescriptor_t d   = AUT_EMPTY_DESCRIPTOR_S;
  err = aut_descriptor_num_transitions_inc(&d);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(d.num_transitions, 1);

  d.num_transitions = 10;
  err = aut_descriptor_num_transitions_inc(&d);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(d.num_transitions, 11);

  autDescriptor_t *dd = AUT_EMPTY_DESCRIPTOR_H;
  EXPECT_NE(dd, nullptr);
  err = aut_descriptor_num_transitions_inc(dd);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(dd->num_transitions, 1);

  dd->num_transitions = 10;
  err = aut_descriptor_num_transitions_inc(dd);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(dd->num_transitions, 11);
  free(dd);
}

TEST(aut_descriptor_num_transitions_inc, invalid)
{
  autError_t err;
  err = aut_descriptor_num_transitions_inc(nullptr);
  ASSERT_EQ(err, AUT_EINVAL1);

  autDescriptor_t d   = AUT_EMPTY_DESCRIPTOR_S;
  d.num_transitions = AUT_TRANS_COUNT_MAX;
  err = aut_descriptor_num_transitions_inc(&d);
  ASSERT_EQ(err, AUT_EFAILURE);
  ASSERT_EQ(d.num_transitions, AUT_TRANS_COUNT_MAX);
  

  autDescriptor_t *dd = AUT_EMPTY_DESCRIPTOR_H;
  EXPECT_NE(dd, nullptr);
  dd->num_transitions = AUT_TRANS_COUNT_MAX;
  err = aut_descriptor_num_transitions_inc(dd);
  ASSERT_EQ(err, AUT_EFAILURE);
  ASSERT_EQ(dd->num_transitions, AUT_TRANS_COUNT_MAX);

  free(dd);
}

TEST(aut_descriptor_set_num_states, valid)
{
  autDescriptor_t d    = AUT_EMPTY_DESCRIPTOR_S;
  autDescriptor_t *dd  = AUT_EMPTY_DESCRIPTOR_H;
  autError_t err;

  err = aut_descriptor_set_num_states(&d, 10);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(d.num_states, 10);
  err = aut_descriptor_set_num_states(&d, 20);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(d.num_states, 20);

  EXPECT_NE(dd, nullptr);
  err = aut_descriptor_set_num_states(dd, 10);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(dd->num_states, 10);
  err = aut_descriptor_set_num_states(dd, 20);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(dd->num_states, 20);
  free(dd);
}

TEST(aut_descriptor_set_num_states, invalid)
{
  autError_t err = aut_descriptor_set_num_states(nullptr, 10);
  ASSERT_EQ(err, AUT_EINVAL1);
  autDescriptor_t *d  = AUT_EMPTY_DESCRIPTOR_H;
  EXPECT_NE(d, nullptr);
  err = aut_descriptor_set_num_states(d, AUT_STATE_COUNT_T_MAX);
  ASSERT_NE(err, AUT_EINVAL1);
#if AUT_STATE_COUNT_MAX < AUT_STATE_COUNT_T_MAX
  ASSERT_EQ(err, AUT_EINVAL2);
#endif

  err = aut_descriptor_set_num_states(d, 0);
  ASSERT_NE(err, AUT_EINVAL1);
#if AUT_STATE_COUNT_MIN > 0
  ASSERT_EQ(err, AUT_EINVAL2);
#endif
  free(d);
}

TEST(aut_descriptor_get_num_states, _)
{
  AUT_STATE_COUNT_T t;
  autDescriptor_t d   = AUT_EMPTY_DESCRIPTOR_S;
  t = aut_descriptor_get_num_states(&d);
  ASSERT_EQ(t, 0);
  d.num_states = 10;
  t = aut_descriptor_get_num_states(&d);
  ASSERT_EQ(t, 10);

  autDescriptor_t *dd  = AUT_EMPTY_DESCRIPTOR_H;
  EXPECT_NE(dd, nullptr);
  t = aut_descriptor_get_num_states(dd);
  ASSERT_EQ(t, 0);
  dd->num_states = 20;
  t = aut_descriptor_get_num_states(dd);
  ASSERT_EQ(t, 20);
  free(dd);
}

TEST(aut_descriptor_num_states_inc, valid)
{
  autError_t err;
  autDescriptor_t d   = AUT_EMPTY_DESCRIPTOR_S;
  err = aut_descriptor_num_states_inc(&d);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(d.num_states, 1);

  d.num_states = 10;
  err = aut_descriptor_num_states_inc(&d);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(d.num_states, 11);

  autDescriptor_t *dd = AUT_EMPTY_DESCRIPTOR_H;
  EXPECT_NE(dd, nullptr);
  err = aut_descriptor_num_states_inc(dd);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(dd->num_states, 1);

  dd->num_states = 10;
  err = aut_descriptor_num_states_inc(dd);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(dd->num_states, 11);
  free(dd);
}

TEST(aut_descriptor_num_states_inc, invalid)
{
  autError_t err;
  err = aut_descriptor_num_states_inc(nullptr);
  ASSERT_EQ(err, AUT_EINVAL1);

  autDescriptor_t d   = AUT_EMPTY_DESCRIPTOR_S;
  d.num_states = AUT_STATE_COUNT_MAX;
  err = aut_descriptor_num_states_inc(&d);
  ASSERT_EQ(err, AUT_EFAILURE);
  ASSERT_EQ(d.num_states, AUT_STATE_COUNT_MAX);
  

  autDescriptor_t *dd = AUT_EMPTY_DESCRIPTOR_H;
  EXPECT_NE(dd, nullptr);
  dd->num_states = AUT_STATE_COUNT_MAX;
  err = aut_descriptor_num_states_inc(dd);
  ASSERT_EQ(err, AUT_EFAILURE);
  ASSERT_EQ(dd->num_states, AUT_STATE_COUNT_MAX);
  free(dd);
}
