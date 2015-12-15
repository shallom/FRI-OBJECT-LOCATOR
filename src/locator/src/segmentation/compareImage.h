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

#ifndef IMAGE_COMPARE
#define IMAGE_COMPARE

#include "opencv2/features2d/features2d.hpp"
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>

using namespace cv;

class error_Reading_Image{ };

vector< DMatch > bruteForceDescriptorMatch(Mat image_1_descriptor, Mat image_2_descriptor){
	BFMatcher matcher;
	vector< DMatch > matches;
	matcher.match( image_1_descriptor, image_2_descriptor, matches );

	double max_dist = 0, min_dist = 100, dist;

	//create lower and upper bounds for distances
	for( int i = 0; i < image_1_descriptor.rows; i++ ){ 
		dist = matches[i].distance;
		if( dist < min_dist ) 
			min_dist = dist;
		if( dist > max_dist ) max_dist = dist;
	}

	vector< DMatch > good_matches;
	//say a good match is a match whose distance is less than there times the lower bound
	for( int i = 0; i < image_1_descriptor.rows; i++ ){
		if( matches[i].distance <= 3*min_dist)
			good_matches.push_back( matches[i]);
	}

	return good_matches;
}

int compareTwoImages(Mat image_1, Mat image_2){
        
        if(!image_1.data || !image_2.data)
                throw error_Reading_Image();
	OrbFeatureDetector detector;
	OrbDescriptorExtractor extractor;
	Mat image_1_descriptor, image_2_descriptor;
	vector<KeyPoint> image_1_keypoints, image_2_keypoints;
	//Detect keypoints
	detector.detect( image_1, image_1_keypoints );
	detector.detect( image_2, image_2_keypoints );
	//Calculate feature vectors
	extractor.compute( image_1, image_1_keypoints, image_1_descriptor );
	extractor.compute( image_2, image_2_keypoints, image_2_descriptor );

	vector< DMatch > good_matches= bruteForceDescriptorMatch(image_1_descriptor, image_2_descriptor);

	Mat img_matches;
  	drawMatches( image_1, image_1_keypoints, image_2, image_2_keypoints, good_matches, img_matches );
	
	return good_matches.size();
}

#endif

