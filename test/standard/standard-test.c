#include "standard-test.h"
#include "stupid.h"
#include <stdint.h>
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

  stupid_int_char(test_buffer_1, sizeof(test_buffer_1), test_int_1);
  stupid_int_char(test_buffer_2, sizeof(test_buffer_2), test_int_2);
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

void test_stupid_case_change(void) {
  char test_buffer_1[] = "Hello how are you doing?";
  char test_buffer_2[] = "ITS 1Am, why ask...";
  stupid_str_lowercase(test_buffer_1);
  stupid_str_lowercase(test_buffer_2);

  TEST_ASSERT_EQUAL_CHAR_ARRAY("hello how are you doing?", test_buffer_1,
                               stupid_strlen(test_buffer_1));
  TEST_ASSERT_EQUAL_CHAR_ARRAY("its 1am, why ask...", test_buffer_2,
                               stupid_strlen(test_buffer_2));

  stupid_str_uppercase(test_buffer_1);
  stupid_str_uppercase(test_buffer_2);

  TEST_ASSERT_EQUAL_CHAR_ARRAY("HELLO HOW ARE YOU DOING?", test_buffer_1,
                               stupid_strlen(test_buffer_1));
  TEST_ASSERT_EQUAL_CHAR_ARRAY("ITS 1AM, WHY ASK...", test_buffer_2,
                               stupid_strlen(test_buffer_2));
}

void test_stupid_strcmp(void) {
  char test_buffer_1[] = "This is the first string";
  char test_buffer_2[] = "This is the second string";
  char test_buffer_3[] = "This is the first string\0That is a lie";

  // Should not be -2 as there not equal
  int result_1 = stupid_strcmp(test_buffer_1, test_buffer_2);
  // Should be 0 because it uses strlen to find the length
  int result_2 = stupid_strcmp(test_buffer_1, test_buffer_3);

  TEST_ASSERT_EQUAL(-2, result_1);
  TEST_ASSERT_EQUAL(0, result_2);
}

void test_stupid_strcpy(void) {
  char test_buffer_1[] = "This is the first string.";
  char test_buffer_2[] = "This is the second string";
  char test_buffer_3[] = "This is the first string\0That is a lie";

  char destbuffer_1[32] = {0};
  char destbuffer_2[32] = {0};
  char destbuffer_3[32] = {0};

  // Should copy over the entirety of test_buffer_1
  stupid_strcpy(destbuffer_1, test_buffer_1);
  // Should copy over the first 4 character so "This"
  stupid_strncpy(destbuffer_2, test_buffer_2, 4);
  // Should copy over the entirety of test_buffer_3
  stupid_strcpy(destbuffer_3, test_buffer_3);

  TEST_ASSERT_EQUAL_CHAR_ARRAY(test_buffer_1, destbuffer_1,
                               stupid_strlen(test_buffer_1));
  TEST_ASSERT_EQUAL_CHAR_ARRAY("This", destbuffer_2, 4);
  TEST_ASSERT_EQUAL_CHAR_ARRAY(test_buffer_3, destbuffer_3,
                               stupid_strlen(test_buffer_3));
}

void test_stupid_average(void) {
  // Average should be 12, (10+10+10+10+20)/5=12
  int test_int_1 = 10 + 10 + 10 + 10 + 20;
  float average_1 = stupid_average(test_int_1, 5);

  // Average should be 15.8, (10+10+29+10+20)/5=15.8
  int test_int_2 = 10 + 10 + 29 + 10 + 20;
  float average_2 = stupid_average(test_int_2, 5);

  // Average should be 20.2, (10+32+29+10+20)/5=20.2
  int test_int_3 = 10 + 32 + 29 + 10 + 20;
  float average_3 = stupid_average(test_int_3, 5);

  TEST_ASSERT_EQUAL_FLOAT(12, average_1);
  TEST_ASSERT_EQUAL_FLOAT(15.8, average_2);
  TEST_ASSERT_EQUAL_FLOAT(20.2, average_3);
}

void test_stupid_substring_find(void) {
  char test_buffer_1[] = "This is the first string.";
  char test_buffer_2[] = "This is the second string";
  char test_buffer_3[] = "This is the first string\0That is a lie";

  char test_substring_1[] = "string";
  char test_substring_2[] = "i";
  char test_substring_3[] = "lie";

  // Should find it on the index 18 as that's where the s character of string
  // is with 0 indexing
  int result_1 = stupid_find_substring(test_buffer_1, test_substring_1);
  // Should find it on index 2 because it's the first i that is present.
  int result_2 = stupid_find_substring(test_buffer_2, test_substring_2);
  // Should not find it and as such return -2 because it's after the inserted
  // null-terminator.
  int result_3 = stupid_find_substring(test_buffer_3, test_substring_3);

  TEST_ASSERT_EQUAL(18, result_1);
  TEST_ASSERT_EQUAL(2, result_2);
  TEST_ASSERT_EQUAL(-2, result_3);
}

void test_stupid_bytes_to_hex(void) {
  uint8_t test_bytes_1[] = {
      'a', 'c', 'd', 'e', 'h', 'm', 'q', 'x', 'c', 'd', 'z',
  };
  // Known correct representation of above bytes in hexadecimal format.
  char test_bytes_1_converted[] = "61636465686d717863647a";

  char output_buffer[128] = {0};

  // Should return -1 because the size of the buffer is smaller than 2*(Bytes)+1
  int result_1 =
      stupid_bytes_to_hex(output_buffer, 8, test_bytes_1, sizeof(test_bytes_1));
  stupid_bytes_to_hex(output_buffer, sizeof(output_buffer), test_bytes_1,
                      sizeof(test_bytes_1));

  TEST_ASSERT_EQUAL(-1, result_1);
  TEST_ASSERT_EQUAL_CHAR_ARRAY(test_bytes_1_converted, output_buffer,
                               sizeof(test_bytes_1_converted));
}
