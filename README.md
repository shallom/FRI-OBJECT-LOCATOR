

#A C++ program for identifying objects which allows the user drive the [segbot](http://wiki.ros.org/segbot) around using TCP while the [segbot](http://wiki.ros.org/segbot) takes pictures of its surroundings and records the objects in it.

##Software Used:

1. [The Robot Operating System:](http://www.ros.org/)

	1. The base platform.

2. [Open Computer Vision(OpenCV)](http://opencv.org/): 

	1. Used to read from the web-cam.

	2. Used to read and write images from files. 

	3. Used to compare images using an implementation of Oriented FAST and Rotated BRIEF (ORB) for image comparison.

3. [CloudSight:](https://cloudsightapi.com/) 

	1. The Web API used to recognize objects.

4. Segmentation: 

	 [Implementation of the segmentation algorithm described in: Efficient Graph-Based Image Segmentation Pedro F. Felzenszwalb and Daniel P. Huttenlocher International Journal of Computer Vision, 59(2) September 2004.](http://cs.brown.edu/~pff/papers/seg-ijcv.pdf)

	 1. Used to segment the image and retrieve the number of components in a picture to make sure image isn't overly complicated.

##Steps to Setup.

1. Move opencv.sh into home

2. give permission opencv.sh

3. Run opencv.sh

4. Give read permission to cloud-curl.sh and cloud-curl-resp.sh

4. Put Cloudsight key into cloud-curl.sh and cloud-curl-resp.sh

5. Put IP address into subMoveCmds.cpp

6. Run files:
	
	1. pubMoveCmds.cpp

	2. subMoveCmds.cpp

	3. cloudsightInterface.cpp

	4. doesFrameExistInDatabase.cpp

	5. captureFrame.cpp




