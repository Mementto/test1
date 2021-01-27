#include "Supplier.h"

Supplier::Supplier(): 
	mPath(""), mId(-1), mCriticalArea(nullptr), flag(false) {}

Supplier::~Supplier() {
	if (!flag) {
		cout << mId << "号相机无法找到，请检查路径" << endl;
		//qDebug() << mId << "号相机无法找到，请检查路径" << endl;

		cout << mId << "号相机线程启动失败" << endl;
		//qDebug() << mId << "号相机线程启动失败" << endl;

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
		cout << mId << "号相机打开失败" << endl;
		//qDebug() << mId << "号相机打开失败" << endl;

		cout << mId << "号相机线程启动失败" << endl;
		//qDebug() << mId << "号相机线程启动失败" << endl;
	} else {
		cout << mId << "号相机打开成功" << endl;
		//qDebug() << mId << "号相机打开成功" << endl;

		mCriticalArea->getQMutex_3().lock();
		mCriticalArea->getVideoCaptureItem()->insert(pair<int, VideoCapture>(mId, capture));
		mCriticalArea->getQMutex_3().unlock();
	}
	flag = true;
}
