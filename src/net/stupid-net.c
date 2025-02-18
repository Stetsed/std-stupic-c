/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */

#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdbool.h>
#include <stdint.h>
#include <stupid.h>
#include <sys/socket.h>
#include <sys/types.h>

uint32_t stupid_bytes_to_address(uint8_t *byte_array) {
  uint32_t address = 0;
  address |= byte_array[0] << 24;
  address |= byte_array[1] << 16;
  address |= byte_array[2] << 8;
  address |= byte_array[3];
  return address;
}
