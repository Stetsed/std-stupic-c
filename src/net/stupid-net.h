/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */

#ifndef STD_STUPID_NET
#define STD_STUPID_NET
#pragma once

#include "stupid-net.c"
// Takes in an array of bytes, and returns a uint32_t that represents the
// address to be used in network byte order.
uint32_t stupid_bytes_to_address(uint8_t *byte_array);

#endif // !STD_STUPID_NET
