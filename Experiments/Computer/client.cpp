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

// basic file operations
#include <fstream>
#include <sstream>      // std::stringstream
using namespace std;

//system time stuff
#include <chrono>
#include <ctime>


void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
	ofstream output("E1_data/tempData.txt");
	if(!output.is_open()) return 0;
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

	//initialize variables for your experiment
	int index = 1;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    
	while(1)
	{
		//make a system call to take a picture (give it the index input)
		string command = "./snapPic.sh";
		command = command + " " + to_string(index);
		system (command.c_str());

		//obtain the timestamp
		end = std::chrono::system_clock::now();
   		std::chrono::duration<double> elapsed_seconds = end-start;
 		double timestamp = elapsed_seconds.count();
		//double timestamp = 10;

		//printf("Please enter the message: ");
		bzero(buffer,256);
		//fgets(buffer,255,stdin);

		//initiate the call to the server (ask for data)
		n = write(sockfd,"gimme data",strlen("gimme data"));
		if (n < 0) 
		     error("ERROR writing to socket");

		//read the data from the server
		bzero(buffer,256);
		n = read(sockfd,buffer,255);
		if (n < 0) 
			 error("ERROR reading from socket");
		printf("%s\n",buffer);

		//save the data to the file (with index and timestamps)
		output << buffer << "_" << index << "_" << timestamp << endl;

		//increment the index
		index++;
	}
	output.close();
    close(sockfd);
    return 0;
}
