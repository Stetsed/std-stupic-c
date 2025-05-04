/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */

// Header
#include "stupid-protocol.h"
//

#include "monocypher.h"

int stpprot_packet_init(stpprot_message_packet_t *packet) {
  if (packet == NULL) {
    return -1;
  }
  for (int i = 0; i < MAX_LENGTH_PACKET; i++) {
    packet->data_bytes[i] = 0;
  }
  for (int i = 0; i < STANDARD_BLAKE_HASH_SIZE; i++) {
    packet->hash[i] = 0;
  }
  packet->hash_status = HASH_INVALID;
  packet->len = 0;
  packet->type = SEND_MESSAGE;
  return 0;
}

int stpprot_packet_set_message(stpprot_message_packet_t *packet, uint8_t *data,
                               int len, stpprot_message_type type) {
  if (packet == NULL || data == NULL || len > 127) {
    return -1;
  }

  crypto_blake2b_ctx ctx;

  crypto_blake2b_keyed_init(&ctx, STANDARD_BLAKE_HASH_SIZE, STANDARD_BLAKE_KEY,
                            STANDARD_BLAKE_KEY_SIZE);

  uint8_t start_byte = 0;
  start_byte ^= type;
  start_byte ^= len;

  crypto_blake2b_update(&ctx, &start_byte, 1);
  crypto_blake2b_update(&ctx, data, len);
  packet->type = type;
  packet->len = len;
  packet->hash_status = HASH_VALID;

  for (int i = 0; i < len; i++) {
    packet->data_bytes[i] = data[i];
  }

  uint8_t hash[STANDARD_BLAKE_HASH_SIZE] = {0};
  crypto_blake2b_final(&ctx, hash);
  for (int i = 0; i < STANDARD_BLAKE_HASH_SIZE; i++) {
    packet->hash[i] = hash[i];
  }

  return 0;
}

int stpprot_packet_prepare_message(stpprot_message_packet_t *packet,
                                   uint8_t *send_buffer, int len) {
  if (packet == NULL || send_buffer == NULL) {
    return -1;
  }
  // Make sure the length of the buffer is atleast 1(Start byte) + Len(Data) +
  // Hash Size
  if (len < (1 + packet->len + STANDARD_BLAKE_HASH_SIZE)) {
    return -2;
  }

  send_buffer[0] = 0;
  send_buffer[0] ^= packet->type;
  send_buffer[0] ^= packet->len;
  send_buffer++;

  for (int i = 0; i < packet->len; i++) {
    send_buffer[i] = packet->data_bytes[i];
  }
  send_buffer += packet->len;
  for (int i = 0; i < STANDARD_BLAKE_HASH_SIZE; i++) {
    send_buffer[i] = packet->hash[i];
  }
  return (1 + packet->len + STANDARD_BLAKE_HASH_SIZE);
}

int stpprot_start_retrieve_data(stpprot_message_start_byte_t *start_byte,
                                uint8_t start) {
  if (start_byte == NULL) {
    return -1;
  }

  start_byte->byte = start;
  start_byte->type = start & 128;
  start_byte->len = start & 127;
  return 0;
}

int stpprot_packet_parse(stpprot_message_start_byte_t *start_byte,
                         stpprot_message_packet_t *packet, uint8_t *data) {
  if (start_byte == NULL || packet == NULL || data == NULL) {
    return -1;
  }

  uint8_t hash[STANDARD_BLAKE_HASH_SIZE] = {0};
  crypto_blake2b_ctx ctx;

  crypto_blake2b_keyed_init(&ctx, STANDARD_BLAKE_HASH_SIZE, STANDARD_BLAKE_KEY,
                            STANDARD_BLAKE_KEY_SIZE);

  packet->type = start_byte->type;
  packet->len = start_byte->len;

  crypto_blake2b_update(&ctx, &start_byte->byte, 1);
  crypto_blake2b_update(&ctx, data, packet->len);
  crypto_blake2b_final(&ctx, hash);

  for (int i = 0; i < packet->len; i++) {
    packet->data_bytes[i] = data[i];
  }
  data += packet->len;
  for (int i = 0; i < STANDARD_BLAKE_HASH_SIZE; i++) {
    packet->hash[i] = data[i];
  }

  if (crypto_verify32(packet->hash, hash) == 0) {
    packet->hash_status = HASH_VALID;
  } else {
    packet->hash_status = HASH_INVALID;
  }

  return 0;
}
