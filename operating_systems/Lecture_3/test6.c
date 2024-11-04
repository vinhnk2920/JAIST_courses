
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

char *server_ip = "127.0.0.1";
int port_no = 8888;

const int MSG_SIZE = 256;

int main(int argc, char *argv[]) {

  int socket_id;

  // Open the socket.
  if ((socket_id = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("socket");
    return -1;
  }

  char message[MSG_SIZE];

  // Prepare listening address.
  struct sockaddr_in dest_addr;
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_port = htons(port_no); // Host to network byte order conversion.
  dest_addr.sin_addr.s_addr = inet_addr(server_ip);

  // Bind to the address we want to listen to. 
  if (bind(socket_id, (struct sockaddr *) &dest_addr, 
	   sizeof(dest_addr)) == -1) {
    perror("bind");
    return -3;
  }

  struct sockaddr_storage client_addr;
  socklen_t client_addr_len = sizeof(client_addr);

  while (1) {

    // Receive message.
    if (recvfrom(socket_id, message, MSG_SIZE, 0,
	       (struct sockaddr *)&client_addr, 
	       &client_addr_len) == -1) {
      perror("sendto");
      return -2;
    }

    printf("Received message from client: %s", message);
  }

  // Close the socket.
  close(socket_id);

  return 0;
}
