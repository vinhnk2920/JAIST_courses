
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

  if (argc == 3) {
    server_ip = argv[1];
    port_no = atoi(argv[2]);
  }

  printf("Client connects to %s:%d\n", server_ip, port_no);

  int socket_id;

  // Open the socket.
  if ((socket_id = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("socket");
    return -1;
  }

  char message[MSG_SIZE];

  // Prepare destination address.
  struct sockaddr_in dest_addr;
  dest_addr.sin_family = AF_INET;
  dest_addr.sin_port = htons(port_no); // Host to network byte order conversion.
  dest_addr.sin_addr.s_addr = inet_addr(server_ip);

  while (1) {
    // Read message from keyboard.
    printf("Type the message to send:\n");
    fgets(message, MSG_SIZE, stdin);

    // Send message.
    if (sendto(socket_id, message, strlen(message)+1, 0,
	       (struct sockaddr *)&dest_addr, 
	       sizeof(dest_addr)) == -1) {
      perror("sendto");
      return -2;
    }
  }

  // Close the socket.
  close(socket_id);

  return 0;
}
