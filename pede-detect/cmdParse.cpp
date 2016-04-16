#include "cmdParse.hpp"

int CmdParser::cmdParser(int argc, char** argv)
{
	if (argc == 1) {
		printUsage();
		return -1;
	}
	for (int i = 1; i < argc; ++i) {
		if (string(argv[i]) == "--help") {
			printUsage();
			return -1;
		}
		else if (string(argv[i]) == "--cameraCapture") {
			if (string(argv[++i]) == "yes") {
				isVideo_ = 1;
				cout << "testtest===============" << endl;
			}
			else if (string(argv[++i]) == "no") {
				isVideo_ = 0;
			}
			else {
				cout << "error status ,default setting will be used" << endl;
			}
		}
		else if(string(argv[i]) == "--init"){
			initNumOfPeople_ = int(argv[++i][0]) - 0x30;
			if (argv[i][1] != '\0') {
				initNumOfPeople_ = initNumOfPeople_ * 10 + int(argv[i][1] - 0x30);
			}
			cout << "this is the parser" << char(argv[i][1]) << endl;
		}
		else {
			Mat imgTemp = imread(string(argv[i]));
			if (imgTemp.empty()) {
				cout << "cannot find " << string(argv[i]) << endl;
				return -1;
			}
			else {
				imgNames_.push_back(string(argv[i]));
			}
		}
	}
	return 0;
}

int CmdParser::printUsage()
{
	cout << "this is for a pedestrian detection" << endl;
	cout << endl;
	cout << "./pede-detect img1 [...img N] to use the default function" << endl;
	cout << "Flags:" << endl;
	cout << "--help" << endl;
	cout << "will print the Useage" << endl;
	cout << "--cameraCapture(yes|no)" << endl;
	cout << "will open your camera and detect dynamically" << endl;
	cout << "--init" << endl;
	cout << "add the initial number of people in classroom(0-99 supported)";
	return 0;
}
