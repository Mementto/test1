/**************************************************

Copyright:

Author:韩俊博

Date:2021/1/19

Description:生产者线程，使用opencv读入视频流，
			按帧存入1号临界区的栈中。

**************************************************/

#ifndef __PRODUCER__
#define __PRODUCER__

#include "CriticalArea.h"

using namespace std;
using namespace cv;

class Producer : public QThread {
public:

	/**************************************************

	Function:Producer

	Description:构造函数，初始化成员变量

	Calls:null

	Input:null

	Output:null

	Others:初始化了mData、mPath、mId

	**************************************************/
	Producer();

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

	Function:setPath

	Description:从GUIMain中获取摄像头路径

	Calls:null

	Input:path，通过此路径找到每一个摄像头。

	Output:null

	Others:null

	**************************************************/
	void setPath(string path);

	/**************************************************

	Function:setId

	Description:从GUIMain中获取摄像头编号

	Calls:null

	Input:id，通过此编号来区分imshow窗口（imshow窗
		  口的窗口名字必须不同），但是该id跟随线程
		  的开启经过栈和队列，一直到窗口显示，需要
		  用到map，操作复杂，是否有更好的办法。

	Output:null

	Others:null

	**************************************************/
	void setId(int id);

	/**************************************************

	Function:~Producer

	Description:析构函数

	Calls:null

	Input:null

	Output:null

	Others:null

	**************************************************/
	~Producer();

	/**************************************************

	Function:run

	Description:生产者线程需要执行的功能——使用
				opencv读入视频流，按帧存入1号临
				界区的栈中。

	Calls:类CriticalArea中，getQMutex_1()、
		  getNumUsedBytes_1()、getBufferSize_1()、
		  getEmpty_1()、getVideoStream()、
		  getClearThreshold_1()、getFull_1()

	Input:null

	Output:null

	Others:null

	**************************************************/
	void run();
private:

	/* 指向临界区的指针 */
	CriticalArea* mCriticalArea;

	/* 摄像头路径 */
	string mPath;

	/* 摄像头编号 */
	int mId;
};

#endif // !__PRODUCER__