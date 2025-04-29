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

void test_stupid_int_char(void) {
  int test_int_1 = 82000;
  int test_int_2 = -72000;
  int test_int_3 = 0;
  int test_int_4 = -386;

  char test_buffer_1[64];
  char test_buffer_2[64];
  char test_buffer_3[64];
  char test_buffer_4[4];

  int result_1 =
      stupid_int_char(test_buffer_1, sizeof(test_buffer_1), test_int_1);
  int result_2 =
      stupid_int_char(test_buffer_2, sizeof(test_buffer_2), test_int_2);
  int result_3 =
      stupid_int_char(test_buffer_3, sizeof(test_buffer_3), test_int_3);
  int result_4 =
      stupid_int_char(test_buffer_4, sizeof(test_buffer_4), test_int_4);

  TEST_ASSERT_EQUAL_CHAR_ARRAY("82000", test_buffer_1, stupid_strlen("82000"));
  TEST_ASSERT_EQUAL_CHAR_ARRAY("-72000", test_buffer_2,
                               stupid_strlen("-72000"));
  TEST_ASSERT_EQUAL_CHAR_ARRAY("0", test_buffer_3, stupid_strlen("0"));
  // Should return an error because the array is not big enough, so should be -1
  TEST_ASSERT_EQUAL(result_4, -1);
}
