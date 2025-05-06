#if defined(unix) || defined(__unix__) || defined(__unix)
/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */
#ifndef STD_STUPID_UNIX
#define STD_STUPID_UNIX
#pragma once

#include <netinet/ip.h>
#include <poll.h>
#include <standard/stupid.h>
#include <stdint.h>
#include <unistd.h>

/**
 * Takes in a pointer to a null-terminated character array and prints this to
 * STDOUT(1)
 *
 * Input:
 * - Pointer to a charachter array
 *
 * Returns:
 * - 0 String was correctly printed
 * - -1 if pointer was NULL
 */
int stupid_print(const char *output);

/**
 * Takes in a pointer to a null-terminated character array and prints this to
 * STDOUT(1) and a line return
 *
 * Input:
 * - Pointer to a character array
 *
 * Returns:
 * - 0 String was correctly printed
 * - -1 if pointer was NULL
 */
int stupid_println(const char *output);

/**
 * Takes in a pointer to a byte array, and an amount of bytes to read from
 * STDIN(0)
 *
 * Input:
 * - Pointer to a byte array to store data in
 * - Int of the amount of bytes to read, not > size buffer
 *
 * Returns:
 * - >=0 Amount of bytes read into buffer
 * - -1 Pointer to buffer was NULL or Error occurred while reading
 */
int stupid_buffer_read(uint8_t *buff, int bytes);

/**
 * Takes in an upper bound and a lower bound and generates a random number, rand
 * source should be set before calling with srand(time(NULL))
 *
 * Input:
 * - Int of the maximum number the random should return
 * - Int of the minimum number the random should return
 *
 * Returns:
 * - Maximum > Return > Minimum Integer is returned
 */
int stupid_random(int maximum, int minimum);

typedef enum _stpunix_socket_status {
  SocketInactive,
  SocketActive,
  SocketError,
} stpunix_socket_status_s;

typedef struct _stpunix_tcp_instance {
  int socketfd;
  struct pollfd poll_descriptor;
  stpunix_socket_status_s status;
} stpunix_tcp_instance_s;

typedef struct _stpunix_tcp_connection {
  int socketfd;
  struct sockaddr_in clientinfo;
  struct pollfd poll_descriptor;
  struct pollfd poll_descriptor_r;
  socklen_t clientlen;
  stpunix_socket_status_s status;
} stpunix_tcp_connection_s;

/**
 * Takes in a pointer to a TCP Instance object to initialize it to it's base
 * state.
 *
 * Input:
 * - Pointer to a TCP Instance object
 *
 * Returns:
 * - 0 Object is initialized
 * - -1 Pointer is NULL
 */
int stpunix_instance_init(stpunix_tcp_instance_s *instance);

// Binds the TCPInstance to the given port and address, will exit if error case
// is hit, such as if the address is already in use, or it doesn't exist. The
// address is in the form of it's binary representation.

/**
 * Takes in a pointer to a TCP Instance object and binds it to the given address
 * and port.
 *
 * Input:
 * - Pointer to a TCP Instance object
 * - 32-bit Integer that represents the address
 * - 16-bit Integer that represents the port
 *
 * Returns:
 * - 0 Instance is bound
 * - -1 Pointer is NULL
 * - -2 Binding failed
 */
int stpunix_bind_tcp_serv(stpunix_tcp_instance_s *server, uint32_t address,
                          uint16_t port);

/**
 * Takes in a pointer to a TCP Instance object binds it to a an OS assigned port
 * to act as a client.
 *
 * Input:
 * - Pointer to a TCP Instance object
 *
 * Returns:
 * - 0 Instance is bound
 * - -1 Pointer is NULL
 * - -2 Binding failed
 */
int stpunix_bind_tcp_client(stpunix_tcp_instance_s *client);

// Takes in a TcpInstance and connects to a remote host on the given address and
// port. This will use the Instance's socketfd to use in the connection socketfd
// due to client fd's being 1:1 instead of 1:*.

/**
 * Takes in a pointer to a TCP Instance object and a TCP Connection object and
 * uses the Instance to connect to the remote host, it then stores this
 * connection using the same Socketfd from the instance to the connection, it
 * should be assumed after this point that TCP Instance is used up.
 *
 * Input:
 * - Pointer to a TCP Instance object
 * - Pointer to a TCP Connection object
 * - 32-bit Integer that represents the address of the remote
 * - 16-bit Integer that represents the port of the remote
 *
 * Returns:
 * - 0 Connection is setup
 * - -1 Pointer is NULL
 * - -2 Connection failed
 */
int stpunix_connect_tcp_client(stpunix_tcp_instance_s *client,
                               stpunix_tcp_connection_s *connection,
                               uint32_t address, uint16_t port);

/**
 * Takes in a pointer to a TCP Instance object that represents the server, and a
 * TCP Connection Object, it then attempts to accept a connection on the
 * Instance and if valid it will store it in the TCP Connection object.
 *
 * Input:
 * - Pointer to a TCP Instance object
 * - Pointer to a TCP Connection object
 *
 * Returns:
 * - 0 Connection is setup
 * - -1 Pointer is NULL or there was an error on accepting a Connection
 * - -2 When attempting to accept a connection an expected error was received
 */
int stpunix_accept_connection_serv(stpunix_tcp_instance_s *server,
                                   stpunix_tcp_connection_s *connection);

/**
 * Takes in a pointer to a TCP Instance object that represents the server, and a
 * TCP Connection Object, it then attempts to accept a connection on the
 * Instance and if valid it will store it in the TCP Connection object. Blocking
 * until the poll receives a return
 *
 * Input:
 * - Pointer to a TCP Instance object
 * - Pointer to a TCP Connection object
 *
 * Returns:
 * - 0 Connection is setup
 * - -1 Pointer is NULL or there was an error on accepting a Connection
 */
int stpunix_blocking_accept_connection_serv(
    stpunix_tcp_instance_s *server, stpunix_tcp_connection_s *connection);

/**
 * Takes in a pointer to a TCP Connection object, and a buffer of bytes, and
 * reads from the connection into the buffer up to a maximun of the value of len
 * of bytes.
 *
 * Input:
 * - Pointer to a TCP Connection Object
 * - Pointer to an array of bytes
 * - Int that represents the maximun number of bytes to read, <= length of array
 *
 * Returns:
 * - >0 Amount of bytes read
 * - 0 Socket has become inactive
 * - -1 Pointer is NULL or there was an error on reading
 * - -2 When attempting to read the connection it is blocked in an expected way
 */
int stpunix_read_connection(stpunix_tcp_connection_s *connection,
                            uint8_t *buffer, int len);

/**
 * Takes in a pointer to a TCP Connection object, and a buffer of bytes, and
 * writes from the buffer into connection buffer for len amount of bytes.
 *
 * Input:
 * - Pointer to a TCP Connection Object
 * - Pointer to an array of bytes
 * - Int that represents the number of bytes to written, <= length of array
 *
 * Returns:
 * - 0 Have finished writing buffer to socket
 * - -1 Pointer is NULL or there was an error on writing
 */
int stpunix_write_connection(stpunix_tcp_connection_s *connection,
                             uint8_t *buffer, int len);

/**
 * Takes in a pointer to a TCP Connection object and polls it to see if it's
 * active
 *
 * Input:
 * - Pointer to a TCP Connection Object
 *
 * Returns:
 * - >0 Amount of descriptors returned
 * - 0 No active polls
 * - -1 Polling returned error or pointer is NULL
 */
int stpunix_poll_connection(stpunix_tcp_connection_s *connection);

#endif /* ifndef STD_STUPID_UNIX */

#endif /* Check if platform is unix */
