#include "Detect.h"

Detect::Detect() {

	startAllThread();

}

Detect::~Detect() {
	
}

void Detect::startAllThread() {

	FileAndSectionName name;
	BasicParamKey1 key1;
	string fileName = name.fileName;
	string section1 = name.section1;
	string section2 = name.section2;
	
	CParseIniFile* file = new CParseIniFile();
	map<string, string> basicParam;
	map<string, string> cameraInfo;
	file->ReadConfig(fileName, basicParam, section1);
	file->ReadConfig(fileName, cameraInfo, section2);
	int handleNum = stoi(basicParam[key1.handleNum]);
	int bufferSize_1 = stoi(basicParam[key1.bufferSize_1]);
	int bufferSize_2 = stoi(basicParam[key1.bufferSize_2]);
	int lessNum = stoi(basicParam[key1.lessNum]);
	int videoCaptureReadTime = stoi(basicParam[key1.videoCaptureReadTime]);
	delete file;
	file = nullptr;
	StartAllThread* main = new StartAllThread
	(handleNum, bufferSize_1, bufferSize_2, lessNum, videoCaptureReadTime, cameraInfo);
	main->create();
}