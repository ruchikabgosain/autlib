#include <gtest/gtest.h>

extern "C" {
  #include <string.h>
  #include <aut/read.h>
}

#define SMALL_FILE_1  "../../files/simple/cycle.aut"
#define SMALL_FILE_2  "../../files/simple/serial.aut"
#define SMALL_FILE_3  "../../files/simple/confluence.aut"
#define SMALL_FILE_4  "../../files/simple/bintree1.aut"
#define MEDIUM_FILE_1 "../../files/mcrl2/bus.aut"
#define LARGE_FILE_1  "../../files/mcrl2/link1.1.aut"

bool find_transition(aut_t *lts, autState_t from, autState_t to, const char *action)
{
  autTransition_t *t;

  for ( size_t i = 0; i < aut_get_size(lts); ++i) {
    t = aut_get_transition(lts, i);
    if ( t->source == from && t->target == to && strcmp(t->action, action) == 0)  
        return true;
  }
  
  return false;
}
 
TEST(aut_read, invalid_args)
{
  aut_t *lts;
  autError_t err;
  err = aut_read(nullptr, nullptr);
  ASSERT_EQ(err, AUT_EINVAL1);
  err = aut_read("random", nullptr);
  ASSERT_EQ(err, AUT_EINVAL2);
}

TEST(aut_read, file_open_error)
{
  aut_t *lts;
  autError_t err;
  err = aut_read("../random", &lts);
  ASSERT_EQ(err, AUT_EFOPEN); 
  err = aut_read("", &lts);
  ASSERT_EQ(err, AUT_EFOPEN);
  err = aut_read(nullptr, &lts);
  ASSERT_EQ(err, AUT_EINVAL1);
}

TEST(aut_read, valid_descriptor)
{
  aut_t *lts;
  autError_t err;
  autDescriptor_t *d;

  err = aut_read(SMALL_FILE_1, &lts);
  EXPECT_EQ(err, AUT_ESUCCESS);
  d = aut_get_descriptor(lts);
  EXPECT_NE(d, nullptr);
  ASSERT_EQ(aut_descriptor_get_initstate(d), 1);
  ASSERT_EQ(aut_descriptor_get_num_transitions(d), 3);
  ASSERT_EQ(aut_descriptor_get_num_states(d), 3);
  aut_destroy(&lts);

  err = aut_read(SMALL_FILE_2, &lts);
  EXPECT_EQ(err, AUT_ESUCCESS);
  d = aut_get_descriptor(lts);
  EXPECT_NE(d, nullptr);
  ASSERT_EQ(aut_descriptor_get_initstate(d), 0);
  ASSERT_EQ(aut_descriptor_get_num_transitions(d), 3);
  ASSERT_EQ(aut_descriptor_get_num_states(d), 4);
  aut_destroy(&lts);

  err = aut_read(SMALL_FILE_3, &lts);
  EXPECT_EQ(err, AUT_ESUCCESS);
  d = aut_get_descriptor(lts);
  EXPECT_NE(d, nullptr);
  ASSERT_EQ(aut_descriptor_get_initstate(d), 0);
  ASSERT_EQ(aut_descriptor_get_num_transitions(d), 4);
  ASSERT_EQ(aut_descriptor_get_num_states(d), 4);
  aut_destroy(&lts);
}

TEST(aut_read, valid_transitions_simple_anton)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/simple/anton.aut", &lts);
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_TRUE(find_transition(lts, 0, 1, "t"));
  ASSERT_TRUE(find_transition(lts, 0, 2, "a"));
  ASSERT_TRUE(find_transition(lts, 3, 4, "a"));
  ASSERT_TRUE(find_transition(lts, 1, 7, "t"));
  ASSERT_TRUE(find_transition(lts, 3, 5, "b"));
  ASSERT_TRUE(find_transition(lts, 3, 6, "t"));
  ASSERT_TRUE(find_transition(lts, 6, 6, "c"));
  ASSERT_TRUE(find_transition(lts, 1, 3, "t"));
  ASSERT_TRUE(find_transition(lts, 7, 7, "c"));
}

TEST(aut_read, valid_transitions_simple_cycle)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/simple/cycle.aut", &lts);
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_TRUE(find_transition(lts, 0, 1, "f(1, g(\"2\"))"));
  ASSERT_TRUE(find_transition(lts, 2, 0, "c"));
  ASSERT_TRUE(find_transition(lts, 1, 2, "b"));
}

TEST(aut_read, valid_transitions_mcrl2_link01)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/mcrl2/link0.1.aut", &lts);
  EXPECT_EQ(err, AUT_ESUCCESS);
  ASSERT_TRUE(find_transition(lts, 26, 182, "PDind(id0, sig(a2, bottom))"));
  ASSERT_TRUE(find_transition(lts, 27, 46, "PDind(id0, sig(id0))"));
}


