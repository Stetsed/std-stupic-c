/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */

#ifndef STD_STUPID_TCP
#define STD_STUPID_TCP
#pragma once

#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <poll.h>
#include <stdbool.h>
#include <stdint.h>
#include <stupid.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

typedef enum SocketStatus {
  SocketInactive,
  SocketActive,
  SocketError,

} SocketStatus;

typedef enum ClientType {
  Client,
  Server,
  Unitialized,
} ClientType;

typedef struct TcpInstance {
  int socketfd;
  struct pollfd poll_descriptor;
  SocketStatus Status;
  ClientType type;
} TcpInstance;

typedef struct TcpConnection {
  int socketfd;
  struct sockaddr_in ClientInformation;
  struct pollfd poll_descriptor;
  struct pollfd poll_descriptor_r;
  socklen_t ClientLength;
  SocketStatus Status;
} TcpConnection;

// Returns an instance of type TcpClient, which holds the Status of the socket
// and the socket file descriptor it has. It can error and will exit if the
// creation of the socket which is of type IPv4 and TCP fails, this can also
// happen if the OS is an older linux version and doesn't support non-block
// sock.
TcpInstance setup_tcp_instance();

// Binds the TCPInstance to the given port and address, will exit if error case
// is hit, such as if the address is already in use, or it doesn't exist. The
// address is in the form of it's binary representation.
void bind_tcp_serv(TcpInstance *client, uint16_t port, uint32_t address);

// Ment to be used for TCP Clients which make outbound connection, will bind to
// all addresses locally and a random OS designated port, this should be used if
// you plan to make outbound connections according to spec.
void bind_tcp_client(TcpInstance *client);

// Takes in a TcpInstance and connects to a remote host on the given address and
// port. This will use the Instance's socketfd to use in the connection socketfd
// due to client fd's being 1:1 instead of 1:*.
int connect_tcp_client(TcpInstance *client, TcpConnection *connection,
                       uint16_t port, uint32_t address);
// Takes in a struct of type client and type connection, it then fills this
// with data, if the return is 0 this should be a valid socket file
// descriptor, if it's -2 an error that is due to no connection being
// available. If another error happens such as as the given TcpClient has an
// invalid socket it will return -1;
int accept_connection(TcpInstance *instance, TcpConnection *connection);

// Takes in a struct of type client and type connection, it then fills this
// withis with data, if the return is 0 it means it was valid, otherwise it will
// continue looping till one is available, if another error happens such as the
// socket isn't valid, it will error with a return of -1, and connection should
// be assumed to be invalid.
int accept_connection_blocking(TcpInstance *instance,
                               TcpConnection *connection);

// Functio that takes in a TCP connection, a buffer and the amount of bytes to
// be read, it will then attempt to read this, and it returns a positive integer
// of the amount of bytes it was able to read, or a -1 with a socket failure for
// example, or -2 if there isn't data available to read, can be avoided by
// polling it first, but shouldn't be possible because the socketfd is blocking,
int read_connection(TcpConnection *connection, uint8_t *buffer, uint count);

// Function that takes in a TCPConnection, and a buffer of bytes that should be
// sent over the connection, and a count of these bytes, it will loop until
// either the entire message is sent, or an error is hit, however this should
// only happen in cases of invalid socket, as it's blocking so shouldn't be able
// to return a normal expected error.
int write_connection(TcpConnection *connection, uint8_t const *buffer,
                     uint count);

// Polls a connection using it's pollfd, will either return 0 if no events where
// gotten, or a 1 if an event was received. It can also return -1 if an error
// was encountered.
int poll_connection(TcpConnection *connection);

// Function that takes in a connection and closes it's socketfd, after this
// function is ran it should be assumed that the socketfd is no longer usable to
// send or receive data.
void close_connection(TcpConnection *connection);
#endif /* ifndef STD_STUPID_TCP */
