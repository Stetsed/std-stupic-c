/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */

#ifndef STD_STUPID_PROTOCOL
#define STD_STUPID_PROTOCOL
#pragma once

#include <stdint.h>

#define STANDARD_BLAKE_HASH_SIZE 32
#define STANDARD_BLAKE_KEY (uint8_t *)"StupidProtocol"
#define STANDARD_BLAKE_KEY_SIZE 14
#define MAX_LENGTH_PACKET 127

typedef enum _stpprot_message_type {
  GET_MESSAGE = 128,
  SEND_MESSAGE = 0,
} stpprot_message_type;

typedef enum _stpprot_hash_status {
  HASH_VALID = 1,
  HASH_INVALID = 0,
} stpprot_hash_status;

/**
 * Protocol Design:
 *
 * | Start Byte | Data   | Hash    |
 * | 1 Byte     | X Byte | 32 Byte |
 *
 * Start Byte:
 *  - First bit determines whether it is sending(0) or requesting(1)
 *    information.
 *  - Bit 2-8 determines the length of the data field
 *
 * Data Field:
 *   - Length determined by Start Byte, max 2^7-1(127)
 *   - Contains arbitrary bytes as data
 * Hash:
 *   - 32 Byte Length Blake2b Hash
 *   - Blake2b hash salted with "StupidProtocol"
 */

typedef struct _stpprot_message_start_byte {
  uint8_t byte;
  stpprot_message_type type;
  uint8_t len;
} stpprot_message_start_byte_t;

typedef struct _stpprot_message_packet {
  stpprot_message_type type;
  stpprot_hash_status hash_status;
  uint8_t len;
  uint8_t data_bytes[MAX_LENGTH_PACKET];
  uint8_t hash[STANDARD_BLAKE_HASH_SIZE];
} stpprot_message_packet_t;

/**
 * Takes in a pointer to a message_packet object to initialize it to it's base
 * state.
 *
 * Input:
 * - Pointer to a message_packet object
 *
 * Returns:
 * - 0 Object is initialized
 * - -1 Pointer is NULL
 */
int stpprot_packet_init(stpprot_message_packet_t *packet);

/**
 * Takes in a pointer to a message_packet object, a pointer to an array of data
 * and the length of this data. It then inserts this into the packet including
 * calculating the start byte and the hash.
 *
 * Input:
 * - Pointer to a message_packet object
 * - Pointer to an array of bytes that is the data
 * - Int of the length of the array
 *
 * Returns:
 * - 0 Data is inserted
 * - -1 Pointer is NULL or length is too high
 */
int stpprot_packet_set_message(stpprot_message_packet_t *packet, uint8_t *data,
                               int len, stpprot_message_type type);

/**
 * Takes in a pointer to a message_packet object, a pointer to a byte array and
 * the length of this array. It then takes the start byte, data and hash from
 * the packet and puts it into the send_buffer, and returns the length of the
 * message to be sent.
 *
 * Input:
 * - Pointer to a message_packet object
 * - Pointer to an array of bytes that is the sending buffer
 * - Int of the length of the array
 *
 * Returns:
 * - >0 Total length of the packet
 * - -1 Pointer is NULL
 * - -2 Length of array is not long enough
 */
int stpprot_packet_prepare_message(stpprot_message_packet_t *packet,
                                   uint8_t *send_buffer, int len);

/**
 * Retrieve the data contained in the start byte including the length and the
 * type of the message.
 *
 * Input:
 * - Pointer to a message start byte
 * - Byte that is the first byte received
 *
 * Returns:
 * - 0 Data parsed succesfully
 * - -1 Pointer is NULL
 */
int stpprot_start_retrieve_data(stpprot_message_start_byte_t *start_byte,
                                uint8_t start);

/**
 * Retrieve the data contained in the start byte including the length and the
 * type of the message.
 *
 * Input:
 * - Pointer to a message start object that contains the first parsed byte that
 * was received
 * - Pointer to a message_packet object
 * - Pointer to an array of data that contains the amount of bytes specified in
 * the start byte
 *
 * Returns:
 * - 0 Data parsed succesfully
 * - -1 Pointer is NULL
 */
int stpprot_packet_parse(stpprot_message_start_byte_t *start_byte,
                         stpprot_message_packet_t *packet, uint8_t *data);

#endif /* ifndef STD_STUPID_PROTOCOL */