TEST(aut_read, valid_transition1)
{
  aut_t *lts;
  autError_t err;
  autDescriptor_t *d;
  err = aut_read("../../files/valid/valid_transition1.aut", &lts);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_TRUE(find_transition(lts, 0, 2, "a1111"));
}

TEST(aut_read, valid_transition2)
{
  aut_t *lts;
  autError_t err;
  autDescriptor_t *d;
  err = aut_read("../../files/valid/valid_transition2.aut", &lts);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_TRUE(find_transition(lts, 0, 2, "a_____"));
}

TEST(aut_read, valid_transition3)
{
  aut_t *lts;
  autError_t err;
  autDescriptor_t *d;
  err = aut_read("../../files/valid/valid_transition3.aut", &lts);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_TRUE(find_transition(lts, 0, 2, "a _   a"));
}

TEST(aut_read, valid_transition4)
{
  aut_t *lts;
  autError_t err;
  autDescriptor_t *d;
  err = aut_read("../../files/valid/valid_transition4.aut", &lts);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_TRUE(find_transition(lts, 0, 2, "\"\\n\""));
}

TEST(aut_read, valid_transition5)
{
  aut_t *lts;
  autError_t err;
  autDescriptor_t *d;
  err = aut_read("../../files/valid/valid_transition5.aut", &lts);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_TRUE(find_transition(lts, 0, 2, "\"\""));
}

TEST(aut_read, valid_transition6)
{
  aut_t *lts;
  autError_t err;
  autDescriptor_t *d;
  err = aut_read("../../files/valid/valid_transition6.aut", &lts);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_TRUE(find_transition(lts, 0, 2, "\""));
}

TEST(aut_read, valid_transition7)
{
  aut_t *lts;
  autError_t err;
  autDescriptor_t *d;
  err = aut_read("../../files/valid/valid_transition7.aut", &lts);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_TRUE(find_transition(lts, 0, 2, ""));
}

TEST(aut_read, valid_transition8)
{
  aut_t *lts;
  autError_t err;
  autDescriptor_t *d;
  err = aut_read("../../files/valid/valid_transition8.aut", &lts);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_TRUE(find_transition(lts, 0, 2, "**"));
}

TEST(aut_read, valid_transition9)
{
  aut_t *lts;
  autError_t err;
  autDescriptor_t *d;
  err = aut_read("../../files/valid/valid_transition9.aut", &lts);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_TRUE(find_transition(lts, 0, 2, "*"));
}

TEST(aut_read, valid_transition10)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/valid/valid_transition10.aut", &lts);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_TRUE(find_transition(lts, 1, 2, "________"));
}

TEST(aut_read, valid_transition11)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/valid/valid_transition11.aut", &lts);
  ASSERT_EQ(err, AUT_ESUCCESS);
  ASSERT_TRUE(find_transition(lts, 1, 2, "f(f(f(f())))"));
}




TEST(aut_read, invalid_empty)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;

  err = aut_read("../../files/invalid/invalid_empty.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_descriptor1)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;

  err = aut_read("../../files/invalid/invalid_descriptor1.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_descriptor2)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_descriptor2.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_EINTERNAL); //MALLOC FAIL unless huge memory available
}

TEST(aut_read, invalid_descriptor3)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;

  err = aut_read("../../files/invalid/invalid_descriptor3.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_descriptor4)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_descriptor4.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_descriptor5)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_descriptor5.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_descriptor6)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_descriptor6.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_descriptor7)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_descriptor7.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_descriptor8)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_descriptor8.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_descriptor9)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_descriptor9.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_descriptor10)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_descriptor10.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_missing_transitions)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_missing_transitions.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_transition1)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;

  err = aut_read("../../files/invalid/invalid_transition1.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
} 

TEST(aut_read, invalid_transition2)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_transition2.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_transition3)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_transition3.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_transition4)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_transition4.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_transition5)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_transition5.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_transition6)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_transition6.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_transition7)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_transition7.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_transition8)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_transition8.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_transition9)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_transition9.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_transition10)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_transition10.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_transition11)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_transition11.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_transition12)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_transition12.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}

TEST(aut_read, invalid_transition13)
{
  aut_t *lts;
  autDescriptor_t *d;
  autError_t err;
  err = aut_read("../../files/invalid/invalid_transition13.aut", &lts);
  ASSERT_NE(err, AUT_ESUCCESS);
  ASSERT_EQ(err, AUT_ESYNTAX);
}
