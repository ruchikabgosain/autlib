/**
 * @file test/test_repr.cpp
 * @brief Test functionality of aut/repr/transition.h
 */
#include <gtest/gtest.h>

extern "C" {
  #include <string.h>
  #include <aut/repr.h>
}

TEST(MACRO__aut_empty_transition_h, _)
{
  autTransition_t *t = AUT_EMPTY_TRANSITION_H;
  EXPECT_NE(t, nullptr);
  ASSERT_EQ(t->source, 0);
  ASSERT_EQ(t->target, 0);
  ASSERT_EQ(t->action, nullptr);
}

TEST(MACRO__aut_empty_transition_s, _)
{
  autTransition_t t = AUT_EMPTY_TRANSITION_S;
  ASSERT_EQ(t.source, 0);
  ASSERT_EQ(t.target, 0);
  ASSERT_EQ(t.action, nullptr);
}

TEST(aut_transition_create, valid)
{
  autTransition_t *t = nullptr;
  auto err = aut_transition_create(&t, 0, 1, "a");
  EXPECT_EQ(err, AUT_ESUCCESS);
  EXPECT_NE(t, nullptr);
  ASSERT_EQ(t->source, 0);
  ASSERT_EQ(t->target, 1);
  ASSERT_EQ( strncmp("a", t->action, strlen("a")), 0);

  err = aut_transition_create(&t, 0, 1, 
    "aaaaaaaaaabbbbbbbbb");
  EXPECT_EQ(err, AUT_ESUCCESS);
  EXPECT_NE(t, nullptr);
  ASSERT_EQ(t->source, 0);
  ASSERT_EQ(t->target, 1);
  ASSERT_EQ( strncmp("aaaaaaaaaabbbbbbbbb", 
    t->action, strlen("aaaaaaaaaabbbbbbbbb")), 0);
}

TEST(aut_transition_create, invalid_arg1)
{
  auto err = aut_transition_create(nullptr, 0, 10, "a");
  EXPECT_EQ(err, AUT_EINVAL1);
}

TEST(aut_transition_create, invalid_arg2_arg3)
{
  autTransition_t *d;
  auto err = aut_transition_create(&d, AUT_STATE_MAX + 1, AUT_STATE_MAX + 1, "a");
  EXPECT_EQ(err, AUT_EINVAL2);
  err = aut_transition_create(&d, 2, AUT_STATE_MAX + 1, "a");
  EXPECT_EQ(err, AUT_EINVAL3);
}

TEST(aut_transition_create, valid_arg4_null)
{
  autTransition_t *d;
  auto err = aut_transition_create(&d, 1, 1, nullptr);
  EXPECT_EQ(err, AUT_ESUCCESS);
}

TEST(aut_transition_init, valid)
{
  autError_t err;
  autTransition_t *t = (autTransition_t *) calloc( sizeof(autTransition_t), 1);
  EXPECT_NE(t, nullptr);
  err = aut_transition_init(t, 0, 1, "a");
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(t->source, 0);
  ASSERT_EQ(t->target, 1);
  ASSERT_EQ( strncmp("a", t->action, strlen("a")), 0);

  err = aut_transition_create(&t, 0, 1, "aaaaaaaaaabbbbbbbbb");
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(t->source, 0);
  ASSERT_EQ(t->target, 1);
  ASSERT_EQ( strncmp("aaaaaaaaaabbbbbbbbb", 
    t->action, strlen("aaaaaaaaaabbbbbbbbb")), 0);
}

TEST(aut_transition_init, invalid_arg1)
{
  auto err = aut_transition_init(nullptr, 0, 10, "a");
  EXPECT_EQ(err, AUT_EINVAL1);
}

TEST(aut_transition_init, invalid_arg2_arg3)
{
  autTransition_t *t = (autTransition_t *) calloc( sizeof(autTransition_t), 1);
  auto err = aut_transition_init(t, AUT_STATE_MAX + 1, AUT_STATE_MAX + 1, "a");
  EXPECT_EQ(err, AUT_EINVAL2);
  err = aut_transition_init(t, 2, AUT_STATE_MAX + 1, "a");
  EXPECT_EQ(err, AUT_EINVAL3);
}

TEST(aut_transition_init, valid_arg4_null)
{
  autTransition_t *t = (autTransition_t *) calloc( sizeof(autTransition_t), 1);
  auto err = aut_transition_init(t, 1, 1, nullptr);
  EXPECT_EQ(err, AUT_ESUCCESS);
}

TEST(aut_transition_new, _)
{
  autTransition_t *d;
  auto err = aut_transition_new(&d);
  EXPECT_EQ(err, AUT_ESUCCESS);
  EXPECT_NE(d, nullptr);
  ASSERT_EQ(d->source, 0);
  ASSERT_EQ(d->target, 0);
  ASSERT_EQ(d->action, nullptr);
}

