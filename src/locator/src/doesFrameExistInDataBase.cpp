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
#include "compareImage.h"

int main(int argc, char **argv)
{
	Mat image, currImage;
	ostringstream oss;
	string loc="../object_locator/pic/", ext=".jpg", result="";
	bool similarImage=true;
	while(true){
		int numberOfPics;
		if(readFromFile("../object_locator/src/locator/src/readyForNewPic.txt").compare("no")==0){//when we arn't looking for a new pic
			numberOfPics=atoi(readFromFile("../object_locator/pic/numberOfPics.txt").c_str()); //get the number of pictures we have
			image=imread("../object_locator/src/locator/src/frameToSend.jpg", 1 );
			cout<<"Starting comparision \n";
			for(int pic=0; pic<numberOfPics; pic++){//compare all the pics in the database to the pic we have
				oss << pic;
				result= loc + oss.str() + ext;
				oss.str("");
				oss.clear();
				currImage=imread(result,1);
				cout<<"Comparing... \n";
				if(compareTwoImages(image, currImage)>15){//if greater than 15 the images are somwhat alike so look for new pic
					writeToFile("yes","../object_locator/src/locator/src/readyForNewPic.txt");
					cout<<"Similar image found. Image discarded \n";
					similarImage=true;
					break;
				}
				similarImage=false;
			}
			if(!similarImage){
				cout<<"Image is Differnt. Sending to CloudSight \n";
				writeToFile("yes","../object_locator/src/locator/src/doneComparing.txt");
				//cloudsight should read when doneComparing says yes
				//it sets recieved info to no,
				//while loop here waits till recieved info say yes;
				while(readFromFile("../object_locator/src/locator/src/recievedResult.txt").compare("no")==0){
					cout<<"Waiting For CloudSight \n";
				}
				if(readFromFile("../object_locator/src/locator/src/recievedResult.txt").compare("yes")==0){
					writeToFile("no","../object_locator/src/locator/src/doneComparing.txt");
					oss << numberOfPics++;
					result= loc + oss.str() + ext;
					oss.str("");
					oss.clear();
					imwrite(result, image);
					stringstream temp_str;
					temp_str<<(numberOfPics);
					string str = temp_str.str();
					writeToFile(str.c_str(),"../object_locator/pic/numberOfPics.txt");
					writeToFile("yes","../object_locator/src/locator/src/readyForNewPic.txt");
					writeToFile("no","../object_locator/src/locator/src/recievedResult.txt");
					cout<<"CloudSight returned description. Now waiting for new image \n";
				}
			//after recieved info it sets received info to yes
			//cloudsight writes info to file
			//after the while loop fails we write the pic in frameToSendToCloudsight to the pic direc
			//and ready for new pic to yes
			//and done comparing to no.
			//and ready received info to no;
			}
		}
	}
}
