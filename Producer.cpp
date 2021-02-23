/**************************************************

Copyright:

Author:������

Date:2021/1/19

Description:Producer�Ĺ���ʵ��Դ�ļ�

**************************************************/

#include "Producer.h"

Producer::Producer() : mId(-1), mCriticalArea(nullptr) {}

Producer::~Producer() {

	mVideoCapture.release();

	/* ֹͣ��ǰ�߳� */
	quit();

	/* �ȴ������������ */
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

	/* �жϸ��߳��Ƿ�������ֹ */
	while (mCriticalArea->getRunSignal()) {
		Mat frame;

		/* ��captureѭ������Mat֡�� */
		mVideoCapture >> frame;
		if (frame.empty()) {
			break;
		}

		/* ��1���ٽ������� */
		mCriticalArea->getQMutex_1(mId).lock();

		map<int, stack<Mat>*>::iterator iter = mCriticalArea->getVideoStream()->find(mId);

		/* ���2���ٽ����Ļ������Ƿ����� */
		while (mCriticalArea->getNumUsedBytes_1(mId) == mCriticalArea->getBufferSize_1()) {

			/* ������������ȴ���������Ϊ���ڸ��̵߳ȴ�ʱ�����ñ���̼߳���
			ʹ�ø��ٽ�����һֱ���п���ռ��������������һ�� */
			mCriticalArea->getEmpty_1(mId).wait(&mCriticalArea->getQMutex_1(mId));
		}

		/* �ж�1���ٽ�����ջ�����Ƿ�ﵽ���ޣ����������Լ�����С�ڻ����������� */
		if (iter->second->size() > mCriticalArea->getClearThreshold_1()) {

			/* ���ջ */
			while (iter->second->size() > 0) {

				/* ���Mat */
				iter->second->pop();

				/* 1���ٽ����������������ݼ���һ�� */
				--mCriticalArea->getNumUsedBytes_1(mId);
			}
		}

		/* ��mapѹջ */
		iter->second->push(frame);

		/* 1���ٽ���������������������һ�� */
		++mCriticalArea->getNumUsedBytes_1(mId);

		/* ���������ڡ��ȴ�1���ٽ��������ݡ����߳� */
		mCriticalArea->getFull_1(mId).wakeAll();

		/* ����1���ٽ��� */
		mCriticalArea->getQMutex_1(mId).unlock();
	}

	/* �߳�ֹͣ���к󷵻��źż�1 */
	mCriticalArea->getStopReturnSignal()++;
}