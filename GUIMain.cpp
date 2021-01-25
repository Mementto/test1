/**************************************************

Copyright:

Author:韩俊博

Date:2021/1/19

Description:GUIMain的功能实现源文件

**************************************************/

#include "GUIMain.h"

GUIMain::GUIMain(
	const string& fileName,
	const string& section,
	const int& cameraNum = 0,
	const int& windowNum = 0,
	const int& bufferSize_1 = 0,
	const int& bufferSize_2 = 0,
	const int& lessNum = 0)
	: mWindowNum(windowNum),
	mFileName(fileName),
	mSection(section),
	mCameraNum(cameraNum) {

	mCParseIniFile = new CParseIniFile();
	mCriticalArea = new CriticalArea(bufferSize_1, bufferSize_2, 0, 0, lessNum);
	mProducer = new Producer[cameraNum];
	mConsumer = new Consumer[windowNum];
}

void GUIMain::create() {

	/* 将ini文件中的指定键-值对输出到map中 */
	mCParseIniFile->ReadConfig(mFileName, mPath, mSection);
	map<int, string>::iterator iter;
	int i;

	/* 根据path中的键-值对数量来确定创建的生产者线程数（上面的
	windowNum并没有用到，只是用来确定数组的范围） */
	for (iter = mPath.begin(), i = 0; iter != mPath.end(); iter++, i++) {
		mProducer[i].setData(mCriticalArea);
		mProducer[i].setPath(iter->second);
		mProducer[i].setId(iter->first);
		mProducer[i].start();
	}

	/* 根据windowNum确定消费者线程数 */
	for (size_t i = 0; i < mWindowNum; i++) {
		mConsumer[i].setData(mCriticalArea);
		mConsumer[i].start();
	}
}

void GUIMain::run() {

	/* 1：开始或者继续循环；0：停止循环 */
	while (mCriticalArea->getRunSignal()) {
		Mat frame;

		/* 创建迭代器（不能和上面的重名） */
		map<int, Mat>::iterator iter1;

		/* 对2号临界区加锁 */
		mCriticalArea->getQMutex_2().lock();

		/* 检查2号临界区的缓冲区是否为空 */
		while (mCriticalArea->getNumUsedBytes_2() == 0) {

			/* 若为空则解锁等待（解锁是为了在该线程等待时可以让别的线程继续
			使用该临界区）一直到有可用数据输入则加锁并进行下一步 */
			mCriticalArea->getFull_2().wait(&mCriticalArea->getQMutex_2());
		}

		/* 判断2号临界区的测试队列是否为空 */
		if (!mCriticalArea->getTestStream()->empty()) {

			/* 从队列中读取数据 */
			map<int, Mat>* item = mCriticalArea->getTestStream()->front();

			/* 移除该数据 */
			mCriticalArea->getTestStream()->pop();

			/* 从map中读取数据 */
			iter1 = item->begin();

			/* 从迭代器中读取第二个数据（Mat） */
			frame = iter1->second;
			cout <<
				"栈" << mCriticalArea->getNumUsedBytes_1() << " " <<
				"队列" << mCriticalArea->getNumUsedBytes_2() << " " <<
				"1号" << mCriticalArea->getNumUsedBytes_1() << " " <<
				"2号" << mCriticalArea->getNumUsedBytes_2() << " " << endl;
			if (!frame.empty()) {

				/* 迭代器中第一个数据为摄像头编号 */
				imshow("?_" + to_string(iter1->first), frame);
				waitKey(1);
			}
			delete item;
			item = nullptr;

			/* 2号临界区缓冲区可用数据减少一个 */
			--mCriticalArea->getNumUsedBytes_2();

			/* 唤醒所有在“等待2号临界区空闲”的线程 */
			mCriticalArea->getEmpty_2().wakeAll();
		}

		/* 解锁2号临界区 */
		mCriticalArea->getQMutex_2().unlock();
	}
}

void GUIMain::stopAll() {

	/* 发送停止信号 */
	mCriticalArea->setRunSignal(0);

	/* 检查所有线程是否停止 */
	while (mCriticalArea->getStopReturnSignal() < (mCameraNum + mWindowNum));

	cout << mCriticalArea->getStopReturnSignal() << endl;
}

GUIMain::~GUIMain() {

	/* 停止当前线程 */
	quit();

	/* 等待上述操作完成 */
	wait();

	delete[] mProducer;
	delete[] mConsumer;
	delete mCriticalArea;
	delete mCParseIniFile;
	mProducer = nullptr;
	mConsumer = nullptr;
	mCriticalArea = nullptr;
	mCParseIniFile = nullptr;
}