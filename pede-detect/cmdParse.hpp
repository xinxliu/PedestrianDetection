#ifndef _CMDPARSE_H_
#define _CMDPARSE_H_

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using namespace cv;

class CmdParser{
public:
	CmdParser() :isVideo_(0) {

	}
	bool isVideo() {
		return bool(isVideo_);
	}
	int cmdParser(int argc, char** argv);
	int printUsage();
	vector<string> getImgNames() {
		return imgNames_;
	}
	int getInit() {
		return initNumOfPeople_;
	}
private:
	int isVideo_;
	int initNumOfPeople_;
	vector<string> imgNames_;
}; 
#endif