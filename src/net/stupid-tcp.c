/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */


#include "stupid-net.h"
#include <errno.h>
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

typedef struct TcpClient {
  int socketfd;
  struct pollfd poll_descriptor;
  SocketStatus Status;
} TcpClient;

typedef struct TcpConnection {
  int socketfd;
  struct sockaddr_in ClientInformation;
  struct pollfd poll_descriptor;
  socklen_t ClientLength;
} TcpConnection;

TcpClient setup_tcp_client() {
  // Initialize a socket on IPv4, using TCP, and manual protocol selection, and
  // if blocking is false it also sets the socket to be non-blocking
  int socketfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
  // Returned an error;
  if (socketfd < 0) {
    stupid_handle_errno(errno);
  }
  struct pollfd poll_descriptor = {socketfd, POLLIN};
  TcpClient TcpClient = {.socketfd = socketfd,
                         .poll_descriptor = poll_descriptor,
                         .Status = SocketInactive};
  return TcpClient;
}

void bind_tcp_client(TcpClient *client, uint16_t port, uint32_t address) {
  struct sockaddr_in address_info;
  address_info.sin_addr.s_addr = htonl(address);
  address_info.sin_port = htons(port);
  address_info.sin_family = AF_INET;
  if (bind(client->socketfd, (struct sockaddr *)&address_info,
           sizeof(address_info)) < 0) {
    stupid_handle_errno(errno);
  };
  if (listen(client->socketfd, 16)) {
    stupid_handle_errno(errno);
  }
  client->Status = SocketActive;
}

void bind_tcp_client_array(TcpClient *client, uint16_t port,
                           uint8_t *address_array) {
  uint32_t address = stupid_bytes_to_address(address_array);
  struct sockaddr_in address_info;
  address_info.sin_addr.s_addr = htonl(address);
  address_info.sin_port = htons(port);
  address_info.sin_family = AF_INET;
  if (bind(client->socketfd, (struct sockaddr *)&address_info,
           sizeof(address_info)) < 0) {
    stupid_handle_errno(errno);
  };
  if (listen(client->socketfd, 16)) {
    stupid_handle_errno(errno);
  }
  client->Status = SocketActive;
}
// Takes in a struct of type client and type connection, it then fills this with
// data, if the return is 0 this should be a valid socket file descriptor, if
// it's -2 an error that is due to no connection being available. If another
// error happens such as as the given TcpClient has an invalid socket it will
// return -1;
int accept_connection(TcpClient *client, TcpConnection *connection) {
  struct sockaddr_in addr;
  socklen_t len;
  int socketfd;
  socketfd = accept(client->socketfd, (struct sockaddr *)&addr, &len);
  if (socket < 0) {
    if (errno == EAGAIN || errno == EWOULDBLOCK) {
      return EXPECTED_ERROR;
    } else {
      return CATASTROPHIC_ERROR;
    }
  }
  connection->ClientInformation = addr;
  connection->ClientLength = len;
  connection->socketfd = socketfd;
  return NO_ERROR;
}

int accept_connection_blocking(TcpClient *client, TcpConnection *connection) {
  struct sockaddr_in addr;
  socklen_t len;
  int socketfd;
  if (poll(&client->poll_descriptor, 1, -1) == 1) {
    socketfd = accept(client->socketfd, (struct sockaddr *)&addr, &len);
  } else {
    return CATASTROPHIC_ERROR;
  }
  connection->socketfd = socketfd;
  connection->ClientInformation = addr;
  connection->ClientLength = len;
  struct pollfd poll_descriptor = {socketfd, POLLIN};
  connection->poll_descriptor = poll_descriptor;
  return NO_ERROR;
}

int read_connection(TcpConnection *connection, uint8_t *buffer, uint count) {
  int status = read(connection->socketfd, buffer, count);

  if (status < 0) {
    // This shouldn't be possible cuz its a blocking socket??
    if (errno == EAGAIN || errno == EWOULDBLOCK) {
      return EXPECTED_ERROR;
    } else {
      return CATASTROPHIC_ERROR;
    }
  }
  return status;
}

int write_connection(TcpConnection *connection, uint8_t const *buffer,
                     uint count) {
  while (count > 0) {
    int bytes_status = write(connection->socketfd, buffer, count);
    if (bytes_status < 0) {
      return CATASTROPHIC_ERROR;
    } else {
      count -= bytes_status;
    }
  }
  return 0;
}

int poll_connection(TcpConnection *connection) {
  int polling = poll(&connection->poll_descriptor, 1, 10);

  return polling;
}
