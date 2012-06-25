
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "io.h"
#include <stdlib.h>
#include <stdio.h>



#define ECHO_PORT          (2002)
#define MAX_LINE           (1000)


int main(int argc, char *argv[]) {
    int       listening_socket;
    int       connection_socket;
    short int port;
    struct    sockaddr_in servaddr;
    char      buffer[MAX_LINE];
    char     *endptr;

    if ( argc == 2 ) {
	port = strtol(argv[1], &endptr, 0);
	if ( *endptr ) {
	    fprintf(stderr, "Invalid port number.\n");
	    exit(EXIT_FAILURE);
	}
    }
    else if ( argc < 2 ) {
	port = ECHO_PORT;
    }
    else {
	fprintf(stderr, "Invalid arguments.\n");
	exit(EXIT_FAILURE);
    }

    if ( (listening_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
	fprintf(stderr, "Error creating listening socket.\n");
	exit(EXIT_FAILURE);
    }


    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(port);

    if ( bind(listening_socket, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0 ) {
	fprintf(stderr, "Error calling bind()\n");
	exit(EXIT_FAILURE);
    }

    if ( listen(listening_socket, LISTENQ) < 0 ) {
	fprintf(stderr, "Error calling listen()\n");
	exit(EXIT_FAILURE);
    }


    while ( 1 ) {


	if ( (connection_socket = accept(listening_socket, NULL, NULL) ) < 0 ) {
	    fprintf(stderr, "Error calling accept()\n");
	    exit(EXIT_FAILURE);
	}

	Readline(connection_socket, buffer, MAX_LINE-1);
	Writeline(connection_socket, buffer, strlen(buffer));

    }
}

