/**************************************************

Copyright:

Author:韩俊博

Date:2021/1/19

Description:Producer的功能实现源文件

**************************************************/

#include "Producer.h"

Producer::Producer() : mId(-1), mCriticalArea(nullptr) {}

Producer::~Producer() {

	mVideoCapture.release();

	/* 停止当前线程 */
	quit();

	/* 等待上述操作完成 */
	wait();
}

void Producer::setVideoCapture(const VideoCapture& videoCapture) {
	mVideoCapture = videoCapture;
}

void Producer::setId(int id) {
	mId = id;
}

void Producer::setData(CriticalArea* data) {
	mCriticalArea = data;
}

void Producer::run() {

	/* 判断该线程是否被请求终止 */
	while (mCriticalArea->getRunSignal()) {
		Mat frame;

		/* 将capture循环输入Mat帧中 */
		mVideoCapture >> frame;
		if (frame.empty()) {
			break;
		}

		/* 对1号临界区加锁 */
		mCriticalArea->getQMutex_1(mId).lock();

		map<int, stack<Mat>*>::iterator iter = mCriticalArea->getVideoStream()->find(mId);

		/* 检查2号临界区的缓冲区是否已满 */
		while (mCriticalArea->getNumUsedBytes_1(mId) == mCriticalArea->getBufferSize_1()) {

			/* 若已满则解锁等待（解锁是为了在该线程等待时可以让别的线程继续
			使用该临界区）一直到有空余空间则加锁并进行下一步 */
			mCriticalArea->getEmpty_1(mId).wait(&mCriticalArea->getQMutex_1(mId));
		}

		/* 判断1号临界区的栈容量是否达到上限（该上限由自己定，小于缓冲区容量） */
		if (iter->second->size() > mCriticalArea->getClearThreshold_1()) {

			/* 清空栈 */
			while (iter->second->size() > 0) {

				/* 清除Mat */
				iter->second->pop();

				/* 1号临界区缓冲区可用数据减少一个 */
				--mCriticalArea->getNumUsedBytes_1(mId);
			}
		}

		/* 将map压栈 */
		iter->second->push(frame);

		/* 1号临界区缓冲区可用数据增加一个 */
		++mCriticalArea->getNumUsedBytes_1(mId);

		/* 唤醒所有在“等待1号临界区有数据”的线程 */
		mCriticalArea->getFull_1(mId).wakeAll();

		/* 解锁1号临界区 */
		mCriticalArea->getQMutex_1(mId).unlock();
	}

	/* 线程停止运行后返回信号加1 */
	mCriticalArea->getStopReturnSignal()++;
}