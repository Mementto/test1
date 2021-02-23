/**************************************************

Copyright:

Author:韩俊博

Date:2021/1/19

Description:StartAllThread的功能实现源文件

**************************************************/

#include "VideoLoader.h"

VideoLoader::VideoLoader(
	const int& bufferSize_1,
	const int& lessNum,
	const int& videoCaptureReadTime,
	map<string, string> path):
	mPath(path),
	mVideoCaptureReadTime(videoCaptureReadTime),
	mThreadNum(0) {

	mCParseIniFile = new CParseIniFile();
	mCriticalArea = new CriticalArea(bufferSize_1, 0, lessNum, path.size());
	mSupplier = new Supplier[path.size()];
	mProducer = new Producer[path.size()];
}

void VideoLoader::create() {

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

void VideoLoader::receiveImage() {
	/* 判断该线程是否被请求终止 */
	while (mCriticalArea->getRunSignal()) {

		map<int, stack<Mat>*>::iterator iter = mCriticalArea->getVideoStream()->begin();
		for (; iter != mCriticalArea->getVideoStream()->end(); iter++) {
			int imageKey = iter->first;

			/* 对1号临界区加锁 */
			mCriticalArea->getQMutex_1(imageKey).lock();

			/* 检查1号临界区的缓冲区是否为空 */
			while (mCriticalArea->getNumUsedBytes_1(imageKey) == 0) {

				/* 若为空则解锁等待（解锁是为了在该线程等待时可以让别的线程继续
				使用该临界区）一直到有可用数据输入则加锁并进行下一步 */
				mCriticalArea->getFull_1(imageKey).wait(&mCriticalArea->getQMutex_1(imageKey));
			}

			/* 判断1号临界区的栈是否为空 */
			if (!iter->second->empty()) {

				/* 从栈中读取数据 */
				Mat frame = iter->second->top();

				/* 移除该数据 */
				iter->second->pop();

				cout << mCriticalArea->getVideoStream()->size() << endl;
				if (!frame.empty()) {
					imshow(to_string(imageKey), frame);
					waitKey(1);
				}

				/* 1号临界区缓冲区可用数据减少一个 */
				--mCriticalArea->getNumUsedBytes_1(imageKey);

				/* 唤醒所有在“等待1号临界区空闲”的线程 */
				mCriticalArea->getEmpty_1(imageKey).wakeAll();

				/* 解锁1号临界区 */
				mCriticalArea->getQMutex_1(imageKey).unlock();
			}
		}
	}
}

void VideoLoader::stopAll() {

	/* 发送停止信号 */
	mCriticalArea->setRunSignal(0);

	/* 检查所有线程是否停止 */
	while (mCriticalArea->getStopReturnSignal() < mThreadNum);
}

VideoLoader::~VideoLoader() {

	delete[] mSupplier;
	delete[] mProducer;
	delete mCriticalArea;
	delete mCParseIniFile;
	mSupplier = nullptr;
	mProducer = nullptr;
	mCriticalArea = nullptr;
	mCParseIniFile = nullptr;

	cout << "错误！已重启项目" << endl;
	//qDebug() << "错误！已重启项目" << endl;
}