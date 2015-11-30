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

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include "fileInputOutput.h"
#include "ros/ros.h"


//Send image to cloudsight servers and write token to token.txt
int sendImg(const char* filename){
	char s[200];
	const char *front="./cloud-curl.sh ", *end =" | tee ../object_locator/src/locator/src/token.txt";
  	strcpy(s,front);
	strcat(s, filename);
	strcat(s, end);
  	system(s);
}

//Send token to cloudsight for a response and write output to output.txt (streamline this later)
//Call this over and over again to poll for response
int getResponse(string token){
	char s[200];
	const char *front="./cloud-curl-resp.sh ", *end =" | tee ../object_locator/src/locator/src/output.txt";
	strcpy(s,front);
	strcat(s, token.c_str());
	strcat(s, end);
	system(s);
}


int main(int argc, char** argv){
	sendImg("../object_locator/src/locator/src/test1.JPG");
	string token=getToken();
	cout<< token<<"\n";
		getResponse(token);
}
