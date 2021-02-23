/**************************************************

Copyright:

Author:韩俊博

Date:2021/1/19

Description:负责存储1号和2号临界区中的变量
			（后缀为_1的变量属于1号，_2的为2号）

**************************************************/

#ifndef __CRITICALAREA__
#define __CRITICALAREA__

#include <opencv2/opencv.hpp>
#include <QWaitCondition>
#include <QThread>
#include <iostream>
#include <QMutex>
#include <stack>

using namespace std;
using namespace cv;

class CriticalArea {
public:

	/**************************************************

	Function:CriticalArea

	Description:构造函数，初始化成员变量

	Calls:null

	Input:buffer_1，1号临界区缓冲区大小

		  buffer_2，2号临界区缓冲区大小

		  bytes_1，1号临界区缓冲区存在多少可用数据

		  bytes_2，2号临界区缓冲区存在多少可用数据

		  lessNum，为了防止缓冲区和图片存储空间同
		  时满而阻塞（图片存储空间满后要进行循环
		  删除图片），图片存储空间要略小与可用缓
		  冲区大小。LessNum为略小于的量

	Output:null

	Others:null

	**************************************************/
	CriticalArea(
		const int& buffer_1, 
		const int& bytes_1, 
		const int& lessNum, 
		const int& cameraNum);

	/**************************************************

	Function:~CriticalArea

	Description:析构函数

	Calls:null

	Input:null

	Output:null

	Others:null

	**************************************************/
	virtual ~CriticalArea();

	/**************************************************

	Function:getNumUsedBytes_1

	Description:返回1号临界区缓冲区可用数据量

	Calls:null

	Input:null

	Output:mNumUsedBytes_1，1号临界区缓冲区可用数据量

	Others:null

	**************************************************/
	int& getNumUsedBytes_1(int id);

	/**************************************************

	Function:getBufferSize_1

	Description:返回1号临界区缓冲区大小

	Calls:null

	Input:null

	Output:mBufferSize_1，1号临界区缓冲区大小

	Others:null

	**************************************************/
	const int& getBufferSize_1() const;

	/**************************************************

	Function:getClearThreshold_1

	Description:返回1号临界区栈的数据上限

	Calls:null

	Input:null

	Output:mBufferSize_1 - lessNum，1号临界区栈的数据上限

	Others:null

	**************************************************/
	const int getClearThreshold_1() const;

	/**************************************************

	Function:getVideoStream

	Description:返回指向1号临界区栈的指针

	Calls:null

	Input:null

	Output:mVideoStream，指向1号临界区栈的指针

	Others:null

	**************************************************/
	map<int, stack<Mat>*>* getVideoStream();

	/**************************************************

	Function:getEmpty_1

	Description:返回1号临界区缓冲区“等待缓冲区有空
				位”对象

	Calls:null

	Input:null

	Output:mBufferEmpty_1，1号临界区缓冲区“等待缓冲区有空位”对象

	Others:null

	**************************************************/
	QWaitCondition& getEmpty_1(int id);

	/**************************************************

	Function:getFull_1

	Description:返回1号临界区缓冲区“等待缓冲区有可
				用数据”对象

	Calls:null

	Input:null

	Output:mBufferFull_1，1号临界区缓冲区“等待缓冲区有可用数据”对象

	Others:null

	**************************************************/
	QWaitCondition& getFull_1(int id);

	/**************************************************

	Function:getQMutex_1

	Description:返回1号临界区缓冲区互斥类对象

	Calls:null

	Input:null

	Output:mQMutex_1，1号临界区缓冲区互斥类对象

	Others:null

	**************************************************/
	QMutex& getQMutex_1(int id);

	/**************************************************

	Function:getQMutex_3

	Description:返回3号临界区缓冲区互斥类对象

	Calls:null

	Input:null

	Output:mQMutex_3，3号临界区缓冲区互斥类对象

	Others:null

	**************************************************/
	QMutex& getQMutex_3();

	/**************************************************

	Function:getRunSignal

	Description:返回线程运行信号

	Calls:null

	Input:null

	Output:mRunSignal，线程运行信号

	Others:null

	**************************************************/
	const int& getRunSignal() const;

	/**************************************************

	Function:setRunSignal

	Description:传入线程运行信号

	Calls:null

	Input:runSignal，线程运行信号

	Output:null

	Others:null

	**************************************************/
	void setRunSignal(const int& runSignal);

	/**************************************************

	Function:getStopReturnSignal

	Description:返回线程终止返回信号

	Calls:null

	Input:null

	Output:mStopReturnSignal，线程终止返回信号

	Others:null

	**************************************************/
	int& getStopReturnSignal();


	map<int, VideoCapture>* getVideoCaptureItem() const;

private:

	/* 指向1号临界区栈的指针 */
	map<int, stack<Mat>*>* mVideoStream;

	/* 1号临界区缓冲区“等待缓冲区有空位”对象 */
	QWaitCondition mBufferEmpty_1[100];

	/* 1号临界区缓冲区“等待缓冲区有可用数据”对象 */
	QWaitCondition mBufferFull_1[100];

	/* 3号临界区缓冲区互斥类对象 */
	QMutex mQMutex_3;

	/* 1号临界区缓冲区互斥类对象 */
	QMutex mQMutex_1[100];

	/* 1号临界区缓冲区大小 */
	int mBufferSize_1;

	/* 1号临界区缓冲区可用数据量 */
	int mNumUsedBytes_1[100];

	/* 为了防止缓冲区和图片存储空间同
	时满而阻塞（图片存储空间满后要进行循环
	删除图片），图片存储空间要略小与可用缓
	冲区大小。LessNum为略小于的量 */
	int mLessNum;

	/* 线程运行信号，0：停止；1：运行 */
	int mRunSignal;

	/* 线程停止后的反馈信号，初始值为0，每个线程停止加1 */
	int mStopReturnSignal;

	map<int, VideoCapture>* mItems;
};

#endif // !__CRITICALAREA__