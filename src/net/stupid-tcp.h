#ifndef STD_STUPID_TCP
#define STD_STUPID_TCP
#pragma once

#include "stupid-tcp.c"

// Returns an instance of type TcpClient, which holds the Status of the socket
// and the socket file descriptor it has. It can error and will exit if the
// creation of the socket which is of type IPv4 and TCP fails.
TcpClient setup_tcp_client();

// Binds the TCP-Client to the given port and address, will exit if error case
// is hit, such as if the address is already in use, or it doesn't exist. The
// address is in the form of it's binary representation, use
// bind_tcp_client_array if you wish to use an array of bytes for the address,
// which does the same function but using an array of 4 bytes.
void bind_tcp_client(TcpClient *client, uint16_t port, uint32_t address);
void bind_tcp_client_array(TcpClient *client, uint16_t port, uint8_t *address);
#endif /* ifndef STD_STUPID_TCP */