TEST(aut_transition_destroy, simple)
{
  autTransition_t *t = nullptr, *t1 = nullptr;
  t = AUT_EMPTY_TRANSITION_H;
  autError_t err;
  EXPECT_NE(t, nullptr);
  t1 = t;
  aut_transition_destroy(&t);
  ASSERT_EQ(t, nullptr);
  ASSERT_EQ(t1->action, nullptr);
}

TEST(aut_transition_dup, AUT_EMPTY_TRANSITION_H__)
{
  autTransition_t *d = AUT_EMPTY_TRANSITION_H;
  EXPECT_NE(d, nullptr);
  autTransition_t *dd;
  autError_t err = aut_transition_dup(d, &dd);
  EXPECT_NE(dd, nullptr);
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(dd->source,  d->source);
  ASSERT_EQ(dd->target,  d->target);
  ASSERT_EQ(dd->action,  nullptr);
}

TEST(aut_transition_dup, AUT_EMPTY_TRANSITION_S__)
{
  autTransition_t t = AUT_EMPTY_TRANSITION_S;
  autTransition_t *tt;
  autError_t err = aut_transition_dup(&t, &tt);
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(tt->source,  t.source);
  ASSERT_EQ(tt->target,  t.target);
  ASSERT_EQ(tt->action,  t.action);
}

TEST(aut_transition_dup, valid_stack)
{
  const char *action = "abc";
  autTransition_t t = (autTransition_t) {0, 10, (char*) action};
  autTransition_t *tt;
  autError_t err = aut_transition_dup(&t, &tt);
  EXPECT_NE(tt, nullptr);
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(tt->source,  t.source);
  ASSERT_EQ(tt->target,  t.target);
  ASSERT_EQ(strcmp(tt->action, t.action),  0);
}

TEST(aut_transition_dup, valid_heap)
{
  const char *action = "abc";
  autTransition_t *t = (autTransition_t*) malloc( sizeof(autTransition_t));
  autTransition_t *tt;
  t->source = 0;
  t->target = 1;
  t->action = strdup("ab");
  autError_t err = aut_transition_dup(t, &tt);
  EXPECT_NE(tt, nullptr);
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(tt->source,  t->source);
  ASSERT_EQ(tt->target,  t->target);
  ASSERT_EQ(strcmp(tt->action, t->action),  0);
  free(tt);
}

TEST(aut_transition_dup, invalid_nullarg1)
{
  autTransition_t *t;
  autError_t err = aut_transition_dup(nullptr, &t);
  EXPECT_EQ(err, AUT_EINVAL1);
}

TEST(aut_transition_dup, invalid_nullarg2)
{
  autTransition_t *t = (autTransition_t*) malloc( sizeof(autTransition_t));
  autError_t err = aut_transition_dup(t, nullptr);
  EXPECT_EQ(err, AUT_EINVAL2);
  free(t);
}

TEST(aut_transition_dup2, AUT_EMPTY_TRANSITION_H__)
{
  autTransition_t *t = AUT_EMPTY_TRANSITION_H;
  EXPECT_NE(t, nullptr);
  t->source = 0;
  t->target = 10;
  t->action = strdup("ab");
  autTransition_t *tt = AUT_EMPTY_TRANSITION_H;
  EXPECT_NE(tt, nullptr);
  autError_t err = aut_transition_dup2(t, tt);
  EXPECT_EQ(err, AUT_ESUCCESS);
  EXPECT_EQ(tt->source, t->source);
  EXPECT_EQ(tt->target, t->target);
  EXPECT_EQ(strcmp(tt->action, "ab"), 0);
  free(t);
}

TEST(aut_transition_dup2, AUT_EMPTY_TRANSITION_S__)
{
  autTransition_t t = AUT_EMPTY_TRANSITION_S;
  t.source = 0;
  t.target = 10;
  t.action = strdup("ab");
  autTransition_t *tt = AUT_EMPTY_TRANSITION_H;
  EXPECT_NE(tt, nullptr);
  autError_t err = aut_transition_dup2(&t, tt);
  EXPECT_EQ(err, AUT_ESUCCESS);
  EXPECT_EQ(tt->source, t.source);
  EXPECT_EQ(tt->target, t.target);
  EXPECT_EQ(strcmp(tt->action, "ab"), 0);
}

TEST(aut_transition_dup2, valid_stack)
{
  const char *action = "abc";
  autTransition_t t = (autTransition_t) {0, 10, (char*) action};
  autTransition_t *tt = (autTransition_t *) malloc( sizeof(autTransition_t));
  autError_t err = aut_transition_dup2(&t, tt);
  EXPECT_NE(tt, nullptr);
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(tt->source,  t.source);
  ASSERT_EQ(tt->target,  t.target);
  ASSERT_EQ(strcmp(tt->action, t.action),  0);
}

