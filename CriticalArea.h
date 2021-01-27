/**************************************************

Copyright:

Author:������

Date:2021/1/19

Description:����洢1�ź�2���ٽ����еı���
			����׺Ϊ_1�ı�������1�ţ�_2��Ϊ2�ţ�

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

	Description:���캯������ʼ����Ա����

	Calls:null

	Input:buffer_1��1���ٽ�����������С

		  buffer_2��2���ٽ�����������С

		  bytes_1��1���ٽ������������ڶ��ٿ�������

		  bytes_2��2���ٽ������������ڶ��ٿ�������

		  lessNum��Ϊ�˷�ֹ��������ͼƬ�洢�ռ�ͬ
		  ʱ����������ͼƬ�洢�ռ�����Ҫ����ѭ��
		  ɾ��ͼƬ����ͼƬ�洢�ռ�Ҫ��С����û�
		  ������С��LessNumΪ��С�ڵ���

	Output:null

	Others:null

	**************************************************/
	CriticalArea(const int& buffer_1, const int& buffer_2, const int& bytes_1, const int& bytes_2, const int& lessNum);

	/**************************************************

	Function:~CriticalArea

	Description:��������

	Calls:null

	Input:null

	Output:null

	Others:null

	**************************************************/
	virtual ~CriticalArea();

	/**************************************************

	Function:getNumUsedBytes_1

	Description:����1���ٽ�������������������

	Calls:null

	Input:null

	Output:mNumUsedBytes_1��1���ٽ�������������������

	Others:null

	**************************************************/
	int& getNumUsedBytes_1();

	/**************************************************

	Function:getNumUsedBytes_2

	Description:����2���ٽ�������������������

	Calls:null

	Input:null

	Output:mNumUsedBytes_2��2���ٽ�������������������

	Others:null

	**************************************************/
	int& getNumUsedBytes_2();

	/**************************************************

	Function:getBufferSize_1

	Description:����1���ٽ�����������С

	Calls:null

	Input:null

	Output:mBufferSize_1��1���ٽ�����������С

	Others:null

	**************************************************/
	const int& getBufferSize_1() const;

	/**************************************************

	Function:getBufferSize_2

	Description:����2���ٽ�����������С

	Calls:null

	Input:null

	Output:mBufferSize_2��2���ٽ�����������С

	Others:null

	**************************************************/
	const int& getBufferSize_2() const;

	/**************************************************

	Function:getClearThreshold_1

	Description:����1���ٽ���ջ����������

	Calls:null

	Input:null

	Output:mBufferSize_1 - lessNum��1���ٽ���ջ����������

	Others:null

	**************************************************/
	const int getClearThreshold_1() const;

	/**************************************************

	Function:getClearThreshold_2

	Description:����2���ٽ���ջ����������

	Calls:null

	Input:null

	Output:mBufferSize_2 - lessNum��2���ٽ���ջ����������

	Others:null

	**************************************************/
	const int getClearThreshold_2() const;

	/**************************************************

	Function:getVideoStream

	Description:����ָ��1���ٽ���ջ��ָ��

	Calls:null

	Input:null

	Output:mVideoStream��ָ��1���ٽ���ջ��ָ��

	Others:null

	**************************************************/
	stack<map<int, Mat>*>* getVideoStream();

	/**************************************************

	Function:getTestStream

	Description:����ָ��2���ٽ������Զ��е�ָ��

	Calls:null

	Input:null

	Output:mTestStream��ָ��2���ٽ������Զ��е�ָ��

	Others:null

	**************************************************/
	queue<map<int, Mat>*>* getTestStream();

	/**************************************************

	Function:getEmpty_1

	Description:����1���ٽ������������ȴ��������п�
				λ������

	Calls:null

	Input:null

	Output:mBufferEmpty_1��1���ٽ������������ȴ��������п�λ������

	Others:null

	**************************************************/
	QWaitCondition& getEmpty_1();

	/**************************************************

	Function:getFull_1

	Description:����1���ٽ������������ȴ��������п�
				�����ݡ�����

	Calls:null

	Input:null

	Output:mBufferFull_1��1���ٽ������������ȴ��������п������ݡ�����

	Others:null

	**************************************************/
	QWaitCondition& getFull_1();

	/**************************************************

	Function:getEmpty_2

	Description:����2���ٽ������������ȴ��������п�
				λ������

	Calls:null

	Input:null

	Output:mBufferEmpty_2��2���ٽ������������ȴ��������п�λ������

	Others:null

	**************************************************/
	QWaitCondition& getEmpty_2();

	/**************************************************

	Function:getFull_2

	Description:����2���ٽ������������ȴ��������п�
				�����ݡ�����

	Calls:null

	Input:null

	Output:mBufferFull_2��2���ٽ������������ȴ��������п������ݡ�����

	Others:null

	**************************************************/
	QWaitCondition& getFull_2();

	/**************************************************

	Function:getQMutex_1

	Description:����1���ٽ������������������

	Calls:null

	Input:null

	Output:mQMutex_1��1���ٽ������������������

	Others:null

	**************************************************/
	QMutex& getQMutex_1();

	/**************************************************

	Function:getQMutex_2

	Description:����2���ٽ������������������

	Calls:null

	Input:null

	Output:mQMutex_2��2���ٽ������������������

	Others:null

	**************************************************/
	QMutex& getQMutex_2();

	/**************************************************

	Function:getQMutex_3

	Description:����3���ٽ������������������

	Calls:null

	Input:null

	Output:mQMutex_3��3���ٽ������������������

	Others:null

	**************************************************/
	QMutex& getQMutex_3();

	/**************************************************

	Function:getRunSignal

	Description:�����߳������ź�

	Calls:null

	Input:null

	Output:mRunSignal���߳������ź�

	Others:null

	**************************************************/
	const int& getRunSignal() const;

	/**************************************************

	Function:setRunSignal

	Description:�����߳������ź�

	Calls:null

	Input:runSignal���߳������ź�

	Output:null

	Others:null

	**************************************************/
	void setRunSignal(const int& runSignal);

	/**************************************************

	Function:getStopReturnSignal

	Description:�����߳���ֹ�����ź�

	Calls:null

	Input:null

	Output:mStopReturnSignal���߳���ֹ�����ź�

	Others:null

	**************************************************/
	int& getStopReturnSignal();


	map<int, VideoCapture>* getVideoCaptureItem() const;

