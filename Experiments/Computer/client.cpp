
Skip to content
This repository

    Pull requests
    Issues
    Gist

    @romanomatthew23

1
0

    0

romanomatthew23/lavaLamp
Code
Issues 0
Pull requests 0
Projects 0
Wiki
Pulse
Graphs
Settings
lavaLamp/Experiments/Computer/client.cpp
55f9e02 an hour ago
@romanomatthew23 romanomatthew23 Create client.cpp
73 lines (66 sloc) 1.76 KB
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

//added to work as a c++ program
#include <cstdlib>
#include <cstring>
#include <unistd.h>

//extra help :)
#include <iostream>   // std::cout
#include <string>     // std::string, std::stod

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
//if (connect(sockfd,&serv_addr,sizeof(serv_addr)) < 0) { ... }
//if (connect(sockfd,(const sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

	while(1)
	{
		printf("Please enter the message: ");
		bzero(buffer,256);
		fgets(buffer,255,stdin);
		n = write(sockfd,buffer,strlen(buffer));
		if (n < 0) 
		     error("ERROR writing to socket");
		bzero(buffer,256);
		n = read(sockfd,buffer,255);
		if (n < 0) 
			 error("ERROR reading from socket");
		printf("%s\n",buffer);
	}
    close(sockfd);
    return 0;
}

    Contact GitHub API Training Shop Blog About 

    © 2016 GitHub, Inc. Terms Privacy Security Status Help 

