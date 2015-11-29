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
#include "segment.h"
#include "fileInputOutput.h"
#include "ros/ros.h"
#include <stdlib.h>

using namespace cv;

class readFrameError{ };

//Send image to cloudsight servers and write token to token.txt
int sendImg(char** filename)
{
  std::string s = "./cloud-curl.sh " + filename + " | tee token.txt";
  return system(s);

}
//Send token to cloudsight for a response and write output to output.txt (streamline this later)
//Call this over and over again to poll for response
int getResponse(char** token)
{
	std::string s = "./cloud-curl-resp.sh " + token +" | tee output.txt";
	return system(s);
}

int main(int argc, char** argv)
{
    //inni ros
    ros::init (argc, argv, "captureFrame");
	ros::NodeHandle nh;

    int components;

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    namedWindow("frames",1); //opens up window to view webcam. not quit important, but if not included will need to create a  function that ends when a key is pressed
     Mat frame;
    while (true)
    {
        cap >> frame; // get a new frame from camera
	if(frame.empty())//if the a fram wasn't recived throw an exception
		throw readFrameError();
	else if(readFromFile("../object_locator/src/locator/src/readyForNewPic.txt").compare("yes")!=0){
		//need to include a boolean as to whether file readyfornewpic is yes in the above else
		imwrite("../object_locator/src/locator/src/frame.ppm", frame); //save the frame
		components=numberOfComponents("../object_locator/src/locator/src/frame.ppm");
		if(components<40&&components>4){
			//if first line of readyForNewPic says yes we can save the frame to frameToSend
			//else we don't do any of the things described below.
			imwrite("../object_locator/src/locator/src/frameToSend.jpg", frame);
			//if true we then make readyForNewPic no;
			writeToFile("no","../object_locator/src/locator/src/readyForNewPic.txt");
			//using the image comparison algo we check to see if the picture in frameToSend has been sent before
			//and exists in the pics database
			//if true readyForNewPic still is yes and we skip the below
			//else we set readyForNewPic to no
			//if readyForNewPic says yes 
			//objectDescription does its thing: gets info from cloudsight,
			//saves the features description and room location to a database
			//after we wait 30 seconds we write yes to readyForNewPic
}
	}
        imshow("frames", frame);
        if(waitKey(30) >= 0) break;
	if(ros::ok()) ros::spinOnce();
    }
    // the camera will be deinitialized automatically in VideoCapture destructor

    return 0;
}
