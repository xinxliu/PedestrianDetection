#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstddef>
#include <vector>

#include "cmdParse.hpp"
#include "xhogDetector.h"

using namespace std;
using namespace cv;
//global definitions
size_t numOfPeople = 0;
size_t numIN = 0;
size_t numOUT = 0;

int main(int argc,char** argv){
	//parse the command line
	CmdParser parser;
	int trival = parser.cmdParser(argc, argv);
	if (trival) {
		return -1;
	}
	
	//init the detector
	XHOGDetector xhog;
	
	//video mod
	if (parser.isVideo()){
		numOfPeople += parser.getInit();
		VideoCapture capture(0);
		capture.set(CV_CAP_PROP_POS_MSEC,100000);
		
		//some definitions here
		Mat frame;
		vector<Point> points0;
		vector<Point> points1;
		vector<Point> points2;
		int counter0, counter1, counter2 = 0;
		
		//initial the first frame;
		capture >> frame;
		xhog.getImgs(frame);
		xhog.detector();
		points0 = xhog.getPoints();
		counter0 = points0.size();
		
		capture >> frame;
		xhog.getImgs(frame);
		frame = xhog.detector();
		points1 = xhog.getPoints();
		counter1 = points1.size();
		
		//read and detect
		while (1) {
			capture >> frame;
			xhog.getImgs(frame);
			frame = xhog.detector();
			points2 = xhog.getPoints();
			counter2 = points2.size();
			if (counter2 != counter1) {
				//================To do
				
				cout << counter2 - counter1 << endl;
			}

			//using move semantic will speed it up,but I haven't test it because of 
			//the time constraint.for safety,a copy semantic will be used
			//points1 = std::move(points2);
			points0 = points1;
			counter0 = counter1;
			points1 = points2;
			counter1 = counter2;
			//imshow("video test", frame);

			//waiting for 'q' to quit
			if (char(waitKey(1) == 'q')) {
				break;
			}
		}
		cout << "number of people is"<< numOfPeople << endl;
	return 0;	
	}
	//picture mode
	else {
		Mat img;
		img = imread((parser.getImgNames())[0]);
		namedWindow("pede-detect");
		cout << (parser.getImgNames())[0] << endl;
		xhog.getImgs(img);
		img = xhog.detector();
		vector<Point> foundPoints = xhog.getPoints();
		for (vector<Point>::iterator it = foundPoints.begin(); it != foundPoints.end(); it++) {
			cout << "(" << (*it).x << "," << (*it).y << ")" << endl;
			circle(img, *it, 4, Scalar(0, 0, 255), -1);
		}
		imshow("pede-detect", img);
	}
	//press q to quit
	while(char(waitKey(1)) != 'q'){};
	return 0;
}