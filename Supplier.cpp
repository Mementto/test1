#include "Supplier.h"

Supplier::Supplier(): 
	mPath(""), mId(-1), mCriticalArea(nullptr), flag(false) {}

Supplier::~Supplier() {
	if (!flag) {
		cout << mId << "������޷��ҵ�������·��" << endl;
		//qDebug() << mId << "������޷��ҵ�������·��" << endl;

		cout << mId << "������߳�����ʧ��" << endl;
		//qDebug() << mId << "������߳�����ʧ��" << endl;

		cout << mId << " " << mPath << endl;
	}
	terminate();
	wait();
}

void Supplier::setId(const int& id) {
	mId = id;
}

void Supplier::setPath(const string& path) {
	mPath = path;
}

void Supplier::setData(CriticalArea* const criticalArea) {
	mCriticalArea = criticalArea;
}

void Supplier::run() {
	VideoCapture capture;
	capture.open(mPath);
	if (!capture.isOpened()) {
		cout << mId << "�������ʧ��" << endl;
		//qDebug() << mId << "�������ʧ��" << endl;

		cout << mId << "������߳�����ʧ��" << endl;
		//qDebug() << mId << "������߳�����ʧ��" << endl;
	} else {
		cout << mId << "������򿪳ɹ�" << endl;
		//qDebug() << mId << "������򿪳ɹ�" << endl;

		mCriticalArea->getQMutex_3().lock();
		mCriticalArea->getVideoCaptureItem()->insert(pair<int, VideoCapture>(mId, capture));
		mCriticalArea->getQMutex_3().unlock();
	}
	flag = true;
}
