/**************************************************

Copyright:

Author:韩俊博

Date:2021/1/19

Description:Consumer的功能实现源文件

**************************************************/

#include "Consumer.h"

Consumer::Consumer() : mCriticalArea(nullptr) {}

Consumer::~Consumer() {

	/* 停止当前线程 */
	quit();

	/* 等待上述操作完成 */
	wait();
}

void Consumer::setData(CriticalArea* data) {
	mCriticalArea = data;
}

void Consumer::run() {

	/* 判断该线程是否被请求终止 */
	while (mCriticalArea->getRunSignal()) {

		/* 对1号临界区加锁 */
		mCriticalArea->getQMutex_1().lock();

		/* 检查1号临界区的缓冲区是否为空 */
		while (mCriticalArea->getNumUsedBytes_1() == 0) {

			/* 若为空则解锁等待（解锁是为了在该线程等待时可以让别的线程继续
			使用该临界区）一直到有可用数据输入则加锁并进行下一步 */
			mCriticalArea->getFull_1().wait(&mCriticalArea->getQMutex_1());
		}

		/* 判断1号临界区的栈是否为空 */
		if (!mCriticalArea->getVideoStream()->empty()) {

			/* 从栈中读取数据 */
			map<int, Mat>* item = mCriticalArea->getVideoStream()->top();

			/* 移除该数据 */
			mCriticalArea->getVideoStream()->pop();

			/* 1号临界区缓冲区可用数据减少一个 */
			--mCriticalArea->getNumUsedBytes_1();

			/* 唤醒所有在“等待1号临界区空闲”的线程 */
			mCriticalArea->getEmpty_1().wakeAll();

			/* 解锁1号临界区 */
			mCriticalArea->getQMutex_1().unlock();

			/* 对2号临界区加锁 */
			mCriticalArea->getQMutex_2().lock();

			/* 检查1号临界区的缓冲区是否已满 */
			while (mCriticalArea->getNumUsedBytes_2() == mCriticalArea->getBufferSize_2()) {

				/* 若已满则解锁等待（解锁是为了在该线程等待时可以让别的线程继续
				使用该临界区）一直到有空余空间则加锁并进行下一步 */
				mCriticalArea->getEmpty_2().wait(&mCriticalArea->getQMutex_2());
			}

			/* 判断2号临界区的测试队列容量是否达到上限（该上限由自己定，小于缓冲区容量） */
			if (mCriticalArea->getTestStream()->size() > mCriticalArea->getClearThreshold_2()) {

				/* 清空队列 */
				while (mCriticalArea->getTestStream()->size() > 0) {

					/* 注意，队列中全是指向开辟堆空间的指针，
					pop了以后好像不管用，还得delete */
					delete mCriticalArea->getTestStream()->front();
					mCriticalArea->getTestStream()->front() = nullptr;
					mCriticalArea->getTestStream()->pop();

					/* 2号临界区缓冲区可用数据减少一个 */
					--mCriticalArea->getNumUsedBytes_2();
				}
			}

			/* 将数据存入队列 */
			mCriticalArea->getTestStream()->push(item);

			/* 2号临界区缓冲区可用数据增加一个 */
			++mCriticalArea->getNumUsedBytes_2();

			/* 唤醒所有在“等待2号临界区有数据”的线程 */
			mCriticalArea->getFull_2().wakeAll();

			/* 解锁2号临界区 */
			mCriticalArea->getQMutex_2().unlock();
		} else {

			/* 解锁1号临界区 */
			mCriticalArea->getQMutex_1().unlock();
		}

	}
	/* 线程停止运行后返回信号加1 */
	mCriticalArea->getStopReturnSignal()++;
}
