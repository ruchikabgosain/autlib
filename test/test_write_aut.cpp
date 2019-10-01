#include <gtest/gtest.h>

#include <cstdio>

extern "C" {
  #include <string.h>
  #include <aut.h>
  #include <aut/write.h>
}

#define SMALL_FILE_1  "../../files/simple/cycle.aut"
#define SMALL_FILE_2  "../../files/simple/serial.aut"
#define SMALL_FILE_3  "../../files/simple/confluence.aut"
#define SMALL_FILE_4  "../../files/simple/bintree1.aut"
#define MEDIUM_FILE_1 "../../files/mcrl2/bus.aut"
#define LARGE_FILE_1  "../../files/mcrl2/link1.1.aut"

#define OUTFILE "outfile.aut"

TEST(aut_write, invalid_arg)
{
  aut_t *lts;
  autError_t err;
  err = aut_write(NULL, lts);
  ASSERT_EQ(err, AUT_EINVAL1);
  err = aut_write(OUTFILE, NULL);
  ASSERT_EQ(err, AUT_EINVAL2);
}

TEST(aut_write, valid)
{
  aut_t *lts1, *lts2;
  autError_t err = aut_read(SMALL_FILE_1, &lts1);
  EXPECT_EQ( AUT_ESUCCESS, err);
  EXPECT_NE( AUT_NULL, lts1);

  err = aut_write(OUTFILE, lts1);
  EXPECT_EQ( AUT_ESUCCESS, err);

  err = aut_read(OUTFILE, &lts2);
  EXPECT_EQ( AUT_ESUCCESS, err);

  autDescriptor_t *d1 = aut_get_descriptor(lts1);
  autDescriptor_t *d2 = aut_get_descriptor(lts2);
  EXPECT_NE(AUT_NULL, d1);
  EXPECT_NE(AUT_NULL, d2);

  ASSERT_EQ(aut_descriptor_get_initstate(d1), aut_descriptor_get_initstate(d2));
  ASSERT_EQ(aut_descriptor_get_num_transitions(d1), aut_descriptor_get_num_transitions(d2));
  ASSERT_EQ(aut_descriptor_get_num_states(d1), aut_descriptor_get_num_states(d2));

  autTransition_t *t1, *t2;
  char *a1, *a2;

  for ( size_t i = 0; i < aut_descriptor_get_num_transitions(d1); ++i) {
    t1 = aut_get_transition(lts1, i);
    t2 = aut_get_transition(lts2, i);

    ASSERT_EQ(aut_transition_get_source(t1), aut_transition_get_source(t2));
    ASSERT_EQ(aut_transition_get_target(t1), aut_transition_get_target(t2));
    err = aut_transition_get_action(t1, &a1);
    ASSERT_EQ(AUT_ESUCCESS, err);
    err = aut_transition_get_action(t2, &a2);
    ASSERT_EQ(AUT_ESUCCESS, err);
    ASSERT_EQ( 0, strcmp(a1, a2));
  }

  remove(OUTFILE);
}


