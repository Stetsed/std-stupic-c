#include "standard-test.h"
#include "stupid.h"
#include <unity.h>

void test_stupid_strlen(void) {
  char test_string_1[] = "Hello how are you doing!";
  char test_string_2[] = "Hello how are\0you doing!";

  int length_string_1 = stupid_strlen(test_string_1);
  int length_string_2 = stupid_strlen(test_string_2);

  // 24 because length of string is 24
  TEST_ASSERT_EQUAL(24, length_string_1);
  // 13 because a null terminator is in the middle
  TEST_ASSERT_EQUAL(13, length_string_2);
}

void test_stupid_power(void) {
  int power_result_1 = stupid_power(10, 4);
  int power_result_2 = stupid_power(100, 100000000);

  // 10^4 = 10000
  TEST_ASSERT_EQUAL(10000, power_result_1);
  // Should return -1 because it overflows
  TEST_ASSERT_EQUAL(-1, power_result_2);
}

void test_stupid_abs(void) {
  int abs_result_1 = stupid_abs(-10);
  int abs_result_2 = stupid_abs(42);
  int abs_result_3 = stupid_abs(-42);

  // Absolute value of -10 = 10
  TEST_ASSERT_EQUAL(10, abs_result_1);
  // Absolute value of both 42 and -42 should be 42
  TEST_ASSERT_EQUAL(42, abs_result_2);
  TEST_ASSERT_EQUAL(42, abs_result_3);
  TEST_ASSERT_EQUAL(abs_result_2, abs_result_3);
}

void test_stupid_char_int(void) {
  char test_string_1[] = "-120320";
  char test_string_2[] = "320";
  char test_string_3[] = "0";
  char test_string_4[] = "abc";

  int int_value_1 = stupid_char_int(test_string_1);
  int int_value_2 = stupid_char_int(test_string_2);
  int int_value_3 = stupid_char_int(test_string_3);
  int int_value_4 = stupid_char_int(test_string_4);

  TEST_ASSERT_EQUAL(-120320, int_value_1);
  TEST_ASSERT_EQUAL(320, int_value_2);
  TEST_ASSERT_EQUAL(0, int_value_3);
  // Should return 0 because it has no valid integer
  TEST_ASSERT_EQUAL(0, int_value_4);
}
