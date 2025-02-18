// #include "./stupid-bindgen/bindings.h"

#include "stupid-school.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stupid-tcp.h>
#include <stupid.h>
#include <unistd.h>
#define EXIT_SUCCESS 0
#define ENTER 10

int main(int argc, char *argv[]) {
  TcpClient client = setup_tcp_client();
  char hello[] = "It works you dum cunt";
  bind_tcp_client(&client, 8080, 0);
  TcpConnection connection;
  accept_connection_blocking(&client, &connection);
  write_connection(&connection, (uint8_t *)hello, 22);

  exit(0);
}
