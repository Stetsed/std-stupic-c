#include "protocol/protocol-test.h"
#include "standard/standard-test.h"
#include "unity.h"
#include "unity_internals.h"

void setUp(void) {}
void tearDown(void) {}
int main(int argc, char *argv[]) {
  UNITY_BEGIN();
  // Standard library tests.
  RUN_TEST(test_stupid_strlen);
  RUN_TEST(test_stupid_power);
  RUN_TEST(test_stupid_abs);
  RUN_TEST(test_stupid_char_int);
  RUN_TEST(test_stupid_int_char);
  RUN_TEST(test_stupid_case_change);
  RUN_TEST(test_stupid_strcmp);
  RUN_TEST(test_stupid_strcpy);
  RUN_TEST(test_stupid_average);
  RUN_TEST(test_stupid_substring_find);
  RUN_TEST(test_stupid_bytes_to_hex);

  // Protocol Testing
  RUN_TEST(test_stpprt_message_test);
  return UNITY_END();
}
