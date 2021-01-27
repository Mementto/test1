#include "TestClass.h"

TestClass::TestClass(CriticalArea* criticalArea): 
	mCriticalArea(criticalArea) {}

TestClass::~TestClass() {

	destroyAllWindows();

	/* ֹͣ��ǰ�߳� */
	quit();

	/* �ȴ������������ */
	wait();
}

void TestClass::run() {
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
				imshow("�����߳�_" + to_string(iter1->first), frame);
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
	/* �߳�ֹͣ���к󷵻��źż�1 */
	mCriticalArea->getStopReturnSignal()++;
}
