/**************************************************

Copyright:

Author:������

Date:2021/1/19

Description:Consumer�Ĺ���ʵ��Դ�ļ�

**************************************************/

#include "Consumer.h"

Consumer::Consumer() : mCriticalArea(nullptr) {}

Consumer::~Consumer() {

	/* ֹͣ��ǰ�߳� */
	quit();

	/* �ȴ������������ */
	wait();
}

void Consumer::setData(CriticalArea* data) {
	mCriticalArea = data;
}

void Consumer::run() {

	/* �жϸ��߳��Ƿ�������ֹ */
	while (mCriticalArea->getRunSignal()) {

		/* ��1���ٽ������� */
		mCriticalArea->getQMutex_1().lock();

		/* ���1���ٽ����Ļ������Ƿ�Ϊ�� */
		while (mCriticalArea->getNumUsedBytes_1() == 0) {

			/* ��Ϊ��������ȴ���������Ϊ���ڸ��̵߳ȴ�ʱ�����ñ���̼߳���
			ʹ�ø��ٽ�����һֱ���п������������������������һ�� */
			mCriticalArea->getFull_1().wait(&mCriticalArea->getQMutex_1());
		}

		/* �ж�1���ٽ�����ջ�Ƿ�Ϊ�� */
		if (!mCriticalArea->getVideoStream()->empty()) {

			/* ��ջ�ж�ȡ���� */
			map<int, Mat>* item = mCriticalArea->getVideoStream()->top();

			/* �Ƴ������� */
			mCriticalArea->getVideoStream()->pop();

			/* 1���ٽ����������������ݼ���һ�� */
			--mCriticalArea->getNumUsedBytes_1();

			/* ���������ڡ��ȴ�1���ٽ������С����߳� */
			mCriticalArea->getEmpty_1().wakeAll();

			/* ����1���ٽ��� */
			mCriticalArea->getQMutex_1().unlock();

			/* ��2���ٽ������� */
			mCriticalArea->getQMutex_2().lock();

			/* ���1���ٽ����Ļ������Ƿ����� */
			while (mCriticalArea->getNumUsedBytes_2() == mCriticalArea->getBufferSize_2()) {

				/* ������������ȴ���������Ϊ���ڸ��̵߳ȴ�ʱ�����ñ���̼߳���
				ʹ�ø��ٽ�����һֱ���п���ռ��������������һ�� */
				mCriticalArea->getEmpty_2().wait(&mCriticalArea->getQMutex_2());
			}

			/* �ж�2���ٽ����Ĳ��Զ��������Ƿ�ﵽ���ޣ����������Լ�����С�ڻ����������� */
			if (mCriticalArea->getTestStream()->size() > mCriticalArea->getClearThreshold_2()) {

				/* ��ն��� */
				while (mCriticalArea->getTestStream()->size() > 0) {

					/* ע�⣬������ȫ��ָ�򿪱ٶѿռ��ָ�룬
					pop���Ժ���񲻹��ã�����delete */
					delete mCriticalArea->getTestStream()->front();
					mCriticalArea->getTestStream()->front() = nullptr;
					mCriticalArea->getTestStream()->pop();

					/* 2���ٽ����������������ݼ���һ�� */
					--mCriticalArea->getNumUsedBytes_2();
				}
			}

			/* �����ݴ������ */
			mCriticalArea->getTestStream()->push(item);

			/* 2���ٽ���������������������һ�� */
			++mCriticalArea->getNumUsedBytes_2();

			/* ���������ڡ��ȴ�2���ٽ��������ݡ����߳� */
			mCriticalArea->getFull_2().wakeAll();

			/* ����2���ٽ��� */
			mCriticalArea->getQMutex_2().unlock();
		} else {

			/* ����1���ٽ��� */
			mCriticalArea->getQMutex_1().unlock();
		}

	}
	/* �߳�ֹͣ���к󷵻��źż�1 */
	mCriticalArea->getStopReturnSignal()++;
}