TEST(aut_transition_dup2, valid_heap)
{
  const char *action = "abc";
  autTransition_t *t = (autTransition_t*) malloc( sizeof(autTransition_t));
  autTransition_t *tt = (autTransition_t *) malloc( sizeof(autTransition_t));
  t->source = 0;
  t->target = 1;
  t->action = strdup("ab");
  autError_t err = aut_transition_dup2(t, tt);
  EXPECT_NE(tt, nullptr);
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(tt->source,  t->source);
  ASSERT_EQ(tt->target,  t->target);
  ASSERT_EQ(strcmp(tt->action, t->action),  0);
}

TEST(Aut_tranistion_dup2, valid_stack_to_heap)
{
  autTransition_t d   = AUT_EMPTY_TRANSITION_S;
  d.source  = 0;
  d.target  = 10;
  d.action  = strdup("ab");

  autTransition_t *dd = AUT_EMPTY_TRANSITION_H;
  EXPECT_NE(dd, nullptr);
  autError_t err = aut_transition_dup2(&d, dd);
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(dd->source, d.source);
  ASSERT_EQ(dd->target, d.target);
  ASSERT_EQ(strcmp(dd->action, d.action),  0);
}

TEST(aut_transition_dup2, invalid_nullarg1)
{
  autTransition_t *t;
  autError_t err = aut_transition_dup2(nullptr, t);
  EXPECT_EQ(err, AUT_EINVAL1);
}

TEST(aut_transition_dup2, invalid_nullarg2)
{
  autTransition_t *t = (autTransition_t*) malloc( sizeof(autTransition_t));
  autError_t err = aut_transition_dup(t, nullptr);
  EXPECT_EQ(err, AUT_EINVAL2);
  free(t);
}

TEST(aut_transition_set, valid)
{
  autTransition_t *t = AUT_EMPTY_TRANSITION_H;
  EXPECT_NE(t, nullptr);
  const char *action = "abc";
  autError_t err = aut_transition_set(t, 10, 20, action);
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(t->source, 10);
  ASSERT_EQ(t->target, 20);
  ASSERT_EQ( strcmp(t->action, action), 0);
  ASSERT_EQ(t->action, action);
  free(t);
}

TEST(aut_transition_set, invalid_arg1)
{
  auto err = aut_transition_set(nullptr, 0, 10, "ab");
  EXPECT_EQ(err, AUT_EINVAL1);
}

TEST(aut_transition_set, invalid_arg2)
{
  autTransition_t t = AUT_EMPTY_TRANSITION_S;
  auto err = aut_transition_set(&t, AUT_STATE_MAX + 1, 10, "ab");
  EXPECT_EQ(err, AUT_EINVAL2);
}

TEST(aut_transition_set, invalid_arg3)
{
  autTransition_t t = AUT_EMPTY_TRANSITION_S;
  auto err = aut_transition_set(&t, 10, AUT_STATE_MAX + 1, "ab");
  EXPECT_EQ(err, AUT_EINVAL3);
}

TEST(aut_transition_set, valid_nullarg4)
{
  autTransition_t *t = AUT_EMPTY_TRANSITION_H;
  EXPECT_NE(t, nullptr);
  autError_t err = aut_transition_set(t, 10, 20, nullptr);
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(t->source, 10);
  ASSERT_EQ(t->target, 20);
  ASSERT_EQ(t->action, nullptr);
  free(t);
}

TEST(aut_transition_set_source, valid)
{
  autTransition_t *t = AUT_EMPTY_TRANSITION_H;
  EXPECT_NE(t, nullptr);
  auto err = aut_transition_set_source(t, 10);
  ASSERT_EQ(t->source, 10);
  free(t);
}

TEST(aut_transition_set_source, invalid)
{
  autTransition_t *t = AUT_EMPTY_TRANSITION_H;
  EXPECT_NE(t, nullptr);
  auto err = aut_transition_set_source(nullptr, AUT_STATE_MAX + 1);
  ASSERT_EQ(err, AUT_EINVAL1);
  err = aut_transition_set_source(t, AUT_STATE_MAX + 1);
  ASSERT_EQ(err, AUT_EINVAL2);
  free(t);
}

TEST(aut_transition_get_source, _)
{
  autState_t s;
  autTransition_t *t = AUT_EMPTY_TRANSITION_H;
  s = aut_transition_get_source(t);
  ASSERT_EQ(s, 0);
  t->source = 10;
  s = aut_transition_get_source(t);
  ASSERT_EQ(s, 10);
  free(t);
  
  autTransition_t tt = AUT_EMPTY_TRANSITION_S;
  s = aut_transition_get_source(&tt);
  ASSERT_EQ(s, 0);
  tt.source = 10;
  s = aut_transition_get_source(&tt);
  ASSERT_EQ(s, 10);

}

