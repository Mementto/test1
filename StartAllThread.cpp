/**************************************************

Copyright:

Author:韩俊博

Date:2021/1/19

Description:StartAllThread的功能实现源文件

**************************************************/

#include "StartAllThread.h"

StartAllThread::StartAllThread(
	const int& handleNum,
	const int& bufferSize_1,
	const int& bufferSize_2,
	const int& lessNum,
	const int& videoCaptureReadTime,
	map<string, string> path) :
	mHandleNum(handleNum),
	mPath(path),
	mVideoCaptureReadTime(videoCaptureReadTime),
	mThreadNum(0) {

	mCParseIniFile = new CParseIniFile();
	mCriticalArea = new CriticalArea(bufferSize_1, bufferSize_2, 0, 0, lessNum);
	mSupplier = new Supplier[path.size()];
	mProducer = new Producer[path.size()];
	mConsumer = new Consumer[handleNum];
	mTestClass = new TestClass(mCriticalArea);
}

void StartAllThread::create() {

	
	map<string, string>::iterator iter;
	int i;

	/* 根据path中的键-值对数量来确定创建的供应者线程数（上面的
	windowNum并没有用到，只是用来确定数组的范围） */
	for (iter = mPath.begin(), i = 0; iter != mPath.end() && i < mPath.size(); iter++, i++) {
		mSupplier[i].setData(mCriticalArea);
		mSupplier[i].setPath(iter->second);
		mSupplier[i].setId(stoi(iter->first));
		mSupplier[i].start();
	}

	/* 根据windowNum确定消费者线程数 */
	for (size_t i = 0; i < mHandleNum; i++) {
		mConsumer[i].setData(mCriticalArea);
		mConsumer[i].start();
		mThreadNum ++;
	}

	mTestClass->start();
	mThreadNum ++;

	clock_t start, end;
	start = clock();
	do {
		end = clock();
		mCriticalArea->getQMutex_3().lock();
		if (mCriticalArea->getVideoCaptureItem()->size() > 0) {
			map<int, VideoCapture>::iterator iter1;
			for (iter1 = mCriticalArea->getVideoCaptureItem()->begin();
				iter1 != mCriticalArea->getVideoCaptureItem()->end(); iter1++) {
				mProducer[iter1->first].setData(mCriticalArea);
				mProducer[iter1->first].setId(iter1->first);
				mProducer[iter1->first].setVideoCapture(iter1->second);
				mProducer[iter1->first].start();
				mThreadNum ++;
				cout << iter1->first << "号相机线程启动成功" << endl;
				//qDebug() << iter1->first << "号相机线程启动成功" << endl;
			}

			for (iter1 = mCriticalArea->getVideoCaptureItem()->begin();
				iter1 != mCriticalArea->getVideoCaptureItem()->end();) {
				mCriticalArea->getVideoCaptureItem()->erase(iter1++);
			}
		}
		mCriticalArea->getQMutex_3().unlock();
	} while (end - start < mVideoCaptureReadTime);
	
	delete[] mSupplier;
	mSupplier = nullptr;
}

void StartAllThread::stopAll() {

	/* 发送停止信号 */
	mCriticalArea->setRunSignal(0);

	/* 检查所有线程是否停止 */
	while (mCriticalArea->getStopReturnSignal() < mThreadNum);
}

StartAllThread::~StartAllThread() {

	delete[] mSupplier;
	delete[] mProducer;
	delete[] mConsumer;
	delete mTestClass;
	delete mCriticalArea;
	delete mCParseIniFile;
	mSupplier = nullptr;
	mProducer = nullptr;
	mConsumer = nullptr;
	mTestClass = nullptr;
	mCriticalArea = nullptr;
	mCParseIniFile = nullptr;

	cout << "错误！已重启项目" << endl;
	//qDebug() << "错误！已重启项目" << endl;
}