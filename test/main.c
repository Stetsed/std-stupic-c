#include "standard/standard-test.h"
#include "unity.h"
#include "unity_internals.h"

void setUp(void) {}
void tearDown(void) {}
int main(int argc, char *argv[]) {
  UNITY_BEGIN();
  RUN_TEST(test_stupid_strlen);
  RUN_TEST(test_stupid_power);
  RUN_TEST(test_stupid_abs);
  RUN_TEST(test_stupid_char_int);
  return EXIT_SUCCESS;
  return UNITY_END();
}
