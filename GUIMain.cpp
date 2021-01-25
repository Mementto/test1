/**************************************************

Copyright:

Author:������

Date:2021/1/19

Description:GUIMain�Ĺ���ʵ��Դ�ļ�

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

	/* ��ini�ļ��е�ָ����-ֵ�������map�� */
	mCParseIniFile->ReadConfig(mFileName, mPath, mSection);
	map<int, string>::iterator iter;
	int i;

	/* ����path�еļ�-ֵ��������ȷ���������������߳����������
	windowNum��û���õ���ֻ������ȷ������ķ�Χ�� */
	for (iter = mPath.begin(), i = 0; iter != mPath.end(); iter++, i++) {
		mProducer[i].setData(mCriticalArea);
		mProducer[i].setPath(iter->second);
		mProducer[i].setId(iter->first);
		mProducer[i].start();
	}

	/* ����windowNumȷ���������߳��� */
	for (size_t i = 0; i < mWindowNum; i++) {
		mConsumer[i].setData(mCriticalArea);
		mConsumer[i].start();
	}
}

void GUIMain::run() {

	/* 1����ʼ���߼���ѭ����0��ֹͣѭ�� */
	while (mCriticalArea->getRunSignal()) {
		Mat frame;

		/* ���������������ܺ������������ */
		map<int, Mat>::iterator iter1;

		/* ��2���ٽ������� */
		mCriticalArea->getQMutex_2().lock();

		/* ���2���ٽ����Ļ������Ƿ�Ϊ�� */
		while (mCriticalArea->getNumUsedBytes_2() == 0) {

			/* ��Ϊ��������ȴ���������Ϊ���ڸ��̵߳ȴ�ʱ�����ñ���̼߳���
			ʹ�ø��ٽ�����һֱ���п������������������������һ�� */
			mCriticalArea->getFull_2().wait(&mCriticalArea->getQMutex_2());
		}

		/* �ж�2���ٽ����Ĳ��Զ����Ƿ�Ϊ�� */
		if (!mCriticalArea->getTestStream()->empty()) {

			/* �Ӷ����ж�ȡ���� */
			map<int, Mat>* item = mCriticalArea->getTestStream()->front();

			/* �Ƴ������� */
			mCriticalArea->getTestStream()->pop();

			/* ��map�ж�ȡ���� */
			iter1 = item->begin();

			/* �ӵ������ж�ȡ�ڶ������ݣ�Mat�� */
			frame = iter1->second;
			cout <<
				"ջ" << mCriticalArea->getNumUsedBytes_1() << " " <<
				"����" << mCriticalArea->getNumUsedBytes_2() << " " <<
				"1��" << mCriticalArea->getNumUsedBytes_1() << " " <<
				"2��" << mCriticalArea->getNumUsedBytes_2() << " " << endl;
			if (!frame.empty()) {

				/* �������е�һ������Ϊ����ͷ��� */
				imshow("?_" + to_string(iter1->first), frame);
				waitKey(1);
			}
			delete item;
			item = nullptr;

			/* 2���ٽ����������������ݼ���һ�� */
			--mCriticalArea->getNumUsedBytes_2();

			/* ���������ڡ��ȴ�2���ٽ������С����߳� */
			mCriticalArea->getEmpty_2().wakeAll();
		}

		/* ����2���ٽ��� */
		mCriticalArea->getQMutex_2().unlock();
	}
}

void GUIMain::stopAll() {

	/* ����ֹͣ�ź� */
	mCriticalArea->setRunSignal(0);

	/* ��������߳��Ƿ�ֹͣ */
	while (mCriticalArea->getStopReturnSignal() < (mCameraNum + mWindowNum));

	cout << mCriticalArea->getStopReturnSignal() << endl;
}

GUIMain::~GUIMain() {

	/* ֹͣ��ǰ�߳� */
	quit();

	/* �ȴ������������ */
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