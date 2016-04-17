#include "xhogDetector.h"

void XHOGDetector::getImgs(vector<string>& filenames)
{
	{
		imgNames_ = filenames;
		counter_ = filenames.size();
		for (int i = 0; i < counter_; i++) {
			imgs_[i] = imread(imgNames_[i]);
		}
	}
}

Mat & XHOGDetector::detector()
{
	foundPoints_ = vector<Point>();
	vector<Rect> found,foundFiltered;
	hog.detectMultiScale(img_, found, 0, Size(8, 8), Size(32, 32), 1.05, 2);
	size_t i, j;
	for (i = 0; i < found.size(); i++) {
		Rect r = found[i];
		for (j = 0; j < found.size(); j++)
			if (j != i && (r & found[j]) == r)
				break;
		if (j == found.size())
			foundFiltered.push_back(r);
	}
	for (i = 0; i < foundFiltered.size(); i++) {
		Rect r = foundFiltered[i];
		int midX = cvRound(r.x + r.width / 2);
		int midY = cvRound(r.y + r.height/2);
		foundPoints_.push_back(Point(midX,midY));
		foundPointsX_.push_back(midX);
		r.x += cvRound(r.width*0.1);
		r.width = cvRound(r.width*0.8);
		r.y += cvRound(r.height*0.07);
		r.height = cvRound(r.height*0.8);
		rectangle(img_, r.tl(), r.br(), Scalar(0, 255, 0), 3);
	}
	
	return img_;
}

vector<Mat>& XHOGDetector::detectorMulti()
{
	int numOfFrame = imgNames_.size();
	if (numOfFrame < 1) {
		cout << "please use detector instead of detectorMulti!" << endl;
		return imgs_;
	}
	for (vector<string>::iterator it = imgNames_.begin(); it != imgNames_.end(); it++) {
		imgs_.push_back(imread(*it));
	}
	int counter;
	vector<Mat>::iterator it;
	for (it = imgs_.begin(),counter = 0; it != imgs_.end();it++,counter++) {
		vector<Rect> found, foundFiltered;
		hog.detectMultiScale(*it,found, 0, Size(8, 8), Size(32, 32), 1.05, 2);
		size_t i, j;
		for (i = 0; i < found.size(); i++) {
			Rect r = found[i];
			for (j = 0; j < found.size(); j++)
				if (j != i && (r & found[j]) == r)
					break;
			if (j == found.size())
				foundFiltered.push_back(r);
		}
		for (i = 0; i < foundFiltered.size(); i++) {
			Rect r = foundFiltered[i];
			int midX = cvRound(r.x + r.width / 2);
			int midY = cvRound(r.y + r.height / 2);
			foundMultiPoints_[counter].push_back(Point(midX, midY));
			r.x += cvRound(r.width*0.1);
			r.width = cvRound(r.width*0.8);
			r.y += cvRound(r.height*0.07);
			r.height = cvRound(r.height*0.8);
			rectangle(*it, r.tl(), r.br(), Scalar(0, 255, 0), 3);
		}
	}
	return imgs_;
}
