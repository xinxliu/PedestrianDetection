#ifndef _XHOGDETECTOR_H_
#define _XHOGDETECTOR_H_
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <string>

using namespace cv;
using std::vector;
using std::string;
using std::cout;
using std::endl;

enum method {
	IMAGE = 0,
	IMAGES = 1
};

class XHOGDetector {
public:
	XHOGDetector() {
		hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
	}
	void getImgs(vector<string>& filenames);
	void getImgs(Mat& img) {
		img_ = img;
	}
	vector<Point> getPoints() {
		return foundPoints_;
	}
	vector<int> getPointsX() {
		return foundPointsX_;
	}
	Mat& detector();
	vector<Mat>& detectorMulti();
	
	HOGDescriptor hog;
private:
	vector<string> imgNames_;
	vector<Mat> imgs_;
	vector<Point> foundPoints_;
	vector<int> foundPointsX_;
	vector<vector<Point>> foundMultiPoints_;
	Mat img_;
	int counter_;
};


#endif