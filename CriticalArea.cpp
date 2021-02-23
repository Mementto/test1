/**************************************************

Copyright:

Author:韩俊博

Date:2021/1/19

Description:CriticalArea的功能实现源文件

**************************************************/

#include "CriticalArea.h"

CriticalArea::CriticalArea(const int& buffer_1,
	const int& bytes_1, const int& lessNum, const int& cameraNum)
	: mBufferSize_1(buffer_1), mLessNum(lessNum), 
	mRunSignal(1), mStopReturnSignal(0),
	mVideoStream(new map<int, stack<Mat>*>),
	mItems(new map<int, VideoCapture>) {
	
	for (size_t i = 0; i < cameraNum; i++) {
		mNumUsedBytes_1[i] = bytes_1;
	}

	for (size_t i = 0; i < cameraNum; i++) {
		stack<Mat>* container = new stack<Mat>;
		mVideoStream->insert(pair<int, stack<Mat>*>(i, container));
	}
}

CriticalArea::~CriticalArea() {
	

	delete mVideoStream;
	delete mItems;
	mVideoStream = nullptr;
	mItems = nullptr;
}

int& CriticalArea::getNumUsedBytes_1(int id) {
	return mNumUsedBytes_1[id];
}
const int& CriticalArea::getBufferSize_1() const {
	return mBufferSize_1;
}
const int CriticalArea::getClearThreshold_1() const {
	int temp = mBufferSize_1;
	return temp - mLessNum;
}
map<int, stack<Mat>*>* CriticalArea::getVideoStream() {
	return mVideoStream;
}
QWaitCondition& CriticalArea::getEmpty_1(int id) {
	return mBufferEmpty_1[id];
}
QWaitCondition& CriticalArea::getFull_1(int id) {
	return mBufferFull_1[id];
}
QMutex& CriticalArea::getQMutex_1(int id) {
	return mQMutex_1[id];
}
QMutex& CriticalArea::getQMutex_3() {
	return mQMutex_3;
}
const int& CriticalArea::getRunSignal() const {
	return mRunSignal;
}
void CriticalArea::setRunSignal(const int& runSignal) {
	mRunSignal = runSignal;
}
int& CriticalArea::getStopReturnSignal() {
	return mStopReturnSignal;
}
map<int, VideoCapture>* CriticalArea::getVideoCaptureItem() const {
	return mItems;
}