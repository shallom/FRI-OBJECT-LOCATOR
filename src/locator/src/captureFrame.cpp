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

//Logic Overview

/*	if(readyForNewPic==yes) 
		save the frame to frameToSend;
		readyForNewPic==no;
		
		//Logic For Comparison 
			
			//using the image comparison algorithm check to see if the picture in frameToSend has been sent before
			if(frame is in database)
				readyForNewPic==yes;
			else
				readyForNewPic==no;
				send frame to be sent to cloudsight
			
				//Logic For cloudsight
				
					if(done comparing image)
						send image to cloudsight;
						get response and save picture;
						set readyForNewPic to yes;
	else 
		don't do any of the things described below;
*/

#include "opencv2/opencv.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include "segmentation/segment.h"
#include "fileInputOutput.h"
#include <iostream>
#include "ros/ros.h"

using namespace cv;

class readFrameError{ };

int main(int argc, char** argv){

    //init ros
    ros::init(argc, argv, "captureFrame");
	ros::NodeHandle nh;

    int components;

    VideoCapture cap(0); // open the default camera, change the number for camera different from default
    if(!cap.isOpened())  // check if camera is opened

    namedWindow("frames",1); //opens up window to view web cam.
    
    Mat frame;
    
    while (true){
	
		cout<<"Waiting for new Image \n";
    	cap >> frame; //get a new frame from camera
	
		if(frame.empty())//if the a frame wasn't received throw an exception
			throw readFrameError();
		
		else if(readFromFile("../object_locator/src/locator/src/text_files/readyForNewPic.txt").compare("yes")==0){
		
			cout<<"Found new Image \n";
		
			imwrite("../object_locator/src/locator/src/frame.ppm", frame); //save the frame
		
			components=numberOfComponents("../object_locator/src/locator/src/frame.ppm"); //get the number of components in the frame
		
			if(components<40&&components>4){//the thresholds should be changed to a better heuristic
			
				cout<<"Image has: "<<components<<". it is good and is sent to be compared \n";
				
				imwrite("../object_locator/src/locator/src/frameToSend.jpg", frame);
				
				writeToFile("no","../object_locator/src/locator/src/text_files/readyForNewPic.txt");
				
			}else{
				cout<<"Image has: "<<components<<". it is not good and is discarded \n";
			}
    
    		imshow("frames", frame);
        
    		if(waitKey(30) >= 0) break;
	
			if(ros::ok()) ros::spinOnce();
		}
    // the camera will be deinitialized automatically in VideoCapture destructor
	}

    return 0;
}
