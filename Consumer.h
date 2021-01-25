/**************************************************

Copyright:

Author:韩俊博

Date:2021/1/19

Description:消费者线程，负责从1号临界区栈中读取
			图片帧并存入2号临界区测试队列中。

**************************************************/

#ifndef __CONSUMER__
#define __CONSUMER__

#include "CriticalArea.h"

using namespace std;
using namespace cv;

class Consumer : public QThread {
public:

	/**************************************************

	Function:Consumer

	Description:构造函数，初始化成员变量

	Calls:null

	Input:null

	Output:null

	Others:null

	**************************************************/
	Consumer();

	/**************************************************

	Function:~Consumer

	Description:析构函数

	Calls:null

	Input:null

	Output:null

	Others:null

	**************************************************/
	~Consumer();

	/**************************************************

	Function:setData

	Description:从GUIMain中获取指向临界区的指针

	Calls:null

	Input:data，通过此获取临界区所有数据

	Output:null

	Others:null

	**************************************************/
	void setData(CriticalArea* data);

	/**************************************************

	Function:run

	Description:消费者线程所需要执行的功能——从1号
				临界区栈中读取图片帧，并将其存入2号
				临界区测试队列中

	Calls:CriticalArea类，getQMutex_1()、
		  getNumUsedBytes_1()、getFull_1()、
		  getVideoStream()、getEmpty_1()、
		  getQMutex_2()、getEmpty_2()、
		  getNumUsedBytes_2()、getTestStream()、
		  getFull_2()、getBufferSize_2()、
		  getClearThreshold_2()

	Input:null

	Output:null

	Others:null

	**************************************************/
	void run();
private:

	/* 指向临界区的指针 */
	CriticalArea* mCriticalArea;
};

#endif // ! __CONSUMER__