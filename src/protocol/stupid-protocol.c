/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */

// Header
#include "stupid-protocol.h"
//

#include "monocypher.h"
#include "stupid.h"

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
