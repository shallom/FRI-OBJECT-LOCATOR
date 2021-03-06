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

#include "opencv2/opencv.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include "fileInputOutput.h"
#include "segmentation/compareImage.h"

int main(int argc, char **argv){
	
	Mat image, currImage;
	ostringstream oss;
	string loc="../object_locator/pic/", ext=".jpg", result="";
	bool similarImage=true;
	
	while(true){
		
		int numberOfPics;
		
		//when no longer looking for a new image
		if(readFromFile("../object_locator/src/locator/src/text_files/readyForNewPic.txt").compare("no")==0){

			//get the number of pictures already sent
			numberOfPics=atoi(readFromFile("../object_locator/pic/numberOfPics.txt").c_str());
			image=imread("../object_locator/src/locator/src/frameToSend.jpg", 1 );
			
			cout<<"Starting comparison \n";

			//compare all the images in the database to the image we have
			for(int pic=0; pic<numberOfPics; pic++){
				oss << pic;
				result= loc + oss.str() + ext;
				oss.str("");
				oss.clear();
				currImage=imread(result,1);
				cout<<"Comparing... \n";
				
				//If images have more than 15 good descriptions then they are considered similar
				if(compareTwoImages(image, currImage)>15){
					writeToFile("yes","../object_locator/src/locator/src/text_files/readyForNewPic.txt");
					cout<<"Similar image found. Image discarded \n";
					similarImage=true;
					break;
				}
				
				similarImage=false;
			}
			
			if(!similarImage){
				cout<<"Image is Different. Sending to CloudSight \n";
				writeToFile("yes","../object_locator/src/locator/src/text_files/doneComparing.txt");
				//cloudsight should read when doneComparing says yes
				//it sets received info to no,
				//while loop here waits till received info say yes;
				while(readFromFile("../object_locator/src/locator/src/text_files/recievedResult.txt").compare("no")==0){
					cout<<"Waiting For CloudSight \n";
				}
				if(readFromFile("../object_locator/src/locator/src/text_files/recievedResult.txt").compare("yes")==0){
					writeToFile("no","../object_locator/src/locator/src/text_files/doneComparing.txt");
					oss << numberOfPics++;
					result= loc + oss.str() + ext;
					oss.str("");
					oss.clear();
					imwrite(result, image);
					stringstream temp_str;
					temp_str<<(numberOfPics);
					string str = temp_str.str();
					writeToFile(str.c_str(),"../object_locator/pic/numberOfPics.txt");
					writeToFile("yes","../object_locator/src/locator/src/text_files/readyForNewPic.txt");
					writeToFile("no","../object_locator/src/locator/src/text_files/recievedResult.txt");
					cout<<"CloudSight returned description. Now waiting for new image \n";
				}
			
			//when we get a response from cloudsight set received info to yes
			//cloudsight writes response to file
			//after while loop, write the image in frameToSendToCloudsight to the image database
			//and ready for new image to yes
			//and done comparing to no.
			//and receivedInfo to no;
			}
		}
	}
}
