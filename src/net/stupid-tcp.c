/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */


#include "stupid-net.h"
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdbool.h>
#include <stdint.h>
#include <stupid.h>
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
  SocketStatus Status;
} TcpClient;

typedef struct TcpConnection {
  int socketfd;
  struct sockaddr_in ClientInformation;
  socklen_t ClientLength;
} TcpConnection;

TcpClient setup_tcp_client() {
  // Initialize a socket on IPv4, using TCP, and manual protocol selection, and
  // if blocking is false it also sets the socket to be non-blocking
  int socket_file = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
  // Returned an error;
  if (socket_file < 0) {
    stupid_handle_errno(errno);
  }

  TcpClient TcpClient = {.socketfd = socket_file, .Status = SocketInactive};
  return TcpClient;
}

void bind_tcp_client(TcpClient *client, uint16_t port, uint32_t address) {
  struct sockaddr_in address_info;
  address_info.sin_addr.s_addr = address;
  address_info.sin_port = port;
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
  while (1) {
    socketfd = accept(client->socketfd, (struct sockaddr *)&addr, &len);
    if (socketfd < 0) {
      if (errno != EAGAIN && errno != EWOULDBLOCK) {
        stupid_handle_errno(errno);
      }
    } else {
      break;
    }
  }
  connection->socketfd = socketfd;
  connection->ClientInformation = addr;
  connection->ClientLength = len;
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

  int status = 0;
  while (count > 0 && status > -1) {
    int bytes = write(connection->socketfd, buffer, count);
    buffer += bytes;
    count -= bytes;
  }
  if (status < 0) {
    // This shouldn't be possible cuz its a blocking socket??
    if (errno == EAGAIN || errno == EWOULDBLOCK) {
      return EXPECTED_ERROR;
    } else {
      return CATASTROPHIC_ERROR;
    }
  }
  return 0;
}
