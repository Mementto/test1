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
		mCriticalArea->getQMutex_1().lock();

		/* ���2���ٽ����Ļ������Ƿ����� */
		while (mCriticalArea->getNumUsedBytes_1() == mCriticalArea->getBufferSize_1()) {

			/* ������������ȴ���������Ϊ���ڸ��̵߳ȴ�ʱ�����ñ���̼߳���
			ʹ�ø��ٽ�����һֱ���п���ռ��������������һ�� */
			mCriticalArea->getEmpty_1().wait(&mCriticalArea->getQMutex_1());
		}

		/* �ж�1���ٽ�����ջ�����Ƿ�ﵽ���ޣ����������Լ�����С�ڻ����������� */
		if (mCriticalArea->getVideoStream()->size() > mCriticalArea->getClearThreshold_1()) {

			/* ���ջ */
			while (mCriticalArea->getVideoStream()->size() > 0) {

				/* ע�⣬ջ��ȫ��ָ�򿪱ٶѿռ��ָ�룬
				pop���Ժ���񲻹��ã�����delete */
				delete mCriticalArea->getVideoStream()->top();
				mCriticalArea->getVideoStream()->top() = nullptr;
				mCriticalArea->getVideoStream()->pop();

				/* 1���ٽ����������������ݼ���һ�� */
				--mCriticalArea->getNumUsedBytes_1();
			}
		}
		map<int, Mat>* item = new map<int, Mat>;

		/* ��Mat֡����map�У�������Գ��Ե�������
		һ���࣬ר��������װMat������int�����ţ� */
		item->insert(pair<int, Mat>(mId, frame));

		/* ��mapѹջ */
		mCriticalArea->getVideoStream()->push(item);

		/* 1���ٽ���������������������һ�� */
		++mCriticalArea->getNumUsedBytes_1();

		/* ���������ڡ��ȴ�1���ٽ��������ݡ����߳� */
		mCriticalArea->getFull_1().wakeAll();

		/* ����1���ٽ��� */
		mCriticalArea->getQMutex_1().unlock();
	}

	/* �߳�ֹͣ���к󷵻��źż�1 */
	mCriticalArea->getStopReturnSignal()++;
}