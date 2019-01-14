#include "networking.h"

int main(int argc, char **argv) {

  int server_socket;
  char buffer[BUFFER_SIZE];

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  for (int i = 0; i < 2; i++)
    {
      read( server_socket, buffer, sizeof(buffer) );
      printf("%s", buffer);
      fflush(stdout);
    }
  
  while (1)
    {
      read( server_socket, buffer, sizeof(buffer) );
      printf("%s", buffer);
      fflush(stdout);

      read( server_socket, buffer, sizeof(buffer) );
      printf("%s", buffer);
      fflush(stdout);
      
      fscanf(stdin, "%s", buffer);
      write( server_socket, buffer, sizeof(buffer) );
    }
  
  /*
  while (1) {
    printf("enter data: ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    write(server_socket, buffer, sizeof(buffer));
    read(server_socket, buffer, sizeof(buffer));
    printf("received: [%s]\n", buffer);
  }
  */
}
