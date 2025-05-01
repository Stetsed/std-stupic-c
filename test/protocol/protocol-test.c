#include "protocol-test.h"
#include "protocol/stupid-protocol.h"
#include <unity.h>

void test_stpprt_message_test(void) {
  char data_buffer[] = "Hello how are you doing?";

  stpprot_message_packet_t packet_send;
  stpprot_packet_init(&packet_send);
  stpprot_packet_set_message(&packet_send, (uint8_t *)data_buffer,
                             sizeof(data_buffer) - 1, SEND_MESSAGE);

  uint8_t output_buffer[256] = {0};
  uint8_t *output_buffer_p = output_buffer;

  stpprot_packet_prepare_message(&packet_send, output_buffer,
                                 sizeof(output_buffer));

  stpprot_message_start_byte_t start_byte_receive;
  stpprot_message_packet_t packet_receive;
  stpprot_start_retrieve_data(&start_byte_receive, output_buffer_p[0]);
  output_buffer_p++;
  stpprot_packet_parse(&start_byte_receive, &packet_receive, output_buffer_p);

  TEST_ASSERT_EQUAL_MESSAGE(HASH_VALID, packet_receive.hash_status,
                            "Hash was not valid");
  TEST_ASSERT_EQUAL_UINT8_ARRAY((uint8_t *)data_buffer,
                                packet_receive.data_bytes, packet_receive.len);
}