TEST(aut_transition_set_target, valid)
{
  autTransition_t *t = AUT_EMPTY_TRANSITION_H;
  EXPECT_NE(t, nullptr);
  auto err = aut_transition_set_target(t, 10);
  ASSERT_EQ(t->target, 10);
  free(t);
}

TEST(aut_transition_set_target, invalid)
{
  autTransition_t *t = AUT_EMPTY_TRANSITION_H;
  EXPECT_NE(t, nullptr);
  auto err = aut_transition_set_target(nullptr, AUT_STATE_MAX + 1);
  ASSERT_EQ(err, AUT_EINVAL1);
  err = aut_transition_set_target(t, AUT_STATE_MAX + 1);
  ASSERT_EQ(err, AUT_EINVAL2);
  free(t);
}

TEST(aut_transition_get_target, _)
{
  autState_t s;
  autTransition_t *t = AUT_EMPTY_TRANSITION_H;
  s = aut_transition_get_target(t);
  ASSERT_EQ(s, 0);
  t->target = 10;
  s = aut_transition_get_target(t);
  ASSERT_EQ(s, 10);
  free(t);
  
  autTransition_t tt = AUT_EMPTY_TRANSITION_S;
  s = aut_transition_get_target(&tt);
  ASSERT_EQ(s, 0);
  tt.target = 10;
  s = aut_transition_get_target(&tt);
  ASSERT_EQ(s, 10);
}

TEST(aut_transition_set_action, simple)
{
  autTransition_t *t = AUT_EMPTY_TRANSITION_H;
  EXPECT_NE(t, nullptr);
  auto err = aut_transition_set_action(t, "abc");
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ( strcmp(t->action, "abc"), 0);
  free(t);
}

TEST(aut_transition_set_action, emptystr)
{
  autTransition_t *t = AUT_EMPTY_TRANSITION_H;
  EXPECT_NE(t, nullptr);
  auto err = aut_transition_set_action(t, "");
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ( strcmp(t->action, ""), 0);
  free(t);
}

TEST(aut_transition_set_action, nullaction)
{
  autTransition_t *t = AUT_EMPTY_TRANSITION_H;
  EXPECT_NE(t, nullptr);
  auto err = aut_transition_set_action(t, nullptr);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(t->action, nullptr);
  free(t);
}

TEST(aut_transition_set_action, invalid)
{
  autTransition_t *t = AUT_EMPTY_TRANSITION_H;
  EXPECT_NE(t, nullptr);
  auto err = aut_transition_set_action(nullptr, nullptr);
  ASSERT_EQ(err, AUT_EINVAL1);
  ASSERT_EQ( t->action, nullptr);
  free(t);
}

TEST(aut_transition_get_action, _)
{
  char *action;
  autTransition_t *t = AUT_EMPTY_TRANSITION_H;
  EXPECT_NE(t, nullptr);
  autError_t err = aut_transition_get_action(t, &action);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(action, nullptr);
  t->action = strdup("abc");
  err = aut_transition_get_action(t, &action);
  ASSERT_EQ( strcmp(t->action, "abc"), 0);
  free(t);
  
  action = nullptr;
  autTransition_t tt = AUT_EMPTY_TRANSITION_S;
  err = aut_transition_get_action(&tt, &action);
  ASSERT_EQ(err, AUT_ESUCCESS);
  tt.action = strdup("abc");
  err = aut_transition_get_action(&tt, &action);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ( strcmp(t->action, "abc"), 0);
  free(t);

  action = nullptr;
  char *act1 = strdup("abcd");
  char *act2 = act1;
  t->action = act1;
  err = aut_transition_get_action(&tt, &action);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_EQ(act2, action);
}

TEST(aut_transition_get_action, invalid_nullarg1)
{
  char *action;
  auto err = aut_transition_get_action( nullptr, &action);
  EXPECT_EQ(err, AUT_EINVAL1);
}

TEST(aut_transition_get_action, invalid_nullarg2)
{
  autTransition_t *t = AUT_EMPTY_TRANSITION_H;
  auto err = aut_transition_get_action( t, nullptr);
  ASSERT_EQ(err, AUT_EINVAL2);
}

TEST(aut_transition_get_action_dup, valid)
{
  autTransition_t *t = AUT_EMPTY_TRANSITION_H;
  EXPECT_NE(t, nullptr);
  char *act = strdup("abc");
  t->action = act;
  char *action;
  autError_t err = aut_transition_get_action_dup(t, &action);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_NE(act, action);
}

TEST(aut_transition_get_action_dup, invalid_nullarg1)
{
  auto err = aut_transition_get_action_dup(nullptr, nullptr);
  EXPECT_EQ(err, AUT_EINVAL1);
}
