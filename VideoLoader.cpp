/**************************************************

Copyright:

Author:������

Date:2021/1/19

Description:StartAllThread�Ĺ���ʵ��Դ�ļ�

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

	/* ����path�еļ�-ֵ��������ȷ�������Ĺ�Ӧ���߳����������
	windowNum��û���õ���ֻ������ȷ������ķ�Χ�� */
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
				cout << iter1->first << "������߳������ɹ�" << endl;
				//qDebug() << iter1->first << "������߳������ɹ�" << endl;
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
	/* �жϸ��߳��Ƿ�������ֹ */
	while (mCriticalArea->getRunSignal()) {

		map<int, stack<Mat>*>::iterator iter = mCriticalArea->getVideoStream()->begin();
		for (; iter != mCriticalArea->getVideoStream()->end(); iter++) {
			int imageKey = iter->first;

			/* ��1���ٽ������� */
			mCriticalArea->getQMutex_1(imageKey).lock();

			/* ���1���ٽ����Ļ������Ƿ�Ϊ�� */
			while (mCriticalArea->getNumUsedBytes_1(imageKey) == 0) {

				/* ��Ϊ��������ȴ���������Ϊ���ڸ��̵߳ȴ�ʱ�����ñ���̼߳���
				ʹ�ø��ٽ�����һֱ���п������������������������һ�� */
				mCriticalArea->getFull_1(imageKey).wait(&mCriticalArea->getQMutex_1(imageKey));
			}

			/* �ж�1���ٽ�����ջ�Ƿ�Ϊ�� */
			if (!iter->second->empty()) {

				/* ��ջ�ж�ȡ���� */
				Mat frame = iter->second->top();

				/* �Ƴ������� */
				iter->second->pop();

				cout << mCriticalArea->getVideoStream()->size() << endl;
				if (!frame.empty()) {
					imshow(to_string(imageKey), frame);
					waitKey(1);
				}

				/* 1���ٽ����������������ݼ���һ�� */
				--mCriticalArea->getNumUsedBytes_1(imageKey);

				/* ���������ڡ��ȴ�1���ٽ������С����߳� */
				mCriticalArea->getEmpty_1(imageKey).wakeAll();

				/* ����1���ٽ��� */
				mCriticalArea->getQMutex_1(imageKey).unlock();
			}
		}
	}
}

void VideoLoader::stopAll() {

	/* ����ֹͣ�ź� */
	mCriticalArea->setRunSignal(0);

	/* ��������߳��Ƿ�ֹͣ */
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

	cout << "������������Ŀ" << endl;
	//qDebug() << "������������Ŀ" << endl;
}