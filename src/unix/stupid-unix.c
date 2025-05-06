#if defined(unix) || defined(__unix__) || defined(__unix)
/*
 * Copyright (c) Quinn Hooft (Stetsed)
 * SPDX-License-Identifier: MIT
 */

// Header
#include "stupid-unix.h"
//

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int stupid_print(const char *output) {
  if (output == NULL) {
    return -1;
  }
  write(STDOUT, output, stupid_strlen(output));
  return 0;
}

int stupid_println(const char *output) {
  if (output == NULL) {
    return -1;
  }
  write(STDOUT, output, stupid_strlen(output));
  write(STDOUT, "\n", 1);
  return 0;
}

int stupid_buffer_read(uint8_t *buff, int bytes) {
  if (buff == NULL) {
    return -1;
  }
  int length = read(STDIN, buff, bytes);
  if (length >= 0) {
    return length;
  } else {
    return -1;
  }
}

int stupid_random(int maximum, int minimum) {
  return (rand() % (maximum + 1 - minimum) + minimum);
}

int stpunix_instance_init(stpunix_tcp_instance_s *instance) {
  if (instance == NULL) {
    return -1;
  }
  int socketfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

  if (socketfd < 0) {
    return -1;
  }
  int value_one = 1;
  setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &value_one, sizeof(value_one));

  instance->poll_descriptor.fd = socketfd;
  instance->poll_descriptor.events = POLLIN;

  instance->socketfd = socketfd;
  instance->status = SocketInactive;
  return 0;
}

int stpunix_bind_tcp_serv(stpunix_tcp_instance_s *server, uint32_t address,
                          uint16_t port) {
  if (server == NULL) {
    return -1;
  }
  struct sockaddr_in address_info;
  address_info.sin_addr.s_addr = htonl(address);
  address_info.sin_port = htons(port);
  address_info.sin_family = AF_INET;
  if (bind(server->socketfd, (struct sockaddr *)&address_info,
           sizeof(address_info)) < 0) {
    printf("Error while atempting to bind. %d\n", errno);
    return -2;
  };
  if (listen(server->socketfd, 16)) {
    printf("Error while attempting to listen");
    return -2;
  }
  server->status = SocketActive;

  return 0;
}

int stpunix_bind_tcp_client(stpunix_tcp_instance_s *client) {
  if (client == NULL) {
    return -1;
  }
  struct sockaddr_in address_info;
  address_info.sin_addr.s_addr = 0;
  address_info.sin_port = 0;
  address_info.sin_family = AF_INET;
  if (bind(client->socketfd, (struct sockaddr *)&address_info,
           sizeof(address_info)) < 0) {
    return -2;
  };
  client->status = SocketActive;

  return 0;
}

int stpunix_connect_tcp_client(stpunix_tcp_instance_s *client,
                               stpunix_tcp_connection_s *connection,
                               uint32_t address, uint16_t port) {
  if (client == NULL || connection == NULL) {
    return -1;
  }
  struct sockaddr_in addr;
  addr.sin_addr.s_addr = address;
  addr.sin_port = htons(port);
  addr.sin_family = AF_INET;

  while (1) {
    if (connect(client->socketfd, (struct sockaddr *)&addr, sizeof(addr))) {
      if (errno != EINPROGRESS && errno != EALREADY && errno != ETIMEDOUT) {
        return -1;
      }
    } else {
      break;
    };
  };

  connection->clientinfo = addr;
  connection->clientlen = sizeof(addr);
  connection->socketfd = client->socketfd;

  return 0;
}

int stpunix_accept_connection_serv(stpunix_tcp_instance_s *server,
                                   stpunix_tcp_connection_s *connection) {
  if (server == NULL || connection == NULL) {
    return -1;
  }

  struct sockaddr_in addr;
  socklen_t len;
  int socketfd;
  socketfd = accept(server->socketfd, (struct sockaddr *)&addr, &len);
  if (socketfd < 0) {
    if (errno == EAGAIN || errno == EWOULDBLOCK) {
      return -2;
    } else {
      return -1;
    }
  }
  connection->clientinfo = addr;
  connection->clientlen = len;
  connection->socketfd = socketfd;
  connection->status = SocketActive;

  struct pollfd poll_descriptor = {socketfd, POLLIN, 0};
  connection->poll_descriptor = poll_descriptor;
  struct pollfd poll_descriptor_r = {socketfd, .revents = POLLHUP};
  connection->poll_descriptor_r = poll_descriptor_r;
  return 0;
}

int stpunix_blocking_accept_connection_serv(
    stpunix_tcp_instance_s *server, stpunix_tcp_connection_s *connection) {
  if (server == NULL || connection == NULL) {
    return -1;
  }

  struct sockaddr_in addr;
  socklen_t len;
  int socketfd;
  if (poll(&server->poll_descriptor, 1, -1) == 1) {
    socketfd = accept(server->socketfd, (struct sockaddr *)&addr, &len);
  } else {
    return -1;
  }
  connection->socketfd = socketfd;
  connection->clientinfo = addr;
  connection->clientlen = len;
  connection->status = SocketActive;

  struct pollfd poll_descriptor = {socketfd, POLLIN, 0};
  connection->poll_descriptor = poll_descriptor;
  struct pollfd poll_descriptor_r = {socketfd, .revents = POLLHUP};
  connection->poll_descriptor_r = poll_descriptor_r;
  return NO_ERROR;

  return 0;
}

int stpunix_read_connection(stpunix_tcp_connection_s *connection,
                            uint8_t *buffer, int len) {
  if (connection == NULL || connection->status == SocketError ||
      connection->status == SocketInactive || buffer == NULL) {
    return -1;
  }

  int status = read(connection->socketfd, buffer, len);

  if (status < 0) {
    if (errno == EAGAIN || errno == EWOULDBLOCK) {
      return -2;
    } else {
      connection->status = SocketError;
      return -1;
    }
  }
  if (status == 0) {
    connection->status = SocketInactive;
  }
  return status;
}

int stpunix_write_connection(stpunix_tcp_connection_s *connection,
                             uint8_t *buffer, int len) {
  if (connection == NULL || connection->status == SocketError ||
      connection->status == SocketInactive || buffer == NULL) {
    return -1;
  }

  while (len > 0) {
    int bytes_status = write(connection->socketfd, buffer, len);
    if (bytes_status < 0) {
      return -1;
    } else {
      len -= bytes_status;
    }
  }
  return 0;
}

int stpunix_poll_connection(stpunix_tcp_connection_s *connection) {
  if (connection == NULL || connection->status == SocketError ||
      connection->status == SocketInactive) {
    return -1;
  }

  return poll(&connection->poll_descriptor, 1, 10);
}

#endif /* Check if platform is unix */
