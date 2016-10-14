/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h> /* system, NULL, EXIT_FAILURE */
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

//added to work as a c++ program
#include <cstdlib>
#include <cstring>
#include <unistd.h>

#include <string>
#include <iostream>

// basic file operations
#include <fstream>
#include <sstream>      // std::stringstream
using namespace std;



void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
          
     int i=0;
     
     double temp = 98.6;
     while(i++ < 10)
     {
         bzero(buffer,256);
         
         //Let the client initiate (wait for them)
         n = read(newsockfd,buffer,255);
         if (n < 0) error("ERROR reading from socket");
         printf("Here is the message: %s\n",buffer);
         
         temp++;
         //obtain the temp data using a system call
         //std::string TEMP = system("python 3_temps.py");
         system("python obtainTemps.py > tempsOut.txt");
         //now grab this data from the file
         string line;
         ifstream input("tempsOut.txt");
         getline(input,line);
         string TEMP = line;
         getline(input,line);
         TEMP = TEMP + "_" + line;
         getline(input,line);
         TEMP = TEMP + "_" + line;
         input.close();
         
         //send this data to the client as a large string
         //std::string TEMP = std::to_string(temp);
         //TEMP = TEMP + "_" + TEMP + "_" + TEMP; 
         std::cout << "temp = " << TEMP << std::endl;
         const void * a = TEMP.c_str();
         n = write(newsockfd,a,255);
         if (n < 0) error("ERROR writing to socket");
     }
     close(newsockfd);
     close(sockfd);
     return 0; 
}
