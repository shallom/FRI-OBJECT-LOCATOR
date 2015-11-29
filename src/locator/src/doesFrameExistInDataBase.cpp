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
	string loc="hello", ext=".jpg", result="";
	while(true){
		if(readFromFile("../object_locator/src/locator/src/readyForNewPic.txt").compare("no")==0){
			int numberOfPics=sscanf(readFromFile("../object_locator/pic/numberOfPics.txt").c_str(), "%d", &numberOfPics);
			image=imread("../object_locator/src/locator/src/frameToSend.jpg", 1 );
			for(int pic=0; pic<numberOfPics; pic++){
				oss << pic;
				result= loc + oss.str() + ext;
				currImage=imread(result,1);
				if(compareTwoImages(image, currImage)>25){//if greater than 25 the images are somwhat alike so look for new pic
					writeToFile("yes","../object_locator/src/locator/src/readyForNewPic.txt");
					break;
				}
			}
			writeToFile("yes","../object_locator/src/locator/src/doneComparing.txt");
			//cloudsight should read when doneComparing says yes
			//it sets recieved info to no,
			//while loop here waits till recieved info say yes;
			//after recieved info it sets received info to yes
			//cloudsight writes info to file
			//after the while loop fails we write the pic in frameToSendToCloudsight to the pic direc
			//and ready for new pic to yes
			//and done comparing to no.
			//and ready received info to no;
		}
	}
}
