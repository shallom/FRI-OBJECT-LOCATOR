#include "ros/ros.h"
#include "std_msgs/String.h"
#include <cstdio>
#include "geometry_msgs/Twist.h"
#include <cmath>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

bool enterConnection=true;
char action[30];
ros::Publisher publisher;
geometry_msgs::Twist direction;
int left(){
direction.angular.z=3.14/2;
direction.linear.x=.4;
publisher.publish(direction);
}
int right(){
}
int forward(){
}
int backward(){
}
int spin(){
}
int main (int argc, char** argv)
{
	// Initialize ROS
    ros::init (argc, argv, "player");
	ros::NodeHandle nh;

	
	//refresh rate
	double ros_rate = 3.0;
	ros::Rate r(ros_rate);

int sock, bytes_recieved, turns;  
        char send_data[1024],recv_data[1024];
        struct hostent *host;
        struct sockaddr_in server_addr;  

        host = gethostbyname("10.147.156.83");//ip adress of host

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }

        server_addr.sin_family = AF_INET;     
        server_addr.sin_port = htons(5109);   
        server_addr.sin_addr = *((struct in_addr *)host->h_addr);
        bzero(&(server_addr.sin_zero),8); 

        if (connect(sock, (struct sockaddr *)&server_addr,
                    sizeof(struct sockaddr)) == -1) 
        {
            perror("Connect");
            exit(1);
        }
	
	while (ros::ok())
	{
		ros::spinOnce();
		r.sleep();
		 publisher=nh.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/teleop", 1000);
geometry_msgs::Twist direction;

		if(enterConnection){
          bytes_recieved=recv(sock,recv_data,1024,0);
          recv_data[bytes_recieved] = '\0';
		printf("\nRecieved data = %s " , recv_data);
		enterConnection=false;
		}
		if(!enterConnection){
		if(recv_data[0]=='l'){
			left();
		}
		enterConnection=true;
		}
         
           if(enterConnection){
		char end[]="done";
		send(sock,end,strlen(end), 0);  
		}
        
		
        
	}
	
	return 0;
}

