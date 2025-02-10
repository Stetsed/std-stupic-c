
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
typedef enum SocketStatus {
  SocketInactive,
  SocketActive,
  SocketError,

} SocketStatus;

// Socket implementation that let's you initialize a TCP socket, and bind it to
// a port and address and use it to connect to stuff. It is initialized with
// SOCK_NONBLOCK, and has 2 reading functions one which is blocking the other
// which is non-blocking and is the default.
typedef struct TcpClient {
  int Socket;
  SocketStatus Status;
} TcpClient;

typedef struct TcpConnection {
  int Socket;
  struct sockaddr_in ClientInformation;
  socklen_t ClientLength;
} TcpConnection;

TcpClient setup_tcp_client() {
  // Initialize a socket on IPv4, using TCP, and manual protocol selection, and
  // if blocking is false it also sets the socket to be non-blocking
  int socket_file = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 1);
  // Returned an error;
  if (socket_file < 0) {
    stupid_handle_errno(errno);
  }

  TcpClient TcpClient = {.Socket = socket_file, .Status = SocketInactive};
  return TcpClient;
}

void bind_tcp_client(TcpClient *client, uint16_t port, uint32_t address) {
  struct sockaddr_in address_info;
  address_info.sin_addr.s_addr = address;
  address_info.sin_port = port;
  address_info.sin_family = AF_INET;
  if (bind(client->Socket, (struct sockaddr *)&address_info,
           sizeof(address_info)) < 0) {
    stupid_handle_errno(errno);
  };
  client->Status = SocketActive;
}

void bind_tcp_client_array(TcpClient *client, uint16_t port,
                           uint8_t *address_array) {
  uint32_t address = stupid_bytes_to_address(address_array);
  struct sockaddr_in address_info;
  address_info.sin_addr.s_addr = address;
  address_info.sin_port = port;
  address_info.sin_family = AF_INET;
  if (bind(client->Socket, (struct sockaddr *)&address_info,
           sizeof(address_info)) < 0) {
    stupid_handle_errno(errno);
  };
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
  int socket = accept(client->Socket, (struct sockaddr *)&addr, &len);
  if (socket < 0) {
    if (errno == EAGAIN || errno == EWOULDBLOCK) {
      return EXPECTED_ERROR;
    } else {
      return CATASTROPHIC_ERROR;
    }
  }
  connection->ClientInformation = addr;
  connection->ClientLength = len;
  return NO_ERROR;
}

// Same functionality as accept_connection, however it will not return with a
// status code of -2 if the connection isn't available, and will only return
// with either 0 if a valid connection was received, or a -1 if there was a
// problem with the TcpClient.
int accept_connection_blocking(TcpClient *client, TcpConnection *connection) {
  struct sockaddr_in addr;
  socklen_t len;
  while (1) {
    int socket = accept(client->Socket, (struct sockaddr *)&addr, &len);
    if (socket < 0) {
      if (errno != EAGAIN || errno != EWOULDBLOCK) {
        return CATASTROPHIC_ERROR;
      } else {
        break;
      }
    } else {
      break;
    }
  }
  connection->ClientInformation = addr;
  connection->ClientLength = len;
  return NO_ERROR;
}

// Function that takes in a pointer to a TcpConnection gotten from TcpClient,
// and then reads content from this into buffer, make sure buffer has a size of
// >= count, otherwise it would be possible for a party to sent a large packet
// and overflow, can return either NO_ERROR or CATASTROPHIC_ERROR, which will
// happen if the read fails. The read data will be read into buffer, it can also
// return 0 which indicates that the EOF was hit, and otherwise returns the
// amount of bytes actually read.
int read_connection(TcpConnection *connection, uint8_t *buffer, uint count) {
  int status = read(connection->Socket, buffer, count);

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
