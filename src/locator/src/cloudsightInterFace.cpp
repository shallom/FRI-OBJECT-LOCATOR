/*
Copyright (C) 2015 Laura Canto, Shallom Onoja

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
#include <fstream>

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

//saave the response to response.txt
int saveResponse(){
	ifstream outputFile ("../object_locator/src/locator/src/output.txt");
	string line;
	char lineArr[1024];
	if(outputFile.is_open()){
		while(getline(outputFile, line)){
			string first (line.begin(), line.begin()+1);
			if(first.compare("{")==0){
				strncpy(lineArr, line.c_str(), sizeof(lineArr));
				break;
			}
		}
		int size=line.length();
		if(size<30){
			return -1;
		}
		string first (line,23, 24);
		if(first.compare("n")){
			string response (line, 30, size-1);
			writeToFile(response.c_str(), "../object_locator/src/locator/src/response.txt" );
			return 1;
		}else 
			return -1;
	}else
		return -1;
}


int main(int argc, char** argv){
	while(true){
		if(readFromFile("../object_locator/src/locator/src/doneComparing.txt").compare("yes")==0){//if we are done comparing start
			writeToFile("no","../object_locator/src/locator/src/recievedResult.txt");//say we haven't recieved the result yet
			sendImg("../object_locator/src/locator/src/frameToSend.jpg");//send the image to cloudiight 
			string token=getToken();//get the token
			for(int i=0; i<50; i++){//for loop that just waits for 50 runs to get response
				cout<<"Working... \n";
				getResponse(token);	
			}
			saveResponse();//save the response
			writeToFile("yes","../object_locator/src/locator/src/recievedResult.txt");//tell everyone we have recieved the file
			cout<<"Finished \n";
		}
	}
}
