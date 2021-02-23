/**************************************************

Copyright:

Author:韩俊博

Date:2021/1/19

Description:启动生产者线程和消费者线程，
			并接收来自2号临界区队列中的图片帧。

**************************************************/

#ifndef __GUIMAIN__
#define __GUIMAIN__
#include "Supplier.h"
#include "Producer.h"
#include "CParseIniFile.h"
#include "CriticalArea.h"
#include <time.h>

class VideoLoader {
public:

	/**************************************************

	Function:GUIMain

	Description:构造函数，初始化成员变量

	Calls:null

	Input:fileName，配置文件的文件名

		  section，配置文件的节名

		  cameraNum，相机数量的上限，初始化生产者
		  指针数组的大小（生产者线程的数量以及相机
		  数量由配置文件中的键-值数量对确定）

		  windowNum，初始化消费者指针数组的大小并
		  确定消费者线程数量

		  bufferSize_1，1号临界区缓冲区大小

		  bufferSize_2，2号临界区缓冲区大小

		  lessNum，为了防止缓冲区和图片存储空间同
		  时满而阻塞（图片存储空间满后要进行循环
		  删除图片），图片存储空间要略小与可用缓
		  冲区大小。LessNum为略小于的量

	Output:null

	Others:对普通成员变量初始化，对指针成员变量开
	辟堆空间

	**************************************************/
	VideoLoader(
		const int& bufferSize_1,
		const int& lessNum,
		const int& videoCaptureReadTime,
		map<string, string> path);

	/**************************************************

	Function:~GUIMain()

	Description:析构函数，delete所有指向堆的指针

	Calls:null

	Input:null

	Output:null

	Others:null

	**************************************************/
	virtual ~VideoLoader();

	/**************************************************

	Function:create

	Description:启动生产者线程和消费者线程

	Calls:Producer类，setData(CriticalArea* data)、
		  setPath(string path)、setId(int id)、
		  run()

		  Consumer类，setData(CriticalArea* data)、
		  run()

	Input:null

	Output:null

	Others:null

	**************************************************/
	void create();

	/**************************************************

	Function:stopAll

	Description:终止所有线程

	Calls:CriticalArea类，getStopReturnSignal()，
		  setRunSignal(const int& runSignal)

	Input:null

	Output:null

	Others:null

	**************************************************/
	void stopAll();

	void receiveImage();

private:

	Supplier* mSupplier;

	/* 生产者：从相机中读取并存入临界区栈图片的线程指针 */
	Producer* mProducer;

	/* 指向临界区中所有变量的指针 */
	CriticalArea* mCriticalArea;

	/* 获取ini配置文件信息类的指针 */
	CParseIniFile* mCParseIniFile;

	const int mVideoCaptureReadTime;

	map<string, string> mPath;

	int mThreadNum;
};

#endif // !__GUIMAIN__
