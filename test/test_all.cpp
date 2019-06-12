#include <gtest/gtest.h>

#include "test_read.cpp"
#include "test_repr_aut.cpp"
#include "test_repr_descriptor.cpp"
#include "test_repr_transition.cpp"

GTEST_API_ int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}