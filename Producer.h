/**************************************************

Copyright:

Author:������

Date:2021/1/19

Description:�������̣߳�ʹ��opencv������Ƶ����
			��֡����1���ٽ�����ջ�С�

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

	Description:���캯������ʼ����Ա����

	Calls:null

	Input:null

	Output:null

	Others:��ʼ����mData��mPath��mId

	**************************************************/
	Producer();

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

	Function:setPath

	Description:��GUIMain�л�ȡ����ͷ·��

	Calls:null

	Input:path��ͨ����·���ҵ�ÿһ������ͷ��

	Output:null

	Others:null

	**************************************************/
	void setPath(string path);

	/**************************************************

	Function:setId

	Description:��GUIMain�л�ȡ����ͷ���

	Calls:null

	Input:id��ͨ���˱��������imshow���ڣ�imshow��
		  �ڵĴ������ֱ��벻ͬ�������Ǹ�id�����߳�
		  �Ŀ�������ջ�Ͷ��У�һֱ��������ʾ����Ҫ
		  �õ�map���������ӣ��Ƿ��и��õİ취��

	Output:null

	Others:null

	**************************************************/
	void setId(int id);

	/**************************************************

	Function:~Producer

	Description:��������

	Calls:null

	Input:null

	Output:null

	Others:null

	**************************************************/
	~Producer();

	/**************************************************

	Function:run

	Description:�������߳���Ҫִ�еĹ��ܡ���ʹ��
				opencv������Ƶ������֡����1����
				������ջ�С�

	Calls:��CriticalArea�У�getQMutex_1()��
		  getNumUsedBytes_1()��getBufferSize_1()��
		  getEmpty_1()��getVideoStream()��
		  getClearThreshold_1()��getFull_1()

	Input:null

	Output:null

	Others:null

	**************************************************/
	void run();
private:

	/* ָ���ٽ�����ָ�� */
	CriticalArea* mCriticalArea;

	/* ����ͷ·�� */
	string mPath;

	/* ����ͷ��� */
	int mId;
};

#endif // !__PRODUCER__