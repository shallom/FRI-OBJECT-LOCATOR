#include "opencv2/opencv.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include "segment.h"
#include "ros/ros.h"

using namespace cv;

int main(int argc, char** argv)
{
    //inni ros
    ros::init (argc, argv, "captureFrame");
	ros::NodeHandle nh;

    char exit='w';
    const char* pictureName="frame.ppm";
    int components;

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    namedWindow("frames",1); //opens up window to view webcam. not quit important, but if not included will need to create a  function that ends when a key is pressed
     Mat frame;
    while (ros::ok())
    {
        cap >> frame; // get a new frame from camera
	if(frame.empty())//if the a fram wasn't recived throw an exception
		throw "Frame reading error";
	else{
		imwrite("../object_locator/src/locator/src/frame.ppm", frame); //save the frame
		components=30;//numberOfComponents(pictureName);
		if(components<26&&components>4){
			//send to cloudsight. if we have this in c++ we could just call it here but we will have to write to a new file and that is always worthy of being sent. cloudsight then waits 30 seconds to read the file and then compares that file with a database of all the other pictures we have taken. if it dosent match any of those other pictures it sends it to cloudsight.
			imwrite("frameToSend.jpg", frame);
			//cloudsight has a timer and every 30 seconds writes to a file sayinf that it is ready to read from picture to send.
			//the image comparison algo then writes to the same file saying that it is ready, and both problems check to see if their are two yes', when there is, they read to the read the picture, the sift algo gets the returned info and combines the features to the description and both are saved to a file and the room loction is read from the sift code and and saved. 
}
	}
        imshow("frames", frame);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
