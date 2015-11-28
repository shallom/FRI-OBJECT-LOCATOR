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


#include "opencv2/features2d/features2d.hpp"
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
//#include "fileInputOutput.h"


using namespace cv;


int main(int argc, char **argv)
{

	//std::cout << writeToFile("NOOOOO") << '\n';
     Mat img_1, img_2, grey1, grey2;
	img_1 = imread("../object_locator/src/locator/src/test1.JPG", 1 );
img_2 = imread("../object_locator/src/locator/src/test2.JPG", 1 );
if( !img_1.data || !img_2.data )
{ std::cout<< " --(!) Error reading images " << std::endl; return -1; }

//-- Step 1: Detect the keypoints using ORB Detector
OrbFeatureDetector detector;

std::vector<KeyPoint> keypoints_1, keypoints_2;

detector.detect( img_1, keypoints_1 );
detector.detect( img_2, keypoints_2 );

//-- Step 2: Calculate descriptors (feature vectors)
OrbDescriptorExtractor extractor;

Mat descriptors_1, descriptors_2;

extractor.compute( img_1, keypoints_1, descriptors_1 );
extractor.compute( img_2, keypoints_2, descriptors_2 );

//-- Step 3: Matching descriptor vectors using BF matcher
BFMatcher matcher;
std::vector< DMatch > matches;
matcher.match( descriptors_1, descriptors_2, matches );

double max_dist = 0; double min_dist = 100;

//-- Quick calculation of max and min distances between keypoints
for( int i = 0; i < descriptors_1.rows; i++ )
{ double dist = matches[i].distance;
if( dist < min_dist ) min_dist = dist;
if( dist > max_dist ) max_dist = dist;
}

printf("-- Max dist : %f \n", max_dist );
printf("-- Min dist : %f \n", min_dist );

//-- Draw only "good" matches (i.e. whose distance is less than 2*min_dist,
//-- or a small arbitary value ( 0.02 ) in the event that min_dist is very
//-- small)
//-- PS.- radiusMatch can also be used here.
std::vector< DMatch > good_matches;

for( int i = 0; i < descriptors_1.rows; i++ )
{ if( matches[i].distance <= 3*min_dist)
{ good_matches.push_back( matches[i]); }
}

std::cout << "size: " << good_matches.size() << '\n';
Mat img_matches;
  drawMatches( img_1, keypoints_1, img_2, keypoints_2, good_matches, img_matches );

  //-- Show detected matches
  imshow("Matches", img_matches );

  waitKey(0);


    return 0;
}

