/**************************************************

Copyright:

Author:������

Date:2021/1/19

Description:�������̣߳������1���ٽ���ջ�ж�ȡ
			ͼƬ֡������2���ٽ������Զ����С�

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

	Description:���캯������ʼ����Ա����

	Calls:null

	Input:null

	Output:null

	Others:null

	**************************************************/
	Consumer();

	/**************************************************

	Function:~Consumer

	Description:��������

	Calls:null

	Input:null

	Output:null

	Others:null

	**************************************************/
	~Consumer();

	/**************************************************

	Function:setData

	Description:��GUIMain�л�ȡָ���ٽ�����ָ��

	Calls:null

	Input:data��ͨ���˻�ȡ�ٽ�����������

	Output:null

	Others:null

	**************************************************/
	void setData(CriticalArea* data);

	/**************************************************

	Function:run

	Description:�������߳�����Ҫִ�еĹ��ܡ�����1��
				�ٽ���ջ�ж�ȡͼƬ֡�����������2��
				�ٽ������Զ�����

	Calls:CriticalArea�࣬getQMutex_1()��
		  getNumUsedBytes_1()��getFull_1()��
		  getVideoStream()��getEmpty_1()��
		  getQMutex_2()��getEmpty_2()��
		  getNumUsedBytes_2()��getTestStream()��
		  getFull_2()��getBufferSize_2()��
		  getClearThreshold_2()

	Input:null

	Output:null

	Others:null

	**************************************************/
	void run();
private:

	/* ָ���ٽ�����ָ�� */
	CriticalArea* mCriticalArea;
};

#endif // ! __CONSUMER__