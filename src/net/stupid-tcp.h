#ifndef STD_STUPID_TCP
#define STD_STUPID_TCP
#pragma once

#include "stupid-tcp.c"

// Returns an instance of type TcpClient, which holds the Status of the socket
// and the socket file descriptor it has. It can error and will exit if the
// creation of the socket which is of type IPv4 and TCP fails, this can also
// happen if the OS is an older linux version and doesn't support non-block
// sock.
TcpClient setup_tcp_client();

// Binds the TCP-Client to the given port and address, will exit if error case
// is hit, such as if the address is already in use, or it doesn't exist. The
// address is in the form of it's binary representation, use
// bind_tcp_client_array if you wish to use an array of bytes for the address,
// which does the same function but using an array of 4 bytes.
void bind_tcp_client(TcpClient *client, uint16_t port, uint32_t address);
void bind_tcp_client_array(TcpClient *client, uint16_t port, uint8_t *address);

// Takes in a struct of type client and type connection, it then fills this with
// data, if the return is 0 this should be a valid socket file descriptor, if
// it's -2 an error that is due to no connection being available. If another
// error happens such as as the given TcpClient has an invalid socket it will
// return -1;
int accept_connection(TcpClient *client, TcpConnection *connection);
#endif /* ifndef STD_STUPID_TCP */
