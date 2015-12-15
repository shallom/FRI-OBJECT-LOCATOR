/*
Copyright (C) 2015 Shallom Onoja

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/



#include "std_msgs/String.h"
#include <cstdio>
#include <cmath>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main (int argc, char** argv){

	int sock, connected, bytes_recieved, one=1;  
    char send_data [1024] , recv_data[1024];       

    struct sockaddr_in server_addr,client_addr;    
       	socklen_t sin_size;
        
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }

        if (setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&one,sizeof(int)) == -1) {
            perror("Setsockopt");
            exit(1);
        }
        
        server_addr.sin_family = AF_INET;         
        server_addr.sin_port = htons(5116); //the port opened to listen to tcp client   
        server_addr.sin_addr.s_addr = INADDR_ANY;
        bzero(&(server_addr.sin_zero),8); 

        if (bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))== -1) {
            perror("Unable to bind");
            exit(1);
        }

        if (listen(sock, 5) == -1) {
            perror("Listen");
            exit(1);
        }
		
	    printf("\nTCPServer Waiting for client on port");
        fflush(stdout);

	   sin_size = sizeof(struct sockaddr_in);

       	connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);

      	printf("\n Received connection from (%s , %d)", inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

	while(true){

      		fgets(send_data, 255, stdin);//get the data from terminal
		send(connected, send_data,strlen(send_data), 0);//send data
		bytes_recieved = recv(connected,recv_data,1024,0);
		recv_data[bytes_recieved] = '\0';

		printf("\n RECIEVED DATA = %s " , recv_data);
		fflush(stdout);
	}

}
