#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>

main()
{
   int optlen, gs, socktype, s;

      /* Create a datagram socket. */
   s = socket(AF_INET, SOCK_DGRAM, 0);
   if (s == -1) {
      perror("Socket not created");
      return EXIT_FAILURE;
   }

      /* Ask for the socket type. */
   optlen = sizeof(socktype);
   gs = getsockopt (s, SOL_SOCKET, SO_TYPE, &socktype, &optlen);
   if (gs == -1) {
      perror("getsockopt failed");
      return EXIT_FAILURE;
   }
      /* Print socket type. */
   switch (socktype)
   {
   case SOCK_STREAM:
      puts("Stream socket.\n");
      break;
   case SOCK_DGRAM:
      puts("Datagram socket.\n");
      break;
   case SOCK_RAW:
      puts("Raw socket.\n");
      break;
   default:
      puts("Unknown socket type.\n");
      break;
   }
   return EXIT_SUCCESS;
}