private:

	/* ָ��1���ٽ���ջ��ָ�� */
	stack<map<int, Mat>*>* mVideoStream;

	/* ָ��2���ٽ������Զ��е�ָ�� */
	queue<map<int, Mat>*>* mTestStream;

	/* 1���ٽ������������ȴ��������п�λ������ */
	QWaitCondition mBufferEmpty_1;

	/* 1���ٽ������������ȴ��������п������ݡ����� */
	QWaitCondition mBufferFull_1;

	/* 2���ٽ������������ȴ��������п�λ������ */
	QWaitCondition mBufferEmpty_2;

	/* 2���ٽ������������ȴ��������п������ݡ����� */
	QWaitCondition mBufferFull_2;

	/* 3���ٽ������������������ */
	QMutex mQMutex_3;

	/* 2���ٽ������������������ */
	QMutex mQMutex_2;

	/* 1���ٽ������������������ */
	QMutex mQMutex_1;

	/* 1���ٽ�����������С */
	int mBufferSize_1;

	/* 2���ٽ�����������С */
	int mBufferSize_2;

	/* 1���ٽ������������������� */
	int mNumUsedBytes_1;

	/* 2���ٽ������������������� */
	int mNumUsedBytes_2;

	/* Ϊ�˷�ֹ��������ͼƬ�洢�ռ�ͬ
	ʱ����������ͼƬ�洢�ռ�����Ҫ����ѭ��
	ɾ��ͼƬ����ͼƬ�洢�ռ�Ҫ��С����û�
	������С��LessNumΪ��С�ڵ��� */
	int mLessNum;

	/* �߳������źţ�0��ֹͣ��1������ */
	int mRunSignal;

	/* �߳�ֹͣ��ķ����źţ���ʼֵΪ0��ÿ���߳�ֹͣ��1 */
	int mStopReturnSignal;

	map<int, VideoCapture>* mItems;
};

#endif // !__CRITICALAREA__