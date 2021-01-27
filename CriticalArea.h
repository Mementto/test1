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
	CriticalArea(const int& buffer_1, const int& buffer_2, const int& bytes_1, const int& bytes_2, const int& lessNum);

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
	int& getNumUsedBytes_1();

	/**************************************************

	Function:getNumUsedBytes_2

	Description:返回2号临界区缓冲区可用数据量

	Calls:null

	Input:null

	Output:mNumUsedBytes_2，2号临界区缓冲区可用数据量

	Others:null

	**************************************************/
	int& getNumUsedBytes_2();

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

	Function:getBufferSize_2

	Description:返回2号临界区缓冲区大小

	Calls:null

	Input:null

	Output:mBufferSize_2，2号临界区缓冲区大小

	Others:null

	**************************************************/
	const int& getBufferSize_2() const;

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

	Function:getClearThreshold_2

	Description:返回2号临界区栈的数据上限

	Calls:null

	Input:null

	Output:mBufferSize_2 - lessNum，2号临界区栈的数据上限

	Others:null

	**************************************************/
	const int getClearThreshold_2() const;

	/**************************************************

	Function:getVideoStream

	Description:返回指向1号临界区栈的指针

	Calls:null

	Input:null

	Output:mVideoStream，指向1号临界区栈的指针

	Others:null

	**************************************************/
	stack<map<int, Mat>*>* getVideoStream();

	/**************************************************

	Function:getTestStream

	Description:返回指向2号临界区测试队列的指针

	Calls:null

	Input:null

	Output:mTestStream，指向2号临界区测试队列的指针

	Others:null

	**************************************************/
	queue<map<int, Mat>*>* getTestStream();

	/**************************************************

	Function:getEmpty_1

	Description:返回1号临界区缓冲区“等待缓冲区有空
				位”对象

	Calls:null

	Input:null

	Output:mBufferEmpty_1，1号临界区缓冲区“等待缓冲区有空位”对象

	Others:null

	**************************************************/
	QWaitCondition& getEmpty_1();

	/**************************************************

	Function:getFull_1

	Description:返回1号临界区缓冲区“等待缓冲区有可
				用数据”对象

	Calls:null

	Input:null

	Output:mBufferFull_1，1号临界区缓冲区“等待缓冲区有可用数据”对象

	Others:null

	**************************************************/
	QWaitCondition& getFull_1();

	/**************************************************

	Function:getEmpty_2

	Description:返回2号临界区缓冲区“等待缓冲区有空
				位”对象

	Calls:null

	Input:null

	Output:mBufferEmpty_2，2号临界区缓冲区“等待缓冲区有空位”对象

	Others:null

	**************************************************/
	QWaitCondition& getEmpty_2();

	/**************************************************

	Function:getFull_2

	Description:返回2号临界区缓冲区“等待缓冲区有可
				用数据”对象

	Calls:null

	Input:null

	Output:mBufferFull_2，2号临界区缓冲区“等待缓冲区有可用数据”对象

	Others:null

	**************************************************/
	QWaitCondition& getFull_2();

	/**************************************************

	Function:getQMutex_1

	Description:返回1号临界区缓冲区互斥类对象

	Calls:null

	Input:null

	Output:mQMutex_1，1号临界区缓冲区互斥类对象

	Others:null

	**************************************************/
	QMutex& getQMutex_1();

	/**************************************************

	Function:getQMutex_2

	Description:返回2号临界区缓冲区互斥类对象

	Calls:null

	Input:null

	Output:mQMutex_2，2号临界区缓冲区互斥类对象

	Others:null

	**************************************************/
	QMutex& getQMutex_2();

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
	stack<map<int, Mat>*>* mVideoStream;

	/* 指向2号临界区测试队列的指针 */
	queue<map<int, Mat>*>* mTestStream;

	/* 1号临界区缓冲区“等待缓冲区有空位”对象 */
	QWaitCondition mBufferEmpty_1;

	/* 1号临界区缓冲区“等待缓冲区有可用数据”对象 */
	QWaitCondition mBufferFull_1;

	/* 2号临界区缓冲区“等待缓冲区有空位”对象 */
	QWaitCondition mBufferEmpty_2;

	/* 2号临界区缓冲区“等待缓冲区有可用数据”对象 */
	QWaitCondition mBufferFull_2;

	/* 3号临界区缓冲区互斥类对象 */
	QMutex mQMutex_3;

	/* 2号临界区缓冲区互斥类对象 */
	QMutex mQMutex_2;

	/* 1号临界区缓冲区互斥类对象 */
	QMutex mQMutex_1;

	/* 1号临界区缓冲区大小 */
	int mBufferSize_1;

	/* 2号临界区缓冲区大小 */
	int mBufferSize_2;

	/* 1号临界区缓冲区可用数据量 */
	int mNumUsedBytes_1;

	/* 2号临界区缓冲区可用数据量 */
	int mNumUsedBytes_2;

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